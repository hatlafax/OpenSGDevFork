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

#include "OSGAssimpExaminer.h"
#include "OSGAssimpLog.h"

#ifdef OSG_WITH_ASSIMP
#pragma warning( push )
#pragma warning(disable : 4800)
#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/ProgressHandler.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/material.h>
#include <assimp/GltfMaterial.h>
#include <assimp/anim.h>
#include <assimp/metadata.h>
#include <assimp/vector3.h>
#include <assimp/color4.h>
#include <assimp/postprocess.h>

#pragma warning( pop )
#endif // OSG_WITH_ASSIMP

OSG_BEGIN_NAMESPACE

const std::string space = "    ";

AssimpExaminer::AssimpExaminer(const AssimpOptions& options, const std::string& importer)
: _options(options)
, _importer(importer)
, _filename()
, _log()
, _spaces()
{
    _spaces.push("");
}

AssimpExaminer::~AssimpExaminer(void)
{
}

#ifdef OSG_WITH_ASSIMP
bool AssimpExaminer::examine(const aiScene* scene)
{
    if (!scene || _filename.empty())
        return false;

    std::ofstream os(_filename.c_str());

    os << "##" << std::endl;
    os << "## This file is written by the OpenSG Assimp file examinator. Its purpose is mere informative." << std::endl;
    os << "## It should allow to inspect the content and structure of the original 3D import file." << std::endl;
    os << "## Additionally, the OpenSG Assimp file examinator is a boilerplate implementation for working" << std::endl;
    os << "## with the Assimp library. OpenSG does not take credit of all the options the Assimp library" << std::endl;
    os << "## provides." << std::endl;
    os << "##" << std::endl;
    os << "## Version: 1.0" << std::endl;
    os << "## Implementation: April 2018" << std::endl;
    os << "##" << std::endl;
    os << std::endl;

    if (!_importer.empty())
    {
        os << "Importer = " << _importer << std::endl;
    }
    else
    {
        os << "Importer = not available" << std::endl;
    }

    os << std::endl;

    os << std::fixed << std::setprecision(6);

    doExamine(scene, os);

    return true;
}

