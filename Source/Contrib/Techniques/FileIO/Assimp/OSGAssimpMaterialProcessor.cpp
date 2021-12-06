/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                Copyright (C) 2011 by the OpenSG Forum                     *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#include <fstream>
#include <boost/filesystem.hpp>

#include "OSGBaseTypes.h"

#include "OSGAssimpMaterialProcessor.h"
#include "OSGAssimpLog.h"

#include "OSGMaterialDesc.h"
#include "OSGTextureDesc.h"

#include "OSGSceneFileHandler.h"
#include "OSGMaterialManager.h"

#include "OSGDescMaterial.h"

#ifdef OSG_WITH_ASSIMP
#pragma warning( push )
#pragma warning(disable : 4800)

#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/ProgressHandler.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/material.h>
#include <assimp/pbrmaterial.h>
#include <assimp/anim.h>
#include <assimp/metadata.h>
#include <assimp/vector3.h>
#include <assimp/color4.h>
#include <assimp/postprocess.h>

#pragma warning( pop )
#endif // OSG_WITH_ASSIMP

OSG_BEGIN_NAMESPACE

AssimpMaterialProcessor::AssimpMaterialProcessor(
    const AssimpOptions& options, 
    const std::string&   importer,
    const std::string&   directory)
: _directory(directory)
, _filename()
, _materialMap()
, _imageMap()
, _sfImageMap(NULL)
, _meshInfoMap()
, _options(options)
, _importer(importer)
, _hasORMTexture(false)
{
    HashKeyToFieldContainerMapUnrecPtr imageMap = HashKeyToFieldContainerMap::createLocal();
    _sfImageMap.setValue(imageMap);
}

AssimpMaterialProcessor::~AssimpMaterialProcessor(void)
{
}

#ifdef OSG_WITH_ASSIMP
bool AssimpMaterialProcessor::process(const aiScene* scene)
{
    OSG_ASSERT(scene && (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) == 0 && scene->mRootNode);

    //
    // End result: a map (_materialMap) of Assimp material index to DescMaterial instances.
    //
    // First a MaterialDesc instance is build from the Assimp scene. This is provided to
    // to the MaterialManager, which either builds a new DescMaterial instance or returns
    // an existing one for the description. If the MaterialManager is not available, then
    // the DescMaterial is always build from scratch.
    //
    //

    _materialMap.clear();
    _imageMap.clear();
    _meshInfoMap.clear();

    MaterialManager* matManager = SceneFileHandler::the()->getMaterialManager();
    
    if (scene->HasMeshes())
    {
        for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
        {
            aiMesh* mesh = scene->mMeshes[i];

            UInt32 materialIdx = mesh->mMaterialIndex;

            UVDimensionStore uvDimensions;

            for (UInt32 j = 0; j < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++j)
            {
                if (mesh->HasTextureCoords(j))
                {
                    switch (mesh->mNumUVComponents[j])
                    {
                        case 1:
                        case 2:
                        case 3:
                            {
                                uvDimensions.push_back(mesh->mNumUVComponents[j]);
                            }
                            break;
                    }
                }
            }

#ifdef _DEBUG
            OSG_ASSERT(uvDimensions.size() == mesh->GetNumUVChannels());
#else
            if (uvDimensions.size() != mesh->GetNumUVChannels())
            {
                return false;   // assertion failure
            }
#endif

            MeshInfo meshInfo;

            meshInfo.hasNormals       = mesh->HasNormals();
            meshInfo.hasPositions     = mesh->HasPositions();
            meshInfo.hasTangents      = mesh->HasTangentsAndBitangents();
            meshInfo.numUVChannels    = mesh->GetNumUVChannels();
            meshInfo.numColorChannels = mesh->GetNumColorChannels();
            meshInfo.uvDimensions     = uvDimensions;

            MeshInfoMap::const_iterator iter = _meshInfoMap.find(materialIdx);
            if (iter == _meshInfoMap.end())
            {
                _meshInfoMap.insert(MeshInfoMap::value_type(materialIdx, meshInfo));
            }
            else
            {
                const MeshInfo& rInfo = iter->second;

                // Adopt for model inconsistencies
                if (meshInfo.numUVChannels > rInfo.numUVChannels)    // the new occurence uses more texture channels
                {
                    // Theoretically, this case should never happen. However, we have
                    // prominent  example for that happening. So our strategy is to 
                    // use the most feature rich material in this case.
                    _meshInfoMap[materialIdx] = meshInfo;
                }
            }
        }
    }

    if (scene->HasTextures())
    {
        for (unsigned int i = 0; i < scene->mNumTextures; ++i)
        {
            aiTexture* texture = scene->mTextures[i];

            ImageUnrecPtr image = process(texture);
            if (image != NULL)
            {
                _imageMap.insert(ImageMap ::value_type(texture, image));
            }
        }
    }

    if (scene->HasMaterials())
    {
        for (unsigned int i = 0; i < scene->mNumMaterials; ++i)
        {
            MaterialDescUnrecPtr matDesc = MaterialDesc::createLocal();

            aiMaterial* material = scene->mMaterials[i];

            if (process(scene, material, matDesc))
            {
                MeshInfoMap::const_iterator iter = _meshInfoMap.find(i);
                if (iter != _meshInfoMap.end())
                {
                    const MeshInfo& meshInfo = iter->second;

                    OSG_ASSERT(meshInfo.uvDimensions.size() == meshInfo.numUVChannels);

                    matDesc->setHasNormalsMode              (meshInfo.hasNormals);
                    matDesc->setHasTangentsAndBitangentsMode(meshInfo.hasTangents);
                    matDesc->setNumUVChannels               (meshInfo.numUVChannels);
                    
                    matDesc->setNumColorChannels            (meshInfo.numColorChannels);
                    
                    MFUInt8& UVDimensions = *(matDesc->editMFUVDimension());
                    UVDimensions.resize(meshInfo.numUVChannels);
                    
                    for (UInt32 j = 0; j < meshInfo.numUVChannels; ++j)
                    {
                        UVDimensions[j] = meshInfo.uvDimensions[j];
                    }
                }

                if (matManager)
                {
                    MaterialManager::ManagedMaterialT result = matManager->addMaterial(matDesc);
                    if (result.first != 0)
                    {
                        _materialMap.insert(MaterialMap::value_type(i, result.second));
                    }
                }
                else
                {
                    DescMaterialUnrecPtr descMat = DescMaterial::createLocal();

                    descMat->setMaterialDesc(matDesc);

                    _materialMap.insert(MaterialMap::value_type(i, descMat));
                }

                if (_options.getLogMaterialDescOnRead())
                {
                    matDesc->dump();
                }
            }
        }
    }

    return true;
}