void AssimpExaminer::doExamine(const aiScene* scene, std::ofstream& os)
{
    std::string spc = _spaces.top();

    if (!_log.empty())
    {
        os << std::endl;
        os << _log;
    }

    os << std::endl;

    os << spc << "aiScene:" << std::endl;
    os << spc << "========" << std::endl;

    spc += space;
    _spaces.push(spc);

    if(!scene)
    {
        os << spc << "No Assimp scene: scene = nullptr!" << std::endl;
        return;
    }

    if (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
    {
        os << spc << "mFlags -> AI_SCENE_FLAGS_INCOMPLETE" << std::endl;
        return;
    }

    if (!scene->mRootNode)
    {
        os << spc << "No Assimp scene root node: mRootNode = nullptr!" << std::endl;
        return;
    }

    if (scene->mFlags & AI_SCENE_FLAGS_VALIDATED)
    {
        os << spc << "mFlags -> AI_SCENE_FLAGS_VALIDATED" << std::endl;
    }

    if (scene->mFlags & AI_SCENE_FLAGS_VALIDATION_WARNING)
    {
        os << spc << "mFlags -> AI_SCENE_FLAGS_VALIDATION_WARNING" << std::endl;
    }

    if (scene->mFlags & AI_SCENE_FLAGS_NON_VERBOSE_FORMAT)
    {
        os << spc << "mFlags -> AI_SCENE_FLAGS_NON_VERBOSE_FORMAT" << std::endl;
    }

    if (scene->mFlags & AI_SCENE_FLAGS_TERRAIN)
    {
        os << spc << "mFlags -> AI_SCENE_FLAGS_TERRAIN" << std::endl;
    }

    if (scene->mFlags & AI_SCENE_FLAGS_ALLOW_SHARED)
    {
        os << spc << "mFlags -> AI_SCENE_FLAGS_ALLOW_SHARED" << std::endl;
    }

    os << std::endl;

    os << spc << "HasAnimations() = " << ( scene->HasAnimations() ? "true" : "false" );
    if (scene->HasAnimations())
    {
        os << " => mNumAnimations = " << scene->mNumAnimations << std::endl;
    }
    else
    {
        os << std::endl;
    }

    os << spc << "HasCameras   () = " << ( scene->HasCameras   () ? "true" : "false" );
    if (scene->HasCameras())
    {
        os << " => mNumCameras    = " << scene->mNumCameras << std::endl;
    }
    else
    {
        os << std::endl;
    }

    os << spc << "HasLights    () = " << ( scene->HasLights    () ? "true" : "false" );
    if (scene->HasLights())
    {
        os << " => mNumLights     = " << scene->mNumLights << std::endl;
    }
    else
    {
        os << std::endl;
    }

    os << spc << "HasMaterials () = " << ( scene->HasMaterials () ? "true" : "false" );
    if (scene->HasMaterials())
    {
        os << " => mNumMaterials  = " << scene->mNumMaterials << std::endl;
    }
    else
    {
        os << std::endl;
    }

    os << spc << "HasMeshes    () = " << ( scene->HasMeshes    () ? "true" : "false" );
    if (scene->HasMeshes())
    {
        os << " => mNumMeshes     = " << scene->mNumMeshes << std::endl;
    }
    else
    {
        os << std::endl;
    }

    os << spc << "HasTextures  () = " << ( scene->HasTextures  () ? "true" : "false" );
    if (scene->HasTextures())
    {
        os << " => mNumTextures   = " << scene->mNumTextures << std::endl;
    }
    else
    {
        os << std::endl;
    }

    os << std::endl;

    if (scene->HasMeshes() && _options.hasExamineFlag(AssimpOptions::ExamineMesh))
    {
        os << spc << "for i in mNumMeshes: doExamine(mMeshes[i])" << std::endl;

        spc += space;
        _spaces.push(spc);

        for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
        {
            os << spc << "Working on mesh number i = " << i << std::endl;
        
            aiMesh* mesh = scene->mMeshes[i];

            doExamine(mesh, os);
        }

        _spaces.pop(); spc = _spaces.top();

        os << std::endl;
    }

    if (scene->HasMaterials() && _options.hasExamineFlag(AssimpOptions::ExamineMaterial))
    {
        os << spc << "for i in mNumMaterials: doExamine(mMaterials[i])" << std::endl;

        spc += space;
        _spaces.push(spc);

        for (unsigned int i = 0; i < scene->mNumMaterials; ++i)
        {
            os << spc << "Working on material number i = " << i << std::endl;
        
            aiMaterial* material = scene->mMaterials[i];

            doExamine(material, os);
        }

        _spaces.pop(); spc = _spaces.top();

        os << std::endl;
    }

    if (scene->HasTextures() && _options.hasExamineFlag(AssimpOptions::ExamineTextures))
    {
        os << spc << "for i in mNumTextures: doExamine(mTextures[i])" << std::endl;

        spc += space;
        _spaces.push(spc);

        for (unsigned int i = 0; i < scene->mNumTextures; ++i)
        {
            os << spc << "Working on texture number i = " << i << std::endl;
        
            aiTexture* texture = scene->mTextures[i];

            doExamine(texture, os);
        }

        _spaces.pop(); spc = _spaces.top();

        os << std::endl;
    }

    if (scene->HasLights() && _options.hasExamineFlag(AssimpOptions::ExamineLights))
    {
        os << spc << "for i in mNumLights: doExamine(mLights[i])" << std::endl;

        spc += space;
        _spaces.push(spc);

        for (unsigned int i = 0; i < scene->mNumLights; ++i)
        {
            os << spc << "Working on light number i = " << i << std::endl;
        
            aiLight* light = scene->mLights[i];

            doExamine(light, os);
        }

        _spaces.pop(); spc = _spaces.top();

        os << std::endl;
    }

    if (scene->HasCameras() && _options.hasExamineFlag(AssimpOptions::ExamineCameras))
    {
        os << spc << "for i in mNumCameras: doExamine(mCameras[i])" << std::endl;

        spc += space;
        _spaces.push(spc);

        for (unsigned int i = 0; i < scene->mNumCameras; ++i)
        {
            os << spc << "Working on camera number i = " << i << std::endl;
        
            aiCamera* camera = scene->mCameras[i];

            doExamine(camera, os);
        }

        _spaces.pop(); spc = _spaces.top();

        os << std::endl;
    }

    if (scene->HasAnimations() && _options.hasExamineFlag(AssimpOptions::ExamineAnimations))
    {
        os << spc << "for i in mNumAnimations: doExamine(mAnimations[i])" << std::endl;

        spc += space;
        _spaces.push(spc);

        for (unsigned int i = 0; i < scene->mNumAnimations; ++i)
        {
            os << spc << "Working on animation number i = " << i << std::endl;
        
            aiAnimation* animation = scene->mAnimations[i];

            doExamine(animation, os);
        }

        _spaces.pop(); spc = _spaces.top();

        os << std::endl;
    }

    if (_options.hasExamineFlag(AssimpOptions::ExamineNodes))
    {
        os << spc << "doExamine(mRootNode)" << std::endl;

        spc += space;
        _spaces.push(spc);

        doExamine(scene->mRootNode, os);

        _spaces.pop(); spc = _spaces.top();
    }

    _spaces.pop(); spc = _spaces.top();
}

void AssimpExaminer::doExamine(const aiMesh* mesh, std::ofstream& os)
{
    std::string spc = _spaces.top();

    os << std::endl;

    os << spc << "aiMesh:" << std::endl;
    os << spc << "=======" << std::endl;

    if(!mesh)
    {
        os << spc << space << "Error: No Assimp mesh: mesh = nullptr!" << std::endl;
        return;
    }

    spc += space;
    _spaces.push(spc);

    os << spc << "mName                       = " << mesh->mName.C_Str()  << std::endl;
    os << spc << "mMaterialIndex              = " << mesh->mMaterialIndex << std::endl;

    if (mesh->mPrimitiveTypes & aiPrimitiveType_POINT)
    {
        os << spc << "mPrimitiveTypes            -> aiPrimitiveType_POINT" << std::endl;
    }

    if (mesh->mPrimitiveTypes & aiPrimitiveType_LINE)
    {
        os << spc << "mPrimitiveTypes            -> aiPrimitiveType_LINE" << std::endl;
    }

    if (mesh->mPrimitiveTypes & aiPrimitiveType_TRIANGLE)
    {
        os << spc << "mPrimitiveTypes            -> aiPrimitiveType_TRIANGLE" << std::endl;
    }

    if (mesh->mPrimitiveTypes & aiPrimitiveType_POLYGON)
    {
        os << spc << "mPrimitiveTypes            -> aiPrimitiveType_POLYGON" << std::endl;
    }

    if (mesh->mMethod & aiMorphingMethod_VERTEX_BLEND)
    {
        os << spc << "mMethod                    -> aiMorphingMethod_VERTEX_BLEND" << std::endl;
    }

    if (mesh->mMethod & aiMorphingMethod_MORPH_NORMALIZED)
    {
        os << spc << "mMethod                    -> aiMorphingMethod_MORPH_NORMALIZED" << std::endl;
    }

    if (mesh->mMethod & aiMorphingMethod_MORPH_RELATIVE)
    {
        os << spc << "mMethod                    -> aiMorphingMethod_MORPH_RELATIVE" << std::endl;
    }

    os << std::endl;
    os << spc << "HasBones                ( ) = " << ( mesh->HasBones() ? "true" : "false" );
    if (mesh->HasBones() && _options.hasExamineFlag(AssimpOptions::ExamineBones))
    {
        os << " => mNumBones             = " << mesh->mNumBones << std::endl;

        os << spc << "for i in mNumBones: doExamine(mBones[i])" << std::endl;

        spc += space;
        _spaces.push(spc);

        for (unsigned int i = 0; i < mesh->mNumBones; ++i)
        {
            os << spc << "Working on bone number i = " << i << std::endl;
        
            aiBone* bone = mesh->mBones[i];

            doExamine(bone, os);
        }

        _spaces.pop(); spc = _spaces.top();
    }
    else
    {
        os << std::endl;
    }

    os << spc << "HasFaces                ( ) = " << ( mesh->HasFaces() ? "true" : "false" );
    if (mesh->HasFaces() && _options.hasExamineFlag(AssimpOptions::ExamineFaces))
    {
        os << " => mNumFaces             = " << mesh->mNumFaces << std::endl;

        for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
        {
            spc += space;
            _spaces.push(spc);

            os << spc << "Working on face number i = " << i << std::endl;
        
            const aiFace* face = &mesh->mFaces[i];

            doExamine(face, os);

            _spaces.pop(); spc = _spaces.top();
        }
    }
    else
    {
        os << std::endl;
    }

    os << spc << "HasNormals              ( ) = " << ( mesh->HasNormals() ? "true" : "false" );
    if (mesh->HasNormals() && _options.hasExamineFlag(AssimpOptions::ExamineNormals))
    {
        os << " => mNumVertices      = " << mesh->mNumVertices << std::endl;

        doExamine("Normals", "mNormals", mesh->mNormals, mesh->mNumVertices, os);
    }
    else
    {
        os << std::endl;
    }

    os << spc << "HasPositions            ( ) = " << ( mesh->HasPositions() ? "true" : "false" );
    if (mesh->HasPositions() && _options.hasExamineFlag(AssimpOptions::ExaminePositions))
    {
        os << " => mNumVertices      = " << mesh->mNumVertices << std::endl;

        doExamine("Positions", "mVertices", mesh->mVertices, mesh->mNumVertices, os);
    }
    else
    {
        os << std::endl;
    }

    os << spc << "HasTangentsAndBitangents( ) = " << ( mesh->HasTangentsAndBitangents() ? "true" : "false" );
    if (mesh->HasTangentsAndBitangents() && _options.hasExamineFlag(AssimpOptions::ExamineTangents))
    {
        os << " => mNumVertices      = " << mesh->mNumVertices << std::endl;

        doExamine("Tangents", "mTangents", mesh->mTangents, mesh->mNumVertices, os);
        doExamine("Bitangents", "mBitangents", mesh->mBitangents, mesh->mNumVertices, os);
    }
    else
    {
        os << std::endl;
    }

    os << spc << "GetNumColorChannels     ( ) = " << mesh->GetNumColorChannels() << std::endl;
    os << std::endl;

    if (mesh->GetNumColorChannels() > 0  && _options.hasExamineFlag(AssimpOptions::ExamineColors))
    {
        for (unsigned int i = 0; i < AI_MAX_NUMBER_OF_COLOR_SETS; ++i)
        {
            os << spc << "HasVertexColors     (" << i << ") = " << ( mesh->HasVertexColors(i) ? "true" : "false" ) << std::endl;
            if (mesh->HasVertexColors(i))
            {
                std::stringstream hlp1, hlp2;
                hlp1 << "VertexColors of color channel = " << i << " < AI_MAX_NUMBER_OF_COLOR_SETS = " << AI_MAX_NUMBER_OF_COLOR_SETS << std::flush;
                hlp2 << "mColors[" << i << "]" << std::flush;

                doExamine(hlp1.str().c_str(), hlp2.str().c_str(), mesh->mColors[i], mesh->mNumVertices, os);
            }
        }
    }

    os << spc << "GetNumUVChannels        ( ) = " << mesh->GetNumUVChannels   () << std::endl;
    os << std::endl;

    if (mesh->GetNumUVChannels() > 0  && _options.hasExamineFlag(AssimpOptions::ExamineUVCoords))
    {
        for (unsigned int i = 0; i < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++i)
        {
            spc += space;
            _spaces.push(spc);

            os << spc << "HasTextureCoords    (" << i << ") = " << ( mesh->HasTextureCoords(i) ? "true" : "false" ) << std::endl;

            if (mesh->HasTextureCoords(i))
            {
                os << spc << "numUVComponents     [" << i << "] = " << mesh->mNumUVComponents[i] << std::endl << std::endl;

                std::stringstream hlp1, hlp2;
                hlp1 << "TextureCoords of UV channel = " << i << " < AI_MAX_NUMBER_OF_TEXTURECOORDS = " << AI_MAX_NUMBER_OF_TEXTURECOORDS << std::flush;
                hlp2 << "mTextureCoords[" << i << "]" << std::flush;

                doExamine(hlp1.str().c_str(), hlp2.str().c_str(), mesh->mTextureCoords[i], mesh->mNumVertices, os);
            }

            _spaces.pop(); spc = _spaces.top();
        }
    }

    os << spc << "mNumAnimMeshes              = " << mesh->mNumAnimMeshes << std::endl;

    if (mesh->mAnimMeshes  && _options.hasExamineFlag(AssimpOptions::ExamineAniMesh))
    {
        for (unsigned int i = 0; i < mesh->mNumAnimMeshes; ++i)
        {
            aiAnimMesh* anim_mesh = mesh->mAnimMeshes[i];
        }

        spc += space;
        _spaces.push(spc);

        for (unsigned int i = 0; i < mesh->mNumAnimMeshes; ++i)
        {
            os << spc << "Working on animation mesh number i = " << i << std::endl;
        
            aiAnimMesh* anim_mesh = mesh->mAnimMeshes[i];

            doExamine(anim_mesh, os);
        }

        _spaces.pop(); spc = _spaces.top();
    }

    os << std::endl;

    _spaces.pop(); spc = _spaces.top();
}

void AssimpExaminer::doExamine(const aiAnimMesh* mesh, std::ofstream& os)
{
    std::string spc = _spaces.top();

    os << std::endl;

    os << spc << "aiAnimMesh:" << std::endl;
    os << spc << "===========" << std::endl;

    if(!mesh)
    {
        os << spc << space << "Error: No Assimp animation mesh: mesh = nullptr!" << std::endl;
        return;
    }

    spc += space;
    _spaces.push(spc);

    os << std::endl;

    os << spc << "mWeight                     = " << mesh->mWeight << std::endl;

    os << spc << "HasNormals              ( ) = " << ( mesh->HasNormals() ? "true" : "false" );
    if (mesh->HasNormals()  && _options.hasExamineFlag(AssimpOptions::ExamineNormals))
    {
        os << " => mNumVertices          = " << mesh->mNumVertices << std::endl;

        doExamine("Normals", "mNormals", mesh->mNormals, mesh->mNumVertices, os);
    }
    else
    {
        os << std::endl;
    }

    os << spc << "HasPositions            ( ) = " << ( mesh->HasPositions() ? "true" : "false" );
    if (mesh->HasPositions()  && _options.hasExamineFlag(AssimpOptions::ExaminePositions))
    {
        os << " => mNumVertices          = " << mesh->mNumVertices << std::endl;

        doExamine("Positions", "mVertices", mesh->mVertices, mesh->mNumVertices, os);
    }
    else
    {
        os << std::endl;
    }

    os << spc << "HasTangentsAndBitangents( ) = " << ( mesh->HasTangentsAndBitangents() ? "true" : "false" );
    if (mesh->HasTangentsAndBitangents()  && _options.hasExamineFlag(AssimpOptions::ExamineTangents))
    {
        os << " => mNumVertices          = " << mesh->mNumVertices << std::endl;

        doExamine("Tangents", "mTangents", mesh->mTangents, mesh->mNumVertices, os);
        doExamine("Bitangents", "mBitangents", mesh->mBitangents, mesh->mNumVertices, os);
    }
    else
    {
        os << std::endl;
    }

    os << std::endl;

    if (_options.hasExamineFlag(AssimpOptions::ExamineColors))
    {
        for (unsigned int i = 0; i < AI_MAX_NUMBER_OF_COLOR_SETS; ++i)
        {
            os << spc << "HasVertexColors         (" << i << ") = " << ( mesh->HasVertexColors(i) ? "true" : "false" ) << std::endl;
            if (mesh->HasVertexColors(i))
            {
                std::stringstream hlp1, hlp2;
                hlp1 << "VertexColors of color channel = " << i << " < AI_MAX_NUMBER_OF_COLOR_SETS = " << AI_MAX_NUMBER_OF_COLOR_SETS << std::flush;
                hlp2 << "mColors[" << i << "]" << std::flush;

                doExamine(hlp1.str().c_str(), hlp2.str().c_str(), mesh->mColors[i], mesh->mNumVertices, os);
            }
        }

        os << std::endl;
    }

    if (_options.hasExamineFlag(AssimpOptions::ExamineUVCoords))
    {
        for (unsigned int i = 0; i < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++i)
        {
            os << spc << "HasTextureCoords        (" << i << ") = " << ( mesh->HasTextureCoords(i) ? "true" : "false" ) << std::endl;
            if (mesh->HasTextureCoords(i))
            {
                std::stringstream hlp1, hlp2;
                hlp1 << "TextureCoords of UV channel = " << i << " < AI_MAX_NUMBER_OF_TEXTURECOORDS = " << AI_MAX_NUMBER_OF_TEXTURECOORDS << std::flush;
                hlp2 << "mTextureCoords[" << i << "]" << std::flush;

                doExamine(hlp1.str().c_str(), hlp2.str().c_str(), mesh->mTextureCoords[i], mesh->mNumVertices, os);
            }
        }
    }

    os << std::endl;

    _spaces.pop(); spc = _spaces.top();
}

void AssimpExaminer::doExamine(const aiMaterial* mat, std::ofstream& os)
{
    std::string spc = _spaces.top();

    os << std::endl;

    os << spc << "aiMaterial:" << std::endl;
    os << spc << "===========" << std::endl;

    if(!mat)
    {
        os << spc << space << "Error: No Assimp material: material = nullptr!" << std::endl;
        return;
    }

    spc += space;
    _spaces.push(spc);

    aiColor4D color;
    aiString path, name, string_value;

    int int_value;
    float float_value;
    int bool_value;

    if (aiGetMaterialString(mat, AI_MATKEY_NAME, &name) == AI_SUCCESS)
    {
        os << spc << "name              = " << name.C_Str() << std::endl;
    }
    else
    {
        os << spc << "name              = not available" << std::endl;
    }

    os << std::endl;

    if (aiGetMaterialColor(mat, AI_MATKEY_COLOR_AMBIENT, &color) == AI_SUCCESS)
    {
        os << spc << "ambient           = (" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")" << std::endl;
    }
    else
    {
        os << spc << "ambient           = not available" << std::endl;
    }

    if (aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &color) == AI_SUCCESS)
    {
        os << spc << "diffuse           = (" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")" << std::endl;
    }
    else
    {
        os << spc << "diffuse           = not available" << std::endl;
    }

    if (aiGetMaterialColor(mat, AI_MATKEY_COLOR_SPECULAR, &color) == AI_SUCCESS)
    {
        os << spc << "specular          = (" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")" << std::endl;
    }
    else
    {
        os << spc << "specular          = not available" << std::endl;
    }

    if (aiGetMaterialColor(mat, AI_MATKEY_COLOR_EMISSIVE, &color) == AI_SUCCESS)
    {
        os << spc << "emissive          = (" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")" << std::endl;
    }
    else
    {
        os << spc << "emissive          = not available" << std::endl;
    }

    if (aiGetMaterialColor(mat, AI_MATKEY_COLOR_TRANSPARENT, &color) == AI_SUCCESS)
    {
        os << spc << "transparent       = (" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")" << std::endl;
    }
    else
    {
        os << spc << "transparent       = not available" << std::endl;
    }

    if (aiGetMaterialColor(mat, AI_MATKEY_COLOR_REFLECTIVE, &color) == AI_SUCCESS)
    {
        os << spc << "reflective        = (" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")" << std::endl;
    }
    else
    {
        os << spc << "reflective        = not available" << std::endl;
    }

    os << std::endl;

    if (aiGetMaterialString(mat, AI_MATKEY_GLOBAL_BACKGROUND_IMAGE, &path) == AI_SUCCESS)
    {
        os << spc << "global bg img     = " << path.C_Str() << std::endl;
    }
    else
    {
        os << spc << "global bg img     = not available" << std::endl;
    }

    os << std::endl;

    if (aiGetMaterialInteger(mat, AI_MATKEY_TWOSIDED, &int_value) == AI_SUCCESS)
    {
        os << spc << "twosided          = " << (int_value ? "true":"false") << std::endl;
    }
    else
    {
        os << spc << "twosided          = not available" << std::endl;
    }

    if (aiGetMaterialInteger(mat, AI_MATKEY_SHADING_MODEL, &int_value) == AI_SUCCESS)
    {
        std::string model = "unknown";
        switch (int_value)
        {
            case aiShadingMode_Flat:            model = "aiShadingMode_Flat";           break;
            case aiShadingMode_Gouraud:         model = "aiShadingMode_Gouraud";        break;
            case aiShadingMode_Phong:           model = "aiShadingMode_Phong";          break;
            case aiShadingMode_Blinn:           model = "aiShadingMode_Blinn";          break;
            case aiShadingMode_Toon:            model = "aiShadingMode_Toon";           break;
            case aiShadingMode_OrenNayar:       model = "aiShadingMode_OrenNayar";      break;
            case aiShadingMode_Minnaert:        model = "aiShadingMode_Minnaert";       break;
            case aiShadingMode_CookTorrance:    model = "aiShadingMode_CookTorrance";   break;
            case aiShadingMode_NoShading:       model = "aiShadingMode_NoShading";      break;  // alias aiShadingMode_Unlit
            case aiShadingMode_Fresnel:         model = "aiShadingMode_Fresnel";        break;
          //case aiShadingMode_Unlit:           model = "aiShadingMode_Unlit";          break; // alias aiShadingMode_NoShading
            case aiShadingMode_PBR_BRDF:        model = "aiShadingMode_PBR_BRDF";          break;
        }
        os << spc << "shading model     = " << model << std::endl;
    }
    else
    {
        os << spc << "shading model     = not available" << std::endl;
    }

    if (aiGetMaterialInteger(mat, AI_MATKEY_ENABLE_WIREFRAME, &int_value) == AI_SUCCESS)
    {
        os << spc << "wireframe         = " << (int_value ? "true":"false") << std::endl;
    }
    else
    {
        os << spc << "wireframe         = not available" << std::endl;
    }

    if (aiGetMaterialInteger(mat, AI_MATKEY_BLEND_FUNC, &int_value) == AI_SUCCESS)
    {
        std::string mode = "unknown";
        switch (int_value)
        {
            case aiBlendMode_Default:  mode = "aiBlendMode_Default";  break;
            case aiBlendMode_Additive: mode = "aiBlendMode_Additive"; break;
        }
        os << spc << "blend mode        = " << mode << std::endl;
    }
    else
    {
        os << spc << "blend mode        = not available" << std::endl;
    }

    os << std::endl;

    if (aiGetMaterialFloat(mat, AI_MATKEY_OPACITY, &float_value) == AI_SUCCESS)
    {
        os << spc << "opacity           = " << float_value << std::endl;
    }
    else
    {
        os << spc << "opacity           = not available" << std::endl;
    }

    if (aiGetMaterialFloat(mat, AI_MATKEY_BUMPSCALING, &float_value) == AI_SUCCESS)
    {
        os << spc << "bump scaling      = " << float_value << std::endl;
    }
    else
    {
        os << spc << "bump scaling      = not available" << std::endl;
    }

    if (aiGetMaterialFloat(mat, AI_MATKEY_SHININESS, &float_value) == AI_SUCCESS)
    {
        os << spc << "shininess         = " << float_value << std::endl;
    }
    else
    {
        os << spc << "shininess         = not available" << std::endl;
    }

    if (aiGetMaterialFloat(mat, AI_MATKEY_SHININESS_STRENGTH, &float_value) == AI_SUCCESS)
    {
        os << spc << "shin. strgth      = " << float_value << std::endl;
    }
    else
    {
        os << spc << "shin. strgth      = not available" << std::endl;
    }

    if (aiGetMaterialFloat(mat, AI_MATKEY_REFLECTIVITY, &float_value) == AI_SUCCESS)
    {
        os << spc << "reflectivity      = " << float_value << std::endl;
    }
    else
    {
        os << spc << "reflectivity      = not available" << std::endl;
    }

    if (aiGetMaterialFloat(mat, AI_MATKEY_REFRACTI, &float_value) == AI_SUCCESS)
    {
        os << spc << "refractivity      = " << float_value << std::endl;
    }
    else
    {
        os << spc << "refractivity      = not available" << std::endl;
    }

    if (aiGetMaterialColor(mat, AI_MATKEY_BASE_COLOR, &color) == AI_SUCCESS)
    {
        os << spc << "base color factor = (" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")" << std::endl;
    }
    else
    {
        os << spc << "base color factor = not available" << std::endl;
    }

    if (aiGetMaterialFloat(mat, AI_MATKEY_METALLIC_FACTOR, &float_value) == AI_SUCCESS)
    {
        os << spc << "metallic factor   = " << float_value << std::endl;
    }
    else
    {
        os << spc << "metallic factor   = not available" << std::endl;
    }

    if (aiGetMaterialFloat(mat, AI_MATKEY_ROUGHNESS_FACTOR, &float_value) == AI_SUCCESS)
    {
        os << spc << "roughness factor  = " << float_value << std::endl;
    }
    else
    {
        os << spc << "roughness factor  = not available" << std::endl;
    }

    if (aiGetMaterialString(mat, AI_MATKEY_GLTF_ALPHAMODE, &string_value) == AI_SUCCESS)
    {
        std::string mode = string_value.C_Str();
        os << spc << "alpha mode        = " << mode << std::endl;
    }
    else
    {
        os << spc << "alpha mode        = not available" << std::endl;
    }

    if (aiGetMaterialFloat(mat, AI_MATKEY_GLTF_ALPHACUTOFF, &float_value) == AI_SUCCESS)
    {
        os << spc << "alpha cutoff      = " << float_value << std::endl;
    }
    else
    {
        os << spc << "alpha cutoff      = not available" << std::endl;
    }

    if (aiGetMaterialFloat(mat, AI_MATKEY_GLOSSINESS_FACTOR, &float_value) == AI_SUCCESS)
    {
        os << spc << "glossiness        = " << "true"      << std::endl;
        os << spc << "glossiness factor = " << float_value << std::endl;
    }
    else
    {
        os << spc << "glossiness        = false"         << std::endl;
        os << spc << "glossiness factor = not available" << std::endl;
    }

    if (aiGetMaterialInteger(mat, AI_MATKEY_SHADING_MODEL, &int_value) == AI_SUCCESS)
    {
        os << spc << "unlit             = " << (int_value == aiShadingMode_Unlit) << std::endl;
    }
    else
    {
        os << spc << "unlit             = not available" << std::endl;
    }

    os << std::endl;

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
    types.push_back(aiTextureType_LIGHTMAP);
    types.push_back(aiTextureType_REFLECTION);
    types.push_back(aiTextureType_BASE_COLOR);
    types.push_back(aiTextureType_METALNESS);
    types.push_back(aiTextureType_DIFFUSE_ROUGHNESS);
    types.push_back(aiTextureType_AMBIENT_OCCLUSION);
    types.push_back(aiTextureType_UNKNOWN);

    for (std::size_t i = 0; i < types.size(); ++i)
    {
        doExamine(mat, types[i], os);
    }
 
    os << std::endl;

    _spaces.pop(); spc = _spaces.top();
}

enum 
{
    aiTextureType_GLTF_PBRMETALLICROUGHNESS_BASE_COLOR        = aiTextureType_DIFFUSE,
    aiTextureType_GLTF_PBRMETALLICROUGHNESS_METALLICROUGHNESS = aiTextureType_UNKNOWN,
};

void AssimpExaminer::doExamine(const aiMaterial*  mat, aiTextureType type, std::ofstream& os)
{
    std::string spc = _spaces.top();

    std::string name = "unknown";
    switch (type)
    {
        case aiTextureType_NONE:                name = "aiTextureType_NONE";                break;
        case aiTextureType_DIFFUSE:
            {
                aiColor4D color;
                if (aiGetMaterialColor(mat, AI_MATKEY_BASE_COLOR, &color) == AI_SUCCESS)
                {
                    name = "aiTextureType_BASE_COLOR";
                }
                else
                {
                    name = "aiTextureType_DIFFUSE";
                }
            }
            break;
        case aiTextureType_SPECULAR:            name = "aiTextureType_SPECULAR";            break;
        case aiTextureType_AMBIENT:             name = "aiTextureType_AMBIENT";             break;
        case aiTextureType_EMISSIVE:            name = "aiTextureType_EMISSIVE";            break;
        case aiTextureType_HEIGHT:              name = "aiTextureType_HEIGHT";              break;
        case aiTextureType_NORMALS:             name = "aiTextureType_NORMALS";             break;
        case aiTextureType_SHININESS:           name = "aiTestring_valuextureType_SHININESS";           break;
        case aiTextureType_OPACITY:             name = "aiTextureType_OPACITY";             break;
        case aiTextureType_DISPLACEMENT:        name = "aiTextureType_DISPLACEMENT";        break;
        case aiTextureType_LIGHTMAP:            name = "aiTextureType_LIGHTMAP";            break;
        case aiTextureType_REFLECTION:          name = "aiTextureType_REFLECTION";          break;
        case aiTextureType_UNKNOWN:
            {
                float float_value;
                if (aiGetMaterialFloat(mat, AI_MATKEY_METALLIC_FACTOR, &float_value) == AI_SUCCESS)
                {
                    name = "aiTextureType_METALLICROUGHNESS";
                }
                else
                {
                    name = "aiTextureType_UNKNOWN";
                }
            }
            break;
        case aiTextureType_BASE_COLOR:          name = "aiTextureType_BASE_COLOR";          break;
        case aiTextureType_METALNESS:           name = "aiTextureType_METALNESS";           break;
        case aiTextureType_DIFFUSE_ROUGHNESS:   name = "aiTextureType_DIFFUSE_ROUGHNESS";   break;
        case aiTextureType_AMBIENT_OCCLUSION:   name = "aiTextureType_AMBIENT_OCCLUSION";   break;
    }

    unsigned int cnt = mat->GetTextureCount(type);

    os << spc << "Texture type  = " << name << " N = " << cnt << std::endl;

    spc += space;
    _spaces.push(spc);

    for(unsigned int index = 0; index < cnt; index++)
    {
        aiString path;
        aiTextureMapping mapping;
        unsigned int uvindex = 0;
        ai_real blend = 0.f;
        aiTextureOp op;
        aiTextureMapMode mapmode[3];
        int flags = 0;
        aiUVTransform transform;
        aiVector3D axis;

        if (mat->GetTexture(type, index, &path, &mapping, &uvindex, &blend, &op, mapmode) == AI_SUCCESS)
        {
            std::string mapping_str, blend_str, op_str, mapmode_r, mapmode_s, mapmode_t;

            switch(mapping)
            {
                case aiTextureMapping_UV:       mapping_str = "aiTextureMapping_UV";
                case aiTextureMapping_SPHERE:   mapping_str = "aiTextureMapping_SPHERE";
                case aiTextureMapping_CYLINDER: mapping_str = "aiTextureMapping_CYLINDER";
                case aiTextureMapping_BOX:      mapping_str = "aiTextureMapping_BOX";
                case aiTextureMapping_PLANE:    mapping_str = "aiTextureMapping_PLANE";
                case aiTextureMapping_OTHER:    mapping_str = "aiTextureMapping_OTHER";
                default:                        mapping_str = "unknown";
            }

            switch(op)
            {
                case aiTextureOp_Multiply:  op_str = "aiTextureOp_Multiply";
                case aiTextureOp_Add:       op_str = "aiTextureOp_Add";
                case aiTextureOp_Subtract:  op_str = "aiTextureOp_Subtract";
                case aiTextureOp_Divide:    op_str = "aiTextureOp_Divide";
                case aiTextureOp_SmoothAdd: op_str = "aiTextureOp_SmoothAdd";
                case aiTextureOp_SignedAdd: op_str = "aiTextureOp_SignedAdd";
                default:                    op_str = "unknown";
            }

            switch(mapmode[0])
            {
                case aiTextureMapMode_Wrap:     mapmode_r = "aiTextureMapMode_Wrap";
                case aiTextureMapMode_Clamp:    mapmode_r = "aiTextureMapMode_Clamp";
                case aiTextureMapMode_Decal:    mapmode_r = "aiTextureMapMode_Decal";
                case aiTextureMapMode_Mirror:   mapmode_r = "aiTextureMapMode_Mirror";
                default:                        mapmode_r = "unknown";
            }

            switch(mapmode[1])
            {
                case aiTextureMapMode_Wrap:     mapmode_s = "aiTextureMapMode_Wrap";
                case aiTextureMapMode_Clamp:    mapmode_s = "aiTextureMapMode_Clamp";
                case aiTextureMapMode_Decal:    mapmode_s = "aiTextureMapMode_Decal";
                case aiTextureMapMode_Mirror:   mapmode_s = "aiTextureMapMode_Mirror";
                default:                        mapmode_s = "unknown";
            }

            switch(mapmode[2])
            {
                case aiTextureMapMode_Wrap:     mapmode_t = "aiTextureMapMode_Wrap";
                case aiTextureMapMode_Clamp:    mapmode_t = "aiTextureMapMode_Clamp";
                case aiTextureMapMode_Decal:    mapmode_t = "aiTextureMapMode_Decal";
                case aiTextureMapMode_Mirror:   mapmode_t = "aiTextureMapMode_Mirror";
                default:                        mapmode_t = "unknown";
            }

            os << spc << "Texture(" << name <<", " << index << ", ...) valid" << std::endl;
            os << spc << "type            = " << name          << std::endl;
            os << spc << "index           = " << index         << std::endl;
            os << spc << "path            = " << path.C_Str()  << std::endl;
            os << spc << "mapping         = " << mapping_str   << std::endl;
            os << spc << "uvindex         = " << uvindex       << std::endl;
            os << spc << "blend factor    = " << blend         << std::endl;
            os << spc << "operation       = " << op_str        << std::endl;
            os << spc << "mapmode         = (" << mapmode_r << ", "<< mapmode_s << ", "<< mapmode_t << ")" << std::endl;

           if (mat->Get(AI_MATKEY_TEXMAP_AXIS(type, index), axis) == AI_SUCCESS)
            {
                os << spc << "axis            = (" << axis.x << ", " << axis.y << ", " << axis.z << ")" << std::endl;
            }
            else
            {
                os << spc << "axis            = not available" << std::endl;
            }

            if (aiGetMaterialInteger(mat, AI_MATKEY_TEXFLAGS(type, index), &flags) == AI_SUCCESS)
            {
                if (flags & aiTextureFlags_Invert)
                {
                    os << spc << "aiTextureFlags -> aiTextureFlags_Invert" << std::endl;
                }

                if (flags & aiTextureFlags_UseAlpha)
                {
                    os << spc << "aiTextureFlags -> aiTextureFlags_UseAlpha" << std::endl;
                }

                if (flags & aiTextureFlags_IgnoreAlpha)
                {
                    os << spc << "aiTextureFlags -> aiTextureFlags_IgnoreAlpha" << std::endl;
                }
            }
            else
            {
                os << spc << "aiTextureFlags -> not available" << std::endl;
            }

            if (mat->Get(AI_MATKEY_UVTRANSFORM(type, index), transform) == AI_SUCCESS)
            {
                os << spc << "uvTr.mRotation  = " << transform.mRotation << std::endl;
                os << spc << "uvTr.mScaling   = (" << transform.mScaling.x << ", " << transform.mScaling.y << ")" << std::endl;
                os << spc << "uvTr.mTranslat  = (" << transform.mTranslation.x << ", " << transform.mTranslation.y << ")" << std::endl;
            }
            else
            {
                os << spc << "transform       = not available" << std::endl;
            }
        }
        else
        {
            os << spc << "Texture(" << name <<", " << index << ", ...) not available" << std::endl;
        }

        os << std::endl;
    }

    _spaces.pop(); spc = _spaces.top();
}