bool AssimpMaterialProcessor::process(const aiScene* scene, const aiMaterial* mat, MaterialDesc* matDesc)
{
    if(!mat) return false;

    aiColor4D color;
    aiString path, name, string_value;

    int   int_value;
    float float_value;
    bool  bool_value;

    if (aiGetMaterialString(mat, AI_MATKEY_NAME, &name) == AI_SUCCESS)
    {
        matDesc->setName(name.C_Str());
    }

    //
    // Material colors are always expected to be always sRGB colors, with the excption of 
    // the gltf2 format that stores linearized color factors.
    //
    if (_importer == "glTF2 Importer")
    {
        matDesc->setSRGBColorMode(false);
    }
    else
    {
        matDesc->setSRGBColorMode(true);
    }
    

    if (aiGetMaterialColor(mat, AI_MATKEY_COLOR_AMBIENT, &color) == AI_SUCCESS)
    {
        //
        // The MaterialDesc class does not support the ambient material property.
        //
        // matDesc->setAmbient(OSG::Vec3f(color.r, color.g, color.b));
    }

    if (aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &color) == AI_SUCCESS)
    {
        //OSG::Color3f randCol;
        //randCol.setRandom();
        //matDesc->setAlbedo(randCol);

        matDesc->setAlbedo(OSG::Vec3f(color.r, color.g, color.b));
        matDesc->setOpacity(color.a);
    }

    if (aiGetMaterialColor(mat, AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_BASE_COLOR_FACTOR, &color) == AI_SUCCESS)
    {
        matDesc->setAlbedo(OSG::Vec3f(color.r, color.g, color.b));
        matDesc->setOpacity(color.a);
    }

    if (aiGetMaterialColor(mat, AI_MATKEY_COLOR_SPECULAR, &color) == AI_SUCCESS)
    {
        matDesc->setSpecular(OSG::Vec3f(color.r, color.g, color.b));
    }

    if (aiGetMaterialColor(mat, AI_MATKEY_COLOR_EMISSIVE, &color) == AI_SUCCESS)
    {
        matDesc->setEmissive(OSG::Vec3f(color.r, color.g, color.b));
    }

    if (aiGetMaterialColor(mat, AI_MATKEY_COLOR_TRANSPARENT, &color) == AI_SUCCESS && !color.IsBlack())
    {
        matDesc->setTransparent(OSG::Vec3f(color.r, color.g, color.b));
    }

    if (aiGetMaterialColor(mat, AI_MATKEY_COLOR_REFLECTIVE, &color) == AI_SUCCESS && !color.IsBlack())
    {
        matDesc->setReflective(OSG::Vec3f(color.r, color.g, color.b));
    }

    if (aiGetMaterialString(mat, AI_MATKEY_GLOBAL_BACKGROUND_IMAGE, &path) == AI_SUCCESS)
    {
        // not supported
    }

    UInt32 model = MaterialDesc::NO_SHADING_MODEL;
    bool   flat  = false;

    if (aiGetMaterialInteger(mat, AI_MATKEY_SHADING_MODEL, &int_value) == AI_SUCCESS)
    {
        switch (int_value)
        {
            case aiShadingMode_Flat:            model = MaterialDesc::GOURAUD_SHADING_MODEL; flat = true; break;
            case aiShadingMode_Gouraud:         model = MaterialDesc::GOURAUD_SHADING_MODEL;              break;
            case aiShadingMode_Phong:           model = MaterialDesc::PHONG_SHADING_MODEL;                break;
            case aiShadingMode_Blinn:           model = MaterialDesc::BLINN_PHONG_SHADING_MODEL;          break;
            case aiShadingMode_Toon:            model = MaterialDesc::TOON_SHADING_MODEL;                 break;
            case aiShadingMode_OrenNayar:       model = MaterialDesc::OREN_NAYAR_SHADING_MODEL;           break;
            case aiShadingMode_Minnaert:        model = MaterialDesc::COOK_TORRANCE_SHADING_MODEL;        break;
            case aiShadingMode_CookTorrance:    model = MaterialDesc::COOK_TORRANCE_SHADING_MODEL;        break;
            case aiShadingMode_NoShading:       model = MaterialDesc::NO_SHADING_MODEL;                   break;
            case aiShadingMode_Fresnel:         model = MaterialDesc::BLINN_PHONG_SHADING_MODEL;          break;
        }
    }

    if (model == MaterialDesc::NO_SHADING_MODEL)
    {
        if (_importer == "glTF2 Importer")
        {
            model = MaterialDesc::COOK_TORRANCE_SHADING_MODEL;
        }
        else
        {
            if (_options.getShadingModel() != MaterialDesc::NO_SHADING_MODEL)
            {
                model = _options.getShadingModel();
            }
            else
            {
                model = MaterialDesc::GOURAUD_SHADING_MODEL;
            }
        }
    }

    matDesc->setFlatShadingMode(flat);
    matDesc->setShadingModel   (model);

    if (aiGetMaterialInteger(mat, AI_MATKEY_ENABLE_WIREFRAME, &int_value) == AI_SUCCESS)
    {
        if (int_value)
        {
            matDesc->setFrontMode(GL_LINE);
            matDesc->setBackMode (GL_LINE);
        }
        else
        {
            matDesc->setFrontMode(GL_FILL);
            matDesc->setBackMode (GL_FILL);
        }
    }

    if (aiGetMaterialInteger(mat, AI_MATKEY_BLEND_FUNC, &int_value) == AI_SUCCESS)
    {
        UInt32 mode = MaterialDesc::DEFAULT_BLEND_MODE;
        switch (int_value)
        {
            case aiBlendMode_Default:  mode = MaterialDesc::DEFAULT_BLEND_MODE;  break;
            case aiBlendMode_Additive: mode = MaterialDesc::ADDITIVE_BLEND_MODE; break;
        }
        matDesc->setBlendMode(mode);
    }

    if (aiGetMaterialFloat(mat, AI_MATKEY_OPACITY, &float_value) == AI_SUCCESS)
    {
        matDesc->setOpacity(float_value);
    }

    if (aiGetMaterialFloat(mat, AI_MATKEY_BUMPSCALING, &float_value) == AI_SUCCESS)
    {
        matDesc->setBumpScaling(float_value);
    }

    if (aiGetMaterialFloat(mat, AI_MATKEY_SHININESS, &float_value) == AI_SUCCESS)
    {
        matDesc->setShininess(float_value);
    }

    if (aiGetMaterialFloat(mat, AI_MATKEY_SHININESS_STRENGTH, &float_value) == AI_SUCCESS)
    {
        matDesc->setSpecularStrength(float_value);
    }

    if (aiGetMaterialFloat(mat, AI_MATKEY_REFLECTIVITY, &float_value) == AI_SUCCESS)
    {
        matDesc->setReflectivity(float_value);
    }

    if (aiGetMaterialFloat(mat, AI_MATKEY_REFRACTI, &float_value) == AI_SUCCESS)
    {
        matDesc->setRefractiveIndex(float_value);
    }

    if (aiGetMaterialFloat(mat, AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_METALLIC_FACTOR, &float_value) == AI_SUCCESS)
    {
        matDesc->setMetalness(float_value);
    }

    if (aiGetMaterialFloat(mat, AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_ROUGHNESS_FACTOR, &float_value) == AI_SUCCESS)
    {
        matDesc->setRoughness(float_value);
    }

    if (aiGetMaterialString(mat, AI_MATKEY_GLTF_ALPHAMODE, &string_value) == AI_SUCCESS)
    {
        std::string mode = string_value.C_Str();
        if (mode == "OPAQUE")
            matDesc->setOpacityMode(MaterialDesc::OPAQUE_OPACITY_MODE);
        else if (mode == "MASK")
            matDesc->setOpacityMode(MaterialDesc::MASK_OPACITY_MODE);
        else if (mode == "BLEND")
            matDesc->setOpacityMode(MaterialDesc::BLEND_OPACITY_MODE);
        else
            matDesc->setOpacityMode(MaterialDesc::NO_OPACITY_MODE);
    }

    if (aiGetMaterialFloat(mat, AI_MATKEY_GLTF_ALPHACUTOFF, &float_value) == AI_SUCCESS)
    {
        matDesc->setOpacityCutOff(float_value);
    }

    if (mat->Get(AI_MATKEY_GLTF_PBRSPECULARGLOSSINESS, bool_value) == AI_SUCCESS)
    {
        matDesc->setPbrSpecularMode(bool_value);
    }

    if (aiGetMaterialFloat(mat, AI_MATKEY_GLTF_PBRSPECULARGLOSSINESS_GLOSSINESS_FACTOR, &float_value) == AI_SUCCESS)
    {
        matDesc->setRoughness(1.f - float_value);
    }

    if (mat->Get(AI_MATKEY_GLTF_UNLIT, bool_value) == AI_SUCCESS)
    {
        matDesc->setUnlitMode(bool_value);
    }

    //
    // Default culling of back faces.
    //
    matDesc->setCullFace(GL_BACK);

    if (mat->Get(AI_MATKEY_TWOSIDED, bool_value) == AI_SUCCESS)
    {
        if (bool_value || _options.getForceTwosided() || osgAbs(1.f - matDesc->getOpacity()) > Eps)
        {
            matDesc->setCullFace(GL_NONE);
        }
        else
        {
            matDesc->setCullFace(GL_BACK);
        }
    }
    else
    {
        if (_options.getForceTwosided())
        {
            matDesc->setCullFace(GL_NONE);
        }
        else if (osgAbs(1.f - matDesc->getOpacity()) > Eps)
        {
            //
            // Transparent objects should not cull faces, but unfortunately this
            // does not work currently goodl with our engine because of missing
            //
            //matDesc->setCullFace(GL_NONE);
        }
    }

    _hasORMTexture = checkORMTextureSupport(mat);

    std::vector<aiTextureType> types; 
    types.push_back(aiTextureType_NONE);
    types.push_back(aiTextureType_DIFFUSE);
    types.push_back(aiTextureType_SPECULAR);
    types.push_back(aiTextureType_AMBIENT);
    types.push_back(aiTextureType_EMISSIVE);
    types.push_back(aiTextureType_HEIGHT);
    types.push_back(aiTextureType_NORMALS);
    types.push_back(aiTextureType_SHININESS);
    types.push_back(aiTextureType_OPACITY);
    types.push_back(aiTextureType_DISPLACEMENT);

    if (!_hasORMTexture)
        types.push_back(aiTextureType_LIGHTMAP);

    types.push_back(aiTextureType_REFLECTION);
    types.push_back(aiTextureType_BASE_COLOR);
    types.push_back(aiTextureType_NORMAL_CAMERA);
    types.push_back(aiTextureType_EMISSION_COLOR);
    types.push_back(aiTextureType_METALNESS);
    types.push_back(aiTextureType_DIFFUSE_ROUGHNESS);

    if (!_hasORMTexture)
        types.push_back(aiTextureType_AMBIENT_OCCLUSION);

    types.push_back(aiTextureType_UNKNOWN);

    for (std::size_t i = 0; i < types.size(); ++i)
    {
        process(scene, mat, types[i], matDesc);
    }

    //
    // Postprocess:
    //      We check if we have any opacity texture that does match the same
    //      resources as the albedo texture. In that case we assume that the
    //      albedo texture is a RGBA texture (better if we would test that)
    //      and omit the opacity texture at all.
    //

    MFUnrecTextureDescPtr* pMFTexDescPtr = matDesc->editMFTextureDesc();
    if (pMFTexDescPtr != NULL)
    {
        MFUnrecTextureDescPtr::iterator iter, end;

        // First find albedo texture: if we find more than one we stop the postprocess.

        iter = pMFTexDescPtr->begin();
        end  = pMFTexDescPtr->end  ();

        MFUnrecTextureDescPtr::iterator iterOpacity;

        TextureDesc* texDescAlbedo  = nullptr;
        TextureDesc* texDescOpacity = nullptr;

        bool proceed = true;

        for (; iter != end; ++iter)
        {
            TextureDesc* texDesc = *iter;
            if (texDesc->getTextureType() == TextureDesc::ALBEDO_TEXTURE)
            {
                if (texDescAlbedo)
                    proceed = false;
                else
                    texDescAlbedo = texDesc;
            }

            if (texDesc->getTextureType() == TextureDesc::OPACITY_TEXTURE)
            {
                if (texDescOpacity)
                    proceed = false;
                else {
                    texDescOpacity = texDesc;
                    iterOpacity = iter;
                }
            }
        }

        if (proceed && texDescAlbedo && texDescOpacity)
        {
            if (texDescAlbedo->getTexImage() == texDescOpacity->getTexImage() && 
                texDescAlbedo->getFilename() == texDescOpacity->getFilename())
            {
                UInt32 flags = texDescAlbedo->getTextureFlags();
                flags &= ~TextureDesc::IGNORE_ALPHA_FLAG;
                flags |=  TextureDesc::USE_ALPHA_FLAG;
                texDescAlbedo->setTextureFlags(flags);

                matDesc->setOpacityMode(MaterialDesc::BLEND_OPACITY_MODE);
                matDesc->setCullFace(GL_NONE);

                pMFTexDescPtr->erase(iterOpacity);

            }
        }
    }

    return true;
}

void AssimpMaterialProcessor::process(const aiScene* scene, const aiMaterial* mat, aiTextureType type, MaterialDesc* matDesc)
{
    switch (type)
    {
        case aiTextureType_NONE:
            return;
    }

    UInt32      textureType   = TextureDesc::UNKNOWN_TEXTURE;
    bool        isSRGBTexture = false;
    bool        invert        = false;
    std::string swizzle       = "rgba";

    switch (type)
    {
        case aiTextureType_AMBIENT:
            {
                // not supported: Expected to be handled by global illumination
                //textureType   = TextureDesc::AMBIENT_TEXTURE;
                //isSRGBTexture = true;
            }
            break;
        case aiTextureType_DIFFUSE:
            {
                textureType   = TextureDesc::ALBEDO_TEXTURE;
                isSRGBTexture = true;
            }
            break;
        case aiTextureType_SPECULAR:
            {
                textureType   = TextureDesc::SPECULAR_TEXTURE;
                isSRGBTexture = true;
            }
            break;
        case aiTextureType_EMISSIVE:
            {
                textureType   = TextureDesc::EMISSIVE_TEXTURE;
                isSRGBTexture = true;
            }
            break;
        case aiTextureType_SHININESS:
            {
                textureType   = TextureDesc::SHININESS_TEXTURE;
                isSRGBTexture = false;
            }
            break;
        case aiTextureType_OPACITY:
            {
                textureType   = TextureDesc::OPACITY_TEXTURE;
                isSRGBTexture = false;
            }
            break;
        case aiTextureType_NORMALS:
            {
                textureType   = TextureDesc::NORMALS_TEXTURE;
                isSRGBTexture = false;
            }
            break;
        case aiTextureType_HEIGHT:
            {
                textureType   = TextureDesc::HEIGHT_TEXTURE;
                isSRGBTexture = false;
                invert        = _options.getInvertHeight();
            }
            break;
        case aiTextureType_DISPLACEMENT:
            {
                textureType   = TextureDesc::DISPLACEMENT_TEXTURE;
                isSRGBTexture = false;
                invert        = _options.getInvertDisplacement();
            }
            break;
        case aiTextureType_LIGHTMAP:
            {
                textureType   = TextureDesc::AMBIENT_OCCLUSION_TEXTURE;
                isSRGBTexture = false;
            }
            break;
        case aiTextureType_REFLECTION:
            {
                textureType   = TextureDesc::REFLECTION_TEXTURE;
                isSRGBTexture = false;
            }
            break;
        case aiTextureType_BASE_COLOR:
            {
                textureType   = TextureDesc::ALBEDO_TEXTURE;
                isSRGBTexture = true;
            }
            break;
        case aiTextureType_METALNESS:
            {
                textureType   = TextureDesc::METAL_TEXTURE;
                isSRGBTexture = false;
            }
            break;
        case aiTextureType_DIFFUSE_ROUGHNESS:
            {
                textureType   = TextureDesc::ROUGH_TEXTURE;
                isSRGBTexture = false;
            }
            break;
        case aiTextureType_AMBIENT_OCCLUSION:
            {
                textureType   = TextureDesc::AMBIENT_OCCLUSION_TEXTURE;
                isSRGBTexture = false;
            }
            break;
        case aiTextureType_UNKNOWN:
            {
                float float_value;
                if (aiGetMaterialFloat(mat, AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_METALLIC_FACTOR, &float_value) == AI_SUCCESS)
                {
                    if (_hasORMTexture)
                        textureType   = TextureDesc::OCCL_ROUGH_METAL_TEXTURE;
                    else
                        textureType   = TextureDesc::ROUGH_METAL_TEXTURE;

                    isSRGBTexture = false;
                }
            }
            break;
    }

    unsigned int cnt = mat->GetTextureCount(type);

    std::set<std::string> loaded_textures;

    for(unsigned int index = 0; index < cnt; index++)
    {
        aiString path;
        aiTextureMapping mapping;
        unsigned int uvindex = 0;
        ai_real blend = 0.f;
        aiTextureOp op = aiTextureOp_Multiply;
        aiTextureMapMode mapmode[3] = {aiTextureMapMode_Wrap, aiTextureMapMode_Wrap, aiTextureMapMode_Wrap};
        unsigned int flags = 0;
        aiUVTransform transform;
        aiVector3D axis;

        if (aiGetMaterialTexture(mat, type, index, &path, &mapping, &uvindex, &blend, &op, mapmode, &flags) == AI_SUCCESS)
        {
            if (path.length == 0)
                continue;

            TextureDescUnrecPtr texDesc = TextureDesc::createLocal();
            texDesc->setImageMap(_sfImageMap.getValue());

            _filename.clear();

            const aiTexture* texture = scene->GetEmbeddedTexture(path.C_Str());

            if (texture)
            {
                ImageMap::const_iterator iter = _imageMap.find(texture);

                if (iter != _imageMap.end())
                {
                    texDesc->setTexImage(iter->second);
                }
                else
                    continue;
            }
            else
            {
                _filename = path.C_Str();

                if (loaded_textures.find(_filename) != loaded_textures.end())
                    continue;

                loaded_textures.insert(_filename);
            }

            UInt32 mappingMode = TextureDesc::UV_MAPPING;
            switch(mapping)
            {
                case aiTextureMapping_UV:       mappingMode = TextureDesc::UV_MAPPING;       break;
                case aiTextureMapping_SPHERE:   mappingMode = TextureDesc::SPHERE_MAPPING;   break;
                case aiTextureMapping_CYLINDER: mappingMode = TextureDesc::CYLINDER_MAPPING; break;
                case aiTextureMapping_BOX:      mappingMode = TextureDesc::BOX_MAPPING;      break;
                case aiTextureMapping_PLANE:    mappingMode = TextureDesc::PLANE_MAPPING;    break;
                case aiTextureMapping_OTHER:    mappingMode = TextureDesc::OTHER_MAPPING;    break;
            }
            

            UInt32 texOp = TextureDesc::MULTIPLY_OPERATION;
            switch(op)
            {
                case aiTextureOp_Multiply:  texOp = TextureDesc::MULTIPLY_OPERATION;  break;
                case aiTextureOp_Add:       texOp = TextureDesc::ADD_OPERATION;       break;
                case aiTextureOp_Subtract:  texOp = TextureDesc::SUBTRACT_OPERATION;  break;
                case aiTextureOp_Divide:    texOp = TextureDesc::DIVIDE_OPERATION;    break;
                case aiTextureOp_SmoothAdd: texOp = TextureDesc::SMOOTHADD_OPERATION; break;
                case aiTextureOp_SignedAdd: texOp = TextureDesc::SIGNEDADD_OPERATION; break;
            }

            if (blend == 0.f && texOp == TextureDesc::MULTIPLY_OPERATION)
            {
                blend = 1.f;
                texOp = TextureDesc::REPLACE_OPERATION;
            }

            

            GLenum wrapS = GL_REPEAT, wrapT = GL_REPEAT, wrapR = GL_REPEAT;
            switch(mapmode[0])
            {
                case aiTextureMapMode_Wrap:     wrapS = GL_REPEAT;          break;
                case aiTextureMapMode_Clamp:    wrapS = GL_CLAMP_TO_EDGE;   break;
                case aiTextureMapMode_Decal:    wrapS = GL_CLAMP_TO_BORDER; break;
                case aiTextureMapMode_Mirror:   wrapS = GL_MIRRORED_REPEAT; break;
            }

            switch(mapmode[1])
            {
                case aiTextureMapMode_Wrap:     wrapT = GL_REPEAT; break;
                case aiTextureMapMode_Clamp:    wrapT = GL_CLAMP_TO_EDGE; break;
                case aiTextureMapMode_Decal:    wrapT = GL_CLAMP_TO_BORDER; break;
                case aiTextureMapMode_Mirror:   wrapT = GL_MIRRORED_REPEAT; break;
            }

            switch(mapmode[2])
            {
                case aiTextureMapMode_Wrap:     wrapR = GL_REPEAT; break;
                case aiTextureMapMode_Clamp:    wrapR = GL_CLAMP_TO_EDGE; break;
                case aiTextureMapMode_Decal:    wrapR = GL_CLAMP_TO_BORDER; break;
                case aiTextureMapMode_Mirror:   wrapR = GL_MIRRORED_REPEAT; break;
            }


            Vec3f mapAxis(0.f,0.f,0.f);
            if (mat->Get(AI_MATKEY_TEXMAP_AXIS(type, index), axis) == AI_SUCCESS)
            {
                mapAxis = Vec3f(axis.x, axis.y, axis.z);
            }

            UInt32 textureFlags = TextureDesc::IGNORE_ALPHA_FLAG;

            if (flags & aiTextureFlags_Invert)
            {
                textureFlags |= TextureDesc::INVERT_FLAG;
            }

            if (invert)
            {
                if (textureFlags & TextureDesc::INVERT_FLAG)
                {
                    textureFlags &= ~TextureDesc::INVERT_FLAG;
                }
                else
                {
                    textureFlags |= TextureDesc::INVERT_FLAG;
                }
            }

            if (flags & aiTextureFlags_UseAlpha)
            {
                textureFlags |=  TextureDesc::USE_ALPHA_FLAG;
                textureFlags &= ~TextureDesc::IGNORE_ALPHA_FLAG;
            }
            if (flags & aiTextureFlags_IgnoreAlpha)
            {
                textureFlags &= ~TextureDesc::USE_ALPHA_FLAG;
                textureFlags |=  TextureDesc::IGNORE_ALPHA_FLAG;
            }

            if (mat->Get(AI_MATKEY_UVTRANSFORM(type, index), transform) == AI_SUCCESS)
            {
                //
                // Assimp assumes a rotation around point P=(0.5,0.5).
                // The TextureDesc expects the rotation around point P'=(0,0)
                // The parameters scale,translate and rotate must be adapted accordingly
                //
                //
                // Assimp:       M  = S(sx,sy) * T(0.5,0.5) * R(r) * T(-0.5,-0.5) * T(tx,ty)
                // DescMaterial: M  = S(sx_,sy_) * R(r_) * T(tx_,ty_)
                //
                Real32 r  = transform.mRotation;
                Real32 sx = transform.mScaling.x;
                Real32 sy = transform.mScaling.y;
                Real32 tx = transform.mTranslation.x;
                Real32 ty = transform.mTranslation.y;

                if (   osgAbs(r)        > OSG::Eps
                    || osgAbs(1.f - sx) > OSG::Eps
                    || osgAbs(1.f - sy) > OSG::Eps
                    || osgAbs(tx)       > OSG::Eps
                    || osgAbs(ty)       > OSG::Eps)
                {
                    const Real32 PiFourth = 0.785398163398f;
                    const Real32 InvSqrt2 = 0.707106781188f;

                    Real32 r_  = r;
                    Real32 sx_ = sx;
                    Real32 sy_ = sy;
                    Real32 tx_ = tx + InvSqrt2 * osgSin(r + PiFourth) - 0.5f;
                    Real32 ty_ = ty + InvSqrt2 * osgCos(r + PiFourth) - 0.5f;

                    texDesc->setScale    (Vec2f(sx_, sy_));
                    texDesc->setTranslate(Vec2f(tx_, ty_));
                    texDesc->setRotate   (r_);

                    texDesc->setHasUVTransform(true);
                }
            }

            adaptTextureImageFile();

            texDesc->setTextureType  (textureType  );
            texDesc->setIsSRGBTexture(isSRGBTexture);
            texDesc->setSwizzle      (swizzle      );
            texDesc->setFilename     (_filename    );
            texDesc->setUVChannel    (uvindex      );
            texDesc->setBlendFactor  (blend        );
            texDesc->setMappingMode  (mappingMode  );
            texDesc->setOperation    (texOp        );
            texDesc->setWrapS        (wrapS        );
            texDesc->setWrapT        (wrapT        );
            texDesc->setWrapR        (wrapR        );
            texDesc->setMapAxis      (mapAxis      );
            texDesc->setTextureFlags (textureFlags );

            matDesc->addTexture      (texDesc      );

            texDesc->setImageMap     (NULL);
        }
    }
}