void AssimpExaminer::doExamine(const aiAnimation* animation, std::ofstream& os)
{
    std::string spc = _spaces.top();

    os << std::endl;

    os << spc << "aiAnimation:" << std::endl;
    os << spc << "============" << std::endl;

    if(!animation)
    {
        os << spc << space << "Error: No Assimp animation: animation = nullptr!" << std::endl;
        return;
    }

    spc += space;
    _spaces.push(spc);

    os << spc << "mName                 = " << animation->mName.C_Str() << std::endl;
    os << spc << "mDuration             = " << animation->mDuration << std::endl;
    os << spc << "mTicksPerSecond       = " << animation->mTicksPerSecond << std::endl;
    os << spc << "mNumChannels          = " << animation->mNumChannels << std::endl;
    os << spc << "mNumMeshChannels      = " << animation->mNumMeshChannels << std::endl;
    os << spc << "mNumMorphMeshChannels = " << animation->mNumMorphMeshChannels << std::endl;

    if (animation->mNumChannels > 0  && _options.hasExamineFlag(AssimpOptions::ExamineNodeAnim))
    {
        os << std::endl;
        os << spc << "for i in mNumChannels: doExamine(mChannels[i])" << std::endl;

        spc += space;
        _spaces.push(spc);

        for (unsigned int i = 0; i < animation->mNumChannels; ++i)
        {
            os << spc << "Working on node animation number i = " << i << std::endl;
        
            aiNodeAnim* nodeAnimation = animation->mChannels[i];

            doExamine(nodeAnimation, os);
        }

        _spaces.pop(); spc = _spaces.top();
    }

    if (animation->mNumMeshChannels > 0  && _options.hasExamineFlag(AssimpOptions::ExamineMeshAnim))
    {
        os << std::endl;
        os << spc << "for i in mNumMeshChannels: doExamine(mMeshChannels[i])" << std::endl;

        spc += space;
        _spaces.push(spc);

        for (unsigned int i = 0; i < animation->mNumMeshChannels; ++i)
        {
            os << spc << "Working on mesh animation number i = " << i << std::endl;
        
            aiMeshAnim* meshAnimation = animation->mMeshChannels[i];

            doExamine(meshAnimation, os);
        }

        _spaces.pop(); spc = _spaces.top();
    }

    if (animation->mNumMorphMeshChannels > 0  && _options.hasExamineFlag(AssimpOptions::ExamineMeshMorphAnim))
    {
        os << std::endl;
        os << spc << "for i in mNumMorphMeshChannels: doExamine(mMorphMeshChannels[i])" << std::endl;

        spc += space;
        _spaces.push(spc);

        for (unsigned int i = 0; i < animation->mNumMorphMeshChannels; ++i)
        {
            os << spc << "Working on mesh morph animation number i = " << i << std::endl;
        
            aiMeshMorphAnim* meshMorphAnimation = animation->mMorphMeshChannels[i];

            doExamine(meshMorphAnimation, os);
        }

        _spaces.pop(); spc = _spaces.top();
    }

    os << std::endl;

    _spaces.pop(); spc = _spaces.top();
}