ImageTransitPtr AssimpMaterialProcessor::process(const aiTexture* texture)
{
    if(!texture || !texture->pcData)
        return ImageTransitPtr(NULL);

    std::string hint = texture->achFormatHint;

    if (texture->mHeight == 0)
    {
        // compressed image case

        if (!hint.empty())
        {
            std::string tmpFile = "OpenSGTempImageFile";
            tmpFile = tmpFile + "." + hint;

            std::ofstream file(tmpFile.c_str(), std::ios::binary);
            file.write(reinterpret_cast<const char*>(texture->pcData), texture->mWidth);
            file.close();

            ImageUnrecPtr image = Image::createLocal();
            image->read(tmpFile.c_str());

            ::remove(tmpFile.c_str());

            return ImageTransitPtr(image);
        }
    }
    else
    {
        // uncompressed image case

        if (hint.empty() || hint == "argb8888")
        {
            ImageUnrecPtr image = Image::createLocal();

            image->set(GL_BGRA,                     // pixel format
                       texture->mWidth,             // width
                       texture->mHeight,            // height
                       1,                           // depth
                       1,                           // mipmapCount
                       1,                           // frameCount
                       0,                           // frameDelay
                       reinterpret_cast
                            <const UInt8*>(
                                texture->pcData),   // the texel data in ARGB8888 format
                       GL_UNSIGNED_INT_8_8_8_8_REV, // the data  type -> the pixel format together with this REV data type gives a GL_RGBA internal format
                       true,                        // allocMem
                       1);                          // sidecount

            return ImageTransitPtr(image);
        }
    }

    return ImageTransitPtr(NULL);
}

void AssimpMaterialProcessor::adaptTextureImageFile()
{
    if (!_filename.empty())
    {
        namespace fs = ::boost::filesystem;

        fs::path filename = _filename;

        if (fs::exists(filename) && fs::is_regular_file(filename))
        {
            return;
        }
        //
        // Ok, we could the image file not found in the first place. Now, we lookup the
        // image heuristically. First we look into the provided path if any, then into the
        // current working directory. If we found an appropriate file we set the _filename
        // variable and exit the procedure.
        //
        std::vector<fs::path> relative_file_pathes;

        fs::path::const_iterator file_path_iter = filename.begin();
        fs::path::const_iterator file_path_end  = filename.end();

        do
        {
            if (file_path_iter != file_path_end)
            {
                --file_path_end;

                fs::path token = *file_path_end;

                if (!relative_file_pathes.empty())
                    token = token / relative_file_pathes.back();

                relative_file_pathes.push_back(token);
            }
        } while (file_path_iter != file_path_end);


        fs::path path = _directory;
        fs::path work = fs::current_path();

        // some typical encountered texture subdirectory names
        fs::path texture  = "texture";
        fs::path textures = "textures";

        std::vector<fs::path> pathes;

        pathes.push_back(path);
        pathes.push_back(path/texture);
        pathes.push_back(path/textures);
        pathes.push_back(work/path);
        pathes.push_back(work/path/texture);
        pathes.push_back(work/path/textures);
        pathes.push_back(work);
        pathes.push_back(work/texture);
        pathes.push_back(work/textures);

        pathes.erase(
            std::unique(pathes.begin(), 
                        pathes.end()), 
            pathes.end());

        std::vector<fs::path>::const_iterator path_iter = pathes.begin();
        std::vector<fs::path>::const_iterator path_end  = pathes.end();

        for (; path_iter != path_end; ++path_iter)
        {
            const fs::path& path = *path_iter;

            if (!fs::is_directory(path))
                continue;

            std::vector<fs::path>::const_reverse_iterator rel_file_iter = relative_file_pathes.rbegin();
            std::vector<fs::path>::const_reverse_iterator rel_file_end  = relative_file_pathes.rend();

            for (; rel_file_iter != rel_file_end; ++rel_file_iter)
            {
                fs::path file = path / *rel_file_iter;
                if (fs::exists(file) && fs::is_regular_file(file))
                {
                    _filename = file.string();
                    return;
                }
            }
        }
    }
}