void AssimpExaminer::doExamine(const aiNodeAnim* nodeAnim, std::ofstream& os)
{
    std::string spc = _spaces.top();

    os << std::endl;

    os << spc << "aiNodeAnim:" << std::endl;
    os << spc << "===========" << std::endl;

    if(!nodeAnim)
    {
        os << spc << space << "Error: No Assimp node animation: nodeAnim = nullptr!" << std::endl;
        return;
    }

    spc += space;
    _spaces.push(spc);

    std::string preState, postState;

    switch (nodeAnim->mPreState)
    {
        case aiAnimBehaviour_DEFAULT:   preState = "aiAnimBehaviour_DEFAULT";   break;
        case aiAnimBehaviour_CONSTANT:  preState = "aiAnimBehaviour_CONSTANT";  break;
        case aiAnimBehaviour_LINEAR:    preState = "aiAnimBehaviour_LINEAR";    break;
        case aiAnimBehaviour_REPEAT:    preState = "aiAnimBehaviour_REPEAT";    break;
    }

    switch (nodeAnim->mPostState)
    {
        case aiAnimBehaviour_DEFAULT:   postState = "aiAnimBehaviour_DEFAULT";   break;
        case aiAnimBehaviour_CONSTANT:  postState = "aiAnimBehaviour_CONSTANT";  break;
        case aiAnimBehaviour_LINEAR:    postState = "aiAnimBehaviour_LINEAR";    break;
        case aiAnimBehaviour_REPEAT:    postState = "aiAnimBehaviour_REPEAT";    break;
    }

    os << spc << "mNodeName        = " << nodeAnim->mNodeName.C_Str() << std::endl;
    os << spc << "mNumPositionKeys = " << nodeAnim->mNumPositionKeys << std::endl;
    os << spc << "mNumRotationKeys = " << nodeAnim->mNumRotationKeys << std::endl;
    os << spc << "mNumScalingKeys  = " << nodeAnim->mNumScalingKeys << std::endl;
    os << spc << "mPreState        = " << preState << std::endl;
    os << spc << "mPostState       = " << postState << std::endl;

    os << std::endl;

    if (nodeAnim->mNumPositionKeys > 0)
    {
        spc += space;
        _spaces.push(spc);

        os << spc << "aiVectorKey -> mPositionKeys:" << std::endl;
        os << spc << "=============================" << std::endl;

        for (unsigned int i = 0; i < nodeAnim->mNumPositionKeys; ++i)
        {
            aiVectorKey key = nodeAnim->mPositionKeys[i];
            os << spc << "mPositionKeys[" << std::setw(4) << i << "] = (mTime = " << std::setw(11) << key.mTime << ", mValue = (" << std::setw(11) << key.mValue.x << ", " << std::setw(11) << key.mValue.y << ", " << std::setw(11) << key.mValue.z <<")" << std::endl;
        }

        _spaces.pop(); spc = _spaces.top();
    }

    os << std::endl;

    if (nodeAnim->mNumScalingKeys > 0)
    {
        spc += space;
        _spaces.push(spc);

        os << spc << "aiVectorKey -> mScalingKeys:" << std::endl;
        os << spc << "============================" << std::endl;

        for (unsigned int i = 0; i < nodeAnim->mNumScalingKeys; ++i)
        {
            aiVectorKey key = nodeAnim->mScalingKeys[i];
            os << spc << "mScalingKeys[" << std::setw(4) << i << "] = (mTime = " << std::setw(11) << key.mTime << ", mValue = (" << std::setw(11) << key.mValue.x << ", " << std::setw(11) << key.mValue.y << ", " << std::setw(11) << key.mValue.z <<")" << std::endl;
        }

        _spaces.pop(); spc = _spaces.top();
    }

    os << std::endl;

    if (nodeAnim->mNumRotationKeys > 0)
    {
        spc += space;
        _spaces.push(spc);

        os << spc << "aiQuatKey -> mRotationKeys:" << std::endl;
        os << spc << "===========================" << std::endl;

        for (unsigned int i = 0; i < nodeAnim->mNumRotationKeys; ++i)
        {
            aiQuatKey key = nodeAnim->mRotationKeys[i];
            os << spc << "mRotationKeys[" << std::setw(4) << i << "] = (mTime = " << std::setw(11) << key.mTime << ", mValue = (" << std::setw(11) << key.mValue.x << ", " << std::setw(11) << key.mValue.y << ", " << std::setw(11) << key.mValue.z << std::setw(11) << key.mValue.w <<")" << std::endl;
        }

        _spaces.pop(); spc = _spaces.top();
    }

    os << std::endl;

    _spaces.pop(); spc = _spaces.top();
}