bool AssimpMaterialProcessor::checkORMTextureSupport(const aiMaterial* mat) const
{
    if (_importer == "glTF2 Importer")
    {
        // ORM only for roghness/metalness workflow
        bool bool_value;
        if (mat->Get(AI_MATKEY_GLTF_PBRSPECULARGLOSSINESS, bool_value) == AI_SUCCESS && bool_value == true)
            return false;

        float float_value;
        if (aiGetMaterialFloat(mat, AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_METALLIC_FACTOR, &float_value) == AI_SUCCESS)
        {
            aiTextureType type = aiTextureType_LIGHTMAP;

            unsigned int cntRoughMetal = mat->GetTextureCount(aiTextureType_UNKNOWN);
            unsigned int cntAmbientOcc = mat->GetTextureCount(type);

            bool proceed = false;

            if (cntRoughMetal == 1 && cntAmbientOcc == 1)
            {
                proceed = true;
            }
            else
            {
                type = aiTextureType_AMBIENT_OCCLUSION;
                cntAmbientOcc = mat->GetTextureCount(type);

                if (cntRoughMetal == 1 && cntAmbientOcc == 1)
                {
                    proceed = true;
                }
            }

            if (proceed)
            {
                aiString              pathRM,       pathAO;
                aiTextureMapping   mappingRM,    mappingAO;
                unsigned int       uvindexRM,    uvindexAO;
                ai_real              blendRM,      blendAO;
                aiTextureOp             opRM,         opAO;
                aiTextureMapMode   mapmodeRM[3], mapmodeAO[3];
                unsigned int         flagsRM,      flagsAO;
                bool             has_trafoRM,  has_trafoAO;
                aiUVTransform    transformRM,  transformAO;
                bool              has_axisRM,   has_axisAO;
                aiVector3D            axisRM,       axisAO;

                  uvindexRM =   uvindexAO = 0;
                    blendRM =     blendAO = 0.f;
                       opRM =        opAO = aiTextureOp_Multiply;
                    flagsRM =     flagsAO = 0;
                has_trafoRM = has_trafoAO = false;
                 has_axisRM =  has_axisAO = false;

                if (aiGetMaterialTexture(mat, aiTextureType_UNKNOWN, 0, &pathRM, &mappingRM, &uvindexRM, &blendRM, &opRM, mapmodeRM, &flagsRM) == AI_SUCCESS)
                {
                    if (pathRM.length == 0)
                        return false;

                    if (aiGetMaterialTexture(mat, type, 0, &pathAO, &mappingAO, &uvindexAO, &blendAO, &opAO, mapmodeAO, &flagsAO) == AI_SUCCESS)
                        if (pathAO.length == 0)
                            return false;

                    if (       pathRM    ==    pathAO
                         && mappingRM    == mappingAO
                         && uvindexRM    == uvindexAO
                         &&   blendRM    ==   blendAO
                         &&      opRM    ==      opAO
                         && mapmodeRM[0] == mapmodeAO[0]
                         && mapmodeRM[1] == mapmodeAO[1]
                         && mapmodeRM[2] == mapmodeAO[2]
                         &&   flagsRM    == flagsAO      )
                    {
                        
                        has_axisRM = mat->Get(AI_MATKEY_TEXMAP_AXIS(aiTextureType_UNKNOWN, 0), axisRM) == AI_SUCCESS;
                        has_axisAO = mat->Get(AI_MATKEY_TEXMAP_AXIS(type                 , 0), axisAO) == AI_SUCCESS;
                        
                        if (has_axisRM == true && has_axisAO == true && axisRM != axisAO)
                            return false;

                        has_trafoRM = mat->Get(AI_MATKEY_UVTRANSFORM(aiTextureType_UNKNOWN, 0), transformRM) == AI_SUCCESS;
                        has_trafoAO = mat->Get(AI_MATKEY_UVTRANSFORM(type                 , 0), transformAO) == AI_SUCCESS;

                        if (has_trafoRM == true && has_trafoAO == true 
                            && (   transformRM.mTranslation != transformAO.mTranslation
                                || transformRM.mScaling     != transformAO.mScaling
                                || transformRM.mRotation    != transformAO.mRotation)
                            )
                            return false;

                        return true;
                    }
                }
            }
        }
    }

    return false;
}

#endif // OSG_WITH_ASSIMP

OSG_END_NAMESPACE