void AssimpExaminer::doExamine(const aiMeshAnim* meshAnim, std::ofstream& os)
{
    std::string spc = _spaces.top();

    os << std::endl;

    os << spc << "aiMeshAnim:" << std::endl;
    os << spc << "===========" << std::endl;

    if(!meshAnim)
    {
        os << spc << space << "Error: No Assimp mesh animation: meshAnim = nullptr!" << std::endl;
        return;
    }

    spc += space;
    _spaces.push(spc);

    os << spc << "mName    = " << meshAnim->mName.C_Str() << std::endl;
    os << spc << "mNumKeys = " << meshAnim->mNumKeys << std::endl;

    os << std::endl;

    if (meshAnim->mNumKeys > 0)
    {
        spc += space;
        _spaces.push(spc);

        os << spc << "aiMeshKey -> mKeys:" << std::endl;
        os << spc << "===================" << std::endl;

        for (unsigned int i = 0; i < meshAnim->mNumKeys; ++i)
        {
            aiMeshKey key = meshAnim->mKeys[i];
            os << spc << "mKeys[" << std::setw(4) << i << "] = (mTime = " << std::setw(11) << key.mTime << ", mValue = " << std::setw(6) << key.mValue << std::endl;
        }

        _spaces.pop(); spc = _spaces.top();
    }

    os << std::endl;

    _spaces.pop(); spc = _spaces.top();
}

void AssimpExaminer::doExamine(const aiMeshMorphAnim* meshMorphAnim, std::ofstream& os)
{
    std::string spc = _spaces.top();

    os << std::endl;

    os << spc << "aiMeshMorphAnim:" << std::endl;
    os << spc << "================" << std::endl;

    if(!meshMorphAnim)
    {
        os << spc << space << "Error: No Assimp mesh morph animation: meshMorphAnim = nullptr!" << std::endl;
        return;
    }

    spc += space;
    _spaces.push(spc);

    os << spc << "mName    = " << meshMorphAnim->mName.C_Str() << std::endl;
    os << spc << "mNumKeys = " << meshMorphAnim->mNumKeys << std::endl;

    os << std::endl;

    if (meshMorphAnim->mNumKeys > 0)
    {
        spc += space;
        _spaces.push(spc);

        os << spc << "aiMeshMorphKey -> mKeys:" << std::endl;
        os << spc << "===========================" << std::endl;

        for (unsigned int i = 0; i < meshMorphAnim->mNumKeys; ++i)
        {
            aiMeshMorphKey key = meshMorphAnim->mKeys[i];
            os << spc << "mKeys[" << std::setw(4) << i << "] = (mTime = " << std::setw(11) << key.mTime << ", mNumValuesAndWeights = " << std::setw(6) << key.mNumValuesAndWeights << std::endl;

            if (key.mNumValuesAndWeights > 0)
            {
                spc += space;
                _spaces.push(spc);

                os << spc << "mValues:" << std::endl;
                os << spc << "========" << std::endl;

                for (unsigned int j = 0; j <key.mNumValuesAndWeights; ++j)
                {
                    unsigned int value  = key.mValues[j];
                    double       weight = key.mWeights[j];
                    os << spc << "mValues[" << std::setw(4) << j << "] = " << std::setw(11) << value << ", mWeights[" << std::setw(4) << j << "] = " << std::setw(11) << weight << std::endl;
                }

                _spaces.pop(); spc = _spaces.top();
            }
        }

        _spaces.pop(); spc = _spaces.top();
    }

    os << std::endl;

    _spaces.pop(); spc = _spaces.top();
}

void AssimpExaminer::doExamine(const aiCamera* camera, std::ofstream& os)
{
    std::string spc = _spaces.top();

    os << std::endl;

    os << spc << "aiCamera:" << std::endl;
    os << spc << "========" << std::endl;

    if(!camera)
    {
        os << spc << space << "Error: No Assimp camera: camera = nullptr!" << std::endl;
        return;
    }

    spc += space;
    _spaces.push(spc);

    aiVector3D d;

    os << spc << "mName          = " << camera->mName.C_Str() << std::endl;
    os << spc << "mAspect        = " << camera->mAspect << std::endl;
    os << spc << "mClipPlaneFar  = " << camera->mClipPlaneFar << std::endl;
    os << spc << "mClipPlaneNear = " << camera->mClipPlaneNear << std::endl;
    os << spc << "mHorizontalFOV = " << camera->mHorizontalFOV << std::endl;
    d = camera->mLookAt;
    os << spc << "mLookAt        = (" << std::setw(11) << d.x << ", " << std::setw(11) << d.y << ", " << std::setw(11) << d.z << ")" << std::endl;
    d = camera->mPosition;
    os << spc << "mPosition      = (" << std::setw(11) << d.x << ", " << std::setw(11) << d.y << ", " << std::setw(11) << d.z << ")" << std::endl;
    d = camera->mUp;
    os << spc << "mUp            = (" << std::setw(11) << d.x << ", " << std::setw(11) << d.y << ", " << std::setw(11) << d.z << ")" << std::endl;

    os << std::endl;

    _spaces.pop(); spc = _spaces.top();
}

void AssimpExaminer::doExamine(const aiLight* light, std::ofstream& os)
{
    std::string spc = _spaces.top();

    os << std::endl;

    os << spc << "aiLight:" << std::endl;
    os << spc << "========" << std::endl;

    if(!light)
    {
        os << spc << space << "Error: No Assimp light: light = nullptr!" << std::endl;
        return;
    }

    spc += space;
    _spaces.push(spc);

    aiColor3D c;
    aiVector3D d;
    aiVector2D s;

    std::string t = "unknown";
    switch (light->mType)
    {
        case aiLightSource_UNDEFINED:   t = "aiLightSource_UNDEFINED";      break;
        case aiLightSource_DIRECTIONAL: t = "aiLightSource_DIRECTIONAL";    break;
        case aiLightSource_POINT:       t = "aiLightSource_POINT";          break;
        case aiLightSource_SPOT:        t = "aiLightSource_SPOT";           break;
        case aiLightSource_AMBIENT:     t = "aiLightSource_AMBIENT";        break;
        case aiLightSource_AREA:        t = "aiLightSource_AREA";           break;
    }

    os << spc << "mName                 = " << light->mName.C_Str() << std::endl;
    os << spc << "mType                 = " << t << std::endl;
    os << spc << "mAngleInnerCone       = " << light->mAngleInnerCone << std::endl;
    os << spc << "mAngleOuterCone       = " << light->mAngleOuterCone << std::endl;
    os << spc << "mAttenuationConstant  = " << light->mAttenuationConstant << std::endl;
    os << spc << "mAttenuationLinear    = " << light->mAttenuationLinear << std::endl;
    os << spc << "mAttenuationQuadratic = " << light->mAttenuationQuadratic << std::endl;
    
    c = light->mColorAmbient;
    os << spc << "mColorAmbient         = (" << std::setw(11) << c.r << ", " << std::setw(11) << c.g << ", " << std::setw(11) << c.b << ")" << std::endl;
    c = light->mColorDiffuse;
    os << spc << "mColorDiffuse         = (" << std::setw(11) << c.r << ", " << std::setw(11) << c.g << ", " << std::setw(11) << c.b << ")" << std::endl;
    c = light->mColorSpecular;
    os << spc << "mColorSpecular        = (" << std::setw(11) << c.r << ", " << std::setw(11) << c.g << ", " << std::setw(11) << c.b << ")" << std::endl;
    d = light->mDirection;
    os << spc << "mDirection            = (" << std::setw(11) << d.x << ", " << std::setw(11) << d.y << ", " << std::setw(11) << d.z << ")" << std::endl;
    d = light->mPosition;
    os << spc << "mPosition             = (" << std::setw(11) << d.x << ", " << std::setw(11) << d.y << ", " << std::setw(11) << d.z << ")" << std::endl;
    d = light->mUp;
    os << spc << "mUp                   = (" << std::setw(11) << d.x << ", " << std::setw(11) << d.y << ", " << std::setw(11) << d.z << ")" << std::endl;
    s = light->mSize;
    os << spc << "mSize                 = (" << std::setw(11) << s.x << ", " << std::setw(11) << s.y << ")" << std::endl;

    os << std::endl;

    _spaces.pop(); spc = _spaces.top();
}

void AssimpExaminer::doExamine(const aiTexture* texture, std::ofstream& os)
{
    std::string spc = _spaces.top();

    os << std::endl;

    os << spc << "aiTexture:" << std::endl;
    os << spc << "==========" << std::endl;

    if(!texture)
    {
        os << spc << space << "Error: No Assimp texture: texture = nullptr!" << std::endl;
        return;
    }

    spc += space;
    _spaces.push(spc);

    os << spc << "achFormatHint = " << texture->achFormatHint << std::endl;
    os << spc << "mHeight       = " << texture->mHeight << std::endl;
    os << spc << "mWidth        = " << texture->mWidth << std::endl;
    os << spc << "pcData        = " << (texture->pcData ? "available" : "nullptr") << std::endl;

    os << std::endl;

    _spaces.pop(); spc = _spaces.top();
}

void AssimpExaminer::doExamine(const aiNode* node, std::ofstream& os)
{
    std::string spc = _spaces.top();

    os << std::endl;

    os << spc << "aiNode:" << std::endl;
    os << spc << "=======" << std::endl;

    if(!node)
    {
        os << spc << space << "Error: No Assimp node: node = nullptr!" << std::endl;
        return;
    }

    spc += space;
    _spaces.push(spc);

    os << spc << "mName           = " << node->mName.C_Str() << std::endl;
    os << spc << "mParent         = " << (node->mParent ? node->mParent->mName.C_Str() : "nullptr") << std::endl;
    os << spc << "mNumMeshes      = " << node->mNumMeshes << std::endl;
    if (node->mNumMeshes > 0)
    {
        os << std::endl;

        spc += space;
        _spaces.push(spc);

        for (unsigned int i = 0; i < node->mNumMeshes; ++i)
        {
            os << spc << "mMeshes[" << std::setw(4) << i << "] = " << node->mMeshes[i] << std::endl;
        }

        _spaces.pop(); spc = _spaces.top();

        os << std::endl;
    }
    
    os << spc << "mTransformation = " << "[ "
              <<                     "[" << std::setw(11) << node->mTransformation[0][0] << ", " << std::setw(11) << std::setw(11) << node->mTransformation[0][1] << ", " << std::setw(11) << node->mTransformation[0][2] << ", " << std::setw(11) << node->mTransformation[0][3] << "]" << std::endl
       << spc << "                    [" << std::setw(11) << node->mTransformation[1][0] << ", " << std::setw(11) << std::setw(11) << node->mTransformation[1][1] << ", " << std::setw(11) << node->mTransformation[1][2] << ", " << std::setw(11) << node->mTransformation[1][3] << "]" << std::endl
       << spc << "                    [" << std::setw(11) << node->mTransformation[2][0] << ", " << std::setw(11) << std::setw(11) << node->mTransformation[2][1] << ", " << std::setw(11) << node->mTransformation[2][2] << ", " << std::setw(11) << node->mTransformation[2][3] << "]" << std::endl
       << spc << "                    [" << std::setw(11) << node->mTransformation[3][0] << ", " << std::setw(11) << std::setw(11) << node->mTransformation[3][1] << ", " << std::setw(11) << node->mTransformation[3][2] << ", " << std::setw(11) << node->mTransformation[3][3] << "] ]" 
       << std::endl;    
    os << spc << "mMetaData       = " << (node->mMetaData ? "available" : "nullptr") << std::endl;

    if (node->mMetaData)
    {
        spc += space;
        _spaces.push(spc);

        doExamine(node->mMetaData, os);

        _spaces.pop(); spc = _spaces.top();
    }

    os << spc << "mNumChildren    = " << node->mNumChildren << std::endl;

    if (node->mNumChildren > 0)
    {
        os << std::endl;

        os << spc << "for i in mNumChildren: doExamine(mChildren[i])" << std::endl;

        spc += space;
        _spaces.push(spc);

        for (unsigned int i = 0; i < node->mNumChildren; ++i)
        {
            if (i > 0) os << std::endl;

            os << spc << "Working on child number i = " << i << std::endl;

            aiNode* child = node->mChildren[i];

            doExamine(child, os);
        }

        _spaces.pop(); spc = _spaces.top();
    }

    _spaces.pop(); spc = _spaces.top();
}

void AssimpExaminer::doExamine(const aiMetadata* metadata, std::ofstream& os)
{
    std::string spc = _spaces.top();

    os << std::endl;

    os << spc << "aiMetadata:" << std::endl;
    os << spc << "===========" << std::endl;

    if(!metadata)
    {
        os << spc << space << "Error: No Assimp meta data: metadata = nullptr!" << std::endl;
        return;
    }

    spc += space;
    _spaces.push(spc);

    os << spc << "mNumProperties = " << metadata->mNumProperties << std::endl;
    
    for (unsigned int i = 0; i < metadata->mNumProperties; ++i)
    {
        aiString          key = metadata->mKeys[i];
        aiMetadataEntry entry = metadata->mValues[i];
        aiMetadataType   type = entry.mType;


        switch (type)
        {
            case AI_BOOL:
                {
                    bool value;
                    metadata->Get(key, value);
                    os << spc << "mKeys[" << std::setw(4) << i << "] = " << key.C_Str() << " \t\t-> bool       value = " << (value ? "true" : "false") << std::endl;
                }
                break;
            case AI_INT32:
                {
                    int32_t value;
                    metadata->Get(key, value);
                    os << spc << "mKeys[" << std::setw(4) << i << "] = " << key.C_Str() << " \t\t-> int32_t   value = " << value << std::endl;
                }
                break;
            case AI_UINT64:
                {
                    uint64_t value;
                    metadata->Get(key, value);
                    os << spc << "mKeys[" << std::setw(4) << i << "] = " << key.C_Str() << " \t\t-> uint64_t   value = " << value << std::endl;
                }
                break;
            case AI_FLOAT:
                {
                    float value;
                    metadata->Get(key, value);
                    os << spc << "mKeys[" << std::setw(4) << i << "] = " << key.C_Str() << " \t\t-> float      value = " << std::setw(11) << value << std::endl;
                }
                break;
            case AI_DOUBLE:
                {
                    double value;
                    metadata->Get(key, value);
                    os << spc << "mKeys[" << std::setw(4) << i << "] = " << key.C_Str() << " \t\t-> double     value = " << std::setw(11) << value << std::endl;
                }
                break;
            case AI_AISTRING:
                {
                    aiString value;
                    metadata->Get(key, value);
                    os << spc << "mKeys[" << std::setw(4) << i << "] = " << key.C_Str() << " \t\t-> aiString   value = " << value.C_Str() << std::endl;
                }
                break;
            case AI_AIVECTOR3D:
                {
                    aiVector3D value;
                    metadata->Get(key, value);
                    os << spc << "mKeys[" << std::setw(4) << i << "] = " << key.C_Str() << " \t\t-> aiVector3D value = (" << std::setw(11) << value.x << ", " << std::setw(11) << value.y << ", " << std::setw(11) << value.z << ")" << std::endl;
                }
                break;
        }
    }

    os << std::endl;

    _spaces.pop(); spc = _spaces.top();
}

void AssimpExaminer::doExamine(const aiFace* face, std::ofstream& os)
{
    std::string spc = _spaces.top();

    os << std::endl;

    os << spc << "aiFace:" << std::endl;
    os << spc << "=======" << std::endl;

    if(!face)
    {
        os << spc << space << "Error: No Assimp face: face = nullptr!" << std::endl;
        return;
    }

    spc += space;
    _spaces.push(spc);

    os << spc << "mNumIndices =  " << face->mNumIndices << std::endl;
    os << spc;

    for (unsigned int i = 0; i < face->mNumIndices; ++i)
    {
        os << "mIndices[" << std::setw(5) << i << "] = " << std::setw(5) << face->mIndices[i] << "  ";
    }
    os << std::endl;

    os << std::endl;

    _spaces.pop(); spc = _spaces.top();
}

void AssimpExaminer::doExamine(const aiBone* bone, std::ofstream& os)
{
    std::string spc = _spaces.top();

    os << std::endl;

    os << spc << "aiBone:" << std::endl;
    os << spc << "=======" << std::endl;

    if(!bone)
    {
        os << spc << space << "Error: No Assimp bone: bone = nullptr!" << std::endl;
        return;
    }

    spc += space;
    _spaces.push(spc);

    
    os << spc << "mName         = " << bone->mName.C_Str() << std::endl;

    os << spc << "mOffsetMatrix = " << "[ "
              <<                   "[" << std::setw(11) << bone->mOffsetMatrix[0][0] << ", " << std::setw(11) << std::setw(11) << bone->mOffsetMatrix[0][1] << ", " << std::setw(11) << bone->mOffsetMatrix[0][2] << ", " << std::setw(11) << bone->mOffsetMatrix[0][3] << "]" << std::endl
       << spc << "                  [" << std::setw(11) << bone->mOffsetMatrix[1][0] << ", " << std::setw(11) << std::setw(11) << bone->mOffsetMatrix[1][1] << ", " << std::setw(11) << bone->mOffsetMatrix[1][2] << ", " << std::setw(11) << bone->mOffsetMatrix[1][3] << "]" << std::endl
       << spc << "                  [" << std::setw(11) << bone->mOffsetMatrix[2][0] << ", " << std::setw(11) << std::setw(11) << bone->mOffsetMatrix[2][1] << ", " << std::setw(11) << bone->mOffsetMatrix[2][2] << ", " << std::setw(11) << bone->mOffsetMatrix[2][3] << "]" << std::endl
       << spc << "                  [" << std::setw(11) << bone->mOffsetMatrix[3][0] << ", " << std::setw(11) << std::setw(11) << bone->mOffsetMatrix[3][1] << ", " << std::setw(11) << bone->mOffsetMatrix[3][2] << ", " << std::setw(11) << bone->mOffsetMatrix[3][3] << "] ]" 
       << std::endl;

    os << spc << "mNumWeights   = " << bone->mNumWeights << std::endl;

    for (unsigned int i = 0; i < bone->mNumWeights; ++i)
    {
        aiVertexWeight w = bone->mWeights[i];
        os << spc << "mWeights[" << std::setw(5) << i << "] = " << "(mVertexId = " << std::setw(4) << w.mVertexId << ", mWeight = " << std::setw(11) << w.mWeight << ")" << std::endl;
    }
    os << std::endl;

    os << std::endl;

    _spaces.pop(); spc = _spaces.top();
}

void AssimpExaminer::doExamine(const char* kind, const char* name, const aiVector3D* vec, unsigned int num, std::ofstream& os)
{
    std::string spc = _spaces.top();

    spc += space;
    _spaces.push(spc);

    os << std::endl;

    std::string line = std::string("aiVector3D") + std::string(" -> ") + std::string(kind) + std::string(":");
    std::size_t sz = line.size();
    std::string underline = "";
    for (std::size_t i = 0; i < sz; ++i) underline += "=";

    os << spc << line << std::endl;
    os << spc << underline << std::endl;

    spc += space;
    _spaces.push(spc);

    for (unsigned int i = 0; i < num; ++i)
    {
        aiVector3D v = vec[i];
        os << spc << name <<"[" << std::setw(5) << i << "] = (" << std::setw(11) << v.x << ", " << std::setw(11) << v.y << ", " << std::setw(11) << v.z << ")" << std::endl;
    }

    _spaces.pop(); spc = _spaces.top();

    os << std::endl;

    _spaces.pop(); spc = _spaces.top();
}

void AssimpExaminer::doExamine(const char* kind, const char* name, const aiColor4D* col, unsigned int num, std::ofstream& os)
{
    std::string spc = _spaces.top();

    spc += space;
    _spaces.push(spc);

    os << std::endl;

    std::string line = std::string("aiColor4D") + std::string(" -> ") + std::string(kind) + std::string(":");
    std::size_t sz = line.size();
    std::string underline = "";
    for (std::size_t i = 0; i < sz; ++i) underline += "=";

    os << spc << line << std::endl;
    os << spc << underline << std::endl;

    spc += space;
    _spaces.push(spc);

    for (unsigned int i = 0; i < num; ++i)
    {
        aiColor4D c = col[i];
        os << spc << name <<"[" << std::setw(5) << i << "] = (" << std::setw(11) << c.r << ", " << std::setw(11) << c.g << ", " << std::setw(11) << c.b << ", " << std::setw(11) << c.a << ")" << std::endl;
    }

    _spaces.pop(); spc = _spaces.top();

    os << std::endl;

    _spaces.pop(); spc = _spaces.top();
}

#endif // OSG_WITH_ASSIMP



OSG_END_NAMESPACE
