/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <boost/filesystem.hpp>

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGQuaternion.h"
#include "OSGShaderUtility.h"
#include "OSGDescMaterial.h"
#include "OSGEnvironmentDesc.h"
#include "OSGMaterialDesc.h"
#include "OSGTextureDesc.h"
#include "OSGTextureObjChunk.h"
#include "OSGCubeTextureObjChunk.h"

//#define OSG_DESCMATERIAL_CUBEMAP_WRITE_TEST_IMAGES
//#define OSG_DESCMATERIAL_USE_PREFERRED_CLIP_PLANE_IMPL
OSG_BEGIN_NAMESPACE

DescMaterial::DescriptionInfo::DescriptionInfo()
: invalid               (true)
, envDesc               (NULL)
, matDesc               (NULL)
, textureDescs          ()
, textureDescsEnv       ()
, texMapDetails         (0)
, blockMemDetailsEnv    (0)
, blockMemDetails       (0)
, matMemDetails         (0)
, numUVTextures         (0)
, numEnvTextures        (0)
, numEquiTextures       (0)
, numCubeTextures       (0)
, numUVChannels         (0)
, maxTexUnit            (0)
, textureOccurrences    (TextureDesc::MAX_NUM_TEXTURE_TYPES, 0)
, textureSuppressed     (TextureDesc::MAX_NUM_TEXTURE_TYPES, false)
, textureEnvMapIsCubeMap(TextureDesc::MAX_NUM_TEXTURE_TYPES, false)
, hasEnvironmentMaps    (false)
, hasEquirectangMaps    (false)
, hasCubeMaps           (false)
, hasStackTexData       (false)
, hasSingleTexData      (false)
, idxFstUVTexture       (-1)
, idxFstEquiTexture     (-1)
, idxFstCubeTexture     (-1)
, vertOptVariant        (NoTextures)
{
}

DescMaterial::DescriptionInfo::DescriptionInfo(const DescriptionInfo& rhs)
: invalid               (rhs.invalid)
, envDesc               (rhs.envDesc)
, matDesc               (rhs.matDesc)
, textureDescs          (rhs.textureDescs)
, textureDescsEnv       (rhs.textureDescsEnv)
, texMapDetails         (rhs.texMapDetails)
, blockMemDetailsEnv    (rhs.blockMemDetailsEnv)
, blockMemDetails       (rhs.blockMemDetails)
, matMemDetails         (rhs.matMemDetails)
, numUVTextures         (rhs.numUVTextures)
, numEnvTextures        (rhs.numEnvTextures)
, numEquiTextures       (rhs.numEquiTextures)
, numCubeTextures       (rhs.numCubeTextures)
, numUVChannels         (rhs.numUVChannels)
, maxTexUnit            (rhs.maxTexUnit)
, textureOccurrences    (rhs.textureOccurrences)
, textureSuppressed     (rhs.textureSuppressed)
, textureEnvMapIsCubeMap(rhs.textureEnvMapIsCubeMap)
, hasEnvironmentMaps    (rhs.hasEnvironmentMaps)
, hasEquirectangMaps    (rhs.hasEquirectangMaps)
, hasCubeMaps           (rhs.hasCubeMaps)
, hasStackTexData       (rhs.hasStackTexData)
, hasSingleTexData      (rhs.hasSingleTexData)
, idxFstUVTexture       (rhs.idxFstUVTexture)
, idxFstEquiTexture     (rhs.idxFstEquiTexture)
, idxFstCubeTexture     (rhs.idxFstCubeTexture)
, vertOptVariant        (rhs.vertOptVariant)
{
}

void DescMaterial::DescriptionInfo::initialize(MaterialDesc* materialDesc, EnvironmentDesc* environmentDesc, Int32 texUnitOffset, CapabilitiesDesc* capabilities)
{
    if (invalid == false)
        return;

    invalid = false;

    matDesc = materialDesc;
    envDesc = environmentDesc;

    initTextureDescs(capabilities);

    texMapDetails  = getTexMapDetails(textureDescs);
    texMapDetails |= getTexMapDetails(textureDescsEnv);

    numUVTextures   = static_cast<UInt32>(textureDescs.size());
    numEnvTextures  = static_cast<UInt32>(textureDescsEnv.size());
    numUVChannels   = matDesc->getNumUVChannels();
    numEquiTextures = 0;
    numCubeTextures = 0;
    maxTexUnit      = 0;

    hasEnvironmentMaps = false;
    hasEquirectangMaps = false;
    hasCubeMaps        = false;
    hasStackTexData    = false;
    hasSingleTexData   = false;

    idxFstUVTexture    = -1;
    idxFstEquiTexture  = -1;
    idxFstCubeTexture  = -1;

    vertOptVariant = getVertOptVariant();

    textureOccurrences    .swap(TextureCountStore(TextureDesc::MAX_NUM_TEXTURE_TYPES, 0));
    textureEnvMapIsCubeMap.swap(     BooleanStore(TextureDesc::MAX_NUM_TEXTURE_TYPES, false));

    OSG_ASSERT(textureOccurrences    .size() == TextureDesc::MAX_NUM_TEXTURE_TYPES);
    OSG_ASSERT(textureEnvMapIsCubeMap.size() == TextureDesc::MAX_NUM_TEXTURE_TYPES);

    UInt32 idx = 0;

    TextureDescStore::const_iterator iter, end;

    iter = textureDescs.begin();
    end  = textureDescs.end  ();

    for (; iter != end; ++iter, ++idx)
    {
        TextureDesc* texDesc = *iter;

        UInt32 texType = texDesc->getTextureType();

        textureOccurrences[texType]++;

        Int32 texUnit = texDesc->getTexUnit();
        if (texUnit < 0         ) texUnit    = texUnitOffset++;
        if (texUnit > maxTexUnit) maxTexUnit = texUnit;

        if (idxFstUVTexture < 0) idxFstUVTexture = idx;
    }

    iter = textureDescsEnv.begin();
    end  = textureDescsEnv.end  ();

    for (; iter != end; ++iter, ++idx)
    {
        TextureDesc* texDesc = *iter;

        UInt32 texType = texDesc->getTextureType();

        textureOccurrences[texType]++;

        Int32 texUnit = texDesc->getTexUnit();
        if (texUnit < 0         ) texUnit    = texUnitOffset++;
        if (texUnit > maxTexUnit) maxTexUnit = texUnit;

        if (texDesc->isEnvironmentMap())
            hasEnvironmentMaps = true;

        if (texDesc->isEquirectangularMap())
        {
            numEquiTextures++;

            hasEquirectangMaps = true;
            if (idxFstEquiTexture < 0) idxFstEquiTexture = idx;

            textureEnvMapIsCubeMap[texType] = false;    // the cardinality of all environment maps is one!
        }

        if (texDesc->isCubeMap())
        {
            numCubeTextures++;

            hasCubeMaps = true;
            if (idxFstCubeTexture < 0) idxFstCubeTexture = idx;

            textureEnvMapIsCubeMap[texType] = true;     // the cardinality of all environment maps is one!
        }
    }

    iter = textureDescs.begin();
    end  = textureDescs.end  ();

    for (; iter != end; ++iter)
    {
        TextureDesc* texDesc = *iter;
        if (textureOccurrences[static_cast<std::size_t>(texDesc->getTextureType())] > 1)
            hasStackTexData = true;

        if (textureOccurrences[static_cast<std::size_t>(texDesc->getTextureType())] == 1)
            hasSingleTexData = true;
    }

    blockMemDetailsEnv = getBlockMemDetailsEnv();
    blockMemDetails    = getBlockMemDetails   ();
    matMemDetails      = getMatMemDetails     ();
}

void DescMaterial::DescriptionInfo::initTextureDescs(CapabilitiesDesc* capabilities)
{
    // We determine a list of valid (with respect to this implementation)
    // textures that the material will support. We will work solely with
    // this list in the following implementation.
    // Actually, we create two list, one for the textures with UV coordinates
    // and one for the evironment map textures that do not need a UV channel.

    textureDescs   .clear();
    textureDescsEnv.clear();

    TextureCountStore texturCounts(TextureDesc::MAX_NUM_TEXTURE_TYPES, 0);

    const MFUnrecTextureDescPtr* pMFTexDescPtr = matDesc->getMFTextureDesc();
    if (pMFTexDescPtr != NULL)
    {
        MFUnrecTextureDescPtr::const_iterator iter, end;

        iter = pMFTexDescPtr->begin();
        end  = pMFTexDescPtr->end  ();

        for (; iter != end; ++iter)
        {
            TextureDesc* texDesc = *iter;

            UInt32 textureType = texDesc->getTextureType();

            if (_textureSupported[textureType])
            {
                texturCounts[textureType]++;
            }
        }

        //
        // First, suppress some textures that are exclusive to each others...
        //
        if (capabilities && capabilities->isFallbackFixedFunction())
        {
            // Fallback case: use fixed function pipeline or minimal 2.1 Shader
            textureSuppressed          .swap(BooleanStore(TextureDesc::MAX_NUM_TEXTURE_TYPES, true));
            textureSupportFixedPipeline.swap(BooleanStore(TextureDesc::MAX_NUM_TEXTURE_TYPES, false));

            textureSuppressed          [TextureDesc::ALBEDO_TEXTURE] = false;
            textureSupportFixedPipeline[TextureDesc::ALBEDO_TEXTURE] = true;
        }
        else
        {
            textureSuppressed          .swap(BooleanStore(TextureDesc::MAX_NUM_TEXTURE_TYPES, false));
            textureSupportFixedPipeline.swap(BooleanStore(TextureDesc::MAX_NUM_TEXTURE_TYPES, false));

            textureSuppressed[TextureDesc::ROUGH_METAL_TEXTURE]      = true;
            textureSuppressed[TextureDesc::OCCL_ROUGH_METAL_TEXTURE] = true;

            if (texturCounts[TextureDesc::ROUGH_METAL_TEXTURE] > 0)
            {
                textureSuppressed[TextureDesc::ROUGH_METAL_TEXTURE]  = false;
                textureSuppressed[TextureDesc::METAL_TEXTURE]        = true;
                textureSuppressed[TextureDesc::ROUGH_TEXTURE]        = true;
            }
            else
            if (texturCounts[TextureDesc::OCCL_ROUGH_METAL_TEXTURE] > 0)
            {
                textureSuppressed[TextureDesc::OCCL_ROUGH_METAL_TEXTURE]  = false;
                textureSuppressed[TextureDesc::METAL_TEXTURE]             = true;
                textureSuppressed[TextureDesc::ROUGH_TEXTURE]             = true;
                textureSuppressed[TextureDesc::AMBIENT_OCCLUSION_TEXTURE] = true;
            }

            textureSuppressed[TextureDesc::ANISOTROPY_UV_TEXTURE] = true;

            if (texturCounts[TextureDesc::ANISOTROPY_UV_TEXTURE] > 0)
            {
                textureSuppressed[TextureDesc::ANISOTROPY_UV_TEXTURE] = false;
                textureSuppressed[TextureDesc::ANISOTROPY_U_TEXTURE]  = true;
                textureSuppressed[TextureDesc::ANISOTROPY_V_TEXTURE]  = true;
            }

            //
            // Secondly, we suppress some textures with respect to the shading model
            //
            UInt32 shadingModel = getShadingModel();
            if (shadingModel != MaterialDesc::COOK_TORRANCE_SHADING_MODEL)
            {
                textureSuppressed[TextureDesc::METAL_TEXTURE]                  = true;
                textureSuppressed[TextureDesc::ROUGH_METAL_TEXTURE]            = true;
                textureSuppressed[TextureDesc::OCCL_ROUGH_METAL_TEXTURE]       = true;

                if (shadingModel != MaterialDesc::OREN_NAYAR_SHADING_MODEL)
                {
                    textureSuppressed[TextureDesc::ROUGH_TEXTURE] = true;
                }

                textureSuppressed[TextureDesc::ANISOTROPY_UV_TEXTURE] = true;
                textureSuppressed[TextureDesc::ANISOTROPY_U_TEXTURE]  = true;
                textureSuppressed[TextureDesc::ANISOTROPY_V_TEXTURE]  = true;

                textureSuppressed[TextureDesc::IRRADIANCE_TEXTURE]  = true;
                textureSuppressed[TextureDesc::PRE_FILTER_TEXTURE]  = true;
                textureSuppressed[TextureDesc::BRDF_LUT_TEXTURE]    = true;
            }
        }

        //
        // Thirdly, prepare the final texture list
        //
        texturCounts.swap(TextureCountStore(TextureDesc::MAX_NUM_TEXTURE_TYPES, 0));

        iter = pMFTexDescPtr->begin();
        end  = pMFTexDescPtr->end  ();

        for (; iter != end; ++iter)
        {
            TextureDesc* texDesc = *iter;

            UInt32 textureType = texDesc->getTextureType();

            if (_textureSupported[textureType] && !textureSuppressed[textureType])
            {
                if (texturCounts[textureType] < _textureMaxCounts[textureType])
                {
                    if (texDesc->isEnvironmentMap())
                    {
                        // We currently do not support reflection/refraction maps from ASSIMP import,
                        // since we do not know how to handle them correctly.
                        if (texDesc->getEnvironmentMapType() != TextureDesc::OTHER_MAP)
                        {
                            texturCounts[textureType]++;
                            textureDescsEnv.push_back(texDesc);
                        }
                    }
                    else
                    {
                        if (matDesc->getNumUVChannels() > 0                         // If there are no UV channels then we can't evaluate texture
                         && texDesc->getMappingMode() == TextureDesc::UV_MAPPING)   // We do not support textures with non UV_MAPPING mode, currently
                        {
                            // We only support 2D UV coordinates, but if the multi field is empty we assume 2D coordinates
                            if (matDesc->getMFUVDimension()->empty() || matDesc->getUVDimension(texDesc->getUVChannel()) == 2)
                            {
                                texturCounts[textureType]++;
                                textureDescs.push_back(texDesc);
                            }
                        }
                    }
                }
            }
        }
    }
}

UInt32 DescMaterial::DescriptionInfo::getTexMapDetails(const TextureDescStore& textureDescs) const
{
    UInt32 result = 0;

    TextureDescStore::const_iterator iter = textureDescs.begin();
    TextureDescStore::const_iterator end  = textureDescs.end  ();

    for (; iter != end; ++iter)
    {
        TextureDesc* texDesc = *iter;

        UInt32 texType = texDesc->getTextureType();

        switch (texType)
        {
            case TextureDesc::ALBEDO_TEXTURE:
                result |= AlbedoTextures;
                break;
            case TextureDesc::SPECULAR_TEXTURE:
                result |= SpecularTextures;
                break;
            case TextureDesc::EMISSIVE_TEXTURE:
                result |= EmissiveTextures;
                break;
            case TextureDesc::SHININESS_TEXTURE:
                result |= ShininessTextures;
                break;
            case TextureDesc::OPACITY_TEXTURE:
                result |= OpacityTextures;
                break;
            case TextureDesc::NORMALS_TEXTURE:
                result |= NormalsTextures;
                break;
            case TextureDesc::HEIGHT_TEXTURE:
                result |= HeightTextures;
                break;
            case TextureDesc::DISPLACEMENT_TEXTURE:
                result |= DisplacementTextures;
                break;
            case TextureDesc::REFLECTION_TEXTURE:
                result |= ReflectionTextures;
                break;
            case TextureDesc::REFRACTION_TEXTURE:
                result |= RefractionTextures;
                break;
            case TextureDesc::ANISOTROPY_U_TEXTURE:
                result |= AnisotropyUTextures;
                break;
            case TextureDesc::ANISOTROPY_V_TEXTURE:
                result |= AnisotropyVTextures;
                break;
            case TextureDesc::ANISOTROPY_UV_TEXTURE:
                result |= AnisotropyUVTextures;
                break;
            case TextureDesc::AMBIENT_OCCLUSION_TEXTURE:
                result |= AmbientOcclusionTextures;
                break;
            case TextureDesc::ROUGH_TEXTURE:
                result |= RoughTextures;
                break;
            case TextureDesc::METAL_TEXTURE:
                result |= MetalTextures;
                break;
            case TextureDesc::ROUGH_METAL_TEXTURE:
                result |= RoughMetalTextures;
                break;
            case TextureDesc::OCCL_ROUGH_METAL_TEXTURE:
                result |= OcclRoughMetalTextures;
                break;
            case TextureDesc::IRRADIANCE_TEXTURE:
                result |= IrradianceTextures;
                break;
            case TextureDesc::PRE_FILTER_TEXTURE:
                result |= PreFilterTextures;
                break;
            case TextureDesc::BRDF_LUT_TEXTURE:
                result |= BrdfLutTextures;
                break;
            case TextureDesc::STANDARD_MATERIAL_TEXTURE:
                result |= StandardMaterialTextures;
                break;
        }
    }

    return result;
}

UInt32 DescMaterial::DescriptionInfo::getBlockMemDetailsEnv() const
{
    UInt32 result = 0;

    if (envDesc)
    {
        if (envDesc->getHasFeatureTonemapping())
        {
            switch (envDesc->getAutoExposureMode())
            {
                case EnvironmentDesc::MANUAL:
                    result |= ExposureBlockMember;
                    break;
                case EnvironmentDesc::KEY_VALUE:
                    result |= KeyValueBlockMember;
                    break;
                case EnvironmentDesc::AUTOMATIC:
                    break;
                case EnvironmentDesc::SATURATION_BASED:
                    result |= ApertureFNumberBlockMember;
                    result |= ShutterSpeedBlockMember;
                    result |= ISOBlockMember;
                    break;
                case EnvironmentDesc::STANDARD_OUTPUT_BASED:
                    result |= ApertureFNumberBlockMember;
                    result |= ShutterSpeedBlockMember;
                    result |= ISOBlockMember;
                    break;
            }

            switch (envDesc->getToneMappingMode())
            {
                case EnvironmentDesc::NO_TONE_MAPPING:
                    break;
                case EnvironmentDesc::LOGARITHMIC_TONE_MAPPING:
                    result |= WhiteLevelBlockMember;
                    break;
                case EnvironmentDesc::EXPONENTIAL_TONE_MAPPING:
                    result |= WhiteLevelBlockMember;
                    break;
                case EnvironmentDesc::DRAGO_LOGARITHMIC_TONE_MAPPING:
                    result |= WhiteLevelBlockMember;
                    result |= DragoBiasBlockMember;
                    break;
                case EnvironmentDesc::REINHARD_TONE_MAPPING:
                    break;
                case EnvironmentDesc::REINHARD_MODIFIED_TONE_MAPPING:
                    result |= WhiteLevelBlockMember;
                    break;
                case EnvironmentDesc::FILMIC_HABLE_TONE_MAPPING:
                    break;
                case EnvironmentDesc::FILMIC_UNCHARTED2_TONE_MAPPING:
                    break;
                case EnvironmentDesc::FILMIC_ACES_TONE_MAPPING:
                    break;
                case EnvironmentDesc::FILMIC_HEJ2015_TONE_MAPPING:
                    result |= WhiteLevelBlockMember;
                    break;
                case EnvironmentDesc::FILMIC_ACES_2_TONE_MAPPING:
                    break;
            }

            result |= SaturationBlockMember;
            result |= ContrastBlockMember;
            result |= FilterColorBlockMember;
        }

        if (envDesc->getHasFeatureGammaCorrection())
        {
            if (envDesc->getApplyGamma() && !envDesc->getAccurateGamma())
            {
                result |= GammaBlockMember;
            }
        }

        if (envDesc->getHasFeatureClassicLightExtension())
        {
            result |= GlobalAmbientIntBlockMember;
        }

        if (envDesc->getHasFeatureFog())
        {
        }
    }

    return result;
}

UInt32 DescMaterial::DescriptionInfo::getBlockMemDetails() const
{
    UInt32 shadingModel = getShadingModel();

    UInt32 result = 0;

    result |= TransparentBlockMember;
    result |= SpecularStrengthBlockMember;
    result |= EmissiveStrengthBlockMember;
    result |= OpacityCutOffBlockMember;

    if (hasTexMapDetail(ReflectionTextures))
    {
        result |= ReflectiveBlockMember;
        result |= ReflectivityBlockMember;
    }
    if (hasTexMapDetail(RefractionTextures))
    {
        result |= ReflectiveBlockMember;
        result |= ReflectivityBlockMember;
        result |= ReflectanceBlockMember;
    }

    if (shadingModel == MaterialDesc::COOK_TORRANCE_SHADING_MODEL)
    {
        result |= ReflectanceBlockMember;
    }

    if (hasTexMapDetail(HeightTextures)
     || hasTexMapDetail(DisplacementTextures))
    {
        result |= BumpScalingBlockMember;
    }

    if (shadingModel == MaterialDesc::GOOCH_SHADING_MODEL)
    {
        result |= GoochCoolBlockMember;
        result |= GoochWarmBlockMember;
        result |= GoochMixinBlockMember;
        result |= GoochCoolMixinBlockMember;
        result |= GoochWarmMixinBlockMember;
    }

    if (shadingModel == MaterialDesc::TOON_SHADING_MODEL)
    {
        result |= ToonLevelsBlockMember;
    }

    return result;
}

UInt32 DescMaterial::DescriptionInfo::getMatMemDetails() const
{
    UInt32 shadingModel = getShadingModel();

    UInt32 result = 0;

    if (numUVTextures > 0)
    {
        result |= TexCoordsMaterialMember;
    }

    result |= AlbedoMaterialMember;
    result |= DiffuseMaterialMember;
    result |= SpecularMaterialMember;
    result |= EmissiveMaterialMember;
    result |= ShininessMaterialMember;
    result |= OpacityMaterialMember;
    result |= NormalMaterialMember;

    if (needTangentSpace())
    {
        result |= TangentMaterialMember;
        result |= BitangentMaterialMember;
    }

    result |= SpecularStrengthMaterialMember;
    result |= EmissiveStrengthMaterialMember;

    if (hasTexMapDetail(ReflectionTextures))
    {
        result |= ReflectiveMaterialMember;
        result |= ReflectionMaterialMember;
    }

    if (hasTexMapDetail(RefractionTextures))
    {
        result |= ReflectiveMaterialMember;
        result |= RefractionMaterialMember;
    }

    if ((hasTexMapDetail(AnisotropyUTextures) && hasTexMapDetail(AnisotropyVTextures))
      || hasTexMapDetail(AnisotropyUVTextures))
    {
        result |= AnisotropyUMaterialMember;
        result |= AnisotropyVMaterialMember;
    }

    if (shadingModel == MaterialDesc::COOK_TORRANCE_SHADING_MODEL)
    {
        result |= RoughnessMaterialMember;
        result |= MetalnessMaterialMember;

        if (hasAmbientOcclusion() && !hasTexMapDetail(AmbientOcclusionTextures))
        {
            result |= AmbientOcclusionMaterialMember;
        }

        if (hasTexMapDetail(IrradianceTextures))
        {
            result |= IrradianceMaterialMember;
        }

        if (hasTexMapDetail(PreFilterTextures))
        {
            result |= PreFilterColorMaterialMember;
        }

        if (hasTexMapDetail(BrdfLutTextures))
        {
            result |= BrdfMaterialMember;
        }
    }

    if (shadingModel == MaterialDesc::OREN_NAYAR_SHADING_MODEL)
    {
        result |= RoughnessMaterialMember;
    }

    if (shadingModel == MaterialDesc::TOON_SHADING_MODEL)
    {
        result |= ToonScaleMaterialMember;
    }

   return result;
}

DescMaterial::VertexOptVariants DescMaterial::DescriptionInfo::getVertOptVariant() const
{
    bool   nonZeroChannel = false;
    bool   hasUVTransform = false;

    TextureDescStore::const_iterator iter = textureDescs.begin();
    TextureDescStore::const_iterator end  = textureDescs.end  ();

    for (; iter != end; ++iter)
    {
        TextureDesc* texDesc = *iter;

        if (texDesc->getUVChannel() != 0)
        {
            nonZeroChannel = true;
        }

        if (texDesc->getHasUVTransform())
        {
            hasUVTransform = true;
        }
    }

    VertexOptVariants variant = FullImplementation;

    if (!textureDescs.empty())
    {
        if (     nonZeroChannel == false && hasUVTransform == false)
        {
            variant = OptOnlyChannel0;
        }
        else if (nonZeroChannel == false && hasUVTransform == true )
        {
            variant = OptOnlyTransform;
        }
        else if (nonZeroChannel == true  && hasUVTransform == false)
        {
            variant = OptOnlyChannels;
        }
        else
        {
            variant = FullImplementation;
        }
    }
    else
    {
        variant = NoTextures;
    }

    return variant;
}

bool DescMaterial::DescriptionInfo::hasSpecularGlossinessWorkflow() const
{
    if (getShadingModel() == MaterialDesc::COOK_TORRANCE_SHADING_MODEL)
    {
        return matDesc->getPbrSpecularMode();
    }
    return false;
}

bool DescMaterial::DescriptionInfo::hasMetalnessRoughnessWorkflow() const
{
    if (getShadingModel() == MaterialDesc::COOK_TORRANCE_SHADING_MODEL)
    {
        return !matDesc->getPbrSpecularMode();
    }
    return false;
}

bool DescMaterial::DescriptionInfo::hasAmbientOcclusion() const
{
    return (    hasTexMapDetail(AmbientOcclusionTextures)
             || hasTexMapDetail(OcclRoughMetalTextures)
           );
}

bool DescMaterial::DescriptionInfo::hasSpecularGlossinessTexture() const
{
    return (   hasSpecularGlossinessWorkflow() 
            //&& !(
            //        hasTexMapDetail(RoughTextures)
            //     || hasTexMapDetail(OcclRoughMetalTextures)
            //    )
           );
}

UInt32 DescMaterial::DescriptionInfo::getShadingModel() const
{
    UInt32 shadingModel = MaterialDesc::NO_SHADING_MODEL;
    if (matDesc)
    {
        shadingModel  = matDesc->getShadingModel();
    
        UInt32 overrideModel = matDesc->getOverrideShadingModel();
        if (overrideModel != MaterialDesc::NO_SHADING_MODEL)
            shadingModel = overrideModel;
    }
    return shadingModel;
}

// Documentation for this class is emitted in the
// OSGDescMaterialBase.cpp file.
// To modify it, please change the .fcd file (OSGDescMaterial.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

DescMaterial::TextureCountStore DescMaterial::_textureMaxCounts;
DescMaterial::BooleanStore      DescMaterial::_textureSupported;
DescMaterial::BooleanStore      DescMaterial::_textureIsEnvMap;
DescMaterial::BooleanStore      DescMaterial::_hasFragBlockColorEntry;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DescMaterial::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _textureSupported.resize(TextureDesc::MAX_NUM_TEXTURE_TYPES);

        _textureSupported[TextureDesc::NONE_TEXTURE                         ] = false;
        _textureSupported[TextureDesc::UNKNOWN_TEXTURE                      ] = false;
        _textureSupported[TextureDesc::ALBEDO_TEXTURE                       ] = true;
        _textureSupported[TextureDesc::SPECULAR_TEXTURE                     ] = true;
        _textureSupported[TextureDesc::EMISSIVE_TEXTURE                     ] = true;
        _textureSupported[TextureDesc::SHININESS_TEXTURE                    ] = true;
        _textureSupported[TextureDesc::OPACITY_TEXTURE                      ] = true;
        _textureSupported[TextureDesc::NORMALS_TEXTURE                      ] = true;
        _textureSupported[TextureDesc::HEIGHT_TEXTURE                       ] = true;
        _textureSupported[TextureDesc::DISPLACEMENT_TEXTURE                 ] = true;
        _textureSupported[TextureDesc::REFLECTION_TEXTURE                   ] = true;
        _textureSupported[TextureDesc::REFRACTION_TEXTURE                   ] = true;
        _textureSupported[TextureDesc::ANISOTROPY_U_TEXTURE                 ] = false;
        _textureSupported[TextureDesc::ANISOTROPY_V_TEXTURE                 ] = false;
        _textureSupported[TextureDesc::ANISOTROPY_UV_TEXTURE                ] = false;
        _textureSupported[TextureDesc::AMBIENT_OCCLUSION_TEXTURE            ] = true;
        _textureSupported[TextureDesc::ROUGH_TEXTURE                        ] = true;
        _textureSupported[TextureDesc::METAL_TEXTURE                        ] = true;
        _textureSupported[TextureDesc::ROUGH_METAL_TEXTURE                  ] = true;
        _textureSupported[TextureDesc::OCCL_ROUGH_METAL_TEXTURE             ] = true;
        _textureSupported[TextureDesc::IRRADIANCE_TEXTURE                   ] = true;
        _textureSupported[TextureDesc::PRE_FILTER_TEXTURE                   ] = true;
        _textureSupported[TextureDesc::BRDF_LUT_TEXTURE                     ] = true;
        _textureSupported[TextureDesc::STANDARD_MATERIAL_TEXTURE            ] = true;
        _textureMaxCounts.resize(TextureDesc::MAX_NUM_TEXTURE_TYPES);

        _textureMaxCounts[TextureDesc::NONE_TEXTURE                         ] = 0;
        _textureMaxCounts[TextureDesc::UNKNOWN_TEXTURE                      ] = 0;
        _textureMaxCounts[TextureDesc::ALBEDO_TEXTURE                       ] = 4;
        _textureMaxCounts[TextureDesc::SPECULAR_TEXTURE                     ] = 4;
        _textureMaxCounts[TextureDesc::EMISSIVE_TEXTURE                     ] = 4;
        _textureMaxCounts[TextureDesc::SHININESS_TEXTURE                    ] = 4;
        _textureMaxCounts[TextureDesc::OPACITY_TEXTURE                      ] = 4;
        _textureMaxCounts[TextureDesc::NORMALS_TEXTURE                      ] = 1;
        _textureMaxCounts[TextureDesc::HEIGHT_TEXTURE                       ] = 1;
        _textureMaxCounts[TextureDesc::DISPLACEMENT_TEXTURE                 ] = 1;
        _textureMaxCounts[TextureDesc::REFLECTION_TEXTURE                   ] = 1;
        _textureMaxCounts[TextureDesc::REFRACTION_TEXTURE                   ] = 1;
        _textureMaxCounts[TextureDesc::ANISOTROPY_U_TEXTURE                 ] = 1;
        _textureMaxCounts[TextureDesc::ANISOTROPY_V_TEXTURE                 ] = 1;
        _textureMaxCounts[TextureDesc::ANISOTROPY_UV_TEXTURE                ] = 1;
        _textureMaxCounts[TextureDesc::AMBIENT_OCCLUSION_TEXTURE            ] = 1;
        _textureMaxCounts[TextureDesc::ROUGH_TEXTURE                        ] = 4;
        _textureMaxCounts[TextureDesc::METAL_TEXTURE                        ] = 4;
        _textureMaxCounts[TextureDesc::ROUGH_METAL_TEXTURE                  ] = 4;
        _textureMaxCounts[TextureDesc::OCCL_ROUGH_METAL_TEXTURE             ] = 1;
        _textureMaxCounts[TextureDesc::IRRADIANCE_TEXTURE                   ] = 1;
        _textureMaxCounts[TextureDesc::PRE_FILTER_TEXTURE                   ] = 1;
        _textureMaxCounts[TextureDesc::BRDF_LUT_TEXTURE                     ] = 1;
        _textureMaxCounts[TextureDesc::STANDARD_MATERIAL_TEXTURE            ] = 4;

        _hasFragBlockColorEntry.resize(TextureDesc::MAX_NUM_TEXTURE_TYPES);

        _hasFragBlockColorEntry[TextureDesc::NONE_TEXTURE                   ] = false;
        _hasFragBlockColorEntry[TextureDesc::UNKNOWN_TEXTURE                ] = false;
        _hasFragBlockColorEntry[TextureDesc::ALBEDO_TEXTURE                 ] = true;
        _hasFragBlockColorEntry[TextureDesc::SPECULAR_TEXTURE               ] = true;
        _hasFragBlockColorEntry[TextureDesc::EMISSIVE_TEXTURE               ] = true;
        _hasFragBlockColorEntry[TextureDesc::SHININESS_TEXTURE              ] = true;
        _hasFragBlockColorEntry[TextureDesc::OPACITY_TEXTURE                ] = true;
        _hasFragBlockColorEntry[TextureDesc::NORMALS_TEXTURE                ] = false;
        _hasFragBlockColorEntry[TextureDesc::HEIGHT_TEXTURE                 ] = false;
        _hasFragBlockColorEntry[TextureDesc::DISPLACEMENT_TEXTURE           ] = false;
        _hasFragBlockColorEntry[TextureDesc::REFLECTION_TEXTURE             ] = false;
        _hasFragBlockColorEntry[TextureDesc::REFRACTION_TEXTURE             ] = false;
        _hasFragBlockColorEntry[TextureDesc::ANISOTROPY_U_TEXTURE           ] = false;
        _hasFragBlockColorEntry[TextureDesc::ANISOTROPY_V_TEXTURE           ] = false;
        _hasFragBlockColorEntry[TextureDesc::ANISOTROPY_UV_TEXTURE          ] = false;
        _hasFragBlockColorEntry[TextureDesc::AMBIENT_OCCLUSION_TEXTURE      ] = false;
        _hasFragBlockColorEntry[TextureDesc::ROUGH_TEXTURE                  ] = true;
        _hasFragBlockColorEntry[TextureDesc::METAL_TEXTURE                  ] = true;
        _hasFragBlockColorEntry[TextureDesc::ROUGH_METAL_TEXTURE            ] = true;
        _hasFragBlockColorEntry[TextureDesc::OCCL_ROUGH_METAL_TEXTURE       ] = false;
        _hasFragBlockColorEntry[TextureDesc::IRRADIANCE_TEXTURE             ] = false;
        _hasFragBlockColorEntry[TextureDesc::PRE_FILTER_TEXTURE             ] = false;
        _hasFragBlockColorEntry[TextureDesc::BRDF_LUT_TEXTURE               ] = false;
        _hasFragBlockColorEntry[TextureDesc::STANDARD_MATERIAL_TEXTURE      ] = true;

        _textureIsEnvMap.resize(TextureDesc::MAX_NUM_TEXTURE_TYPES);

        _textureIsEnvMap[TextureDesc::NONE_TEXTURE                          ] = false;
        _textureIsEnvMap[TextureDesc::UNKNOWN_TEXTURE                       ] = false;
        _textureIsEnvMap[TextureDesc::ALBEDO_TEXTURE                        ] = false;
        _textureIsEnvMap[TextureDesc::SPECULAR_TEXTURE                      ] = false;
        _textureIsEnvMap[TextureDesc::EMISSIVE_TEXTURE                      ] = false;
        _textureIsEnvMap[TextureDesc::SHININESS_TEXTURE                     ] = false;
        _textureIsEnvMap[TextureDesc::OPACITY_TEXTURE                       ] = false;
        _textureIsEnvMap[TextureDesc::NORMALS_TEXTURE                       ] = false;
        _textureIsEnvMap[TextureDesc::HEIGHT_TEXTURE                        ] = false;
        _textureIsEnvMap[TextureDesc::DISPLACEMENT_TEXTURE                  ] = false;
        _textureIsEnvMap[TextureDesc::REFLECTION_TEXTURE                    ] = true;
        _textureIsEnvMap[TextureDesc::REFRACTION_TEXTURE                    ] = true;
        _textureIsEnvMap[TextureDesc::ANISOTROPY_U_TEXTURE                  ] = false;
        _textureIsEnvMap[TextureDesc::ANISOTROPY_V_TEXTURE                  ] = false;
        _textureIsEnvMap[TextureDesc::ANISOTROPY_UV_TEXTURE                 ] = false;
        _textureIsEnvMap[TextureDesc::AMBIENT_OCCLUSION_TEXTURE             ] = false;
        _textureIsEnvMap[TextureDesc::ROUGH_TEXTURE                         ] = false;
        _textureIsEnvMap[TextureDesc::METAL_TEXTURE                         ] = false;
        _textureIsEnvMap[TextureDesc::ROUGH_METAL_TEXTURE                   ] = false;
        _textureIsEnvMap[TextureDesc::OCCL_ROUGH_METAL_TEXTURE              ] = false;
        _textureIsEnvMap[TextureDesc::IRRADIANCE_TEXTURE                    ] = true;
        _textureIsEnvMap[TextureDesc::PRE_FILTER_TEXTURE                    ] = true;
        _textureIsEnvMap[TextureDesc::BRDF_LUT_TEXTURE                      ] = false;
        _textureIsEnvMap[TextureDesc::STANDARD_MATERIAL_TEXTURE             ] = false;
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DescMaterial::DescMaterial(void) :
    Inherited                   (     ),
    _info                       (     ),
    _fragEnvironmentChunk       (NULL ),
    _vertMaterialChunk          (NULL ),
    _fragMaterialChunk          (NULL ),
    _blendChunk                 (NULL ),
    _polygonChunk               (NULL ),
    _twoSidedLightChunk         (NULL ),
    _shadeModelChunk            (NULL ),
    _shaderProgramVariableChunk (NULL ),
    _materialChunk              (NULL ),
    _textureObjChunks           (     ),
    _textureObjChunksEnv        (     ),
    _textureEnvChunks           (     ),
    _textureTransformChunks     (     ),
    _isSRGBTextures             (     ),
    _textureUnits               (     ),
    _isTransparent              (false),
    _bUpdateMaterial            (false)
{
}

DescMaterial::DescMaterial(const DescMaterial &source) :
    Inherited                   (source                            ),
    _info                       (source._info                      ),
    _fragEnvironmentChunk       (source._fragEnvironmentChunk      ),
    _vertMaterialChunk          (source._vertMaterialChunk         ),
    _fragMaterialChunk          (source._fragMaterialChunk         ),
    _blendChunk                 (source._blendChunk                ),
    _polygonChunk               (source._polygonChunk              ),
    _twoSidedLightChunk         (source._twoSidedLightChunk        ),
    _shadeModelChunk            (source._shadeModelChunk           ),
    _shaderProgramVariableChunk (source._shaderProgramVariableChunk),
    _materialChunk              (source._materialChunk             ),
    _textureObjChunks           (source._textureObjChunks          ),
    _textureObjChunksEnv        (source._textureObjChunksEnv       ),
    _textureEnvChunks           (source._textureEnvChunks          ),
    _textureTransformChunks     (source._textureTransformChunks    ),
    _isSRGBTextures             (source._isSRGBTextures            ),
    _textureUnits               (source._textureUnits              ),
    _isTransparent              (source._isTransparent             ),
    _bUpdateMaterial            (source._bUpdateMaterial           )
{
}

DescMaterial::~DescMaterial(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DescMaterial::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    if((whichField & (  MaterialDescFieldMask | EnvironmentDescFieldMask )) != 0)
    {
        addMaterialDescObserver();
        addEnvironmentDescObserver();

        _bUpdateMaterial = true;
        _info.invalid    = true;
    }


    Inherited::changed(whichField, origin, details);
}

void DescMaterial::dump(      UInt32    ,
                        const BitVector ) const
{
    SLOG << "Dump DescMaterial NI" << std::endl;
}

void DescMaterial::resolveLinks(void)
{
    removeMaterialDescObserver();
    removeEnvironmentDescObserver();

    Inherited::resolveLinks();

    _vertMaterialChunk          = NULL;
    _fragMaterialChunk          = NULL;
    _fragEnvironmentChunk       = NULL;
    _blendChunk                 = NULL;
    _polygonChunk               = NULL;
    _twoSidedLightChunk         = NULL;
    //_depthChunk                 = NULL;
    //_logicOpChunk               = NULL;
    _shadeModelChunk            = NULL;
    //_lineChunk                  = NULL;
    _shaderProgramVariableChunk = NULL;
    _materialChunk              = NULL;

    _textureObjChunks           .clear();
    _textureObjChunksEnv        .clear();
    _textureEnvChunks           .clear();
    _textureTransformChunks     .clear();
}


/*----------------------------- Material Desc -------------------------------*/

void DescMaterial::removeMaterialDescObserver()
{
    MaterialDesc* matDesc = getMaterialDesc();
    if (matDesc)
    {
        matDesc->subChangedFunctor(
            boost::bind(&DescMaterial::changedMaterialDesc, this, _1, _2, _3));
    }
}

void DescMaterial::addMaterialDescObserver()
{
    MaterialDesc* matDesc = getMaterialDesc();
    if (matDesc)
    {
        if (matDesc->hasChangedFunctor(
            boost::bind(&DescMaterial::changedMaterialDesc, this, _1, _2, _3)) == false)
        {
            matDesc->addChangedFunctor(
                boost::bind(&DescMaterial::changedMaterialDesc, this, _1, _2, _3), "");
        }
    }
}

void DescMaterial::changedMaterialDesc(
    FieldContainer*     pFC, 
    ConstFieldMaskArg   whichField, 
    UInt32              origin)
{
    MaterialDesc* matDesc = dynamic_cast<MaterialDesc*>(pFC);
    if (matDesc)
    {
        _bUpdateMaterial = true;
        _info.invalid    = true;

        rebuildState();
    }
}

/*----------------------------- Environment Desc ----------------------------*/

void DescMaterial::removeEnvironmentDescObserver()
{
    EnvironmentDesc* envDesc = getEnvironmentDesc();
    if (envDesc)
    {
        envDesc->subChangedFunctor(
            boost::bind(&DescMaterial::changedEnvironmentDesc, this, _1, _2, _3));
    }
}

void DescMaterial::addEnvironmentDescObserver()
{
    EnvironmentDesc* envDesc = getEnvironmentDesc();
    if (envDesc)
    {
        if (envDesc->hasChangedFunctor(
            boost::bind(&DescMaterial::changedEnvironmentDesc, this, _1, _2, _3)) == false)
        {
            envDesc->addChangedFunctor(
                boost::bind(&DescMaterial::changedEnvironmentDesc, this, _1, _2, _3), "");
        }
    }
}

void DescMaterial::changedEnvironmentDesc(
    FieldContainer*     pFC, 
    ConstFieldMaskArg   whichField, 
    UInt32              origin)
{
    EnvironmentDesc* envDesc = dynamic_cast<EnvironmentDesc*>(pFC);
    if (envDesc)
    {
        _bUpdateMaterial = true;
        _info.invalid    = true;

        rebuildState();
    }
}

/*--------------------------------- State -----------------------------------*/

void DescMaterial::prepareLocalChunks(MaterialDesc* matDesc)
{
    if (!matDesc)
        return;

    if (_vertMaterialChunk == NULL && !(isFallbackFixedFunction() || isFallbackShader2()))
    {
        _vertMaterialChunk = UniformBufferObjStd140Chunk::createLocal();
    }

    if (_fragEnvironmentChunk == NULL && anyEnvBlockMember(AllEnvBlockMemberDetails) 
                                      && !(isFallbackFixedFunction() || isFallbackShader2()))
    {
        _fragEnvironmentChunk = UniformBufferObjStd140Chunk::createLocal();
    }

    if (_fragMaterialChunk == NULL && !(isFallbackFixedFunction() || isFallbackShader2()))
    {
        _fragMaterialChunk = UniformBufferObjStd140Chunk::createLocal();
    }

    if (_blendChunk == NULL)
    {
        _blendChunk = BlendChunk::createLocal();
    }

    if (_polygonChunk == NULL)
    {
        _polygonChunk = PolygonChunk::createLocal();
    }

    if (_twoSidedLightChunk == NULL)
    {
        _twoSidedLightChunk = TwoSidedLightingChunk::createLocal();
    }

    if (_shadeModelChunk == NULL && (isFallbackFixedFunction() || isFallbackShader2()))
    {
        _shadeModelChunk = ShadeModelChunk::createLocal();
    }
#ifdef OSG_DESCMATERIAL_USE_PREFERRED_CLIP_PLANE_IMPL
    if (_shaderProgramVariableChunk == NULL)
    {
        _shaderProgramVariableChunk = ShaderProgramVariableChunk::createLocal();

        if (isFallbackShader2())
        {
            if (anyEnvBlockMember(AllEnvBlockMemberDetails))
            {
                addEnvShaderUniformVariables();
            }

            addShaderUniformVariables();
        }

        addClipPlaneUniformVariables();
    }
#else
    if (_shaderProgramVariableChunk == NULL && isFallbackShader2())
    {
        _shaderProgramVariableChunk = ShaderProgramVariableChunk::createLocal();

        if (anyEnvBlockMember(AllEnvBlockMemberDetails))
        {
            addEnvShaderUniformVariables();
        }

        addShaderUniformVariables();
    }
#endif

    if (_materialChunk == NULL && isFallbackFixedFunction())
    {
        _materialChunk = MaterialChunk::createLocal();
    }

    if ( _info.textureDescs   .size() != _textureObjChunks   .size() 
      || _info.textureDescsEnv.size() != _textureObjChunksEnv.size())
    {
        _isSRGBTextures         .clear();
        _textureUnits           .clear();
        _textureObjChunks       .clear();
        _textureTransformChunks .clear();
        _textureEnvChunks       .clear();
        _textureObjChunksEnv    .clear();

        TextureDescStore::const_iterator iter, end;

        iter = _info.textureDescs.begin();
        end  = _info.textureDescs.end  ();
    
        for (; iter != end; ++iter)
        {
            TextureDesc* texDesc = *iter;

            prepareLocalChunks(texDesc);
        }

        iter = _info.textureDescsEnv.begin();
        end  = _info.textureDescsEnv.end  ();
    
        for (; iter != end; ++iter)
        {
            TextureDesc* texDesc = *iter;

            prepareLocalChunksEnv(texDesc);
        }
    }
}

void DescMaterial::prepareLocalChunks(TextureDesc* texDesc)
{
    if (!texDesc)
        return;

    bool hasUVTransform = texDesc->getHasUVTransform();
    bool isSRGBTexture  = texDesc->getIsSRGBTexture ();

    TextureObjChunkUnrecPtr textureObjChunk = TextureObjChunk::createLocal();
    _textureObjChunks.push_back(textureObjChunk);

    ImageUnrecPtr image = texDesc->getTexImage();

    isSRGBTexture = setTexData(texDesc, image, isSRGBTexture, textureObjChunk);
    textureObjChunk->setImage(image);

    _isSRGBTextures.push_back(isSRGBTexture);
    _textureUnits  .push_back(texDesc->getTexUnit());

    if (_info.textureSupportFixedPipeline[texDesc->getTextureType()])
    {
        TextureTransformChunkUnrecPtr textureTransformChunk = TextureTransformChunk::createLocal();
        _textureTransformChunks.push_back(textureTransformChunk);

        TextureEnvChunkUnrecPtr textureEnvChunk = TextureEnvChunk::createLocal();
        textureEnvChunk->setEnvMode(texDesc->getOperation() == TextureDesc::REPLACE_OPERATION ? GL_REPLACE : GL_MODULATE);
        _textureEnvChunks.push_back(textureEnvChunk);

        Matrix texture_matrix = texDesc->getMatrix();
        textureTransformChunk->setMatrix(texture_matrix); 

        _textureUnits[_textureEnvChunks.size()-1] = texDesc->getUVChannel();
    }
    else
    {
        _textureEnvChunks      .push_back(nullptr);
        _textureTransformChunks.push_back(nullptr);
    }
}

void DescMaterial::prepareLocalChunksEnv(TextureDesc* texDesc)
{
    if (!texDesc)
        return;

    bool isSRGBTexture  = texDesc->getIsSRGBTexture();

    // ToDo
    //
    // isEnvironmentMap
    // isEquirectangularMap
    // isCubeMap
    //
    if (texDesc->isCubeMap())
    {
        CubeTextureObjChunkUnrecPtr textureObjChunk = CubeTextureObjChunk::createLocal();
        _textureObjChunksEnv.push_back(textureObjChunk);

        ImageStore images(6, NULL);

        if (getImages(texDesc, images))
        {
            OSG_ASSERT( images[TextureDesc::POS_X] != NULL && images[TextureDesc::POS_Y] != NULL && images[TextureDesc::POS_Z] != NULL
                     && images[TextureDesc::NEG_X] != NULL && images[TextureDesc::NEG_Y] != NULL && images[TextureDesc::NEG_Z] != NULL );

            ImageUnrecPtr image_pos_x = images[TextureDesc::POS_X];
            ImageUnrecPtr image_pos_y = images[TextureDesc::POS_Y];
            ImageUnrecPtr image_pos_z = images[TextureDesc::POS_Z];
            ImageUnrecPtr image_neg_x = images[TextureDesc::NEG_X];
            ImageUnrecPtr image_neg_y = images[TextureDesc::NEG_Y];
            ImageUnrecPtr image_neg_z = images[TextureDesc::NEG_Z];

            isSRGBTexture = setTexData(texDesc, image_pos_x, isSRGBTexture, textureObjChunk);
            isSRGBTexture = setTexData(texDesc, image_pos_y, isSRGBTexture, textureObjChunk);
            isSRGBTexture = setTexData(texDesc, image_pos_z, isSRGBTexture, textureObjChunk);
            isSRGBTexture = setTexData(texDesc, image_neg_x, isSRGBTexture, textureObjChunk);
            isSRGBTexture = setTexData(texDesc, image_neg_y, isSRGBTexture, textureObjChunk);
            isSRGBTexture = setTexData(texDesc, image_neg_z, isSRGBTexture, textureObjChunk);

            textureObjChunk->setPosXImage(image_pos_x);
            textureObjChunk->setPosYImage(image_pos_y);
            textureObjChunk->setPosZImage(image_pos_z);
            textureObjChunk->setNegXImage(image_neg_x);
            textureObjChunk->setNegYImage(image_neg_y);
            textureObjChunk->setImage    (image_neg_z);
        }
    }
    else
    {
        TextureObjChunkUnrecPtr textureObjChunk = TextureObjChunk::createLocal();
        _textureObjChunksEnv.push_back(textureObjChunk);

        ImageUnrecPtr image = texDesc->getTexImage();

        isSRGBTexture = setTexData(texDesc, image, isSRGBTexture, textureObjChunk);
        textureObjChunk->setImage(image);
    }

    _isSRGBTextures.push_back(isSRGBTexture);
    _textureUnits  .push_back(texDesc->getTexUnit());
}

void DescMaterial::rebuildState(void)
{
    Inherited::rebuildState();

    if (getCapabilitiesDesc() == NULL)
    {
        CapabilitiesDescUnrecPtr capabilitiesDesc = CapabilitiesDesc::createLocal();
        setCapabilitiesDesc(capabilitiesDesc);
    }

    EnvironmentDesc* envDesc = getEnvironmentDesc();
    MaterialDesc*    matDesc = getMaterialDesc   ();

    if (!matDesc)
        return;

    _info.initialize(matDesc, envDesc, getTexUnitOffsetRT(), getCapabilitiesDesc());

    prepareLocalChunks(matDesc);
    updateState       (matDesc, envDesc);

    bool transparent = isTransparent();
    bool twosided    = false;

    if (_vertMaterialChunk != NULL && !(isFallbackFixedFunction() || isFallbackShader2()))
    {
        _pState->addChunk(_vertMaterialChunk, getVertMaterialBindingPnt());
    }

    if (_fragEnvironmentChunk != NULL && anyEnvBlockMember(AllEnvBlockMemberDetails) 
                                      && !(isFallbackFixedFunction() || isFallbackShader2()))
    {
        _pState->addChunk(_fragEnvironmentChunk, getFragEnvironmentBindingPnt());
    }

    if (_fragMaterialChunk != NULL && !(isFallbackFixedFunction() || isFallbackShader2()))
    {
        _pState->addChunk(_fragMaterialChunk, getFragMaterialBindingPnt());
    }

    if (_blendChunk != NULL)
    {
        UInt32 blendMode = matDesc->getBlendMode();

        bool doBlend = false;

        switch (blendMode)
        {
            case MaterialDesc::DEFAULT_BLEND_MODE:
                if (transparent)
                {
                    _blendChunk->setSrcFactor (GL_SRC_ALPHA);
                    _blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
                    doBlend = true;
                }
                break;
            case MaterialDesc::ADDITIVE_BLEND_MODE:
                _blendChunk->setSrcFactor (GL_ONE);
                _blendChunk->setDestFactor(GL_ONE);
                doBlend = true;
                break;
            case MaterialDesc::MULTIPLICATIVE_BLEND_MODE:
                _blendChunk->setSrcFactor (GL_DST_COLOR);
                _blendChunk->setDestFactor(GL_ZERO);
                doBlend = true;
                break;
            case MaterialDesc::INTERPOLATION_BLEND_MODE:
                _blendChunk->setSrcFactor (GL_SRC_ALPHA);
                _blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
                doBlend = true;
                break;
            default:
                if (transparent)
                {
                    _blendChunk->setSrcFactor (GL_SRC_ALPHA);
                    _blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
                    doBlend = true;
                }

        }

        if (doBlend)
        {
            _pState->addChunk(_blendChunk);
        }
    }

    if (_polygonChunk != NULL)
    {
        GLenum cullFace     = matDesc->getCullFace        ();
        GLenum frontFace    = matDesc->getFrontFace       ();
        GLenum frontMode    = matDesc->getFrontMode       ();
        GLenum backMode     = matDesc->getBackMode        ();
        Real32 offsetFactor = matDesc->getOffsetFactor    ();
        Real32 offsetBias   = matDesc->getOffsetBias      ();
        bool   offsetPoint  = matDesc->getOffsetPointMode ();
        bool   offsetLine   = matDesc->getOffsetLineMode  ();
        bool   offsetFill   = matDesc->getOffsetFillMode  ();

        if (cullFace == GL_NONE)
            twosided = true;

        if (offsetPoint == false && offsetLine == false && offsetFill == false)
        {
            if (offsetFactor != 0.f || offsetBias != 0.f)
            {
                if (cullFace == GL_BACK || cullFace == GL_NONE)
                {
                    switch (frontMode)
                    {
                        case GL_FILL:
                            offsetFill = true;
                            break;
                        case GL_LINE:
                            offsetLine = true;
                            break;
                        case GL_POINT:
                            offsetPoint = true;
                            break;
                    }
                }
                if (cullFace == GL_FRONT || cullFace == GL_NONE)
                {
                    switch (backMode)
                    {
                        case GL_FILL:
                            offsetFill = true;
                            break;
                        case GL_LINE:
                            offsetLine = true;
                            break;
                        case GL_POINT:
                            offsetPoint = true;
                            break;
                    }
                }
            }
        }

        _polygonChunk->setCullFace      (cullFace    );
        _polygonChunk->setFrontFace     (frontFace   );
        _polygonChunk->setFrontMode     (frontMode   );
        _polygonChunk->setBackMode      (backMode    );
        _polygonChunk->setOffsetFactor  (offsetFactor);
        _polygonChunk->setOffsetBias    (offsetBias  );
        _polygonChunk->setOffsetFill    (offsetPoint );
        _polygonChunk->setOffsetFill    (offsetLine  );
        _polygonChunk->setOffsetFill    (offsetFill  );
        
        _pState->addChunk(_polygonChunk);
    }

    if (_twoSidedLightChunk != NULL && twosided)
    {
        _pState->addChunk(_twoSidedLightChunk);
    }

    if (_shadeModelChunk != NULL && (isFallbackFixedFunction() || isFallbackShader2()))
    {
        _shadeModelChunk->setShadeModel(matDesc->getFlatShadingMode() ? GL_FLAT : GL_SMOOTH);
        _pState->addChunk(_shadeModelChunk);
    }

    if (_materialChunk != NULL && isFallbackFixedFunction())
    {
        //
        // Remark: the material chunk is only used in order to have a non
        //         shader fallback to classic fixed function pipeline
        //         OpenGL. In that case we do not have to apply sRGB
        //         conversion to linear color space.
        //
        Color4f color;

        const Color3f& emissive        = matDesc->getEmissive     ();
        const Color3f& albedo          = matDesc->getAlbedo       ();
        const Color3f& specular        = matDesc->getSpecular     ();
        Real32         shininess       = matDesc->getShininess    ();
        Real32         opacity         = matDesc->getOpacity      ();
        bool           lit             = true;
        UInt32         colorMaterial   = GL_DIFFUSE;

        color.setValuesRGBA(emissive[0], emissive[1], emissive[2], 1.0);
        _materialChunk->setEmission(color);

        color.setValuesRGBA( albedo[0]/3.0f,  albedo[1]/3.0f,  albedo[2]/3.0f, 1.0);
        _materialChunk->setAmbient(color);

        color.setValuesRGBA( albedo[0],  albedo[1],  albedo[2], opacity);
        _materialChunk->setDiffuse(color);
            
        color.setValuesRGBA(specular[0], specular[1], specular[2], 1.0);
        _materialChunk->setSpecular(color);
            
        _materialChunk->setShininess(osgMin(shininess, 128.f));
        _materialChunk->setLit(lit);
        _materialChunk->setColorMaterial(colorMaterial);

        _pState->addChunk(_materialChunk);
    }

    Int32 texUnitOffset = getTexUnitOffsetRT();

    std::size_t sz = _textureObjChunks.size();

    UInt32 idx = 0;

    for (Int32 i = 0; i < sz; ++i, ++idx)
    {
        Int32 texUnit = _textureUnits[idx] >= 0 ? _textureUnits[idx] : texUnitOffset++;

        TextureObjChunk* textureObjChunk = _textureObjChunks[i];
        if (textureObjChunk != NULL)
            _pState->addChunk(textureObjChunk, texUnit);

        TextureTransformChunk* textureTransformChunk = _textureTransformChunks[i];
        if (textureTransformChunk != NULL)
            _pState->addChunk(textureTransformChunk, texUnit);

        TextureEnvChunk* textureEnvChunk = _textureEnvChunks[i];
        if (textureEnvChunk != NULL)
            _pState->addChunk(textureEnvChunk, texUnit);
    }

    sz = _textureObjChunksEnv.size();

    for (Int32 i = 0; i < sz; ++i, ++idx)
    {
        Int32 texUnit = _textureUnits[idx] >= 0 ? _textureUnits[idx] : texUnitOffset++;

        TextureObjChunk* textureObjChunk = _textureObjChunksEnv[i];

        if (textureObjChunk != NULL)
        {
            _pState->addChunk(textureObjChunk, texUnit);
        }
    }
#ifdef OSG_DESCMATERIAL_USE_PREFERRED_CLIP_PLANE_IMPL
    if (_shaderProgramVariableChunk != NULL)
    {
        _pState->addChunk(_shaderProgramVariableChunk);
    }
#else
    if (_shaderProgramVariableChunk != NULL && isFallbackShader2())
    {
        _pState->addChunk(_shaderProgramVariableChunk);
    }
#endif
}

/*----------------------------- Update State --------------------------------*/

void DescMaterial::updateState(MaterialDesc* matDesc, EnvironmentDesc* envDesc)
{
#ifdef OSG_DESCMATERIAL_USE_PREFERRED_CLIP_PLANE_IMPL
    if (   _bUpdateMaterial
        && _shaderProgramVariableChunk != NULL 
        )
    {
        updateClipPlaneUniformVariables(envDesc);
    }
#endif
    if (    _bUpdateMaterial 
         && _shaderProgramVariableChunk != NULL 
         && isFallbackShader2())
    {
        if (anyEnvBlockMember(AllEnvBlockMemberDetails))
        {
            updateEnvShaderUniformVariables(envDesc);
        }

        updateShaderUniformVariables(matDesc);
    }
    else
    {
        if (    _bUpdateMaterial 
             && _fragEnvironmentChunk != NULL 
             && anyEnvBlockMember(AllEnvBlockMemberDetails) 
             && !(isFallbackFixedFunction() || isFallbackShader2()))
        {
            std::vector<UInt8> frag_buffer = createEnvFragBuffer(envDesc);
            _fragEnvironmentChunk->editMFBuffer()->setValues(frag_buffer);
        }

        if (    _bUpdateMaterial 
             && _vertMaterialChunk != NULL 
             && _fragMaterialChunk != NULL 
             && !(isFallbackFixedFunction() || isFallbackShader2()))
        {
            std::vector<UInt8> vert_buffer = createVertBuffer(matDesc);
            _vertMaterialChunk->editMFBuffer()->setValues(vert_buffer);

            std::vector<UInt8> frag_buffer = createFragBuffer(matDesc);
            _fragMaterialChunk->editMFBuffer()->setValues(frag_buffer);

            _isTransparent = isTransparent();
        }
    }

    _bUpdateMaterial = false;
}

bool DescMaterial::isTransparent(void) const
{
    if (_bUpdateMaterial)
    {
        MaterialDesc* matDesc = getMaterialDesc();
        if (!matDesc)
            return false;

        if (matDesc->getOpacityMode()==MaterialDesc::BLEND_OPACITY_MODE)
            return true;
        else if (  (matDesc->getOpacityMode()==MaterialDesc::OPAQUE_OPACITY_MODE)
                 ||(matDesc->getOpacityMode()==MaterialDesc::MASK_OPACITY_MODE))
            return false;

        bool transparent = matDesc->getOpacity() != 1.0;
        if (!transparent)
        {
            TextureDescStore::const_iterator iter = _info.textureDescs.begin();
            TextureDescStore::const_iterator end  = _info.textureDescs.end  ();

            for (; iter != end; ++iter)
            {
                TextureDesc* texDesc = *iter;
                if (texDesc->getTextureType() == TextureDesc::OPACITY_TEXTURE)
                {
                    transparent = true;
                    break;
                }
            }
        }

        return transparent;
    }

    return (_isTransparent || Inherited::isTransparent());
}

/*---------------------------- Vertex Buffer --------------------------------*/

std::size_t DescMaterial::calcVertBufferSize() const
{
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset
    
    switch (_info.vertOptVariant)
    {
        case NoTextures:
            //struct TextureUVData
            //{
            //};
            break;
        case FullImplementation:
            //struct TextureUVData
            //{
            //    int  channel;
            //    bool hasTransform;
            //    mat4 transform;
            //};
            ao = alignOffset( 4, bo); bo = ao + sizeof(Int32);  // int channel
            ao = alignOffset( 4, bo); bo = ao + sizeof(Int32);  // bool hasTransform

            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);  // mat4 transform
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
            break;
        case OptOnlyTransform:
            //struct TextureUVData
            //{
            //    bool hasTransform;
            //    mat4 transform;
            //};
            ao = alignOffset( 4, bo); bo = ao + sizeof(Int32);  // bool hasTransform

            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);  // mat4 transform
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao + sizeof(Vec4f);
            ao = alignOffset(16, bo); bo = ao;
            break;
        case OptOnlyChannels:
            //struct TextureUVData
            //{
            //    int channel;
            //};
            ao = alignOffset( 4, bo); bo = ao + sizeof(Int32); // int channel
            break;
        case OptOnlyChannel0:
            //struct TextureUVData
            //{
            //};

            break;
    }

    ao = alignOffset(16, bo); bo = ao;                  // padding

    std::size_t sz = _info.textureDescs.size();

    ao *= sz;                 bo = ao;                  // array
    ao = alignOffset(16, bo); bo = ao;                  // padding
    
    return ao;
}

std::vector<UInt8> DescMaterial::createVertBuffer(MaterialDesc* matDesc) const
{
    std::size_t size = calcVertBufferSize();
    
    std::vector<UInt8> buffer(size, 0);
    
    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    TextureDescStore::const_iterator iter = _info.textureDescs.begin();
    TextureDescStore::const_iterator end  = _info.textureDescs.end  ();

    for (; iter != end; ++iter)
    {
        TextureDesc* texDesc = *iter;

        UInt32 channel        = texDesc->getUVChannel();
        bool   hasUVTransform = texDesc->getHasUVTransform();
        Matrix uvTransform;

        if (hasUVTransform)
        {
            Vec2f  t = texDesc->getTranslate();
            Vec2f  s = texDesc->getScale();
            Real32 r = texDesc->getRotate();

            Real32 tx = t.x();
            Real32 ty = t.y();
            Real32 tz = 0.f;

            Real32 sx = s.x();
            Real32 sy = s.y();
            Real32 sz = 1.f;

            Vec3f axis(0.f, 0.f, 1.f);

            Int32 intFraction = static_cast<Int32>(r / OSG::TwoPi);
            if (intFraction)
            {
                r -= intFraction * OSG::TwoPi;
            }
                
            if (r < 0.f)
                r += OSG::TwoPi;

            Quaternion rotation(axis, r);

            Matrix S, R, T;

            S.setScale(sx, sy, sz);
            R.setRotate(rotation);
            T.setTranslate(tx, ty, tz);

            uvTransform = S;
            uvTransform.mult(R);
            uvTransform.mult(T);
        }

        switch (_info.vertOptVariant)
        {
            case NoTextures:
                //struct TextureUVData
                //{
                //};
                break;
            case FullImplementation:
                //struct TextureUVData
                //{
                //    int channel;
                //    bool hasTransform;
                //    mat4 transform;
                //};
                ao = alignOffset( 4, bo); *(reinterpret_cast<Int32*>(&buffer[0] + ao)) = Int32(channel);        bo = ao + sizeof(Int32);   // int channel
                ao = alignOffset( 4, bo); *(reinterpret_cast<Int32*>(&buffer[0] + ao)) = Int32(hasUVTransform); bo = ao + sizeof(Int32);   // bool hasTransform

                ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &uvTransform[0][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);             // mat4 transform
                ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &uvTransform[1][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
                ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &uvTransform[2][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
                ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &uvTransform[3][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
                ao = alignOffset(16, bo); bo = ao;
                break;
            case OptOnlyTransform:
                //struct TextureUVData
                //{
                //    bool hasTransform;
                //    mat4 transform;
                //};
                ao = alignOffset( 4, bo); *(reinterpret_cast<Int32*>(&buffer[0] + ao)) = Int32(hasUVTransform); bo = ao + sizeof(Int32);   // bool hasTransform

                ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &uvTransform[0][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);             // mat4 transform
                ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &uvTransform[1][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
                ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &uvTransform[2][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
                ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &uvTransform[3][0], sizeof(Vec4f)); bo = ao + sizeof(Vec4f);
                ao = alignOffset(16, bo); bo = ao;

                break;
            case OptOnlyChannels:
                //struct TextureUVData
                //{
                //    int channel;
                //};
                ao = alignOffset( 4, bo); *(reinterpret_cast<Int32*>(&buffer[0] + ao)) = Int32(channel);        bo = ao + sizeof(Int32);   // int channel
                break;
            case OptOnlyChannel0:
                //struct TextureUVData
                //{
                //};

                break;
        }

        ao = alignOffset(16, bo); bo = ao;  // padding
    }

    return buffer;
}

void DescMaterial::addClipPlaneUniformVariables()
{
    const UInt32 maxClipPlane = getMaxNumClipPlanes();
    MFVec4f clipPlanes(maxClipPlane);
    
    for (UInt32 i = 0; i < maxClipPlane; ++i)
        clipPlanes[i] = Vec4f(0.f, 0.f, 0.f, 0.f);

    _shaderProgramVariableChunk->addUniformVariable<MFVec4f>("uClipPlanes", clipPlanes);
}

void DescMaterial::updateClipPlaneUniformVariables(EnvironmentDesc* envDesc)
{
    const UInt32 maxClipPlane = getMaxNumClipPlanes();

     MFVec4f clipPlanes(maxClipPlane);
    
    for (UInt32 i = 0; i < maxClipPlane; ++i)
        clipPlanes[i] = Vec4f(0.f, 0.f, 0.f, 0.f);

    UInt32 sz = osgMin(envDesc->getMFClipPlanes()->size32(), maxClipPlane);
    for (UInt32 i = 0; i < sz; ++i)
        clipPlanes[i] = envDesc->getClipPlanes(i);

    _shaderProgramVariableChunk->updateUniformVariable<MFVec4f>("uClipPlanes", clipPlanes);
}

/*--------------------------- Fragment Buffer -------------------------------*/

void DescMaterial::addEnvShaderUniformVariables()
{
    //struct FragEnvironmentBlock
    //{
    //    float   exposure;
    //    float   keyValue;
    //    float   apertureFNumber;
    //    float   shutterSpeed;
    //    float   iso;
    //    float   whiteLevel;
    //    float   dragoBias;
    //    float   saturation;
    //    float   contrast;
    //    float   gamma;
    //    vec3    filterColor;
    //    vec3    ambientIntensity;
    //};
    //
    //uniform FragEnvironmentBlock environment;

    if (hasEnvBlockMember(ExposureBlockMember        )) { _shaderProgramVariableChunk->addUniformVariable("environment.exposure",         0.f      ); }  // float exposure
    if (hasEnvBlockMember(KeyValueBlockMember        )) { _shaderProgramVariableChunk->addUniformVariable("environment.keyValue",         0.f      ); }  // float keyValue
    if (hasEnvBlockMember(ApertureFNumberBlockMember )) { _shaderProgramVariableChunk->addUniformVariable("environment.apertureFNumber",  0.f      ); }  // float apertureFNumber
    if (hasEnvBlockMember(ShutterSpeedBlockMember    )) { _shaderProgramVariableChunk->addUniformVariable("environment.shutterSpeed",     0.f      ); }  // float shutterSpeed
    if (hasEnvBlockMember(ISOBlockMember             )) { _shaderProgramVariableChunk->addUniformVariable("environment.iso",              0.f      ); }  // float iso
    if (hasEnvBlockMember(WhiteLevelBlockMember      )) { _shaderProgramVariableChunk->addUniformVariable("environment.whiteLevel",       0.f      ); }  // float whiteLevel
    if (hasEnvBlockMember(DragoBiasBlockMember       )) { _shaderProgramVariableChunk->addUniformVariable("environment.dragoBias",        0.f      ); }  // float dragoBias
    if (hasEnvBlockMember(SaturationBlockMember      )) { _shaderProgramVariableChunk->addUniformVariable("environment.saturation",       0.f      ); }  // float saturation
    if (hasEnvBlockMember(ContrastBlockMember        )) { _shaderProgramVariableChunk->addUniformVariable("environment.contrast",         0.f      ); }  // float contrast
    if (hasEnvBlockMember(GammaBlockMember           )) { _shaderProgramVariableChunk->addUniformVariable("environment.gamma",            0.f      ); }  // float gamma
    if (hasEnvBlockMember(FilterColorBlockMember     )) { _shaderProgramVariableChunk->addUniformVariable("environment.filterColor",      Color3f()); }  // vec3  filterColor
    if (hasEnvBlockMember(GlobalAmbientIntBlockMember)) { _shaderProgramVariableChunk->addUniformVariable("environment.ambientIntensity", Color3f()); }  // vec3  ambientIntensity
}

void DescMaterial::updateEnvShaderUniformVariables(EnvironmentDesc* envDesc)
{
    //struct FragEnvironmentBlock
    //{
    //    float   exposure;
    //    float   keyValue;
    //    float   apertureFNumber;
    //    float   shutterSpeed;
    //    float   iso;
    //    float   whiteLevel;
    //    float   dragoBias;
    //    float   saturation;
    //    float   contrast;
    //    float   gamma;
    //    vec3    filterColor;
    //    vec3    ambientIntensity
    //};
    //
    //uniform FragEnvironmentBlock environment;

    Real32  exposure         = (envDesc ? envDesc->getExposure              ()  : 0.f      );
    Real32  keyValue         = (envDesc ? envDesc->getKeyValue              ()  : 0.f      );
    Real32  apertureFNumber  = (envDesc ? envDesc->getApertureFNumber       ()  : 0.f      );
    Real32  shutterSpeed     = (envDesc ? envDesc->getShutterSpeed          ()  : 0.f      );
    Real32  iso              = (envDesc ? envDesc->getISO                   ()  : 0.f      );
    Real32  whiteLevel       = (envDesc ? osgMax(
                                          envDesc->getWhiteLevel            (), 
                                          0.01f)                                : 0.f      );
    Real32  dragoBias        = (envDesc ? envDesc->getDragoBias             ()  : 0.f      );
    Real32  saturation       = (envDesc ? envDesc->getSaturation            ()  : 0.f      );
    Real32  contrast         = (envDesc ? envDesc->getContrast              ()  : 0.f      );
    Real32  gamma            = (envDesc ? envDesc->getGamma                 ()  : 0.f      );
    Color3f filterColor      = (envDesc ? sRGBToLinear(
                                          envDesc->getFilterColor           ()) : Color3f());
    Color3f globalAmbientInt = (envDesc ? envDesc->getGlobalAmbientIntensity()  : Color3f());

    if (hasEnvBlockMember(ExposureBlockMember        )) { _shaderProgramVariableChunk->updateUniformVariable("environment.exposure",         exposure        ); }  // float exposure
    if (hasEnvBlockMember(KeyValueBlockMember        )) { _shaderProgramVariableChunk->updateUniformVariable("environment.keyValue",         keyValue        ); }  // float keyValue
    if (hasEnvBlockMember(ApertureFNumberBlockMember )) { _shaderProgramVariableChunk->updateUniformVariable("environment.apertureFNumber",  apertureFNumber ); }  // float apertureFNumber
    if (hasEnvBlockMember(ShutterSpeedBlockMember    )) { _shaderProgramVariableChunk->updateUniformVariable("environment.shutterSpeed",     shutterSpeed    ); }  // float shutterSpeed
    if (hasEnvBlockMember(ISOBlockMember             )) { _shaderProgramVariableChunk->updateUniformVariable("environment.iso",              iso             ); }  // float iso
    if (hasEnvBlockMember(WhiteLevelBlockMember      )) { _shaderProgramVariableChunk->updateUniformVariable("environment.whiteLevel",       whiteLevel      ); }  // float whiteLevel
    if (hasEnvBlockMember(DragoBiasBlockMember       )) { _shaderProgramVariableChunk->updateUniformVariable("environment.dragoBias",        dragoBias       ); }  // float dragoBias
    if (hasEnvBlockMember(SaturationBlockMember      )) { _shaderProgramVariableChunk->updateUniformVariable("environment.saturation",       saturation      ); }  // float saturation
    if (hasEnvBlockMember(ContrastBlockMember        )) { _shaderProgramVariableChunk->updateUniformVariable("environment.contrast",         contrast        ); }  // float contrast
    if (hasEnvBlockMember(GammaBlockMember           )) { _shaderProgramVariableChunk->updateUniformVariable("environment.gamma",            gamma           ); }  // float gamma
    if (hasEnvBlockMember(FilterColorBlockMember     )) { _shaderProgramVariableChunk->updateUniformVariable("environment.filterColor",      filterColor     ); }  // vec3  filterColor
    if (hasEnvBlockMember(GlobalAmbientIntBlockMember)) { _shaderProgramVariableChunk->updateUniformVariable("environment.ambientIntensity", globalAmbientInt); }  // vec3  ambientIntensity
}

std::vector<UInt8> DescMaterial::createEnvFragBuffer(EnvironmentDesc* envDesc) const
{
    std::size_t size = calcEnvFragBufferSize(envDesc);

    std::vector<UInt8> buffer(size, 0);

    fillEnvFragBuffer(envDesc, buffer);
    
    return buffer;
}

std::size_t DescMaterial::calcEnvFragBufferSize(EnvironmentDesc* envDesc) const
{
    //layout (std140) uniform FragEnvironmentBlock
    //{
    //    float   exposure;
    //    float   keyValue;
    //    float   apertureFNumber;
    //    float   shutterSpeed;
    //    float   iso;
    //    float   whiteLevel;
    //    float   dragoBias;
    //    float   saturation;
    //    float   contrast;
    //    float   gamma;
    //    vec3    filterColor;
    //    vec3    ambientIntensity;
    //};

    std::size_t ao = 0;
    std::size_t bo = 0;

    if (hasEnvBlockMember(ExposureBlockMember        )) { ao = alignOffset( 4, bo); bo = ao + sizeof( Real32); }  // float exposure
    if (hasEnvBlockMember(KeyValueBlockMember        )) { ao = alignOffset( 4, bo); bo = ao + sizeof( Real32); }  // float keyValue
    if (hasEnvBlockMember(ApertureFNumberBlockMember )) { ao = alignOffset( 4, bo); bo = ao + sizeof( Real32); }  // float apertureFNumber
    if (hasEnvBlockMember(ShutterSpeedBlockMember    )) { ao = alignOffset( 4, bo); bo = ao + sizeof( Real32); }  // float shutterSpeed
    if (hasEnvBlockMember(ISOBlockMember             )) { ao = alignOffset( 4, bo); bo = ao + sizeof( Real32); }  // float iso
    if (hasEnvBlockMember(WhiteLevelBlockMember      )) { ao = alignOffset( 4, bo); bo = ao + sizeof( Real32); }  // float whiteLevel
    if (hasEnvBlockMember(DragoBiasBlockMember       )) { ao = alignOffset( 4, bo); bo = ao + sizeof( Real32); }  // float dragoBias
    if (hasEnvBlockMember(SaturationBlockMember      )) { ao = alignOffset( 4, bo); bo = ao + sizeof( Real32); }  // float saturation
    if (hasEnvBlockMember(ContrastBlockMember        )) { ao = alignOffset( 4, bo); bo = ao + sizeof( Real32); }  // float contrast
    if (hasEnvBlockMember(GammaBlockMember           )) { ao = alignOffset( 4, bo); bo = ao + sizeof( Real32); }  // float gamma
    if (hasEnvBlockMember(FilterColorBlockMember     )) { ao = alignOffset(16, bo); bo = ao + sizeof(  Vec3f); }  // vec3  filterColor
    if (hasEnvBlockMember(GlobalAmbientIntBlockMember)) { ao = alignOffset(16, bo); bo = ao + sizeof(  Vec3f); }  // vec3  ambientIntensity

    ao = alignOffset(16, bo); bo = ao; // padding

    return ao;
}

void DescMaterial::fillEnvFragBuffer(
    EnvironmentDesc*    envDesc,
    std::vector<UInt8>& buffer) const
{
    //layout (std140) uniform FragEnvironmentBlock
    //{
    //    float   exposure;
    //    float   keyValue;
    //    float   apertureFNumber;
    //    float   shutterSpeed;
    //    float   iso;
    //    float   whiteLevel;
    //    float   dragoBias;
    //    float   saturation;
    //    float   contrast;
    //    float   gamma;
    //    vec3    filterColor;
    //    vec3    ambientIntensity;
    //};

    Real32  exposure         = (envDesc ? envDesc->getExposure              () : 0.f      );
    Real32  keyValue         = (envDesc ? envDesc->getKeyValue              () : 0.f      );
    Real32  apertureFNumber  = (envDesc ? envDesc->getApertureFNumber       () : 0.f      );
    Real32  shutterSpeed     = (envDesc ? envDesc->getShutterSpeed          () : 0.f      );
    Real32  iso              = (envDesc ? envDesc->getISO                   () : 0.f      );
    Real32  whiteLevel       = (envDesc ? osgMax(
                                          envDesc->getWhiteLevel            (), 
                                          0.01f)                               : 0.f      );
    Real32  dragoBias        = (envDesc ? envDesc->getDragoBias             () : 0.f      );
    Real32  saturation       = (envDesc ? envDesc->getSaturation            () : 0.f      );
    Real32  contrast         = (envDesc ? envDesc->getContrast              () : 0.f      );
    Real32  gamma            = (envDesc ? envDesc->getGamma                 () : 0.f      );
    Color3f filterColor      = (envDesc ? sRGBToLinear(
                                          envDesc->getFilterColor())           : Color3f());
    Color3f globalAmbientInt = (envDesc ? envDesc->getGlobalAmbientIntensity() : Color3f());

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset

    if (hasEnvBlockMember(ExposureBlockMember        )) { ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = exposure;         bo = ao + sizeof( Real32); }  // float exposure
    if (hasEnvBlockMember(KeyValueBlockMember        )) { ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = keyValue;         bo = ao + sizeof( Real32); }  // float keyValue
    if (hasEnvBlockMember(ApertureFNumberBlockMember )) { ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = apertureFNumber;  bo = ao + sizeof( Real32); }  // float apertureFNumber
    if (hasEnvBlockMember(ShutterSpeedBlockMember    )) { ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = shutterSpeed;     bo = ao + sizeof( Real32); }  // float shutterSpeed
    if (hasEnvBlockMember(ISOBlockMember             )) { ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = iso;              bo = ao + sizeof( Real32); }  // float iso
    if (hasEnvBlockMember(WhiteLevelBlockMember      )) { ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = whiteLevel;       bo = ao + sizeof( Real32); }  // float whiteLevel
    if (hasEnvBlockMember(DragoBiasBlockMember       )) { ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = dragoBias;        bo = ao + sizeof( Real32); }  // float dragoBias
    if (hasEnvBlockMember(SaturationBlockMember      )) { ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = saturation;       bo = ao + sizeof( Real32); }  // float saturation
    if (hasEnvBlockMember(ContrastBlockMember        )) { ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = contrast;         bo = ao + sizeof( Real32); }  // float contrast
    if (hasEnvBlockMember(GammaBlockMember           )) { ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = gamma;            bo = ao + sizeof( Real32); }  // float gamma
    if (hasEnvBlockMember(FilterColorBlockMember     )) { ao = alignOffset(16, bo); memcpy(&buffer[0] + ao,   &filterColor     [0], sizeof(Color3f)); bo = ao + sizeof(  Vec3f); }  // vec3  filterColor
    if (hasEnvBlockMember(GlobalAmbientIntBlockMember)) { ao = alignOffset(16, bo); memcpy(&buffer[0] + ao,   &globalAmbientInt[0], sizeof(Color3f)); bo = ao + sizeof(  Vec3f); }  // vec3  ambientIntensity
}

void DescMaterial::initTexDescPairStoreMap(TexDescPairStoreMap& mapTexDecs) const
{
    TextureDescStore::const_iterator iter, end;

    iter = _info.textureDescs.begin();
    end  = _info.textureDescs.end  ();

    UInt32 idx = 0;

    for (; iter != end; ++iter, ++idx)
    {
        TextureDesc* texDesc = *iter;

        UInt32 type = texDesc->getTextureType();

        TexDescPairStoreMap::iterator it = mapTexDecs.find(type);
        if (it == mapTexDecs.end())
        {
            std::pair<TexDescPairStoreMap::iterator, bool> x = mapTexDecs.insert(TexDescPairStoreMap::value_type(type, TexDescPairStore()));
            if (!x.second)
                continue;

            it = x.first;
        }

        TexDescPairStore& store = it->second;

        TexDescPair p = std::make_pair(texDesc, idx);
        store.push_back(p);
    }

    iter = _info.textureDescsEnv.begin();
    end  = _info.textureDescsEnv.end  ();

    for (; iter != end; ++iter, ++idx)
    {
        TextureDesc* texDesc = *iter;

        UInt32 type = texDesc->getTextureType();

        TexDescPairStoreMap::iterator it = mapTexDecs.find(type);
        if (it == mapTexDecs.end())
        {
            std::pair<TexDescPairStoreMap::iterator, bool> x = mapTexDecs.insert(TexDescPairStoreMap::value_type(type, TexDescPairStore()));
            if (!x.second)
                continue;

            it = x.first;
        }

        TexDescPairStore& store = it->second;

        TexDescPair p = std::make_pair(texDesc, idx);
        store.push_back(p);
    }
}

void DescMaterial::addShaderUniformVariables()
{
    TexDescPairStoreMap mapTexDecs;

    initTexDescPairStoreMap(mapTexDecs);

    //struct StackTexData
    //{
    //    vec3  baseColor;
    //    int   size;
    //    bool  isSRGB   [ciMaxTextureStackSize];
    //    int   flags    [ciMaxTextureStackSize];
    //    int   ops      [ciMaxTextureStackSize];
    //    float strengths[ciMaxTextureStackSize];
    //    int   indices  [ciMaxTextureStackSize];
    //};

    //struct SingleTexData
    //{
    //    vec3  baseColor;
    //    bool  isSRGB;
    //    int   flags;
    //    int   op;
    //    float strength;
    //    int   index;
    //};

    //struct EnvTexData
    //{
    //    bool  isSRGB;
    //    float strength;
    //    int   index;
    //};

    //struct FragDescMaterialBlock
    //{
    //    float   specularStrength;
    //    float   emissiveStrength;
    //    float   opacityCutOff;
    //    float   reflectivity;
    //    float   reflectance;
    //    float   bumpScaling;
    //    vec3    transparent;
    //    vec3    reflective;
    //    vec3    goochCool;
    //    vec3    goochWarm;
    //    float   goochMixin;
    //    float   goochCoolMixin;
    //    float   goochWarmMixin;
    //    int     toonLevels;
    //    TexData albedo;
    //    TexData specular;
    //    TexData emissive;
    //    TexData shininess;
    //    TexData opacity;
    //    TexData normal;
    //    TexData height;
    //    TexData displacement;
    //    TexData reflection;
    //    TexData refraction;
    //    TexData anisotropyU;
    //    TexData anisotropyV;
    //    TexData anisotropyUV;
    //    TexData ambientOcclusion;
    //    TexData roughness;
    //    TexData metalness;
    //    TexData metalRough;
    //    TexData metalRoughOpacity
    //    TexData irradiance;
    //    TexData preFilterColor;
    //    TexData brdf;
    //    TexData standard;
    //    TexData metalRoughDispOcc;
    //    TexData metalRoughDisp;
    //    TexData roughDispOcc;
    //    TexData roughDisp;
    //};
    //
    //uniform FragDescMaterialBlock descMaterial;

    if (hasMatBlockMember(SpecularStrengthBlockMember)) { _shaderProgramVariableChunk->addUniformVariable("descMaterial.specularStrength",  0.f      ); }  // float specularStrength
    if (hasMatBlockMember(EmissiveStrengthBlockMember)) { _shaderProgramVariableChunk->addUniformVariable("descMaterial.emissiveStrength",  0.f      ); }  // float emissiveStrength
    if (hasMatBlockMember(OpacityCutOffBlockMember   )) { _shaderProgramVariableChunk->addUniformVariable("descMaterial.opacityCutOff",     0.f      ); }  // float opacityCutOff
    if (hasMatBlockMember(ReflectivityBlockMember    )) { _shaderProgramVariableChunk->addUniformVariable("descMaterial.reflectivity",      0.f      ); }  // float reflectivity
    if (hasMatBlockMember(ReflectanceBlockMember     )) { _shaderProgramVariableChunk->addUniformVariable("descMaterial.reflectance",       0.f      ); }  // float reflectance
    if (hasMatBlockMember(BumpScalingBlockMember     )) { _shaderProgramVariableChunk->addUniformVariable("descMaterial.bumpScaling",       0.f      ); }  // float bumpScaling
    if (hasMatBlockMember(TransparentBlockMember     )) { _shaderProgramVariableChunk->addUniformVariable("descMaterial.transparent",       Color3f()); }  // vec3  transparent
    if (hasMatBlockMember(ReflectiveBlockMember      )) { _shaderProgramVariableChunk->addUniformVariable("descMaterial.reflective",        Color3f()); }  // vec3  reflective
    if (hasMatBlockMember(GoochCoolBlockMember       )) { _shaderProgramVariableChunk->addUniformVariable("descMaterial.goochCool",         Color3f()); }  // vec3  goochCool
    if (hasMatBlockMember(GoochWarmBlockMember       )) { _shaderProgramVariableChunk->addUniformVariable("descMaterial.goochWarm",         Color3f()); }  // vec3  goochWarm
    if (hasMatBlockMember(GoochMixinBlockMember      )) { _shaderProgramVariableChunk->addUniformVariable("descMaterial.goochMixin",        0.f      ); }  // float goochMixin
    if (hasMatBlockMember(GoochCoolMixinBlockMember  )) { _shaderProgramVariableChunk->addUniformVariable("descMaterial.goochCoolMixin",    0.f      ); }  // float goochCoolMixin
    if (hasMatBlockMember(GoochWarmMixinBlockMember  )) { _shaderProgramVariableChunk->addUniformVariable("descMaterial.goochWarmMixin",    0.f      ); }  // float goochWarmMixin
    if (hasMatBlockMember(ToonLevelsBlockMember      )) { _shaderProgramVariableChunk->addUniformVariable("descMaterial.toonLevels",        0.f      ); }  // int   toonLevels

    Int32 iTextureCnt = 0;

    for (UInt32 texType = 0; texType < TextureDesc::MAX_NUM_TEXTURE_TYPES; ++texType)
    {
        std::string name = "descMaterial.";

        switch (texType)
        {
            case TextureDesc::NONE_TEXTURE:                     name  = "";                          break;
            case TextureDesc::UNKNOWN_TEXTURE:                  name  = "";                          break;
            case TextureDesc::ALBEDO_TEXTURE:                   name += "albedo";                    break;
            case TextureDesc::SPECULAR_TEXTURE:                 name += "specular";                  break;
            case TextureDesc::EMISSIVE_TEXTURE:                 name += "emissive";                  break;
            case TextureDesc::SHININESS_TEXTURE:                name += "shininess";                 break;
            case TextureDesc::OPACITY_TEXTURE:                  name += "opacity";                   break;
            case TextureDesc::NORMALS_TEXTURE:                  name += "normal";                    break;
            case TextureDesc::HEIGHT_TEXTURE:                   name += "height";                    break;
            case TextureDesc::DISPLACEMENT_TEXTURE:             name += "displacement";              break;
            case TextureDesc::REFLECTION_TEXTURE:               name += "reflection";                break;
            case TextureDesc::REFRACTION_TEXTURE:               name += "refraction";                break;
            case TextureDesc::ANISOTROPY_U_TEXTURE:             name += "anisotropyU";               break;
            case TextureDesc::ANISOTROPY_V_TEXTURE:             name += "anisotropyV";               break;
            case TextureDesc::ANISOTROPY_UV_TEXTURE:            name += "anisotropyUV";              break;
            case TextureDesc::AMBIENT_OCCLUSION_TEXTURE:        name += "ambientOcclusion";          break;
            case TextureDesc::ROUGH_TEXTURE:                    name += "roughness";                 break;
            case TextureDesc::METAL_TEXTURE:                    name += "metalness";                 break;
            case TextureDesc::ROUGH_METAL_TEXTURE:              name += "roughMetal";                break;
            case TextureDesc::OCCL_ROUGH_METAL_TEXTURE:         name += "occlRoughMetal";            break;
            case TextureDesc::IRRADIANCE_TEXTURE:               name += "irradiance";                break;
            case TextureDesc::PRE_FILTER_TEXTURE:               name += "preFilterColor";            break;
            case TextureDesc::BRDF_LUT_TEXTURE:                 name += "brdf";                      break;
            case TextureDesc::STANDARD_MATERIAL_TEXTURE:        name += "standard";                  break;
        }

        switch (evalFragtProgTexType(texType))
        {
            case DISCARD:
                break;
            case IS_COLOR_DATA:
                _shaderProgramVariableChunk->addUniformVariable(name.c_str(), Color3f());
                break;
            case IS_SINGLE_DATA:
            case IS_STACK_DATA:
            case IS_ENV_DATA:
                {
                    //struct StackTexData
                    //{
                    //    vec3  baseColor;
                    //    int   size;
                    //    bool  isSRGB   [ciMaxTextureStackSize];
                    //    int  flags     [ciMaxTextureStackSize];
                    //    int  ops       [ciMaxTextureStackSize];
                    //    float strengths[ciMaxTextureStackSize];
                    //    int  indices   [ciMaxTextureStackSize];
                    //};

                    //struct SingleTexData
                    //{
                    //    vec3  baseColor;
                    //    bool  isSRGB;
                    //    int   flags;
                    //    int   op;
                    //    float strength;
                    //    int   index;
                    //};

                    //struct EnvTexData
                    //{
                    //    bool  isSRGB;
                    //    float strength;
                    //    int   index;
                    //};

                    TexDescPairStoreMap::const_iterator map_iter = mapTexDecs.find(texType);
                    if (map_iter != mapTexDecs.end())
                    {
                        std::string var;

                        const TexDescPairStore& texDescPairStore = map_iter->second;

                        if (texDescPairStore.size() == 1)
                        {
                            iTextureCnt += 1;

                            const TexDescPair& texDescPair = *texDescPairStore.begin();
                            TextureDesc* texDesc  = texDescPair.first;

                            if (texDesc->isEnvironmentMap())
                            {
                                var = name + ".isSRGB";   _shaderProgramVariableChunk->addUniformVariable(var.c_str(), false );
                                var = name + ".strength"; _shaderProgramVariableChunk->addUniformVariable(var.c_str(), 0.f   );
                                var = name + ".index";    _shaderProgramVariableChunk->addUniformVariable(var.c_str(), 0     );
                            }
                            else
                            {
                                var = name + ".baseColor";_shaderProgramVariableChunk->addUniformVariable(var.c_str(), Color3f());
                                var = name + ".isSRGB";   _shaderProgramVariableChunk->addUniformVariable(var.c_str(), false    );
                                var = name + ".flags";    _shaderProgramVariableChunk->addUniformVariable(var.c_str(), 0        );
                                var = name + ".op";       _shaderProgramVariableChunk->addUniformVariable(var.c_str(), 0        );
                                var = name + ".strength"; _shaderProgramVariableChunk->addUniformVariable(var.c_str(), 0.f      );
                                var = name + ".index";    _shaderProgramVariableChunk->addUniformVariable(var.c_str(), 0        );
                            }
                        }
                        else
                        {
                            UInt32 size = static_cast<UInt32>(texDescPairStore.size());

                            iTextureCnt += size;

                            OSG_ASSERT(size <= cuiMaxTextureStackSize);

                            var = name + ".baseColor";_shaderProgramVariableChunk->addUniformVariable(var.c_str(), Color3f());
                            var = name + ".size";     _shaderProgramVariableChunk->addUniformVariable(var.c_str(), 0        );

                            for (UInt32 i = 0; i < cuiMaxTextureStackSize; ++i)
                            {
                                std::stringstream ss; ss << name << ".isSRGB[" << i << "]";    _shaderProgramVariableChunk->addUniformVariable(ss.str().c_str(), false);
                            }

                            for (UInt32 i = 0; i < cuiMaxTextureStackSize; ++i)
                            {
                                std::stringstream ss; ss << name << ".flags[" << i << "]";     _shaderProgramVariableChunk->addUniformVariable(ss.str().c_str(), 0    );
                            }

                            for (UInt32 i = 0; i < cuiMaxTextureStackSize; ++i)
                            {
                                std::stringstream ss; ss << name << ".ops[" << i << "]";       _shaderProgramVariableChunk->addUniformVariable(ss.str().c_str(), 0    );
                            }

                            for (UInt32 i = 0; i < cuiMaxTextureStackSize; ++i)
                            {
                                std::stringstream ss; ss << name << ".strengths[" << i << "]"; _shaderProgramVariableChunk->addUniformVariable(ss.str().c_str(), 0.f  );
                            }

                            for (UInt32 i = 0; i < cuiMaxTextureStackSize; ++i)
                            {
                                std::stringstream ss; ss << name << ".indices[" << i << "]";   _shaderProgramVariableChunk->addUniformVariable(ss.str().c_str(), 0    );
                            }
                        }
                    }
                }
                break;
        }
    }

    //
    //uniform sampler2D uTextureMap0
    //uniform sampler2D uTextureMap1
    //...
    //
    for (Int32 i = 0; i < iTextureCnt; ++i)
    {
        std::stringstream ss; ss << "uTextureMap" << i;
        _shaderProgramVariableChunk->addUniformVariable(ss.str().c_str(), 0);
    }

    //struct TextureUVData
    //{
    //     ...
    //};
    //
    //struct VertDescMaterialBlock
    //{
    //    TextureUVData uvData[ciNumUVTextures];
    //};
    //
    //uniform VertDescMaterialBlock textureDesc;

    TextureDescStore::const_iterator iter = _info.textureDescs.begin();
    TextureDescStore::const_iterator end  = _info.textureDescs.end  ();

    for (UInt32 idx = 0; iter != end; ++iter, ++idx)
    {
        TextureDesc* texDesc = *iter;

        switch (_info.vertOptVariant)
        {
            case NoTextures:
                //struct TextureUVData
                //{
                //};
                break;
            case FullImplementation:
                //struct TextureUVData
                //{
                //    int  channel;
                //    bool hasTransform;
                //    mat4 transform;
                //};
                {
                    std::stringstream ss1; ss1 << "textureDesc.uvData[" << idx  << "].channel";
                    _shaderProgramVariableChunk->addUniformVariable(ss1.str().c_str(), 0);

                    std::stringstream ss2; ss2 << "textureDesc.uvData[" << idx  << "].hasTransform";
                    _shaderProgramVariableChunk->addUniformVariable(ss2.str().c_str(), false);

                    std::stringstream ss3; ss3 << "textureDesc.uvData[" << idx  << "].transform";
                    _shaderProgramVariableChunk->addUniformVariable(ss3.str().c_str(), Matrix());
                }
                break;
            case OptOnlyTransform:
                //struct TextureUVData
                //{
                //    bool hasTransform;
                //    mat4 transform;
                //};
                {
                    std::stringstream ss1; ss1 << "textureDesc.uvData[" << idx  << "].hasTransform";
                    _shaderProgramVariableChunk->addUniformVariable(ss1.str().c_str(), false);

                    std::stringstream ss2; ss2 << "textureDesc.uvData[" << idx  << "].transform";
                    _shaderProgramVariableChunk->addUniformVariable(ss2.str().c_str(), Matrix());
                }
                break;
            case OptOnlyChannels:
                //struct TextureUVData
                //{
                //    int channel;
                //};
                {
                    std::stringstream ss1; ss1 << "textureDesc.uvData[" << idx  << "].channel";
                    _shaderProgramVariableChunk->addUniformVariable(ss1.str().c_str(), 0);
                }
                break;

            case OptOnlyChannel0:
                //struct TextureUVData
                //{
                //};
                break;
        }
    }
}

void DescMaterial::updateShaderUniformVariables(MaterialDesc* matDesc)
{
    TexDescPairStoreMap mapTexDecs;

    initTexDescPairStoreMap(mapTexDecs);

    //struct FragDescMaterialBlock
    //{
    //    float   specularStrength;
    //    float   emissiveStrength;
    //    float   opacityCutOff;
    //    float   reflectivity;
    //    float   reflectance;
    //    float   bumpScaling;
    //    vec3    transparent;
    //    vec3    reflective;
    //    vec3    goochCool;
    //    vec3    goochWarm;
    //    float   goochMixin;
    //    float   goochCoolMixin;
    //    float   goochWarmMixin;
    //    int     toonLevels;
    //    TexData albedo;
    //    TexData specular;
    //    TexData emissive;
    //    TexData shininess;
    //    TexData opacity;
    //    TexData normal;
    //    TexData height;
    //    TexData displacement;
    //    TexData reflection;
    //    TexData refraction;
    //    TexData anisotropyU;
    //    TexData anisotropyV;
    //    TexData anisotropyUV;
    //    TexData ambientOcclusion;
    //    TexData roughness;
    //    TexData metalness;
    //    TexData metalRough;
    //    TexData metalRoughOpacity
    //    TexData irradiance;
    //    TexData preFilterColor;
    //    TexData brdf;
    //    TexData standard;
    //    TexData metalRoughDispOcc;
    //    TexData metalRoughDisp;
    //    TexData roughDispOcc;
    //    TexData roughDisp;
    //};
    //
    //uniform FragDescMaterialBlock descMaterial;

    Real32  specularStrength  = matDesc->getSpecularStrength();
    Real32  emissiveStrength  = matDesc->getEmissiveStrength();
    Real32  opacityCutOff     = matDesc->getOpacityCutOff();
    Real32  reflectivity      = matDesc->getReflectivity();
    Real32  reflectance       = matDesc->getReflectance();
    Real32  bumpScaling       = matDesc->getBumpScaling();
    Color3f transparent       = matDesc->getTransparent();
    Color3f reflective        = matDesc->getReflective();
    Color3f goochCool         = matDesc->getGoochCool();
    Color3f goochWarm         = matDesc->getGoochWarm();
    Real32  goochMixin        = matDesc->getGoochMixin();
    Real32  goochCoolMixin    = matDesc->getGoochCoolMixin();
    Real32  goochWarmMixin    = matDesc->getGoochWarmMixin();
    Int32   toonLevels        = matDesc->getToonLevels();

    if (matDesc->getSRGBColorMode())
    {
        transparent = sRGBToLinear(transparent);
        reflective  = sRGBToLinear(reflective);

        goochCool   = sRGBToLinear(goochCool);
        goochWarm   = sRGBToLinear(goochWarm);
    }

    if (hasMatBlockMember(SpecularStrengthBlockMember)) { _shaderProgramVariableChunk->updateUniformVariable("descMaterial.specularStrength",  specularStrength); }  // float specularStrength
    if (hasMatBlockMember(EmissiveStrengthBlockMember)) { _shaderProgramVariableChunk->updateUniformVariable("descMaterial.emissiveStrength",  emissiveStrength); }  // float emissiveStrength
    if (hasMatBlockMember(OpacityCutOffBlockMember   )) { _shaderProgramVariableChunk->updateUniformVariable("descMaterial.opacityCutOff",     opacityCutOff   ); }  // float opacityCutOff
    if (hasMatBlockMember(ReflectivityBlockMember    )) { _shaderProgramVariableChunk->updateUniformVariable("descMaterial.reflectivity",      reflectivity    ); }  // float reflectivity
    if (hasMatBlockMember(ReflectanceBlockMember     )) { _shaderProgramVariableChunk->updateUniformVariable("descMaterial.reflectance",       reflectance     ); }  // float reflectance
    if (hasMatBlockMember(BumpScalingBlockMember     )) { _shaderProgramVariableChunk->updateUniformVariable("descMaterial.bumpScaling",       bumpScaling     ); }  // float bumpScaling
    if (hasMatBlockMember(TransparentBlockMember     )) { _shaderProgramVariableChunk->updateUniformVariable("descMaterial.transparent",       transparent     ); }  // vec3  transparent
    if (hasMatBlockMember(ReflectiveBlockMember      )) { _shaderProgramVariableChunk->updateUniformVariable("descMaterial.reflective",        reflective      ); }  // vec3  reflective
    if (hasMatBlockMember(GoochCoolBlockMember       )) { _shaderProgramVariableChunk->updateUniformVariable("descMaterial.goochCool",         goochCool       ); }  // vec3  goochCool
    if (hasMatBlockMember(GoochWarmBlockMember       )) { _shaderProgramVariableChunk->updateUniformVariable("descMaterial.goochWarm",         goochWarm       ); }  // vec3  goochWarm
    if (hasMatBlockMember(GoochMixinBlockMember      )) { _shaderProgramVariableChunk->updateUniformVariable("descMaterial.goochMixin",        goochMixin      ); }  // float goochMixin
    if (hasMatBlockMember(GoochCoolMixinBlockMember  )) { _shaderProgramVariableChunk->updateUniformVariable("descMaterial.goochCoolMixin",    goochCoolMixin  ); }  // float goochCoolMixin
    if (hasMatBlockMember(GoochWarmMixinBlockMember  )) { _shaderProgramVariableChunk->updateUniformVariable("descMaterial.goochWarmMixin",    goochWarmMixin  ); }  // float goochWarmMixin
    if (hasMatBlockMember(ToonLevelsBlockMember      )) { _shaderProgramVariableChunk->updateUniformVariable("descMaterial.toonLevels",        toonLevels      ); }  // int   toonLevels

    Int32 iTextureCnt = 0;

    for (UInt32 texType = 0; texType < TextureDesc::MAX_NUM_TEXTURE_TYPES; ++texType)
    {
        std::string name = "descMaterial.";

        switch (texType)
        {
            case TextureDesc::NONE_TEXTURE:                     name  = "";                          break;
            case TextureDesc::UNKNOWN_TEXTURE:                  name  = "";                          break;
            case TextureDesc::ALBEDO_TEXTURE:                   name += "albedo";                    break;
            case TextureDesc::SPECULAR_TEXTURE:                 name += "specular";                  break;
            case TextureDesc::EMISSIVE_TEXTURE:                 name += "emissive";                  break;
            case TextureDesc::SHININESS_TEXTURE:                name += "shininess";                 break;
            case TextureDesc::OPACITY_TEXTURE:                  name += "opacity";                   break;
            case TextureDesc::NORMALS_TEXTURE:                  name += "normal";                    break;
            case TextureDesc::HEIGHT_TEXTURE:                   name += "height";                    break;
            case TextureDesc::DISPLACEMENT_TEXTURE:             name += "displacement";              break;
            case TextureDesc::REFLECTION_TEXTURE:               name += "reflection";                break;
            case TextureDesc::REFRACTION_TEXTURE:               name += "refraction";                break;
            case TextureDesc::ANISOTROPY_U_TEXTURE:             name += "anisotropyU";               break;
            case TextureDesc::ANISOTROPY_V_TEXTURE:             name += "anisotropyV";               break;
            case TextureDesc::ANISOTROPY_UV_TEXTURE:            name += "anisotropyUV";              break;
            case TextureDesc::AMBIENT_OCCLUSION_TEXTURE:        name += "ambientOcclusion";          break;
            case TextureDesc::ROUGH_TEXTURE:                    name += "roughness";                 break;
            case TextureDesc::METAL_TEXTURE:                    name += "metalness";                 break;
            case TextureDesc::ROUGH_METAL_TEXTURE:              name += "roughMetal";                break;
            case TextureDesc::OCCL_ROUGH_METAL_TEXTURE:         name += "occlRoughMetal";            break;
            case TextureDesc::IRRADIANCE_TEXTURE:               name += "irradiance";                break;
            case TextureDesc::PRE_FILTER_TEXTURE:               name += "preFilterColor";            break;
            case TextureDesc::BRDF_LUT_TEXTURE:                 name += "brdf";                      break;
            case TextureDesc::STANDARD_MATERIAL_TEXTURE:        name += "standard";                  break;
        }

        Color3f baseColor = getBaseColor(matDesc, texType);

        switch (evalFragtProgTexType(texType))
        {
            case DISCARD:
                break;
            case IS_COLOR_DATA:
                _shaderProgramVariableChunk->updateUniformVariable(name.c_str(), baseColor);
                break;
            case IS_SINGLE_DATA:
            case IS_STACK_DATA:
            case IS_ENV_DATA:
                {
                    //struct StackTexData
                    //{
                    //    vec3  baseColor;
                    //    int   size;
                    //    bool  isSRGB   [ciMaxTextureStackSize];
                    //    int   flags    [ciMaxTextureStackSize];
                    //    int   ops      [ciMaxTextureStackSize];
                    //    float strengths[ciMaxTextureStackSize];
                    //    int   indices  [ciMaxTextureStackSize];
                    //};

                    //struct SingleTexData
                    //{
                    //    vec3  baseColor;
                    //    bool  isSRGB;
                    //    int   flags;
                    //    int   op;
                    //    float strength;
                    //    int   index;
                    //};

                    //struct EnvTexData
                    //{
                    //    bool  isSRGB;
                    //    float strength;
                    //    int   index;
                    //};

                    //_shaderProgramVariableChunk->updateUniformVariable("uTextureMap0", 0);
                    //_shaderProgramVariableChunk->updateUniformVariable("uTextureMap1", 1);
                    //_shaderProgramVariableChunk->updateUniformVariable("uTextureMap2", 2);
                    //_shaderProgramVariableChunk->updateUniformVariable("uTextureMap3", 3);
                    //_shaderProgramVariableChunk->updateUniformVariable("uTextureMap4", 4);

                    TexDescPairStoreMap::const_iterator map_iter = mapTexDecs.find(texType);
                    if (map_iter != mapTexDecs.end())
                    {
                        std::string var;

                        const TexDescPairStore& texDescPairStore = map_iter->second;

                        if (texDescPairStore.size() == 1)
                        {
                            iTextureCnt += 1;

                            const TexDescPair& texDescPair = *texDescPairStore.begin();

                            TextureDesc* texDesc  =                    texDescPair.first;
                            Int32        index    = static_cast<Int32>(texDescPair.second);

                            bool   isSRGB   = _isSRGBTextures[index];
                            Int32  flags    = static_cast<Int32>(texDesc->getTextureFlags());
                            Int32  op       = static_cast<Int32>(texDesc->getOperation   ());
                            Real32 strength =                    texDesc->getBlendFactor ();

                            if (texDesc->isEnvironmentMap())
                            {
                                var = name + ".isSRGB";   _shaderProgramVariableChunk->updateUniformVariable(var.c_str(), isSRGB  );
                                var = name + ".strength"; _shaderProgramVariableChunk->updateUniformVariable(var.c_str(), strength);
                                var = name + ".index";    _shaderProgramVariableChunk->updateUniformVariable(var.c_str(), index   );
                            }
                            else
                            {
                                var = name + ".baseColor";_shaderProgramVariableChunk->updateUniformVariable(var.c_str(), baseColor);
                                var = name + ".isSRGB";   _shaderProgramVariableChunk->updateUniformVariable(var.c_str(), isSRGB   );
                                var = name + ".flags";    _shaderProgramVariableChunk->updateUniformVariable(var.c_str(), flags    );
                                var = name + ".op";       _shaderProgramVariableChunk->updateUniformVariable(var.c_str(), op       );
                                var = name + ".strength"; _shaderProgramVariableChunk->updateUniformVariable(var.c_str(), strength );
                                var = name + ".index";    _shaderProgramVariableChunk->updateUniformVariable(var.c_str(), index    );
                            }
                        }
                        else
                        {
                            UInt32 size = static_cast<UInt32>(texDescPairStore.size());

                            iTextureCnt += size;

                            OSG_ASSERT(size <= cuiMaxTextureStackSize);

                            std::vector<bool>   vecIsSRGB   (cuiMaxTextureStackSize, false);
                            std::vector<Int32>  vecFlags    (cuiMaxTextureStackSize, 0);
                            std::vector<Int32>  vecOps      (cuiMaxTextureStackSize, 0);
                            std::vector<Real32> vecStrengths(cuiMaxTextureStackSize, 0.f);
                            std::vector<Int32>  vecIndices  (cuiMaxTextureStackSize, 0);

                            for (std::size_t i = 0; i < size; ++i)
                            {
                                const TexDescPair& texDescPair = texDescPairStore[i];

                                TextureDesc* texDesc =                    texDescPair.first;
                                Int32        index   = static_cast<Int32>(texDescPair.second);

                                bool   isSRGB    = _isSRGBTextures[index];
                                Int32  flags     = static_cast<Int32>(texDesc->getTextureFlags());
                                Int32  op        = static_cast<Int32>(texDesc->getOperation   ());
                                Real32 strength  =                    texDesc->getBlendFactor ();

                                vecIsSRGB   [i] = isSRGB;
                                vecFlags    [i] = flags;
                                vecOps      [i] = op;
                                vecStrengths[i] = strength;
                                vecIndices  [i] = index;
                            }

                            var = name + ".baseColor";_shaderProgramVariableChunk->updateUniformVariable(var.c_str(), baseColor                 );
                            var = name + ".size";     _shaderProgramVariableChunk->updateUniformVariable(var.c_str(), static_cast<Int32>(size)  );

                            UInt32 sz = static_cast<UInt32>(vecIndices.size());

                            for (UInt32 i = 0; i < cuiMaxTextureStackSize; ++i)
                            {
                                std::stringstream ss; ss << name << ".isSRGB[" << i << "]";    _shaderProgramVariableChunk->updateUniformVariable(ss.str().c_str(), vecIsSRGB[i]);
                            }

                            for (UInt32 i = 0; i < cuiMaxTextureStackSize; ++i)
                            {
                                std::stringstream ss; ss << name << ".flags[" << i << "]";     _shaderProgramVariableChunk->updateUniformVariable(ss.str().c_str(), vecFlags[i]);
                            }

                            for (UInt32 i = 0; i < cuiMaxTextureStackSize; ++i)
                            {
                                std::stringstream ss; ss << name << ".ops[" << i << "]";       _shaderProgramVariableChunk->updateUniformVariable(ss.str().c_str(), vecOps[i]);
                            }

                            for (UInt32 i = 0; i < cuiMaxTextureStackSize; ++i)
                            {
                                std::stringstream ss; ss << name << ".strengths[" << i << "]"; _shaderProgramVariableChunk->updateUniformVariable(ss.str().c_str(), vecStrengths[i]);
                            }

                            for (UInt32 i = 0; i < cuiMaxTextureStackSize; ++i)
                            {
                                std::stringstream ss; ss << name << ".indices[" << i << "]";   _shaderProgramVariableChunk->updateUniformVariable(ss.str().c_str(), vecIndices[i]);
                            }
                        }
                    }
                }
                break;
        }
    }

    //
    //uniform sampler2D uTextureMap0
    //uniform sampler2D uTextureMap1
    //...
    //
    for (Int32 i = 0; i < iTextureCnt; ++i)
    {
        std::stringstream ss; ss << "uTextureMap" << i;
        _shaderProgramVariableChunk->updateUniformVariable(ss.str().c_str(), i);
    }

    //struct TextureUVData
    //{
    //     ...
    //};
    //
    //struct VertDescMaterialBlock
    //{
    //    TextureUVData uvData[ciNumUVTextures];
    //};
    //
    //uniform VertDescMaterialBlock textureDesc;

    TextureDescStore::const_iterator iter = _info.textureDescs.begin();
    TextureDescStore::const_iterator end  = _info.textureDescs.end  ();

    for (UInt32 idx = 0; iter != end; ++iter, ++idx)
    {
        TextureDesc* texDesc = *iter;

        Int32  channel        = static_cast<Int32>(texDesc->getUVChannel());
        bool   hasUVTransform = texDesc->getHasUVTransform();
        Matrix uvTransform;

        if (hasUVTransform)
        {
            Vec2f  t = texDesc->getTranslate();
            Vec2f  s = texDesc->getScale();
            Real32 r = texDesc->getRotate();

            Real32 tx = t.x();
            Real32 ty = t.y();
            Real32 tz = 0.f;

            Real32 sx = s.x();
            Real32 sy = s.y();
            Real32 sz = 1.f;

            Vec3f axis(0.f, 0.f, 1.f);

            Int32 intFraction = static_cast<Int32>(r / OSG::TwoPi);
            if (intFraction)
            {
                r -= intFraction * OSG::TwoPi;
            }
                
            if (r < 0.f)
                r += OSG::TwoPi;

            Quaternion rotation(axis, r);

            Matrix S, R, T;

            S.setScale(sx, sy, sz);
            R.setRotate(rotation);
            T.setTranslate(tx, ty, tz);

            uvTransform = S;
            uvTransform.mult(R);
            uvTransform.mult(T);
        }

        switch (_info.vertOptVariant)
        {
            case NoTextures:
                //struct TextureUVData
                //{
                //};
                break;
            case FullImplementation:
                //struct TextureUVData
                //{
                //    int  channel;
                //    bool hasTransform;
                //    mat4 transform;
                //};
                {
                    std::stringstream ss1; ss1 << "textureDesc.uvData[" << idx  << "].channel";
                    _shaderProgramVariableChunk->updateUniformVariable(ss1.str().c_str(), channel);

                    std::stringstream ss2; ss2 << "textureDesc.uvData[" << idx  << "].hasTransform";
                    _shaderProgramVariableChunk->updateUniformVariable(ss2.str().c_str(), hasUVTransform);

                    std::stringstream ss3; ss3 << "textureDesc.uvData[" << idx  << "].transform";
                    _shaderProgramVariableChunk->updateUniformVariable(ss3.str().c_str(), uvTransform);
                }
                break;
            case OptOnlyTransform:
                //struct TextureUVData
                //{
                //    bool hasTransform;
                //    mat4 transform;
                //};
                {
                    std::stringstream ss1; ss1 << "textureDesc.uvData[" << idx  << "].hasTransform";
                    _shaderProgramVariableChunk->updateUniformVariable(ss1.str().c_str(), hasUVTransform);

                    std::stringstream ss2; ss2 << "textureDesc.uvData[" << idx  << "].transform";
                    _shaderProgramVariableChunk->updateUniformVariable(ss2.str().c_str(), uvTransform);
                }
                break;
            case OptOnlyChannels:
                //struct TextureUVData
                //{
                //    int  channel;
                //};
                {
                    std::stringstream ss1; ss1 << "textureDesc.uvData[" << idx  << "].channel";
                    _shaderProgramVariableChunk->updateUniformVariable(ss1.str().c_str(), channel);
                }
                break;

            case OptOnlyChannel0:
                //struct TextureUVData
                //{
                //};
                break;
        }
    }
}

std::vector<UInt8> DescMaterial::createFragBuffer(MaterialDesc* matDesc) const
{
    TexDescPairStoreMap mapTexDecs;

    initTexDescPairStoreMap(mapTexDecs);

    std::size_t size = calcFragBufferSize(matDesc, mapTexDecs);

    std::vector<UInt8> buffer(size, 0);

    fillFragBuffer(matDesc, buffer, mapTexDecs);
    
    return buffer;
}

std::size_t DescMaterial::calcFragBufferSize(
    MaterialDesc*              matDesc,
    const TexDescPairStoreMap& mapTexDecs) const
{
    //layout (std140) uniform FragDescMaterialBlock
    //{
    //    float   specularStrength;
    //    float   emissiveStrength;
    //    float   opacityCutOff;
    //    float   reflectivity;
    //    float   reflectance;
    //    float   bumpScaling;
    //    vec3    transparent;
    //    vec3    reflective;
    //    vec3    goochCool;
    //    vec3    goochWarm;
    //    float   goochMixin;
    //    float   goochCoolMixin;
    //    float   goochWarmMixin;
    //    int     toonLevels;
    //    TexData albedo;
    //    TexData specular;
    //    TexData emissive;
    //    TexData shininess;
    //    TexData opacity;
    //    TexData normal;
    //    TexData height;
    //    TexData displacement;
    //    TexData reflection;
    //    TexData refraction;
    //    TexData anisotropyU;
    //    TexData anisotropyV;
    //    TexData anisotropyUV;
    //    TexData ambientOcclusion;
    //    TexData roughness;
    //    TexData metalness;
    //    TexData metalRough;
    //    TexData metalRoughOpacity
    //    TexData irradiance;
    //    TexData preFilterColor;
    //    TexData brdf;
    //    TexData standard;
    //    TexData metalRoughDispOcc;
    //    TexData metalRoughDisp;
    //    TexData roughDispOcc;
    //    TexData roughDisp;
    //};

    std::size_t ao = 0;
    std::size_t bo = 0;

    if (hasMatBlockMember(SpecularStrengthBlockMember)) { ao = alignOffset( 4, bo); bo = ao + sizeof( Real32); }  // float specularStrength
    if (hasMatBlockMember(EmissiveStrengthBlockMember)) { ao = alignOffset( 4, bo); bo = ao + sizeof( Real32); }  // float emissiveStrength
    if (hasMatBlockMember(OpacityCutOffBlockMember   )) { ao = alignOffset( 4, bo); bo = ao + sizeof( Real32); }  // float opacityCutOff
    if (hasMatBlockMember(ReflectivityBlockMember    )) { ao = alignOffset( 4, bo); bo = ao + sizeof( Real32); }  // float reflectivity
    if (hasMatBlockMember(ReflectanceBlockMember     )) { ao = alignOffset( 4, bo); bo = ao + sizeof( Real32); }  // float reflectance
    if (hasMatBlockMember(BumpScalingBlockMember     )) { ao = alignOffset( 4, bo); bo = ao + sizeof( Real32); }  // float bumpScaling
    if (hasMatBlockMember(TransparentBlockMember     )) { ao = alignOffset(16, bo); bo = ao + sizeof(  Vec3f); }  // vec3  transparent
    if (hasMatBlockMember(ReflectiveBlockMember      )) { ao = alignOffset(16, bo); bo = ao + sizeof(  Vec3f); }  // vec3  reflective
    if (hasMatBlockMember(GoochCoolBlockMember       )) { ao = alignOffset(16, bo); bo = ao + sizeof(  Vec3f); }  // vec3  goochCool
    if (hasMatBlockMember(GoochWarmBlockMember       )) { ao = alignOffset(16, bo); bo = ao + sizeof(  Vec3f); }  // vec3  goochWarm
    if (hasMatBlockMember(GoochMixinBlockMember      )) { ao = alignOffset( 4, bo); bo = ao + sizeof( Real32); }  // float goochMixin
    if (hasMatBlockMember(GoochCoolMixinBlockMember  )) { ao = alignOffset( 4, bo); bo = ao + sizeof( Real32); }  // float goochCoolMixin
    if (hasMatBlockMember(GoochWarmMixinBlockMember  )) { ao = alignOffset( 4, bo); bo = ao + sizeof( Real32); }  // float goochWarmMixin
    if (hasMatBlockMember(ToonLevelsBlockMember      )) { ao = alignOffset( 4, bo); bo = ao + sizeof(  Int32); }  // int   toonLevels

    //
    // We must use this for-loop in order to get a defined TexData order in the shader
    //
    for (UInt32 texType = 0; texType < TextureDesc::MAX_NUM_TEXTURE_TYPES; ++texType)
    {
        switch (evalFragtProgTexType(texType))
        {
            case DISCARD:
                break;
            case IS_COLOR_DATA:
                ao = alignOffset(16, bo); bo = ao + sizeof(Color3f);   // vec3  baseColor
                break;
            case IS_SINGLE_DATA:
            case IS_STACK_DATA:
            case IS_ENV_DATA:
                calcFragBufferTexDataSize(ao, bo, texType, mapTexDecs);
                break;
        }
    }

    ao = alignOffset(16, bo); bo = ao; // padding

    return ao;
}

void DescMaterial::calcFragBufferTexDataSize(
    std::size_t&               ao,
    std::size_t&               bo,
    UInt32                     texType,
    const TexDescPairStoreMap& mapTexDecs) const
{
    //struct StackTexData
    //{
    //    vec3  baseColor;
    //    int   size;
    //    bool  isSRGB   [ciMaxTextureStackSize];
    //    int   flags    [ciMaxTextureStackSize];
    //    int   ops      [ciMaxTextureStackSize];
    //    float strengths[ciMaxTextureStackSize];
    //    int   indices  [ciMaxTextureStackSize];
    //};

    //struct SingleTexData
    //{
    //    vec3  baseColor;
    //    bool  isSRGB;
    //    int   flags;
    //    int   op;
    //    float strength;
    //    int   index;
    //};

    //struct EnvTexData
    //{
    //    bool  isSRGB;
    //    float strength;
    //    int   index;
    //};

    TexDescPairStoreMap::const_iterator map_iter = mapTexDecs.find(texType);
    if (map_iter != mapTexDecs.end())
    {
        const TexDescPairStore& texDescPairStore = map_iter->second;

        if (texDescPairStore.size() == 1)
        {
            const TexDescPair& texDescPair = *texDescPairStore.begin();

            TextureDesc* texDesc = texDescPair.first;

            if (texDesc->isEnvironmentMap())
            {
                // Rule: If the member is a structure, the base alignment of the structure is N , where N
                //       is the largest base alignment value of any of its members, and rounded up to the 
                //       base alignment of a vec4.
                ao = alignOffset(16, bo); bo = ao;

                ao = alignOffset( 4, bo); bo = ao + sizeof(  Int32);    // bool  isSRGB
                ao = alignOffset( 4, bo); bo = ao + sizeof( Real32);    // float strength
                ao = alignOffset( 4, bo); bo = ao + sizeof(  Int32);    // int   index
            }
            else
            {
                // Rule: If the member is a structure, the base alignment of the structure is N , where N
                //       is the largest base alignment value of any of its members, and rounded up to the 
                //       base alignment of a vec4.
                ao = alignOffset(16, bo); bo = ao;

                ao = alignOffset(16, bo); bo = ao + sizeof(Color3f);    // vec3  baseColor
                ao = alignOffset( 4, bo); bo = ao + sizeof(  Int32);    // bool  isSRGB
                ao = alignOffset( 4, bo); bo = ao + sizeof(  Int32);    // int   flags
                ao = alignOffset( 4, bo); bo = ao + sizeof(  Int32);    // int   op
                ao = alignOffset( 4, bo); bo = ao + sizeof( Real32);    // float strength
                ao = alignOffset( 4, bo); bo = ao + sizeof(  Int32);    // int   index
            }
        }
        else
        {
            // Rule: If the member is a structure, the base alignment of the structure is N , where N
            //       is the largest base alignment value of any of its members, and rounded up to the 
            //       base alignment of a vec4.
            ao = alignOffset(16, bo); bo = ao;

            ao = alignOffset(16, bo); bo = ao + sizeof(Color3f);    // vec3  baseColor
            ao = alignOffset( 4, bo); bo = ao + sizeof(  Int32);    // int   size

            for (UInt32 i = 0; i < cuiMaxTextureStackSize; ++i)
            {
                ao = alignOffset(16, bo); bo = ao + sizeof( Int32); // bool  isSRGB   [ciMaxTextureStackSize]
            }
            ao = alignOffset(16, bo); bo = ao;                      // padding

            for (UInt32 i = 0; i < cuiMaxTextureStackSize; ++i)
            {
                ao = alignOffset(16, bo); bo = ao + sizeof(Int32);  // int   flags    [ciMaxTextureStackSize]
            }
            ao = alignOffset(16, bo); bo = ao;                      // padding

            for (UInt32 i = 0; i < cuiMaxTextureStackSize; ++i)
            {
                ao = alignOffset(16, bo); bo = ao + sizeof(Int32);  // int   ops      [ciMaxTextureStackSize]
            }
            ao = alignOffset(16, bo); bo = ao;                      // padding

            for (UInt32 i = 0; i < cuiMaxTextureStackSize; ++i)
            {
                ao = alignOffset(16, bo); bo = ao + sizeof(Real32); // float strengths[ciMaxTextureStackSize]
            }
            ao = alignOffset(16, bo); bo = ao;                      // padding

            for (UInt32 i = 0; i < cuiMaxTextureStackSize; ++i)
            {
                ao = alignOffset(16, bo); bo = ao + sizeof(Int32);  // int   indices  [cuiMaxTextureStackSize]
            }
            ao = alignOffset(16, bo); bo = ao;                      // padding
        }
    }
}

void DescMaterial::fillFragBuffer(
    MaterialDesc*              matDesc,
    std::vector<UInt8>&        buffer, 
    const TexDescPairStoreMap& mapTexDecs) const
{
    //layout (std140) uniform FragDescMaterialBlock
    //{
    //    float   specularStrength;
    //    float   emissiveStrength;
    //    float   opacityCutOff;
    //    float   reflectivity;
    //    float   reflectance;
    //    float   bumpScaling;
    //    vec3    transparent;
    //    vec3    reflective;
    //    vec3    goochCool;
    //    vec3    goochWarm;
    //    float   goochMixin;
    //    float   goochCoolMixin;
    //    float   goochWarmMixin;
    //    int     toonLevels;
    //    TexData albedo;
    //    TexData specular;
    //    TexData emissive;
    //    TexData shininess;
    //    TexData opacity;
    //    TexData normal;
    //    TexData height;
    //    TexData displacement;
    //    TexData reflection;
    //    TexData refraction;
    //    TexData anisotropyU;
    //    TexData anisotropyV;
    //    TexData anisotropyUV;
    //    TexData ambientOcclusion;
    //    TexData roughness;
    //    TexData metalness;
    //    TexData metalRough;
    //    TexData metalRoughOpacity
    //    TexData irradiance;
    //    TexData preFilterColor;
    //    TexData brdf;
    //    TexData standard;
    //    TexData metalRoughDispOcc;
    //    TexData metalRoughDisp;
    //    TexData roughDispOcc;
    //    TexData roughDisp;
    //};

    Real32  specularStrength  = matDesc->getSpecularStrength();
    Real32  emissiveStrength  = matDesc->getEmissiveStrength();
    Real32  opacityCutOff     = matDesc->getOpacityCutOff();
    Real32  reflectivity      = matDesc->getReflectivity();
    Real32  reflectance       = matDesc->getReflectance();
    Real32  bumpScaling       = matDesc->getBumpScaling();
    Color3f transparent       = matDesc->getTransparent();
    Color3f reflective        = matDesc->getReflective();
    Color3f goochCool         = matDesc->getGoochCool();
    Color3f goochWarm         = matDesc->getGoochWarm();
    Real32  goochMixin        = matDesc->getGoochMixin();
    Real32  goochCoolMixin    = matDesc->getGoochCoolMixin();
    Real32  goochWarmMixin    = matDesc->getGoochWarmMixin();
    Int32   toonLevels        = matDesc->getToonLevels();

    if (matDesc->getSRGBColorMode())
    {
        transparent = sRGBToLinear(transparent);
        reflective  = sRGBToLinear(reflective);

        goochCool   = sRGBToLinear(goochCool);
        goochWarm   = sRGBToLinear(goochWarm);
    }

    std::size_t ao = 0; // aligned offset
    std::size_t bo = 0; // base offset
    
    if (hasMatBlockMember(SpecularStrengthBlockMember)) { ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = specularStrength;  bo = ao + sizeof( Real32); }  // float specularStrength
    if (hasMatBlockMember(EmissiveStrengthBlockMember)) { ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = emissiveStrength;  bo = ao + sizeof( Real32); }  // float emissiveStrength
    if (hasMatBlockMember(OpacityCutOffBlockMember   )) { ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = opacityCutOff;     bo = ao + sizeof( Real32); }  // float opacityCutOff
    if (hasMatBlockMember(ReflectivityBlockMember    )) { ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = reflectivity;      bo = ao + sizeof( Real32); }  // float reflectivity
    if (hasMatBlockMember(ReflectanceBlockMember     )) { ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = reflectance;       bo = ao + sizeof( Real32); }  // float reflectance
    if (hasMatBlockMember(BumpScalingBlockMember     )) { ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = bumpScaling;       bo = ao + sizeof( Real32); }  // float bumpScaling
    if (hasMatBlockMember(TransparentBlockMember     )) { ao = alignOffset(16, bo); memcpy(&buffer[0] + ao,   &transparent[0], sizeof(Color3f));       bo = ao + sizeof(Color3f); }  // vec3  transparent
    if (hasMatBlockMember(ReflectiveBlockMember      )) { ao = alignOffset(16, bo); memcpy(&buffer[0] + ao,   &reflective[0],  sizeof(Color3f));       bo = ao + sizeof(Color3f); }  // vec3  reflective
    if (hasMatBlockMember(GoochCoolBlockMember       )) { ao = alignOffset(16, bo); memcpy(&buffer[0] + ao,   &goochCool[0],   sizeof(Color3f));       bo = ao + sizeof(Color3f); }  // vec3  goochCool
    if (hasMatBlockMember(GoochWarmBlockMember       )) { ao = alignOffset(16, bo); memcpy(&buffer[0] + ao,   &goochWarm[0],   sizeof(Color3f));       bo = ao + sizeof(Color3f); }  // vec3  goochWarm
    if (hasMatBlockMember(GoochMixinBlockMember      )) { ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = goochMixin;        bo = ao + sizeof( Real32); }  // float goochMixin
    if (hasMatBlockMember(GoochCoolMixinBlockMember  )) { ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = goochCoolMixin;    bo = ao + sizeof( Real32); }  // float goochCoolMixin
    if (hasMatBlockMember(GoochWarmMixinBlockMember  )) { ao = alignOffset( 4, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = goochWarmMixin;    bo = ao + sizeof( Real32); }  // float goochWarmMixin
    if (hasMatBlockMember(ToonLevelsBlockMember      )) { ao = alignOffset( 4, bo); *(reinterpret_cast< Int32*>(&buffer[0] + ao)) = toonLevels;        bo = ao + sizeof(  Int32); }  // int   toonLevels

    for (UInt32 texType = 0; texType < TextureDesc::MAX_NUM_TEXTURE_TYPES; ++texType)
    {
        Color3f baseColor = getBaseColor(matDesc, texType);

        switch (evalFragtProgTexType(texType))
        {
            case DISCARD:
                break;
            case IS_COLOR_DATA:
                ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &baseColor[0], sizeof(Color3f)); bo = ao + sizeof(Color3f);   // vec3        baseColor
                break;
            case IS_SINGLE_DATA:
            case IS_STACK_DATA:
            case IS_ENV_DATA:
                fillFragBufferTexData(buffer, ao, bo, baseColor, texType, mapTexDecs);
                break;
        }
    }
}

void DescMaterial::fillFragBufferTexData(
    std::vector<UInt8>&        buffer, 
    std::size_t&               ao,
    std::size_t&               bo,
    const Color3f&             baseColor,
    UInt32                     texType,
    const TexDescPairStoreMap& mapTexDecs) const
{
    //struct StackTexData
    //{
    //    vec3  baseColor;
    //    int   size;
    //    bool  isSRGB   [ciMaxTextureStackSize];
    //    int   flags    [ciMaxTextureStackSize];
    //    int   ops      [ciMaxTextureStackSize];
    //    float strengths[ciMaxTextureStackSize];
    //    int   indices  [ciMaxTextureStackSize];
    //};

    //struct SingleTexData
    //{
    //    vec3  baseColor;
    //    bool  isSRGB;
    //    int   flags;
    //    int   op;
    //    float strength;
    //    int   index;
    //};

    //struct EnvTexData
    //{
    //    bool  isSRGB;
    //    float strength;
    //    int   index;
    //};

    TexDescPairStoreMap::const_iterator map_iter = mapTexDecs.find(texType);
    if (map_iter != mapTexDecs.end())
    {
        const TexDescPairStore& texDescPairStore = map_iter->second;

        if (texDescPairStore.size() == 1)
        {
            const TexDescPair& texDescPair = *texDescPairStore.begin();

            TextureDesc* texDesc  =                    texDescPair.first;
            Int32        index    = static_cast<Int32>(texDescPair.second);

            bool   isSRGB   = _isSRGBTextures[index];
            Int32  flags    = static_cast<Int32>(texDesc->getTextureFlags());
            Int32  op       = static_cast<Int32>(texDesc->getOperation   ());
            Real32 strength =                    texDesc->getBlendFactor ();

            if (texDesc->isEnvironmentMap())
            {
                // Rule: If the member is a structure, the base alignment of the structure is N , where N
                //       is the largest base alignment value of any of its members, and rounded up to the 
                //       base alignment of a vec4.
                ao = alignOffset(16, bo); bo = ao;

                ao = alignOffset( 4, bo); *(reinterpret_cast<  Int32*>(&buffer[0] + ao)) = isSRGB;      bo = ao + sizeof(  Int32); // bool  isSRGB
                ao = alignOffset( 4, bo); *(reinterpret_cast< Real32*>(&buffer[0] + ao)) = strength;    bo = ao + sizeof( Real32); // float strength
                ao = alignOffset( 4, bo); *(reinterpret_cast<  Int32*>(&buffer[0] + ao)) = index;       bo = ao + sizeof(  Int32); // int   index
            }
            else
            {
                // Rule: If the member is a structure, the base alignment of the structure is N , where N
                //       is the largest base alignment value of any of its members, and rounded up to the 
                //       base alignment of a vec4.
                ao = alignOffset(16, bo); bo = ao;

                ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &baseColor[0], sizeof(Color3f)); bo = ao + sizeof(Color3f);   // vec3  baseColor

                ao = alignOffset( 4, bo); *(reinterpret_cast<  Int32*>(&buffer[0] + ao)) = isSRGB;      bo = ao + sizeof(  Int32); // bool  isSRGB
                ao = alignOffset( 4, bo); *(reinterpret_cast<  Int32*>(&buffer[0] + ao)) = flags;       bo = ao + sizeof(  Int32); // int   flags
                ao = alignOffset( 4, bo); *(reinterpret_cast<  Int32*>(&buffer[0] + ao)) = op;          bo = ao + sizeof(  Int32); // int   op
                ao = alignOffset( 4, bo); *(reinterpret_cast< Real32*>(&buffer[0] + ao)) = strength;    bo = ao + sizeof( Real32); // float strength
                ao = alignOffset( 4, bo); *(reinterpret_cast<  Int32*>(&buffer[0] + ao)) = index;       bo = ao + sizeof(  Int32); // int   index
            }
        }
        else
        {
            // Rule: If the member is a structure, the base alignment of the structure is N , where N
            //       is the largest base alignment value of any of its members, and rounded up to the 
            //       base alignment of a vec4.
            ao = alignOffset(16, bo); bo = ao;

            UInt32 size = static_cast<UInt32>(texDescPairStore.size());

            OSG_ASSERT(size <= cuiMaxTextureStackSize);

            std::vector<bool>   vecIsSRGB   (cuiMaxTextureStackSize, false);
            std::vector<Int32>  vecFlags    (cuiMaxTextureStackSize, 0);
            std::vector<Int32>  vecOps      (cuiMaxTextureStackSize, 0);
            std::vector<Real32> vecStrengths(cuiMaxTextureStackSize, 0.f);
            std::vector<Int32>  vecIndices  (cuiMaxTextureStackSize, 0);

            for (std::size_t i = 0; i < size; ++i)
            {
                const TexDescPair& texDescPair = texDescPairStore[i];

                TextureDesc* texDesc =                    texDescPair.first;
                Int32        index   = static_cast<Int32>(texDescPair.second);

                bool   isSRGB    = _isSRGBTextures[index];
                Int32 flags      = static_cast<Int32>(texDesc->getTextureFlags());
                Int32 op         = static_cast<Int32>(texDesc->getOperation   ());
                Real32 strength  =                    texDesc->getBlendFactor ();

                vecIsSRGB   [i] = isSRGB;
                vecFlags    [i] = flags;
                vecOps      [i] = op;
                vecStrengths[i] = strength;
                vecIndices  [i] = index;
            }

            ao = alignOffset(16, bo); memcpy(&buffer[0] + ao, &baseColor[0], sizeof(Color3f)); bo = ao + sizeof(Color3f);             // vec3  baseColor
            ao = alignOffset( 4, bo); *(reinterpret_cast< Int32*>(&buffer[0] + ao)) = size;    bo = ao + sizeof(  Int32);             // int   size

            UInt32 sz = static_cast<UInt32>(vecIndices.size());

            for (UInt32 i = 0; i < cuiMaxTextureStackSize; ++i)
            {
                ao = alignOffset(16, bo); *(reinterpret_cast< Int32*>(&buffer[0] + ao)) = vecIsSRGB[i];         bo = ao + sizeof( Int32); // bool  isSRGB   [ciMaxTextureStackSize]
            }
            ao = alignOffset(16, bo); bo = ao;                                                                                            // padding

            for (UInt32 i = 0; i < cuiMaxTextureStackSize; ++i)
            {
                ao = alignOffset(16, bo); *(reinterpret_cast< Int32*>(&buffer[0] + ao)) = vecFlags[i];          bo = ao + sizeof( Int32); // int   flags    [ciMaxTextureStackSize]
            }
            ao = alignOffset(16, bo); bo = ao;                                                                                            // padding

            for (UInt32 i = 0; i < cuiMaxTextureStackSize; ++i)
            {
                ao = alignOffset(16, bo); *(reinterpret_cast< Int32*>(&buffer[0] + ao)) = vecOps[i];            bo = ao + sizeof( Int32); // int   ops      [ciMaxTextureStackSize]
            }
            ao = alignOffset(16, bo); bo = ao;                                                                                            // padding

            for (UInt32 i = 0; i < cuiMaxTextureStackSize; ++i)
            {
                ao = alignOffset(16, bo); *(reinterpret_cast<Real32*>(&buffer[0] + ao)) = vecStrengths[i];      bo = ao + sizeof(Real32); // float strengths[ciMaxTextureStackSize]
            }
            ao = alignOffset(16, bo); bo = ao;                                                                                            // padding

            for (UInt32 i = 0; i < cuiMaxTextureStackSize; ++i)
            {
                ao = alignOffset(16, bo); *(reinterpret_cast< Int32*>(&buffer[0] + ao)) = vecIndices[i];        bo = ao + sizeof( Int32); // int   indices  [ciMaxTextureStackSize]
            }
            ao = alignOffset(16, bo); bo = ao;                                                                                            // padding
        }
    }
}

/*-------------------------------- sRGB -----------------------------------*/

Color3f DescMaterial::sRGBToLinear(const Color3f& c) const
{
    Real32 r = c.red();
    Real32 g = c.green();
    Real32 b = c.blue();

    r = sRGBToLinear(r);
    g = sRGBToLinear(g);
    b = sRGBToLinear(b);

    return Color3f(r,g,b);
}

Real32 DescMaterial::sRGBToLinear(Real32 x) const
{
    return (x <= 0.04045) ? x / 12.92 : osgPow((x + 0.055) / 1.055, 2.4);
}

/*------------------------------- Helper -----------------------------------*/

bool DescMaterial::getImages(
    const TextureDesc* texDesc,
    ImageStore&        images) const
{
    if (images.size() != 6)
        images.resize(6, NULL);

    images[TextureDesc::POS_X] = texDesc->getTexImage(TextureDesc::POS_X);
    images[TextureDesc::POS_Y] = texDesc->getTexImage(TextureDesc::POS_Y);
    images[TextureDesc::POS_Z] = texDesc->getTexImage(TextureDesc::POS_Z);
    images[TextureDesc::NEG_X] = texDesc->getTexImage(TextureDesc::NEG_X);
    images[TextureDesc::NEG_Y] = texDesc->getTexImage(TextureDesc::NEG_Y);
    images[TextureDesc::NEG_Z] = texDesc->getTexImage(TextureDesc::NEG_Z);

    return ( images[TextureDesc::POS_X] != NULL && images[TextureDesc::POS_Y] != NULL && images[TextureDesc::POS_Z] != NULL
          && images[TextureDesc::NEG_X] != NULL && images[TextureDesc::NEG_Y] != NULL && images[TextureDesc::NEG_Z] != NULL );
}

bool DescMaterial::setTexData(
    const TextureDesc* texDesc, 
    Image*             image,
    bool               isSRGBTexture,
    TextureObjChunk*   texObjChunk) const
{
    if (image)
    {
        GLenum pixelFormat = image->getPixelFormat();
        GLenum dataType    = image->getDataType();

        GLenum        internalFormat = texDesc->getInternalFormat();
        GLenum        externalFormat = texDesc->getExternalFormat();
        GLenum adaptedInternalFormat = texDesc->getAdaptedInternalFormat(pixelFormat, dataType);

        if (adaptedInternalFormat != GL_NONE)
        {
            internalFormat = adaptedInternalFormat;
        }

        if (internalFormat == GL_SRGB || internalFormat == GL_SRGB_ALPHA)
        {
            isSRGBTexture = false;
        }

        texObjChunk->setMinFilter     (texDesc->getMinFilter());
        texObjChunk->setMagFilter     (texDesc->getMagFilter());

        texObjChunk->setWrapS         (texDesc->getWrapS());
        texObjChunk->setWrapT         (texDesc->getWrapT());
        texObjChunk->setWrapR         (texDesc->getWrapR());

        texObjChunk->setInternalFormat(internalFormat);
        texObjChunk->setExternalFormat(texDesc->getExternalFormat());

        texObjChunk->setAnisotropy    (texDesc->getAnisotropy ());

        //
        // Hack: What we normally want to do is to set the border
        //       color in order to handle GL_CLAMP_TO_BORDER.
        //       Because that is not working properly, we hack
        //       the border color with the albedo color.
        // ToDo: Resolve the problem
        //
        Vec4f bordercolor = texDesc->getBorderColor();

        UInt32 texType = texDesc->getTextureType();
        if (texType == TextureDesc::ALBEDO_TEXTURE)
        {
            MaterialDesc* matDesc = getMaterialDesc   ();
            Vec3f bordercolor3 = matDesc->getAlbedo();
            bordercolor = Vec4f(bordercolor3.x(),bordercolor3.y(),bordercolor3.z(),1.0);
        }
        texObjChunk->setBorderColor   (bordercolor);
    }

    return isSRGBTexture;
}

Color3f DescMaterial::getBaseColor(MaterialDesc* matDesc, UInt32 texType) const
{
    Color3f color(1.f, 1.f, 1.f);
    Real32  value;

    switch (texType)
    {
        case TextureDesc::ALBEDO_TEXTURE:
            color = matDesc->getAlbedo();
            if (matDesc->getSRGBColorMode())
            {
                color = sRGBToLinear(color);
            }
            break;
        case TextureDesc::SPECULAR_TEXTURE:
            color = matDesc->getSpecular();
            if (matDesc->getSRGBColorMode())
            {
                color = sRGBToLinear(color);
            }
            break;
        case TextureDesc::EMISSIVE_TEXTURE:
            color = matDesc->getEmissive();
            if (matDesc->getSRGBColorMode())
            {
                color = sRGBToLinear(color);
            }
            break;
        case TextureDesc::SHININESS_TEXTURE:
            value = matDesc->getShininess();
            color = Color3f(value, value, value);
            break;
        case TextureDesc::OPACITY_TEXTURE:
            value = matDesc->getOpacity();
            color = Color3f(value, value, value);
            break;
        case TextureDesc::NORMALS_TEXTURE:
        case TextureDesc::HEIGHT_TEXTURE:
        case TextureDesc::DISPLACEMENT_TEXTURE:
            break;
        case TextureDesc::REFLECTION_TEXTURE:
        case TextureDesc::REFRACTION_TEXTURE:
            break;
        case TextureDesc::ANISOTROPY_U_TEXTURE:
        case TextureDesc::ANISOTROPY_V_TEXTURE:
        case TextureDesc::ANISOTROPY_UV_TEXTURE:
        case TextureDesc::AMBIENT_OCCLUSION_TEXTURE:
            break;
        case TextureDesc::ROUGH_TEXTURE:
            value = matDesc->getRoughness();
            color = Color3f(value, value, value);
            break;
        case TextureDesc::METAL_TEXTURE:
            value = matDesc->getMetalness();
            color = Color3f(value, value, value);
            break;
        case TextureDesc::ROUGH_METAL_TEXTURE:
            {
                Real32 r = matDesc->getRoughness();
                Real32 m = matDesc->getMetalness();

                color = Color3f(0.f, r, m);
            }
            break;
        case TextureDesc::OCCL_ROUGH_METAL_TEXTURE:
            {
                Real32 r = matDesc->getRoughness();
                Real32 m = matDesc->getMetalness();

                color = Color3f(1.f, r, m);
            }
            break;
            break;
        case TextureDesc::IRRADIANCE_TEXTURE:
        case TextureDesc::PRE_FILTER_TEXTURE:
        case TextureDesc::BRDF_LUT_TEXTURE:
            break;
        case TextureDesc::STANDARD_MATERIAL_TEXTURE:
            break;
    }
    
    return color;
}

bool DescMaterial::hasFragBlockEntry(UInt32 texType, UInt32 texMapDetails) const
{
    switch (texType)
    {
        case TextureDesc::NONE_TEXTURE:
        case TextureDesc::UNKNOWN_TEXTURE:
            return false;

        case TextureDesc::ALBEDO_TEXTURE:
        case TextureDesc::SPECULAR_TEXTURE:
        case TextureDesc::EMISSIVE_TEXTURE:
        case TextureDesc::SHININESS_TEXTURE:
            return true;

        case TextureDesc::OPACITY_TEXTURE:
            return true;

        case TextureDesc::NORMALS_TEXTURE:
        case TextureDesc::HEIGHT_TEXTURE:
        case TextureDesc::DISPLACEMENT_TEXTURE:
            return true;

        case TextureDesc::REFLECTION_TEXTURE:
        case TextureDesc::REFRACTION_TEXTURE:
            return true;

        case TextureDesc::ANISOTROPY_U_TEXTURE:
        case TextureDesc::ANISOTROPY_V_TEXTURE:
            if (hasTexMapDetail(AnisotropyUVTextures))
            {
                return false;
            }
            if (hasTexMapDetail(AnisotropyUTextures) || hasTexMapDetail(AnisotropyVTextures))
            {
                return false;
            }
            return true;

        case TextureDesc::ANISOTROPY_UV_TEXTURE:
            return true;

        case TextureDesc::AMBIENT_OCCLUSION_TEXTURE:
            return true;

        case TextureDesc::ROUGH_TEXTURE:
            if (hasTexMapDetail(RoughMetalTextures))
            {
                return false;
            }
            if (hasTexMapDetail(OcclRoughMetalTextures))
            {
                return false;
            }
            return true;

        case TextureDesc::METAL_TEXTURE:
            if (hasTexMapDetail(RoughMetalTextures))
            {
                return false;
            }
            if (hasTexMapDetail(OcclRoughMetalTextures))
            {
                return false;
            }
            return true;
        case TextureDesc::ROUGH_METAL_TEXTURE:
            if (hasTexMapDetail(OcclRoughMetalTextures))
            {
                return false;
            }
            return true;
        case TextureDesc::OCCL_ROUGH_METAL_TEXTURE:
            return true;

        case TextureDesc::IRRADIANCE_TEXTURE:
        case TextureDesc::PRE_FILTER_TEXTURE:
        case TextureDesc::BRDF_LUT_TEXTURE:
            return true;
        case TextureDesc::STANDARD_MATERIAL_TEXTURE:
            if (hasTexMapDetail(StandardMaterialTextures))
            {
                return true;
            }
            return false;
    }
    return false;
}

DescMaterial::TexTypeEvalInfo DescMaterial::evalFragtProgTexType(UInt32 texType) const
{
    TexTypeEvalInfo result = DISCARD;

    if (hasFragBlockEntry(texType, _info.texMapDetails))
    {
        UInt32 detail = (1 << texType);
        if ((_info.texMapDetails & detail) == 0)
        {
            if (_hasFragBlockColorEntry[texType] && !_info.textureSuppressed[texType])
            {
                OSG_ASSERT(_info.textureOccurrences[texType] == 0);
                result = IS_COLOR_DATA;
            }
        }
        else
        {
            if (_textureIsEnvMap[texType])
            {
                result = IS_ENV_DATA;
            }
            else
            switch(_info.textureOccurrences[texType])
            {
                case 0:  break;
                case 1:  result = IS_SINGLE_DATA; break;
                default: result = IS_STACK_DATA;  break;
            }
        }
    }

    return result;
}

/*------------------------- Shader Code Snippet -----------------------------*/

std::string DescMaterial::getVertexProgramSnippet() const
{
    EnvironmentDesc* envDesc = getEnvironmentDesc();
    MaterialDesc*    matDesc = getMaterialDesc   ();

    if (!matDesc)
        return std::string();

    _info.initialize(matDesc, envDesc, getTexUnitOffsetRT(), getCapabilitiesDesc());

    std::stringstream ost;

    getVertexProgramSnippet(ost);

    return ost.str();
}

DescMaterial::PairShadersT DescMaterial::getFragmentProgramSnippet() const
{
    EnvironmentDesc* envDesc = getEnvironmentDesc();
    MaterialDesc*    matDesc = getMaterialDesc   ();
    if (!matDesc)
        return PairShadersT();

    _info.initialize(matDesc, envDesc, getTexUnitOffsetRT(), getCapabilitiesDesc());

    std::stringstream ostDecl, ostImpl;

    getFragmentProgramSnippet(ostDecl, ostImpl);

    return std::make_pair(ostDecl.str(), ostImpl.str());
}

/*---------------------------------------------------------------------------*\
**
**     Shader Code generation
**
\*---------------------------------------------------------------------------*/

/*----------------------- Vertex Shader Code --------------------------------*/

void DescMaterial::getVertexProgramSnippet(std::stringstream& ost) const
{
    //
    // The vertex shader does only bother with UV textures, i.e. from the textureDescs list
    //
    UInt32 numUVTextures = _info.numUVTextures;
    UInt32 numUVChannels = _info.numUVChannels;

    switch (_info.vertOptVariant)
    {
        case NoTextures:         getVertexProgramDetailNoTextures   (ost);                               break;
        case FullImplementation: getVertexProgramDetailFullImpl     (ost, numUVTextures, numUVChannels); break;
        case OptOnlyTransform:   getVertexProgramDetailOnlyTransform(ost, numUVTextures);                break;
        case OptOnlyChannels:    getVertexProgramDetailOnlyChannels (ost, numUVTextures, numUVChannels); break;
        case OptOnlyChannel0:    getVertexProgramDetailOnlyChannel0 (ost, numUVTextures);                break;
    }
}

void DescMaterial::getVertexProgramDetailNoTextures(std::stringstream& ost) const
{
    using namespace std;
}

void DescMaterial::getVertexProgramDetailFullImpl(std::stringstream& ost, UInt32 numUVTextures, UInt32 numUVChannels) const
{
    using namespace std;

    string out = (isFallbackShader2() ? "varying" : "out");

    ost
    << endl << "const int ciNumUVTextures = " << numUVTextures << ";"
    << endl << ""
    << endl << out << " " << "vec2 vTexCoords[ciNumUVTextures];"
    << endl << ""
    << endl << "struct TextureUVData"
    << endl << "{"
    << endl << "    int  channel;"
    << endl << "    bool hasTransform;"
    << endl << "    mat4 transform;"
    << endl << "};"
    << endl << ""
    ;

    if (isFallbackShader2())
    {
        ost
        << endl << "struct " << getVertUniformBlockName()
        << endl << "{"
        << endl << "    TextureUVData uvData[ciNumUVTextures];"
        << endl << "};"
        << endl << ""
        << endl << "uniform " << getVertUniformBlockName() << " textureDesc;"
        << endl << ""
        ;
    }
    else
    {
        ost
        << endl << "layout (std140) uniform " << getVertUniformBlockName()
        << endl << "{"
        << endl << "    TextureUVData uvData[ciNumUVTextures];"
        << endl << "} textureDesc;"
        << endl << ""
        ;
    }

    ost
    << endl << "void CalcTexCoords()"
    << endl << "{"
    << endl << "    vec2 texCoords[" << numUVChannels << "];"
    << endl << ""
    ;

    for (UInt32 channel = 0; channel < numUVChannels; ++channel)
    {
        ost 
        << endl << "    texCoords[" << channel << "] = aTexCoords" << channel << ";"
        ;
    }

    ost
    << endl << ""
    << endl << "    for (int i = 0; i < ciNumUVTextures; ++i)"
    << endl << "    {"
    << endl << "        bool hasTransform = textureDesc.uvData[i].hasTransform;"
    << endl << "        int  channel      = textureDesc.uvData[i].channel;"
    << endl << ""
    << endl << "        vec2 uv = texCoords[channel];"
    << endl << ""
    << endl << "        if (hasTransform)"
    << endl << "        {"
    << endl << "            mat4 T = textureDesc.uvData[i].transform;"
    << endl << "            uv = (T * vec4(uv,1,1)).xy;"
    << endl << "        }"
    << endl << ""
    << endl << "        vTexCoords[i] = uv;"
    << endl << "    }"
    << endl << "}"
    << endl << ""
    ;
}

void DescMaterial::getVertexProgramDetailOnlyTransform(std::stringstream& ost, UInt32 numUVTextures) const
{
    using namespace std;

    string out = (isFallbackShader2() ? "varying" : "out");

    ost
    << endl << "const int ciNumUVTextures = " << numUVTextures << ";"
    << endl << ""
    << endl << out << " " << "vec2 vTexCoords[ciNumUVTextures];"
    << endl << ""
    << endl << "struct TextureUVData"
    << endl << "{"
    << endl << "    bool hasTransform;"
    << endl << "    mat4 transform;"
    << endl << "};"
    << endl << ""
    ;

    if (isFallbackShader2())
    {
        ost
        << endl << "struct " << getVertUniformBlockName()
        << endl << "{"
        << endl << "    TextureUVData uvData[ciNumUVTextures];"
        << endl << "};"
        << endl << ""
        << endl << "uniform " << getVertUniformBlockName() << " textureDesc;"
        << endl << ""
        ;
    }
    else
    {
        ost
        << endl << "layout (std140) uniform " << getVertUniformBlockName()
        << endl << "{"
        << endl << "    TextureUVData uvData[ciNumUVTextures];"
        << endl << "} textureDesc;"
        << endl << ""
        ;
    }

    ost
    << endl << "void CalcTexCoords()"
    << endl << "{"
    << endl << "    for (int i = 0; i < ciNumUVTextures; ++i)"
    << endl << "    {"
    << endl << "        bool hasTransform = textureDesc.uvData[i].hasTransform;"
    << endl << ""
    << endl << "        vec2 uv = aTexCoords0;"
    << endl << ""
    << endl << "        if (hasTransform)"
    << endl << "        {"
    << endl << "            mat4 T = textureDesc.uvData[i].transform;"
    << endl << "            uv = (T * vec4(uv,1,1)).xy;"
    << endl << "        }"
    << endl << ""
    << endl << "        vTexCoords[i] = uv;"
    << endl << "    }"
    << endl << "}"
    << endl << ""
    ;
}

void DescMaterial::getVertexProgramDetailOnlyChannels(std::stringstream& ost, UInt32 numUVTextures, UInt32 numUVChannels) const
{
    using namespace std;

    string out = (isFallbackShader2() ? "varying" : "out");

    ost
    << endl << "const int ciNumUVTextures = " << numUVTextures << ";"
    << endl << ""
    << endl << out << " " << "vec2 vTexCoords[ciNumUVTextures];"
    << endl << ""
    << endl << "struct TextureUVData"
    << endl << "{"
    << endl << "    int channel;"
    << endl << "};"
    << endl << ""
    ;

    if (isFallbackShader2())
    {
        ost
        << endl << "struct " << getVertUniformBlockName()
        << endl << "{"
        << endl << "    TextureUVData uvData[ciNumUVTextures];"
        << endl << "};"
        << endl << ""
        << endl << "uniform " << getVertUniformBlockName() << " textureDesc;"
        << endl << ""
        ;
    }
    else
    {
        ost
        << endl << "layout (std140) uniform " << getVertUniformBlockName()
        << endl << "{"
        << endl << "    TextureUVData uvData[ciNumUVTextures];"
        << endl << "} textureDesc;"
        << endl << ""
        ;
    }

    ost
    << endl << "void CalcTexCoords()"
    << endl << "{"
    << endl << "    vec2 texCoords[" << numUVChannels << "];"
    << endl << ""
    ;

    for (UInt32 channel = 0; channel < numUVChannels; ++channel)
    {
        ost 
        << endl << "    texCoords[" << channel << "] = aTexCoords" << channel << ";"
        ;
    }

    ost
    << endl << ""
    << endl << "    for (int i = 0; i < ciNumUVTextures; ++i)"
    << endl << "    {"
    << endl << "        int channel = textureDesc.uvData[i].channel;"
    << endl << ""
    << endl << "        vec2 uv = texCoords[channel];"
    << endl << ""
    << endl << "        vTexCoords[i] = uv;"
    << endl << "    }"
    << endl << "}"
    << endl << ""
    ;
}

void DescMaterial::getVertexProgramDetailOnlyChannel0(std::stringstream& ost, UInt32 numUVTextures) const
{
    using namespace std;

    string out = (isFallbackShader2() ? "varying" : "out");

    ost
    << endl << "const int ciNumUVTextures = " << numUVTextures << ";"
    << endl << ""
    << endl << out << " " << "vec2 vTexCoord;"
    << endl << ""
    << endl << "void CalcTexCoords()"
    << endl << "{"
    << endl << "    vTexCoord = aTexCoords0;"
    << endl << "}"
    << endl << ""
    ;
}

/*---------------------- Fragment Shader Code -------------------------------*/

void DescMaterial::getFragmentProgramSnippet(std::stringstream& ostDecl, std::stringstream& ostImpl) const
{
    getFragmentProgramPreamble              (ostDecl);
    getFragmentProgramUVInput               (ostDecl);
    getFragmentProgramEnvUniformBlock       (ostDecl);
    getFragmentProgramBindTextures          (ostDecl);
    getFragmentProgramTextureData           (ostDecl);
    getFragmentProgramMatUniformBlock       (ostDecl);
    getFragmentProgramMaterialStruct        (ostDecl);

    getFragmentProgramTextureAccessUtils    (ostImpl);
    getFragmentProgramTextureAccessOpt      (ostImpl);
    getFragmentProgramTextureAccess         (ostImpl);
    getFragmentProgramTextureConstants      (ostImpl);
    getFragmentProgramTextureEvaluation     (ostImpl);
    getFragmentProgramMaterialEvaluation    (ostImpl);
    getFragmentProgramMaterialInitialization(ostImpl);
    getFragmentProgramMaterialShadingModel  (ostImpl);
    getFragmentProgramPostProcessing        (ostImpl);
}

void DescMaterial::getFragmentProgramPreamble(std::stringstream& ost) const
{
    using namespace std;

    switch (_info.getShadingModel())
    {
        case MaterialDesc::NO_SHADING_MODEL:
            break;
        case MaterialDesc::GOURAUD_SHADING_MODEL:
            break;
        case MaterialDesc::PHONG_SHADING_MODEL:
            break;
        case MaterialDesc::BLINN_PHONG_SHADING_MODEL:
            break;
        case MaterialDesc::COOK_TORRANCE_SHADING_MODEL:
            {
                ost
                << endl << "#define MAXIMUM_SPECULAR_COEFFICIENT 0.16"
                << endl << "#define DEFAULT_SPECULAR_COEFFICIENT 0.04"
                << endl << ""
                << endl << "const vec3 defaultDielectricSpecular = vec3(DEFAULT_SPECULAR_COEFFICIENT, DEFAULT_SPECULAR_COEFFICIENT, DEFAULT_SPECULAR_COEFFICIENT);"
                << endl << "const vec3 maximumDielectricSpecular = vec3(MAXIMUM_SPECULAR_COEFFICIENT, MAXIMUM_SPECULAR_COEFFICIENT, MAXIMUM_SPECULAR_COEFFICIENT);"
                << endl << ""
                ;
            }
            break;
        case MaterialDesc::OREN_NAYAR_SHADING_MODEL:
            break;
        case MaterialDesc::TOON_SHADING_MODEL:
            break;
        case MaterialDesc::GOOCH_SHADING_MODEL:
            break;
    }
}

void DescMaterial::getFragmentProgramUVInput(std::stringstream& ost) const
{
    using namespace std;

    if (_info.numUVTextures > 0)
    {
        std::string in = (isFallbackShader2() ? "varying" : "in");

        if (_info.vertOptVariant == OptOnlyChannel0)
        {
            ost
            << endl << "const int ciNumUVTextures = " << _info.numUVTextures << ";"
            << endl << ""
            << endl << in << " " << "vec2 vTexCoord;"
            << endl << ""
            ;
        }
        else
        {
            ost
            << endl << "const int ciNumUVTextures = " << _info.numUVTextures << ";"
            << endl << ""
            << endl << in << " " << "vec2 vTexCoords[ciNumUVTextures];"
            << endl << ""
            ;
        }
    }
}

void DescMaterial::getFragmentProgramEnvUniformBlock(std::stringstream& ost) const
{
    using namespace std;

    if (!anyEnvBlockMember(AllEnvBlockMemberDetails))
        return;

    std::string spc;

    spc = " ";

    //
    // The order of TexData entries corresponds to the order of the 
    // TextureDesc::TextureType enumerations by design and should not
    // be violated.
    //
    if (isFallbackShader2())
    {
        ost
        << endl << "struct " << getFragEnvUniformBlockName()
        << endl << "{"
        ;
    }
    else
    {
        ost
        << endl << "layout (std140) uniform " << getFragEnvUniformBlockName()
        << endl << "{"
        ;
    }

    if (hasEnvBlockMember(ExposureBlockMember        )) ost << endl << "    float " << spc << "exposure;" ;
    if (hasEnvBlockMember(KeyValueBlockMember        )) ost << endl << "    float " << spc << "keyValue;" ;
    if (hasEnvBlockMember(ApertureFNumberBlockMember )) ost << endl << "    float " << spc << "apertureFNumber;" ;
    if (hasEnvBlockMember(ShutterSpeedBlockMember    )) ost << endl << "    float " << spc << "shutterSpeed;" ;
    if (hasEnvBlockMember(ISOBlockMember             )) ost << endl << "    float " << spc << "iso;" ;
    if (hasEnvBlockMember(WhiteLevelBlockMember      )) ost << endl << "    float " << spc << "whiteLevel;" ;
    if (hasEnvBlockMember(DragoBiasBlockMember       )) ost << endl << "    float " << spc << "dragoBias;" ;
    if (hasEnvBlockMember(SaturationBlockMember      )) ost << endl << "    float " << spc << "saturation;" ;
    if (hasEnvBlockMember(ContrastBlockMember        )) ost << endl << "    float " << spc << "contrast;" ;
    if (hasEnvBlockMember(GammaBlockMember           )) ost << endl << "    float " << spc << "gamma;" ;
    if (hasEnvBlockMember(FilterColorBlockMember     )) ost << endl << "    vec3  " << spc << "filterColor;" ;
    if (hasEnvBlockMember(GlobalAmbientIntBlockMember)) ost << endl << "    vec3  " << spc << "ambientIntensity;" ;

    if (isFallbackShader2())
    {
        ost
        << endl << "};"
        << endl << ""
        << endl << "uniform " << getFragEnvUniformBlockName() << " environment;"
        << endl << ""
        ;
    }
    else
    {
        ost
        << endl << "} environment;"
        << endl << ""
        ;
    }
}

void DescMaterial::getFragmentProgramBindTextures(std::stringstream& ost) const
{
    using namespace std;

    Int32 texUnitOffset = getTexUnitOffsetRT();
    Int32 maxTexUnit    = 0;

    std::string spc;

    UInt32 idx = 0;

    TextureDescStore::const_iterator iter, end;

    iter = _info.textureDescs.begin();
    end  = _info.textureDescs.end  ();
    
    for (; iter != end; ++iter, ++idx)
    {
        TextureDesc* texDesc = *iter;

        Int32 texUnit = texDesc->getTexUnit();
        if (texUnit < 0) texUnit = texUnitOffset++;

        spc = texUnit < 10 && _info.maxTexUnit >= 10 ? " " : "";

        if (isFallbackShader2())
        {
            ost
            << endl << "uniform sampler2D   uTextureMap" << idx << ";"
#ifdef _DEBUG
            << "    // " << texDesc->getTextureTypeName()
#endif
            ;
        }
        else
        {
            ost
            << endl << "layout(binding = " << spc  << texUnit << ") uniform sampler2D   uTextureMap" << idx << ";"
#ifdef _DEBUG
            << "    // " << texDesc->getTextureTypeName()
#endif
            ;
        }
    }

    iter = _info.textureDescsEnv.begin();
    end  = _info.textureDescsEnv.end  ();
    
    for (; iter != end; ++iter, ++idx)
    {
        TextureDesc* texDesc = *iter;

        Int32 texUnit = texDesc->getTexUnit();
        if (texUnit < 0) texUnit = texUnitOffset++;

        spc = texUnit < 10 && _info.maxTexUnit >= 10 ? " " : "";

        OSG_ASSERT(texDesc->isEnvironmentMap());

        if (texDesc->isEquirectangularMap())
        {
            if (isFallbackShader2())
            {
                ost
                << endl << "uniform sampler2D   uTextureMap" << idx << ";"
#ifdef _DEBUG
                << "    // " << texDesc->getTextureTypeName()
#endif
                ;
            }
            else
            {
                ost
                << endl << "layout(binding = " << spc  << texUnit << ") uniform sampler2D   uTextureMap" << idx << ";"
#ifdef _DEBUG
                << "    // " << texDesc->getTextureTypeName()
#endif
                ;
            }
        }
        else
        {
            OSG_ASSERT(texDesc->isCubeMap());

            if (isFallbackShader2())
            {
                ost
                << endl << "uniform samplerCube uTextureMap" << idx << ";"
#ifdef _DEBUG
#endif
                ;
            }
            else
            {
                ost
                << endl << "layout(binding = " << spc  << texUnit << ") uniform samplerCube uTextureMap" << idx << ";"
#ifdef _DEBUG
#endif
                ;
            }

        }
    }

    if (_info.numUVChannels > 0 || _info.numEnvTextures > 0)
    {
        ost
        << endl << ""
        ;
    }
}

void DescMaterial::getFragmentProgramTextureData(std::stringstream& ost) const
{
    using namespace std;

    if (_info.hasCubeMaps || _info.hasEquirectangMaps)
    {
        ost
        << endl << "struct EnvTexData"
        << endl << "{"
        << endl << "    bool  isSRGB;"
        << endl << "    float strength;"
        << endl << "    int   index;"
        << endl << "};"
        << endl << ""
        ;
    }

    if (_info.hasSingleTexData)
    {
        ost
        << endl << "struct SingleTexData"
        << endl << "{"
        << endl << "    vec3  baseColor;"
        << endl << "    bool  isSRGB;"
        << endl << "    int   flags;"
        << endl << "    int   op;"
        << endl << "    float strength;"
        << endl << "    int   index;"
        << endl << "};"
        << endl << ""
        ;
    }

    if (_info.hasStackTexData)
    {
        ost
        << endl << "const int ciMaxTextureStackSize = " << cuiMaxTextureStackSize << ";"
        << endl << ""
        << endl << "struct StackTexData"
        << endl << "{"
        << endl << "    vec3  baseColor;"
        << endl << "    int   size;"
        << endl << "    bool  isSRGB   [ciMaxTextureStackSize];"
        << endl << "    int   flags    [ciMaxTextureStackSize];"
        << endl << "    int   ops      [ciMaxTextureStackSize];"
        << endl << "    float strengths[ciMaxTextureStackSize];"
        << endl << "    int   indices  [ciMaxTextureStackSize];"
        << endl << "};"
        << endl << ""
        ;
    }
}

void DescMaterial::getFragmentProgramMatUniformBlock(std::stringstream& ost) const
{
    using namespace std;

    std::string spc;

    spc = " ";
    if ( _info.hasSingleTexData)                          spc = "         ";
    if (!_info.hasSingleTexData && _info.hasStackTexData) spc = "         ";

    //
    // The order of TexData entries corresponds to the order of the 
    // TextureDesc::TextureType enumerations by design and should not
    // be violated.
    //
    if (isFallbackShader2())
    {
        ost
        << endl << "struct " << getFragUniformBlockName()
        << endl << "{"
        ;
    }
    else
    {
        ost
        << endl << "layout (std140) uniform " << getFragUniformBlockName()
        << endl << "{"
        ;
    }

    if (hasMatBlockMember(SpecularStrengthBlockMember)) ost << endl << "    float" << spc << "specularStrength;" ;
    if (hasMatBlockMember(EmissiveStrengthBlockMember)) ost << endl << "    float" << spc << "emissiveStrength;" ;
    if (hasMatBlockMember(OpacityCutOffBlockMember   )) ost << endl << "    float" << spc << "opacityCutOff;" ;
    if (hasMatBlockMember(ReflectivityBlockMember    )) ost << endl << "    float" << spc << "reflectivity;" ;
    if (hasMatBlockMember(ReflectanceBlockMember     )) ost << endl << "    float" << spc << "reflectance;" ;
    if (hasMatBlockMember(BumpScalingBlockMember     )) ost << endl << "    float" << spc << "bumpScaling;" ;
    if (hasMatBlockMember(TransparentBlockMember     )) ost << endl << "    vec3 " << spc << "transparent;" ;
    if (hasMatBlockMember(ReflectiveBlockMember      )) ost << endl << "    vec3 " << spc << "reflective;" ;
    if (hasMatBlockMember(GoochCoolBlockMember       )) ost << endl << "    vec3 " << spc << "goochCool;" ;
    if (hasMatBlockMember(GoochWarmBlockMember       )) ost << endl << "    vec3 " << spc << "goochWarm;" ;
    if (hasMatBlockMember(GoochMixinBlockMember      )) ost << endl << "    float" << spc << "goochMixin;" ;
    if (hasMatBlockMember(GoochCoolMixinBlockMember  )) ost << endl << "    float" << spc << "goochCoolMixin;" ;
    if (hasMatBlockMember(GoochWarmMixinBlockMember  )) ost << endl << "    float" << spc << "goochWarmMixin;" ;
    if (hasMatBlockMember(ToonLevelsBlockMember      )) ost << endl << "    int  " << spc << "toonLevels;" ;

    OSG_ASSERT(_info.textureOccurrences.size() == TextureDesc::MAX_NUM_TEXTURE_TYPES);

    getFragmentProgramMatBlockEntry(ost, spc, TextureDesc::ALBEDO_TEXTURE,                  "albedo");
    getFragmentProgramMatBlockEntry(ost, spc, TextureDesc::SPECULAR_TEXTURE,                "specular");
    getFragmentProgramMatBlockEntry(ost, spc, TextureDesc::EMISSIVE_TEXTURE,                "emissive");
    getFragmentProgramMatBlockEntry(ost, spc, TextureDesc::SHININESS_TEXTURE,               "shininess");
    getFragmentProgramMatBlockEntry(ost, spc, TextureDesc::OPACITY_TEXTURE,                 "opacity");
    getFragmentProgramMatBlockEntry(ost, spc, TextureDesc::NORMALS_TEXTURE,                 "normal");
    getFragmentProgramMatBlockEntry(ost, spc, TextureDesc::HEIGHT_TEXTURE,                  "height");
    getFragmentProgramMatBlockEntry(ost, spc, TextureDesc::DISPLACEMENT_TEXTURE,            "displacement");
    getFragmentProgramMatBlockEntry(ost, spc, TextureDesc::REFLECTION_TEXTURE,              "reflection");
    getFragmentProgramMatBlockEntry(ost, spc, TextureDesc::REFRACTION_TEXTURE,              "refraction");
    getFragmentProgramMatBlockEntry(ost, spc, TextureDesc::ANISOTROPY_U_TEXTURE,            "anisotropyU");
    getFragmentProgramMatBlockEntry(ost, spc, TextureDesc::ANISOTROPY_V_TEXTURE,            "anisotropyV");
    getFragmentProgramMatBlockEntry(ost, spc, TextureDesc::ANISOTROPY_UV_TEXTURE,           "anisotropyUV");
    getFragmentProgramMatBlockEntry(ost, spc, TextureDesc::AMBIENT_OCCLUSION_TEXTURE,       "ambientOcclusion");
    getFragmentProgramMatBlockEntry(ost, spc, TextureDesc::ROUGH_TEXTURE,                   "roughness");
    getFragmentProgramMatBlockEntry(ost, spc, TextureDesc::METAL_TEXTURE,                   "metalness");
    getFragmentProgramMatBlockEntry(ost, spc, TextureDesc::ROUGH_METAL_TEXTURE,             "roughMetal");
    getFragmentProgramMatBlockEntry(ost, spc, TextureDesc::OCCL_ROUGH_METAL_TEXTURE,        "occlRoughMetal");
    getFragmentProgramMatBlockEntry(ost, spc, TextureDesc::IRRADIANCE_TEXTURE,              "irradiance");
    getFragmentProgramMatBlockEntry(ost, spc, TextureDesc::PRE_FILTER_TEXTURE,              "preFilterColor");
    getFragmentProgramMatBlockEntry(ost, spc, TextureDesc::BRDF_LUT_TEXTURE,                "brdf");
    getFragmentProgramMatBlockEntry(ost, spc, TextureDesc::STANDARD_MATERIAL_TEXTURE,       "standard");

    if (isFallbackShader2())
    {
        ost
        << endl << "};"
        << endl << ""
        << endl << "uniform " << getFragUniformBlockName() << " descMaterial;"
        << endl << ""
        ;
    }
    else
    {
        ost
        << endl << "} descMaterial;"
        << endl << ""
        ;
    }
}

void DescMaterial::getFragmentProgramMatBlockEntry(
    std::stringstream&       ost, 
    const std::string&       spc,
    UInt32                   texType, 
    const char*              name) const
{
    using namespace std;

    switch (evalFragtProgTexType(texType))
    {
        case DISCARD:
            break;
        case IS_COLOR_DATA:
            ost << endl << "    vec3 "   << spc << name << ";" ;
            break;
        case IS_SINGLE_DATA:
            ost << endl << "    SingleTexData " << name << ";" ;
            break;
        case IS_STACK_DATA:
            ost << endl << "    StackTexData  " << name << ";" ;
            break;
        case IS_ENV_DATA:
            ost << endl << "    EnvTexData    " << name << ";" ;
            break;
    }
}

void DescMaterial::getFragmentProgramMaterialStruct(std::stringstream& ost) const
{
    using namespace std;

    ost
    << endl << "struct Material"
    << endl << "{"
    ;

    if (_info.vertOptVariant == OptOnlyChannel0)
    {
        if (hasMaterialMember(TexCoordsMaterialMember       )) ost << endl << "    vec2  texCoord;" ;
    }
    else
    {
        if (hasMaterialMember(TexCoordsMaterialMember       )) ost << endl << "    vec2  texCoords[ciNumUVTextures];" ;
    }

    if (hasMaterialMember(AlbedoMaterialMember          )) ost << endl << "    vec3  albedo;"                     ;
    if (hasMaterialMember(DiffuseMaterialMember         )) ost << endl << "    vec3  diffuse;"                    ;
    if (hasMaterialMember(SpecularMaterialMember        )) ost << endl << "    vec3  specular;"                   ;
    if (hasMaterialMember(EmissiveMaterialMember        )) ost << endl << "    vec3  emissive;"                   ;
    if (hasMaterialMember(ShininessMaterialMember       )) ost << endl << "    float shininess;"                  ;
    if (hasMaterialMember(OpacityMaterialMember         )) ost << endl << "    float opacity;"                    ;
    if (hasMaterialMember(NormalMaterialMember          )) ost << endl << "    vec3  normal;"                     ;
    if (hasMaterialMember(TangentMaterialMember         )) ost << endl << "    vec3  tangent;"                    ;
    if (hasMaterialMember(BitangentMaterialMember       )) ost << endl << "    vec3  bitangent;"                  ;
    if (hasMaterialMember(ReflectionMaterialMember      )) ost << endl << "    vec3  reflection;"                 ;
    if (hasMaterialMember(RefractionMaterialMember      )) ost << endl << "    vec3  refraction;"                 ;
    if (hasMaterialMember(ReflectiveMaterialMember      )) ost << endl << "    vec3  reflective;"                 ;
    if (hasMaterialMember(AnisotropyUMaterialMember     )) ost << endl << "    float anisotropyU;"                ;
    if (hasMaterialMember(AnisotropyVMaterialMember     )) ost << endl << "    float anisotropyV;"                ;
    if (hasMaterialMember(RoughnessMaterialMember       )) ost << endl << "    float roughness;"                  ;
    if (hasMaterialMember(RoughnessMaterialMember       )) ost << endl << "    float alphaRoughness;"             ;
    if (hasMaterialMember(MetalnessMaterialMember       )) ost << endl << "    float metalness;"                  ;
    if (hasMaterialMember(AmbientOcclusionMaterialMember)) ost << endl << "    float ambientOcclusion;"           ;
    if (hasMaterialMember(IrradianceMaterialMember      )) ost << endl << "    vec3  irradiance;"                 ;
    if (hasMaterialMember(PreFilterColorMaterialMember  )) ost << endl << "    vec3  preFilterColor;"             ;
    if (hasMaterialMember(BrdfMaterialMember            )) ost << endl << "    vec2  brdf;"                       ;
    if (hasMaterialMember(ToonScaleMaterialMember       )) ost << endl << "    float toonScale;"                  ;
    ost
    << endl << "};"
    << endl << ""
    << endl << "Material material;"
    << endl << ""
    ;
}

void DescMaterial::getFragmentProgramTextureAccessUtils(std::stringstream& ost) const
{
    using namespace std;

    if (_info.numEquiTextures > 0)
    {
        ost
        << endl << "float CalcMipLevel(in vec3 v)"
        << endl << "{"
        << endl << "    vec3 dx = dFdx(v);"
        << endl << "    vec3 dy = dFdy(v);"
        << endl << ""
        << endl << "    float d = max(dot(dx,dx), dot(dy,dy));"
        << endl << ""
        << endl << "    return 0.5 * log2(d) + 8.0;"
        << endl << "}"
        << endl << ""
        ;
    }
}

void DescMaterial::getFragmentProgramTextureAccessOpt(std::stringstream& ost) const
{
    using namespace std;

    if (_info.numUVTextures == 1)
    {
        ost
        << endl << "vec4 getTextureColor(in int idx, in vec2 uv)"
        << endl << "{"
        ;

        TextureDescStore::const_iterator iter = _info.textureDescs.begin();

        if (isFallbackShader2())
        {
            ost
        << endl << "    return texture2D(uTextureMap" << _info.idxFstUVTexture << ", uv)." << (*iter)->getSwizzle() << ";"
            ;
        }
        else
        {
            ost
        << endl << "    return texture(uTextureMap" << _info.idxFstUVTexture << ", uv)." << (*iter)->getSwizzle() << ";"
            ;
        }

        ost
        << endl << "}"
        << endl << ""
        ;

        if (hasTexMapDetail(HeightTextures))
        {
            ost
            << endl << "ivec2 getTextureSize(in int idx)"
            << endl << "{"
            ;

            if (isFallbackShader2())
            {
                ost
            << endl << "    return texture2DSize(uTextureMap" << _info.idxFstUVTexture << ", 0);"
                ;
            }
            else
            {
                ost
            << endl << "    return textureSize(uTextureMap" << _info.idxFstUVTexture << ", 0);"
                ;
            }

            ost
            << endl << "}"
            << endl << ""
            ;
        }
    }

    if (_info.numCubeTextures == 1)
    {
        ost
        << endl << "vec4 getCubeTexture(in int idx, in vec3 v)"
        << endl << "{"
        ;
        if (isFallbackShader2())
        {
            ost
        << endl << "    return texture2D(uTextureMap" << _info.idxFstCubeTexture << ", v);"
            ;
        }
        else
        {
            ost
        << endl << "    return texture(uTextureMap" << _info.idxFstCubeTexture << ", v);"
            ;
        }
        ost
        << endl << "}"
        << endl << ""
        << endl << "vec4 getCubeTexture(in int idx, in vec3 v, in float lod)"
        << endl << "{"
        ;
        if (isFallbackShader2())
        {
            ost
        << endl << "    return texture2DLod(uTextureMap" << _info.idxFstCubeTexture << ", v, lod);"
            ;
        }
        else
        {
            ost
        << endl << "    return textureLod(uTextureMap" << _info.idxFstCubeTexture << ", v, lod);"
            ;
        }
        ost
        << endl << "}"
        << endl << ""
        ;
    }

    if (_info.numEquiTextures == 1)
    {
        ost
        << endl << "vec4 getEquirectangularTexture(in int idx, in vec3 v, in float lod)"
        << endl << "{"
        << endl << "    vec2 uv = vec2(atan(-v.x, -v.z) + OSG_PI, acos(v.y));"
        << endl << "    uv *= OSG_INV_ATAN;"
        << endl << "    uv = 1.0 - uv;"
        ;
        if (isFallbackShader2())
        {
            ost
        << endl << "    return texture2DLod(uTextureMap" << _info.idxFstEquiTexture << ", uv, lod);"
            ;
        }
        else
        {
            ost
        << endl << "    return textureLod(uTextureMap" << _info.idxFstEquiTexture << ", uv, lod);"
            ;
        }
        ost
        << endl << "}"
        << endl << ""
        ;
    }
}

void DescMaterial::getFragmentProgramTextureAccess(std::stringstream& ost) const
{
    using namespace std;

    std::string spc;

    if (_info.numUVTextures > 1)
    {
        ost
        << endl << "vec4 getTextureColor(in int idx, in vec2 uv)"
        << endl << "{"
        << endl << "    vec4 C = vec4(0);"
        << endl << ""
        ;

        if (isFallbackShader2() && !hasSwitchSupport())
        {
            TextureDescStore::const_iterator iter, end;

            iter = _info.textureDescs.begin();
            end  = _info.textureDescs.end  ();
        
            for (UInt32 idx = 0; iter != end; ++iter, ++idx)
            {
                std::string if_ = (idx == 0 ? "         if " 
                                            : "    else if ");

                TextureDesc* texDesc = *iter;

                spc = idx < 10 && _info.textureDescs.size() >= 10 ? " " : "";

                ost
                << endl << if_ << "(idx == " << spc << idx << ") C = texture2D(uTextureMap" << idx << ", " << spc << "uv)." << texDesc->getSwizzle() << ";"
                ;
            }
        }
        else
        {
            ost
            << endl << "    switch (idx)"
            << endl << "    {"
            ;

            TextureDescStore::const_iterator iter, end;

            iter = _info.textureDescs.begin();
            end  = _info.textureDescs.end  ();
        
            for (UInt32 idx = 0; iter != end; ++iter, ++idx)
            {
                TextureDesc* texDesc = *iter;

                spc = idx < 10 && _info.textureDescs.size() >= 10 ? " " : "";

                if (isFallbackShader2())
                {
                    ost
                << endl << "        case " << spc << idx << ": C = texture2D(uTextureMap" << idx << ", " << spc << "uv)." << texDesc->getSwizzle() << "; break;"
                    ;
                }
                else
                {
                    ost
                << endl << "        case " << spc << idx << ": C = texture(uTextureMap" << idx << ", " << spc << "uv)." << texDesc->getSwizzle() << "; break;"
                    ;
                }

            }

            ost
            << endl << "    }"
            ;
        }

        ost
        << endl << ""
        << endl << "    return C;"
        << endl << "}"
        << endl << ""
        ;

        if (hasTexMapDetail(HeightTextures))
        {
            ost
            << endl << "ivec2 getTextureSize(in int idx)"
            << endl << "{"
            << endl << "    ivec2 C = ivec2(0);"
            << endl << ""
            ;

            if (isFallbackShader2() && !hasSwitchSupport())
            {
                TextureDescStore::const_iterator iter, end;

                iter = _info.textureDescs.begin();
                end  = _info.textureDescs.end  ();
        
                for (UInt32 idx = 0; iter != end; ++iter, ++idx)
                {
                    std::string if_ = (idx == 0 ? "         if " 
                                                : "    else if ");

                    TextureDesc* texDesc = *iter;

                    spc = idx < 10 && _info.textureDescs.size() >= 10 ? " " : "";

                    ost
                    << endl << if_ << "(idx == " << spc << idx << ") C = texture2DSize(uTextureMap" << idx << ", " << spc << "0); break;"
                    ;
                }
            }
            else
            {
                ost
                << endl << "    switch (idx)"
                << endl << "    {"
                ;

                TextureDescStore::const_iterator iter, end;

                iter = _info.textureDescs.begin();
                end  = _info.textureDescs.end  ();
        
                for (UInt32 idx = 0; iter != end; ++iter, ++idx)
                {
                    TextureDesc* texDesc = *iter;

                    spc = idx < 10 && _info.textureDescs.size() >= 10 ? " " : "";

                    if (isFallbackShader2())
                    {
                        ost
                    << endl << "        case " << spc << idx << ": C = texture2DSize(uTextureMap" << idx << ", " << spc << "0); break;"
                        ;
                    }
                    else
                    {
                        ost
                    << endl << "        case " << spc << idx << ": C = textureSize(uTextureMap" << idx << ", " << spc << "0); break;"
                        ;
                    }
                }
                ost
                << endl << "    }"
                ;

            }

            ost
            << endl << ""
            << endl << "    return C;"
            << endl << "}"
            << endl << ""
            ;
        }
    }

    if (_info.numCubeTextures > 1)
    {
        ost
        << endl << "vec4 getCubeTexture(in int idx, in vec3 v)"
        << endl << "{"
        << endl << "    vec4 C = vec4(0);"
        << endl << ""
        ;

        if (isFallbackShader2() && !hasSwitchSupport())
        {
            TextureDescStore::const_iterator iter, end;

            iter = _info.textureDescsEnv.begin();
            end  = _info.textureDescsEnv.end  ();

            for (UInt32 idx = UInt32(_info.textureDescs.size()); iter != end; ++iter, ++idx)
            {
                std::string if_ = (idx == UInt32(_info.textureDescs.size()) ? "         if " 
                                                                            : "    else if ");

                TextureDesc* texDesc = *iter;

                if (texDesc->isCubeMap())
                {
                    spc = idx < 10 && _info.textureDescs.size()+_info.textureDescsEnv.size() >= 10 ? " " : "";

                    ost
                    << endl << if_ << "(idx == " << spc << idx << ") C = texture2D(uTextureMap" << idx << ", " << spc << "v); break;"
                    ;
                }
            }
        }
        else
        {
            ost
            << endl << "    switch (idx)"
            << endl << "    {"
            ;

            TextureDescStore::const_iterator iter, end;

            iter = _info.textureDescsEnv.begin();
            end  = _info.textureDescsEnv.end  ();

            for (UInt32 idx = UInt32(_info.textureDescs.size()); iter != end; ++iter, ++idx)
            {
                TextureDesc* texDesc = *iter;

                if (texDesc->isCubeMap())
                {
                    spc = idx < 10 && _info.textureDescs.size()+_info.textureDescsEnv.size() >= 10 ? " " : "";

                    if (isFallbackShader2())
                    {
                        ost
                    << endl << "        case " << spc << idx << ": C = texture2D(uTextureMap" << idx << ", " << spc << "v); break;"
                        ;
                    }
                    else
                    {
                        ost
                    << endl << "        case " << spc << idx << ": C = texture(uTextureMap" << idx << ", " << spc << "v); break;"
                        ;
                    }
                }
            }
            ost
            << endl << "    }"
            ;

        }

        ost
        << endl << ""
        << endl << "    return C;"
        << endl << "}"
        << endl << ""
        << endl << "vec4 getCubeTexture(in int idx, in vec3 v, float lod)"
        << endl << "{"
        << endl << "    vec4 C = vec4(0);"
        << endl << ""
        ;

        if (isFallbackShader2() && !hasSwitchSupport())
        {
            TextureDescStore::const_iterator iter, end;

            iter = _info.textureDescsEnv.begin();
            end  = _info.textureDescsEnv.end  ();
        
            for (UInt32 idx = UInt32(_info.textureDescs.size()); iter != end; ++iter, ++idx)
            {
                std::string if_ = (idx == UInt32(_info.textureDescs.size()) ? "         if " 
                                                                            : "    else if ");

                TextureDesc* texDesc = *iter;

                if (texDesc->isCubeMap())
                {
                    spc = idx < 10 && _info.textureDescs.size()+_info.textureDescsEnv.size() >= 10 ? " " : "";

                    ost
                    << endl << if_ << "(idx == " << spc << idx << ") C = texture2DLod(uTextureMap" << idx << ", " << spc << "v, lod); break;"
                    ;
                }
            }
        }
        else
        {
            ost
            << endl << "    switch (idx)"
            << endl << "    {"
            ;

            TextureDescStore::const_iterator iter, end;

            iter = _info.textureDescsEnv.begin();
            end  = _info.textureDescsEnv.end  ();
        
            for (UInt32 idx = UInt32(_info.textureDescs.size()); iter != end; ++iter, ++idx)
            {
                TextureDesc* texDesc = *iter;

                if (texDesc->isCubeMap())
                {
                    spc = idx < 10 && _info.textureDescs.size()+_info.textureDescsEnv.size() >= 10 ? " " : "";

                    if (isFallbackShader2())
                    {
                        ost
                    << endl << "        case " << spc << idx << ": C = texture2DLod(uTextureMap" << idx << ", " << spc << "v, lod); break;"
                        ;
                    }
                    else
                    {
                        ost
                    << endl << "        case " << spc << idx << ": C = textureLod(uTextureMap" << idx << ", " << spc << "v, lod); break;"
                        ;
                    }
                }
            }

            ost
            << endl << "    }"
            ;
        }

        ost
        << endl << ""
        << endl << "    return C;"
        << endl << "}"
        << endl << ""
        ;
    }

    if (_info.numEquiTextures > 1)
    {
        ost
        << endl << "vec4 getEquirectangularTexture(in int idx, in vec3 v, float lod)"
        << endl << "{"
        << endl << "    vec2 uv = vec2(atan(-v.x, -v.z) + OSG_PI, acos(v.y));"
        << endl << "    uv *= OSG_INV_ATAN;"
        << endl << "    uv = 1.0 - uv;"
        << endl << ""
        ;

        if (isFallbackShader2() && !hasSwitchSupport())
        {
            TextureDescStore::const_iterator iter, end;

            iter = _info.textureDescsEnv.begin();
            end  = _info.textureDescsEnv.end  ();
        
            for (UInt32 idx = UInt32(_info.textureDescs.size()); iter != end; ++iter, ++idx)
            {
                std::string if_ = (idx == UInt32(_info.textureDescs.size()) ? "         if " 
                                                                            : "    else if ");

                TextureDesc* texDesc = *iter;

                if (texDesc->isEquirectangularMap())
                {
                    spc = idx < 10 && _info.textureDescs.size()+_info.textureDescsEnv.size() >= 10 ? " " : "";

                    ost
                    << endl << if_ << "(idx == " << spc << idx << ") C = texture2DLod(uTextureMap" << idx << ", " << spc << "uv, lod); break;"
                    ;
                }
            }
        }
        else
        {
            ost
            << endl << "    switch (idx)"
            << endl << "    {"
            ;

            TextureDescStore::const_iterator iter, end;

            iter = _info.textureDescsEnv.begin();
            end  = _info.textureDescsEnv.end  ();
        
            for (UInt32 idx = UInt32(_info.textureDescs.size()); iter != end; ++iter, ++idx)
            {
                TextureDesc* texDesc = *iter;

                if (texDesc->isEquirectangularMap())
                {
                    spc = idx < 10 && _info.textureDescs.size()+_info.textureDescsEnv.size() >= 10 ? " " : "";

                    if (isFallbackShader2())
                    {
                        ost
                    << endl << "        case " << spc << idx << ": C = texture2DLod(uTextureMap" << idx << ", " << spc << "uv, lod); break;"
                        ;
                    }
                    else
                    {
                        ost
                    << endl << "        case " << spc << idx << ": C = textureLod(uTextureMap" << idx << ", " << spc << "uv, lod); break;"
                        ;
                    }
                }
            }

            ost
            << endl << "    }"
            ;
        }

        ost
        << endl << ""
        << endl << "    return C;"
        << endl << "}"
        << endl << ""
        ;
    }
}


void DescMaterial::getFragmentProgramTextureConstants(std::stringstream& ost) const
{
    using namespace std;

    if (_info.numUVTextures > 0)
    {
        ost
        << endl << "const int ciTexureFlagInvert        = " << TextureDesc::INVERT_FLAG          << ";"
        << endl << "const int ciTexureFlagUseAlpha      = " << TextureDesc::USE_ALPHA_FLAG       << ";"
        << endl << "const int ciTexureFlagIgnoreAlpha   = " << TextureDesc::IGNORE_ALPHA_FLAG    << ";"
        << endl << "const int ciTexureFlagNormalDirectX = " << TextureDesc::NORMAL_DIRECTX_FLAG  << ";"
        << endl << ""
        << endl << "const int ciTexureOpMultiply  = "       << TextureDesc::MULTIPLY_OPERATION   << ";"
        << endl << "const int ciTexureOpAdd       = "       << TextureDesc::ADD_OPERATION        << ";"
        << endl << "const int ciTexureOpSubtract  = "       << TextureDesc::SUBTRACT_OPERATION   << ";"
        << endl << "const int ciTexureOpDivide    = "       << TextureDesc::DIVIDE_OPERATION     << ";"
        << endl << "const int ciTexureOpSmoothAdd = "       << TextureDesc::SMOOTHADD_OPERATION  << ";"
        << endl << "const int ciTexureOpSignedAdd = "       << TextureDesc::SIGNEDADD_OPERATION  << ";"
        << endl << "const int ciTexureOpReplace   = "       << TextureDesc::REPLACE_OPERATION    << ";"
        << endl << "const int ciTexureOpDecal     = "       << TextureDesc::DECAL_OPERATION      << ";"
        << endl << "const int ciTexureOpBlend     = "       << TextureDesc::BLEND_OPERATION      << ";"
        << endl << ""
        ;
    }
}

void DescMaterial::getFragmentProgramTextureEvaluation(std::stringstream& ost) const
{
    using namespace std;

    if (_info.numUVTextures > 0)
    {
        ost
        << endl << "vec4 EvaluateTexture(in bool isSRGB, in int flags, in float f, in int idx, in vec2 uv)"
        << endl << "{"
        << endl << "    vec4 Cs = getTextureColor(idx, uv);"
        << endl << ""
        << endl << "    if (isSRGB)"
        << endl << "        Cs = OSGSRGBToLinear(Cs);"
        << endl << ""
        ;
        if (isFallbackShader2() && !hasBitOpsSupport())
        {
            ost
            << endl << "    if (BitAndOp(flags, ciTexureFlagInvert)  != 0)"
            << endl << "        Cs.rgb = vec3(1,1,1) - Cs.rgb;"
            << endl << "    if (BitAndOp(flags, ciTexureFlagIgnoreAlpha) != 0)"
            << endl << "        Cs.a = 1.0;"
            ;
        }
        else
        {
            ost
            << endl << "    if ((flags & ciTexureFlagInvert)  != 0)"
            << endl << "        Cs.rgb = vec3(1,1,1) - Cs.rgb;"
            << endl << "    if ((flags & ciTexureFlagIgnoreAlpha) != 0)"
            << endl << "        Cs.a = 1.0;"
            ;
        }
        ost
        << endl << ""
        << endl << "    Cs.rgb *= f;"
        << endl << ""
        << endl << "    return Cs;"
        << endl << "}"
        << endl << ""
        << endl << "vec4 EvaluateTexture(in vec4 Cp, in bool isSRGB, in int flags, in int op, in float f, in int idx)"
        << endl << "{"
        ;
        if (_info.vertOptVariant == OptOnlyChannel0)
        {
            ost
            << endl << "    vec2 uv = material.texCoord;"
            ;
        }
        else
        {
            ost
            << endl << "    vec2 uv = material.texCoords[idx];"
            ;
        }
        ost
        << endl << "    vec4 Cs = getTextureColor(idx, uv);"
        << endl << ""
        << endl << "    if (isSRGB)"
        << endl << "        Cs = OSGSRGBToLinear(Cs);"
        << endl << ""
        ;
        if (isFallbackShader2() && !hasBitOpsSupport())
        {
            ost
        << endl << "    if (BitAndOp(flags, ciTexureFlagInvert)  != 0)"
        << endl << "        Cs.rgb = vec3(1,1,1) - Cs.rgb;"
        << endl << "    if (BitAndOp(flags, ciTexureFlagIgnoreAlpha) != 0)"
        << endl << "        Cs.a = 1.0;"
            ;
        }
        else
        {
            ost
        << endl << "    if ((flags & ciTexureFlagInvert)  != 0)"
        << endl << "        Cs.rgb = vec3(1,1,1) - Cs.rgb;"
        << endl << "    if ((flags & ciTexureFlagIgnoreAlpha) != 0)"
        << endl << "        Cs.a = 1.0;"
            ;
        }
        ost
        << endl << ""
        << endl << "    Cs.rgb *= f;"
        << endl << ""
        ;

        if (isFallbackShader2() && !hasSwitchSupport())
        {
            ost
            << endl << "    if (op == ciTexureOpMultiply)"
            << endl << "    {"
            << endl << "        Cp.rgb = Cp.rgb * Cs.rgb;"
            << endl << "        Cp.a   = Cp.a   * Cs.a;"
            << endl << "    }"
            << endl << "    else if (op == ciTexureOpDivide)"
            << endl << "    {"
            << endl << "        Cp.rgb = Cp.rgb / Cs.rgb;"
            << endl << "        Cp.a   = Cp.a   * Cs.a;"
            << endl << "    }"
            << endl << "    else if (op == ciTexureOpAdd)"
            << endl << "    {"
            << endl << "        Cp.rgb = Cp.rgb + Cs.rgb;"
            << endl << "        Cp.a   = Cp.a   * Cs.a;"
            << endl << "    }"
            << endl << "    else if (op == ciTexureOpSubtract)"
            << endl << "    {"
            << endl << "        Cp.rgb = Cp.rgb - Cs.rgb;"
            << endl << "        Cp.a   = Cp.a   * Cs.a;"
            << endl << "    }"
            << endl << "    else if (op == ciTexureOpSmoothAdd)"
            << endl << "    {"
            << endl << "        Cp.rgb = Cp.rgb + Cs.rgb*(1.0 - Cp.rgb);"
            << endl << "        Cp.a   = Cp.a   * Cs.a;"
            << endl << "    }"
            << endl << "    else if (op == ciTexureOpSignedAdd)"
            << endl << "    {"
            << endl << "        Cp.rgb = Cp.rgb + Cs.rgb - 0.5;"
            << endl << "        Cp.a   = Cp.a   * Cs.a;"
            << endl << "    }"
            << endl << "    else if (op == ciTexureOpReplace)"
            << endl << "    {"
            << endl << "        Cp.rgb = Cs.rgb;"
            << endl << "        Cp.a   = Cs.a;"
            << endl << "    }"
            << endl << "    else if (op == ciTexureOpDecal)"
            << endl << "    {"
            << endl << "        Cp.rgb = mix(Cp.rgb, Cs.rgb, vec3(Cs.a));"
            << endl << "    }"
            << endl << "    else if (op == ciTexureOpBlend)"
            << endl << "    {"
            << endl << "        Cp.rgb = (1.0 - f) * Cp.rgb + Cs.rgb;"
            << endl << "        Cp.a   = Cp.a * Cs.a;"
            << endl << "    }"
            ;
        }
        else
        {
            ost
            << endl << "    switch(op)"
            << endl << "    {"
            << endl << "        case ciTexureOpMultiply:"
            << endl << "                Cp.rgb = Cp.rgb * Cs.rgb;"
            << endl << "                Cp.a   = Cp.a   * Cs.a;"
            << endl << "                break;"
            << endl << "        case ciTexureOpDivide:"
            << endl << "                Cp.rgb = Cp.rgb / Cs.rgb;"
            << endl << "                Cp.a   = Cp.a   * Cs.a;"
            << endl << "                break;"
            << endl << "        case ciTexureOpAdd:"
            << endl << "                Cp.rgb = Cp.rgb + Cs.rgb;"
            << endl << "                Cp.a   = Cp.a   * Cs.a;"
            << endl << "                break;"
            << endl << "        case ciTexureOpSubtract:"
            << endl << "                Cp.rgb = Cp.rgb - Cs.rgb;"
            << endl << "                Cp.a   = Cp.a   * Cs.a;"
            << endl << "                break;"
            << endl << "        case ciTexureOpSmoothAdd:"
            << endl << "                Cp.rgb = Cp.rgb + Cs.rgb*(1.0 - Cp.rgb);"
            << endl << "                Cp.a   = Cp.a   * Cs.a;"
            << endl << "                break;"
            << endl << "        case ciTexureOpSignedAdd:"
            << endl << "                Cp.rgb = Cp.rgb + Cs.rgb - 0.5;"
            << endl << "                Cp.a   = Cp.a   * Cs.a;"
            << endl << "                break;"
            << endl << "        case ciTexureOpReplace:"
            << endl << "                Cp.rgb = Cs.rgb;"
            << endl << "                Cp.a   = Cs.a;"
            << endl << "                break;"
            << endl << "        case ciTexureOpDecal:"
            << endl << "                Cp.rgb = mix(Cp.rgb, Cs.rgb, vec3(Cs.a));"
            << endl << "                break;"
            << endl << "        case ciTexureOpBlend:"
            << endl << "                Cp.rgb = (1.0 - f) * Cp.rgb + Cs.rgb;"
            << endl << "                Cp.a   = Cp.a * Cs.a;"
            << endl << "                break;"
            << endl << "    }"
            ;
        }

        ost
        << endl << ""
        << endl << "    return Cp;"
        << endl << "}"
        << endl << ""
        ;

        if (_info.hasStackTexData)
        {
            ost
            << endl << "vec4 EvaluateTexture(in StackTexData texData)"
            << endl << "{"
            << endl << "    vec4 Cp = vec4(texData.baseColor, 1.0);"
            << endl << ""
            << endl << "    for (int i = 0; i < texData.size; ++i)"
            << endl << "    {"
            << endl << "        bool  isSRGB = texData.isSRGB[i];"
            << endl << "        int   flags  = texData.flags[i];"
            << endl << "        int   op     = texData.ops[i];"
            << endl << "        float f      = texData.strengths[i];"
            << endl << "        int   idx    = texData.indices[i];"
            << endl << ""
            << endl << "        Cp = EvaluateTexture(Cp, isSRGB, flags, op, f, idx);"
            << endl << "    }"
            << endl << "    return Cp;"
            << endl << "}"
            << endl << ""
            ;
        }

        if (_info.hasSingleTexData)
        {
            ost
            << endl << "vec4 EvaluateTexture(in SingleTexData texData)"
            << endl << "{"
            << endl << "    vec4 Cp = vec4(texData.baseColor, 1.0);"
            << endl << ""
            << endl << "    bool  isSRGB = texData.isSRGB;"
            << endl << "    int   flags  = texData.flags;"
            << endl << "    int   op     = texData.op;"
            << endl << "    float f      = texData.strength;"
            << endl << "    int   idx    = texData.index;"
            << endl << ""
            << endl << "    Cp = EvaluateTexture(Cp, isSRGB, flags, op, f, idx);"
            << endl << ""
            << endl << "    return Cp;"
            << endl << "}"
            << endl << ""
            ;
        }
    }

    if (_info.numCubeTextures > 0)
    {
        ost
        << endl << "vec4 EvaluateCubeTexture(in EnvTexData texData, in vec3 dir, in float lod)"
        << endl << "{"
        << endl << "    bool  isSRGB = texData.isSRGB;"
        << endl << "    float f      = texData.strength;"
        << endl << "    int   idx    = texData.index;"
        << endl << ""
        << endl << "    vec4 Cs = getCubeTexture(idx, dir, lod);"
        << endl << ""
        << endl << "    if (isSRGB)"
        << endl << "        Cs = OSGSRGBToLinear(Cs);"
        << endl << ""
        << endl << "    Cs.rgb *= f;"
        << endl << ""
        << endl << "    return Cs;"
        << endl << "}"
        << endl << ""
        << endl << "vec4 EvaluateCubeTexture(in EnvTexData texData, in vec3 dir)"
        << endl << "{"
        << endl << "    bool  isSRGB = texData.isSRGB;"
        << endl << "    float f      = texData.strength;"
        << endl << "    int   idx    = texData.index;"
        << endl << ""
        << endl << "    vec4 Cs = getCubeTexture(idx, dir);"
        << endl << ""
        << endl << "    if (isSRGB)"
        << endl << "        Cs = OSGSRGBToLinear(Cs);"
        << endl << ""
        << endl << "    Cs.rgb *= f;"
        << endl << ""
        << endl << "    return Cs;"
        << endl << "}"
        << endl << ""
        ;
    }

    if (_info.numEquiTextures > 0)
    {
        ost
        << endl << "vec4 EvaluateEquirectangularTexture(in EnvTexData texData, in vec3 dir, in float lod)"
        << endl << "{"
        << endl << "    bool  isSRGB = texData.isSRGB;"
        << endl << "    float f      = texData.strength;"
        << endl << "    int   idx    = texData.index;"
        << endl << ""
        << endl << "    vec4 Cs = getEquirectangularTexture(idx, dir, lod);"
        << endl << ""
        << endl << "    if (isSRGB)"
        << endl << "        Cs = OSGSRGBToLinear(Cs);"
        << endl << ""
        << endl << "    Cs.rgb *= f;"
        << endl << ""
        << endl << "    return Cs;"
        << endl << "}"
        << endl << ""
        ;
    }
}

void DescMaterial::getFragmentProgramParallaxRemapTexureCoords(std::stringstream& ost, const char* var, const char* channel) const
{
    using namespace std;

    ost
    //
    // Parallax Occlusion Mapping
    // https://learnopengl.com/Advanced-Lighting/Parallax-Mapping
    //
    << endl << "void ParallaxRemapTexureCoords()"
    << endl << "{"
    << endl << "    bool  isSRGB = descMaterial." << var << ".isSRGB;"
    << endl << "    int   flags  = descMaterial." << var << ".flags;"
    << endl << "    float f      = descMaterial." << var << ".strength;"
    << endl << "    int   idx    = descMaterial." << var << ".index;"
    << endl << ""
    << endl << "    vec3 V = cCameraPositionES - vPositionES;"
    << endl << "    V = geomContext.matTSFromES * V;"
    << endl << "    V = normalize(V);"
    << endl << ""
    << endl << "    const float minLayers = 8;"
    << endl << "    const float maxLayers = 32;"
    << endl << ""
    << endl << "    float numLayers  = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), V)));"
    << endl << "    float layerDepth = 1.0 / numLayers;"
    << endl << ""
    << endl << "    float currLayerDepth = 0.0;"
    << endl << ""
    << endl << "    vec2 P = V.xy / V.z * descMaterial.bumpScaling;"
    << endl << "    vec2 deltaUV = P / numLayers;"
    << endl << ""
    ;
    if (_info.vertOptVariant == OptOnlyChannel0)
    {
        ost
        << endl << "    vec2  currUV    = material.texCoord;"
        ;
    }
    else
    {
        ost
        << endl << "    vec2  currUV    = material.texCoords[idx];"
        ;
    }
    ost
    << endl << "    float currDepth = EvaluateTexture(isSRGB, flags, f, idx, currUV)." << channel << ";"
    << endl << ""
    << endl << "    while(currLayerDepth < currDepth)"
    << endl << "    {"
    << endl << "        currUV -= deltaUV;"
    << endl << "        currDepth = EvaluateTexture(isSRGB, flags, f, idx, currUV)." << channel << ";"
    << endl << "        currLayerDepth += layerDepth;"
    << endl << "    }"
    << endl << ""
    << endl << "    vec2 prevUV = currUV + deltaUV;"
    << endl << ""
    << endl << "    float afterDepth  = currDepth - currLayerDepth;"
    << endl << "    float beforeDepth = EvaluateTexture(isSRGB, flags, f, idx, prevUV)." << channel << " - currLayerDepth + layerDepth;"
    << endl << ""
    << endl << "    float weight = afterDepth / (afterDepth - beforeDepth);"
    << endl << "    vec2 finalUV = prevUV * weight + currUV * (1.0 - weight);"
    << endl << ""
    << endl << "    // Hack: Assumption that all textures use the same uv channel."
    << endl << "    for (int idx = 0; idx < ciNumUVTextures; ++idx)"
    << endl << "    {"
    ;
    if (_info.vertOptVariant == OptOnlyChannel0)
    {
        ost
        << endl << "        material.texCoord = finalUV;"
        ;
    }
    else
    {
        ost
        << endl << "        material.texCoords[idx] = finalUV;"
        ;
    }
    ost
    << endl << "    }"
    << endl << "}"
    << endl << ""
    ;
}

void DescMaterial::getFragmentProgramMaterialEvaluation(std::stringstream& ost) const
{
    using namespace std;

    getFragmentProgramMaterialAlbedo            (ost);
    getFragmentProgramMaterialSpecular          (ost);
    getFragmentProgramMaterialEmissive          (ost);
    getFragmentProgramMaterialStandardMaterial  (ost);
    getFragmentProgramMaterialShininess         (ost);
    getFragmentProgramMaterialOpacity           (ost);
    getFragmentProgramMaterialNormal            (ost);
    getFragmentProgramMaterialHeight            (ost);
    getFragmentProgramMaterialDisplacement      (ost);
    getFragmentProgramMaterialReflection        (ost);
    getFragmentProgramMaterialRefraction        (ost);

    if (hasTexMapDetail(AnisotropyUVTextures))
    {
        getFragmentProgramMaterialAnisotropyUV  (ost);
    }
    else
    {
        getFragmentProgramMaterialAnisotropyU   (ost);
        getFragmentProgramMaterialAnisotropyV   (ost);
    }

    getFragmentProgramMaterialAmbientOccl   (ost);

    if (hasTexMapDetail(RoughMetalTextures))
    {
        getFragmentProgramMaterialRoughMetal(ost);
    }
    else
    if (hasTexMapDetail(OcclRoughMetalTextures))
    {
        getFragmentProgramMaterialOcclRoughMetal(ost);
    }
    else
    {
        getFragmentProgramMaterialRoughness(ost);
        getFragmentProgramMaterialMetalness(ost);
    }
    
    getFragmentProgramMaterialIrradiance    (ost);
    getFragmentProgramMaterialPreFilterColor(ost);
    getFragmentProgramMaterialBrdf          (ost);
    getFragmentProgramMaterialF0            (ost);
}

void DescMaterial::getFragmentProgramMaterialAlbedo(std::stringstream& ost) const
{
    using namespace std;

    switch (evalFragtProgTexType(TextureDesc::ALBEDO_TEXTURE))
    {
        case DISCARD:
            break;
        case IS_COLOR_DATA:
            ost
            << endl << "vec3 getMaterialAlbedo()"
            << endl << "{"
            << endl << "    return descMaterial.albedo;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_SINGLE_DATA:
            ost
            << endl << "vec3 getMaterialAlbedo()"
            << endl << "{"
            << endl << "    SingleTexData data = descMaterial.albedo;"
            << endl << "    vec3 value = EvaluateTexture(data).rgb;"
            << endl << "    return clamp(value, 0.0, 1.0);"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_STACK_DATA:
            ost
            << endl << "vec3 getMaterialAlbedo()"
            << endl << "{"
            << endl << "    StackTexData data = descMaterial.albedo;"
            << endl << "    vec3 value = EvaluateTexture(data).rgb;"
            << endl << "    return clamp(value, 0.0, 1.0);"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_ENV_DATA:
            OSG_ASSERT(false);
            break;
    }
}

void DescMaterial::getFragmentProgramMaterialSpecular(std::stringstream& ost) const
{
    using namespace std;

    switch (evalFragtProgTexType(TextureDesc::SPECULAR_TEXTURE))
    {
        case DISCARD:
            break;
        case IS_COLOR_DATA:
            if (hasSpecularGlossinessTexture())
            {
                ost
                << endl << "vec4 getMaterialSpecularGlossiness()"
                << endl << "{"
                << endl << "    return vec4(descMaterial.specular, 1.0);"
                << endl << "}"
                << endl << ""
                ;
            }
            else if (hasMetalnessRoughnessWorkflow())
            {
            }
            else
            {
                ost
                << endl << "vec3 getMaterialSpecular()"
                << endl << "{"
                << endl << "    return descMaterial.specular;"
                << endl << "}"
                << endl << ""
                ;
            }
            break;
        case IS_SINGLE_DATA:
            if (hasSpecularGlossinessTexture())
            {
                ost
                << endl << "vec4 getMaterialSpecularGlossiness()"
                << endl << "{"
                << endl << "    SingleTexData data = descMaterial.specular;"
                << endl << "    vec4 value = EvaluateTexture(data);"
                << endl << "    return clamp(value, 0.0, 1.0);"
                << endl << "}"
                << endl << ""
                ;
            }
            else if (hasMetalnessRoughnessWorkflow())
            {
            }
            else
            {
                ost
                << endl << "vec3 getMaterialSpecular()"
                << endl << "{"
                << endl << "    SingleTexData data = descMaterial.specular;"
                << endl << "    vec3 value = EvaluateTexture(data).rgb;"
                << endl << "    return clamp(value, 0.0, 1.0);"
                << endl << "}"
                << endl << ""
                ;
            }
            break;
        case IS_STACK_DATA:
            if (hasSpecularGlossinessTexture())
            {
                ost
                << endl << "vec4 getMaterialSpecularGlossiness()"
                << endl << "{"
                << endl << "    StackTexData data = descMaterial.specular;"
                << endl << "    vec4 value = EvaluateTexture(data);"
                << endl << "    return clamp(value, 0.0, 1.0);"
                << endl << "}"
                << endl << ""
                ;
            }
            else if (hasMetalnessRoughnessWorkflow())
            {
            }
            else
            {
                ost
                << endl << "vec3 getMaterialSpecular()"
                << endl << "{"
                << endl << "    StackTexData data = descMaterial.specular;"
                << endl << "    vec3 value = EvaluateTexture(data).rgb;"
                << endl << "    return clamp(value, 0.0, 1.0);"
                << endl << "}"
                << endl << ""
                ;
            }
            break;
        case IS_ENV_DATA:
            OSG_ASSERT(false);
            break;
    }
}

void DescMaterial::getFragmentProgramMaterialEmissive(std::stringstream& ost) const
{
    using namespace std;

    switch (evalFragtProgTexType(TextureDesc::EMISSIVE_TEXTURE))
    {
        case DISCARD:
            break;
        case IS_COLOR_DATA:
            ost
            << endl << "vec3 getMaterialEmissive()"
            << endl << "{"
            << endl << "    return descMaterial.emissive;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_SINGLE_DATA:
            ost
            << endl << "vec3 getMaterialEmissive()"
            << endl << "{"
            << endl << "    SingleTexData data = descMaterial.emissive;"
            << endl << "    return EvaluateTexture(data).rgb;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_STACK_DATA:
            ost
            << endl << "vec3 getMaterialEmissive()"
            << endl << "{"
            << endl << "    StackTexData data = descMaterial.emissive;"
            << endl << "    return EvaluateTexture(data).rgb;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_ENV_DATA:
            OSG_ASSERT(false);
            break;
    }
}

void DescMaterial::getFragmentProgramMaterialStandardMaterial(std::stringstream& ost) const
{
    using namespace std;

    switch (evalFragtProgTexType(TextureDesc::STANDARD_MATERIAL_TEXTURE))
    {
        case DISCARD:
            break;
        case IS_COLOR_DATA:
            break;
        case IS_SINGLE_DATA:
            ost
            << endl << "vec3 getMaterialStandard(in vec3 baseColor)"
            << endl << "{"
            << endl << "    SingleTexData data = descMaterial.standard;"
            << endl << "    data.baseColor = baseColor;"
            << endl << "    vec3 value = EvaluateTexture(data).rgb;"
            << endl << "    return clamp(value, 0.0, 1.0);"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_STACK_DATA:
            ost
            << endl << "vec3 getMaterialStandard(in vec3 baseColor)"
            << endl << "{"
            << endl << "    StackTexData data = descMaterial.standard;"
            << endl << "    data.baseColor = baseColor;"
            << endl << "    vec3 value = EvaluateTexture(data).rgb;"
            << endl << "    return clamp(value, 0.0, 1.0);"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_ENV_DATA:
            OSG_ASSERT(false);
            break;
    }
}

void DescMaterial::getFragmentProgramMaterialShininess(std::stringstream& ost) const
{
    using namespace std;

    switch (evalFragtProgTexType(TextureDesc::SHININESS_TEXTURE))
    {
        case DISCARD:
            break;
        case IS_COLOR_DATA:
            ost
            << endl << "float getMaterialShininess()"
            << endl << "{"
            << endl << "    return descMaterial.shininess.r;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_SINGLE_DATA:
            ost
            << endl << "float getMaterialShininess()"
            << endl << "{"
            << endl << "    SingleTexData data = descMaterial.shininess;"
            << endl << "    return EvaluateTexture(data).r;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_STACK_DATA:
            ost
            << endl << "float getMaterialShininess()"
            << endl << "{"
            << endl << "    StackTexData data = descMaterial.shininess;"
            << endl << "    return EvaluateTexture(data).r;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_ENV_DATA:
            OSG_ASSERT(false);
            break;
    }
}

void DescMaterial::getFragmentProgramMaterialOpacity(std::stringstream& ost) const
{
    using namespace std;

    switch (evalFragtProgTexType(TextureDesc::OPACITY_TEXTURE))
    {
        case DISCARD:
            break;
        case IS_COLOR_DATA:
            ost
            << endl << "float getMaterialOpacity()"
            << endl << "{"
            << endl << "    return descMaterial.opacity.r;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_SINGLE_DATA:
            ost
            << endl << "float getMaterialOpacity()"
            << endl << "{"
            << endl << "    SingleTexData data = descMaterial.opacity;"
            << endl << "    return EvaluateTexture(data).r;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_STACK_DATA:
            ost
            << endl << "float getMaterialOpacity()"
            << endl << "{"
            << endl << "    StackTexData data = descMaterial.opacity;"
            << endl << "    return EvaluateTexture(data).r;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_ENV_DATA:
            OSG_ASSERT(false);
            break;
    }
}

void DescMaterial::getFragmentProgramMaterialNormal(std::stringstream& ost) const
{
    using namespace std;

    switch (evalFragtProgTexType(TextureDesc::NORMALS_TEXTURE))
    {
        case DISCARD:
            break;
        case IS_COLOR_DATA:
            OSG_ASSERT(false);
            break;
        case IS_SINGLE_DATA:
            ost
            << endl << "vec3 getMaterialNormal()"
            << endl << "{"
            << endl << "    SingleTexData data = descMaterial.normal;"
            << endl << ""
            << endl << "    int idx = data.index;"
            << endl << ""
            ;
            if (_info.vertOptVariant == OptOnlyChannel0)
            {
                ost
                << endl << "    vec2 uv = material.texCoord;"
                ;
            }
            else
            {
                ost
                << endl << "    vec2 uv = material.texCoords[idx];"
                ;
            }
            ost
            << endl << "    vec4 Cs = getTextureColor(idx, uv);"
            << endl << ""
            << endl << "    vec3 mapN = 2.0 * Cs.rgb - 1.0;"
            << endl << ""
            ;
            if (isFallbackShader2() && !hasBitOpsSupport())
            {
                ost
            << endl << "    if (BitAndOp(data.flags, ciTexureFlagNormalDirectX) != 0)"
                ;
            }
            else
            {
                ost
            << endl << "    if ((data.flags & ciTexureFlagNormalDirectX) != 0)"
                ;
            }
            ost
            << endl << "        mapN.y *= -1.0;"
            << endl << ""
            << endl << "    mapN = normalize(geomContext.matESFromTS * mapN);"
            << endl << ""
            << endl << "    return mapN;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_STACK_DATA:
            OSG_ASSERT(false);
            break;
        case IS_ENV_DATA:
            OSG_ASSERT(false);
            break;
    }
}

void DescMaterial::getFragmentProgramMaterialHeight(std::stringstream& ost) const
{
    using namespace std;

    switch (evalFragtProgTexType(TextureDesc::HEIGHT_TEXTURE))
    {
        case DISCARD:
            break;
        case IS_COLOR_DATA:
            OSG_ASSERT(false);
            break;
        case IS_SINGLE_DATA:
            ost
            << endl << "vec3 HeighMapping(in vec3 N)"
            << endl << "{"
            << endl << "    bool  isSRGB = descMaterial.height.isSRGB;"
            << endl << "    int   flags  = descMaterial.height.flags;"
            << endl << "    float f      = descMaterial.height.strength;"
            << endl << "    int   idx    = descMaterial.height.index;"
            << endl << ""
            ;
            if (_info.vertOptVariant == OptOnlyChannel0)
            {
                ost
                << endl << "    vec2  uv     = material.texCoord;"
                ;
            }
            else
            {
                ost
                << endl << "    vec2  uv     = material.texCoords[idx];"
                ;
            }
            ost
            << endl << ""
            << endl << "    ivec2 texSize = getTextureSize(idx);"
            << endl << "    vec2 delta = 1.0 / texSize;"
            << endl << ""
            << endl << "    float me = EvaluateTexture(isSRGB, flags, f, idx, uv).x;"
            << endl << "    float n  = EvaluateTexture(isSRGB, flags, f, idx, uv+vec2(0.0, delta.y)).x;"
            << endl << "    float e  = EvaluateTexture(isSRGB, flags, f, idx, uv-vec2(delta.x, 0.0)).x;"
            << endl << "    float s  = EvaluateTexture(isSRGB, flags, f, idx, uv-vec2(0.0, delta.y)).x;"
            << endl << "    float w  = EvaluateTexture(isSRGB, flags, f, idx, uv+vec2(delta.x, 0.0)).x;"
            << endl << ""
            << endl << "    vec3 T = geomContext.T;"
            << endl << "    vec3 B = geomContext.B;"
            << endl << ""
            << endl << "    vec3 normalOffset = -descMaterial.bumpScaling * (((n-me)-(s-me)) * T + ((e-me)-(w-me)) * B);"
            << endl << "    N  = normalize(N + normalOffset);"
            << endl << ""
            << endl << "    return N;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_STACK_DATA:
            OSG_ASSERT(false);
            break;
        case IS_ENV_DATA:
            OSG_ASSERT(false);
            break;
    }
}

void DescMaterial::getFragmentProgramMaterialDisplacement(std::stringstream& ost) const
{
    using namespace std;

    switch (evalFragtProgTexType(TextureDesc::DISPLACEMENT_TEXTURE))
    {
        case DISCARD:
            break;
        case IS_COLOR_DATA:
            OSG_ASSERT(false);
            break;
        case IS_SINGLE_DATA:
            getFragmentProgramParallaxRemapTexureCoords(ost, "displacement", "x");
            break;
        case IS_STACK_DATA:
            OSG_ASSERT(false);
            break;
        case IS_ENV_DATA:
            OSG_ASSERT(false);
            break;
    }
}

void DescMaterial::getFragmentProgramMaterialReflection(std::stringstream& ost) const
{
    using namespace std;

    switch (evalFragtProgTexType(TextureDesc::REFLECTION_TEXTURE))
    {
        case DISCARD:
            break;
        case IS_COLOR_DATA:
            OSG_ASSERT(false);
            break;
        case IS_SINGLE_DATA:
            OSG_ASSERT(false);
            break;
        case IS_STACK_DATA:
            OSG_ASSERT(false);
            break;
        case IS_ENV_DATA:
            ost
            << endl << "vec3 getMaterialReflection(in vec3 N, in vec3 V)"
            << endl << "{"
            << endl << "    vec3 R = reflect(-V, N);"
            << endl << ""
            << endl << "    EnvTexData data = descMaterial.reflection;"
            ;
            if (_info.textureEnvMapIsCubeMap[TextureDesc::REFLECTION_TEXTURE])
            {
                ost
                << endl << "    return EvaluateCubeTexture(data, R).rgb;"
                ;
            }
            else
            {
                ost
                << endl << "    float lod = CalcMipLevel(R);"
                << endl << ""
                << endl << "    return EvaluateEquirectangularTexture(data, R, lod).rgb;"
                ;
            }
            ost
            << endl << "}"
            << endl << ""
            ;
            break;
    }
}

void DescMaterial::getFragmentProgramMaterialRefraction(std::stringstream& ost) const
{
    using namespace std;

    switch (evalFragtProgTexType(TextureDesc::REFRACTION_TEXTURE))
    {
        case DISCARD:
            break;
        case IS_COLOR_DATA:
            OSG_ASSERT(false);
            break;
        case IS_SINGLE_DATA:
            OSG_ASSERT(false);
            break;
        case IS_STACK_DATA:
            OSG_ASSERT(false);
            break;
        case IS_ENV_DATA:
            ost
            << endl << "vec3 getMaterialRefraction(in vec3 N, in vec3 V)"
            << endl << "{"
            << endl << "    float n = 2.0 / (1.0 - 0.4 * descMaterial.reflectance) - 1.0;"    // f0 = (n-1)^2/(n+1)^2 => n = 2/(1-sqrt(f0) -1) with f0 = 0.16 * reflectance^2
            << endl << "    vec3 R = refract(-V, N, n);"
            << endl << ""
            << endl << "    EnvTexData data = descMaterial.refraction;"
            ;
            if (_info.textureEnvMapIsCubeMap[TextureDesc::REFRACTION_TEXTURE])
            {
                ost
                << endl << "    return EvaluateCubeTexture(data, R).rgb;"
                ;
            }
            else
            {
                ost
                << endl << "    float lod = CalcMipLevel(R);"
                << endl << ""
                << endl << "    return EvaluateEquirectangularTexture(data, R, lod).rgb;"
                ;
            }
            ost
            << endl << "}"
            << endl << ""
            ;
            break;
    }
}

void DescMaterial::getFragmentProgramMaterialAnisotropyU(std::stringstream& ost) const
{
    using namespace std;

    if (!hasMaterialMember(AnisotropyUMaterialMember)) return;

    switch (evalFragtProgTexType(TextureDesc::ANISOTROPY_U_TEXTURE))
    {
        case DISCARD:
            ost
            << endl << "float getMaterialAnisotropyU()"
            << endl << "{"
            << endl << "    return 0.0;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_COLOR_DATA:
            OSG_ASSERT(false);
            break;
        case IS_SINGLE_DATA:
            ost
            << endl << "float getMaterialAnisotropyU()"
            << endl << "{"
            << endl << "    SingleTexData data = descMaterial.anisotropyU;"
            << endl << "    return EvaluateTexture(data).r;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_STACK_DATA:
            OSG_ASSERT(false);
            break;
        case IS_ENV_DATA:
            OSG_ASSERT(false);
            break;
    }
}

void DescMaterial::getFragmentProgramMaterialAnisotropyV(std::stringstream& ost) const
{
    using namespace std;

    if (!hasMaterialMember(AnisotropyVMaterialMember)) return;

    switch (evalFragtProgTexType(TextureDesc::ANISOTROPY_V_TEXTURE))
    {
        case DISCARD:
            ost
            << endl << "float getMaterialAnisotropyV()"
            << endl << "{"
            << endl << "    return 0.0;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_COLOR_DATA:
            OSG_ASSERT(false);
            break;
        case IS_SINGLE_DATA:
            ost
            << endl << "float getMaterialAnisotropyV()"
            << endl << "{"
            << endl << "    SingleTexData data = descMaterial.anisotropyV;"
            << endl << "    return EvaluateTexture(data).r;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_STACK_DATA:
            OSG_ASSERT(false);
            break;
        case IS_ENV_DATA:
            OSG_ASSERT(false);
            break;
    }
}

void DescMaterial::getFragmentProgramMaterialAnisotropyUV(std::stringstream& ost) const
{
    using namespace std;

    if (!hasMaterialMember(AnisotropyUMaterialMember)) return;
    if (!hasMaterialMember(AnisotropyVMaterialMember)) return;

    switch (evalFragtProgTexType(TextureDesc::ANISOTROPY_UV_TEXTURE))
    {
        case DISCARD:
            ost
            << endl << "vec2 getMaterialAnisotropyUV()"
            << endl << "{"
            << endl << "    return vec2(0,0);"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_COLOR_DATA:
            OSG_ASSERT(false);
            break;
        case IS_SINGLE_DATA:
            ost
            << endl << "vec2 getMaterialAnisotropyUV()"
            << endl << "{"
            << endl << "    SingleTexData data = descMaterial.anisotropyUV;"
            << endl << "    return EvaluateTexture(data).rg;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_STACK_DATA:
            OSG_ASSERT(false);
            break;
        case IS_ENV_DATA:
            OSG_ASSERT(false);
            break;
    }
}

void DescMaterial::getFragmentProgramMaterialAmbientOccl(std::stringstream& ost) const
{
    using namespace std;

    switch (evalFragtProgTexType(TextureDesc::AMBIENT_OCCLUSION_TEXTURE))
    {
        case DISCARD:
            break;
        case IS_COLOR_DATA:
            OSG_ASSERT(false);
            break;
        case IS_SINGLE_DATA:
            ost
            << endl << "float getMaterialAmbientOcclusion()"
            << endl << "{"
            << endl << "    SingleTexData data = descMaterial.ambientOcclusion;"
            << endl << "    return EvaluateTexture(data).r;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_STACK_DATA:
            OSG_ASSERT(false);
            break;
        case IS_ENV_DATA:
            OSG_ASSERT(false);
            break;
    }

    if (hasMaterialMember(AmbientOcclusionMaterialMember))
    {
        ost
        << endl << "float getMaterialAmbientOcclusion()"
        << endl << "{"
        << endl << "    return material.ambientOcclusion;"
        << endl << "}"
        << endl << ""
        ;
    }
}

void DescMaterial::getFragmentProgramMaterialRoughness(std::stringstream& ost) const
{
    using namespace std;

    if (!hasMaterialMember(RoughnessMaterialMember)) return;

    switch (evalFragtProgTexType(TextureDesc::ROUGH_TEXTURE))
    {
        case DISCARD:
            break;
        case IS_COLOR_DATA:
            ost
            << endl << "float getMaterialRoughness()"
            << endl << "{"
            << endl << "    return descMaterial.roughness.r;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_SINGLE_DATA:
            ost
            << endl << "float getMaterialRoughness()"
            << endl << "{"
            << endl << "    SingleTexData data = descMaterial.roughness;"
            << endl << "    return EvaluateTexture(data).r;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_STACK_DATA:
            ost
            << endl << "float getMaterialRoughness()"
            << endl << "{"
            << endl << "    StackTexData data = descMaterial.roughness;"
            << endl << "    return EvaluateTexture(data).r;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_ENV_DATA:
            OSG_ASSERT(false);
            break;
    }
}

void DescMaterial::getFragmentProgramMaterialMetalness(std::stringstream& ost) const
{
    using namespace std;

    if (!hasMaterialMember(MetalnessMaterialMember)) return;

    switch (evalFragtProgTexType(TextureDesc::METAL_TEXTURE))
    {
        case DISCARD:
            break;
        case IS_COLOR_DATA:
            ost
            << endl << "float getMaterialMetalness()"
            << endl << "{"
            << endl << "    return descMaterial.metalness.r;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_SINGLE_DATA:
            ost
            << endl << "float getMaterialMetalness()"
            << endl << "{"
            << endl << "    SingleTexData data = descMaterial.metalness;"
            << endl << "    return EvaluateTexture(data).r;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_STACK_DATA:
            ost
            << endl << "float getMaterialMetalness()"
            << endl << "{"
            << endl << "    StackTexData data = descMaterial.metalness;"
            << endl << "    return EvaluateTexture(data).r;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_ENV_DATA:
            OSG_ASSERT(false);
            break;
    }
}

void DescMaterial::getFragmentProgramMaterialRoughMetal(std::stringstream& ost) const
{
    using namespace std;

    switch (evalFragtProgTexType(TextureDesc::ROUGH_METAL_TEXTURE))
    {
        case DISCARD:
            break;
        case IS_COLOR_DATA:
            ost
            << endl << "vec2 getMaterialRoughMetal()"
            << endl << "{"
            << endl << "    return descMaterial.roughMetal.gb;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_SINGLE_DATA:
            ost
            << endl << "vec2 getMaterialRoughMetal()"
            << endl << "{"
            << endl << "    SingleTexData data = descMaterial.roughMetal;"
            << endl << "    return EvaluateTexture(data).gb;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_STACK_DATA:
            ost
            << endl << "vec2 getMaterialRoughMetal()"
            << endl << "{"
            << endl << "    StackTexData data = descMaterial.roughMetal;"
            << endl << "    return EvaluateTexture(data).gb;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_ENV_DATA:
            OSG_ASSERT(false);
            break;
    }
}

void DescMaterial::getFragmentProgramMaterialOcclRoughMetal(std::stringstream& ost) const
{
    using namespace std;

    switch (evalFragtProgTexType(TextureDesc::OCCL_ROUGH_METAL_TEXTURE))
    {
        case DISCARD:
            break;
        case IS_COLOR_DATA:
            ost
            << endl << "vec3 getMaterialOcclRoughMetal()"
            << endl << "{"
            << endl << "    return descMaterial.occlRoughMetal.rgb;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_SINGLE_DATA:
            ost
            << endl << "vec3 getMaterialOcclRoughMetal()"
            << endl << "{"
            << endl << "    SingleTexData data = descMaterial.occlRoughMetal;"
            << endl << "    return EvaluateTexture(data).rgb;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_STACK_DATA:
            ost
            << endl << "vec3 getMaterialOcclRoughMetal()"
            << endl << "{"
            << endl << "    StackTexData data = descMaterial.occlRoughMetal;"
            << endl << "    return EvaluateTexture(data).rgb;"
            << endl << "}"
            << endl << ""
            ;
            break;
            break;
        case IS_ENV_DATA:
            OSG_ASSERT(false);
            break;
    }
}

void DescMaterial::getFragmentProgramMaterialIrradiance(std::stringstream& ost) const
{
    using namespace std;

    if (!hasMaterialMember(IrradianceMaterialMember)) return;

    switch (evalFragtProgTexType(TextureDesc::IRRADIANCE_TEXTURE))
    {
        case DISCARD:
            ost
            << endl << "vec3 getMaterialIrradiance(in vec3 N)"
            << endl << "{"
            << endl << "    return vec3(0,0,0);"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_COLOR_DATA:
            OSG_ASSERT(false);
            break;
        case IS_SINGLE_DATA:
            OSG_ASSERT(false);
            break;
        case IS_STACK_DATA:
            OSG_ASSERT(false);
            break;
        case IS_ENV_DATA:
            ost
            << endl << "vec3 getMaterialIrradiance(in vec3 N)"
            << endl << "{"
            << endl << "    EnvTexData data = descMaterial.irradiance;"
            ;
            if (_info.textureEnvMapIsCubeMap[TextureDesc::IRRADIANCE_TEXTURE])
            {
                ost
                << endl << "    return EvaluateCubeTexture(data, N).rgb;"
                ;
            }
            else
            {
                ost
                << endl << "    float lod = CalcMipLevel(N);"
                << endl << ""
                << endl << "    return EvaluateEquirectangularTexture(data, N, lod).rgb;"
                ;
            }
            ost
            << endl << "}"
            << endl << ""
            ;
            break;
    }
}

void DescMaterial::getFragmentProgramMaterialPreFilterColor(std::stringstream& ost) const
{
    using namespace std;

    if (!hasMaterialMember(PreFilterColorMaterialMember)) return;

    switch (evalFragtProgTexType(TextureDesc::PRE_FILTER_TEXTURE))
    {
        case DISCARD:
            ost
            << endl << "vec3 getMaterialPreFilterColor(in vec3 N, in vec3 V, in float roughness)"
            << endl << "{"
            << endl << "    return vec3(0,0,0);"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_COLOR_DATA:
            OSG_ASSERT(false);
            break;
        case IS_SINGLE_DATA:
            OSG_ASSERT(false);
            break;
        case IS_STACK_DATA:
            OSG_ASSERT(false);
            break;
        case IS_ENV_DATA:
            ost
            << endl << "vec3 getMaterialPreFilterColor(in vec3 N, in vec3 V, in float roughness)"
            << endl << "{"
            << endl << "    const float MAX_REFLECTION_LOD = 4.0;"
            << endl << "    float lod = MAX_REFLECTION_LOD * roughness;"
            << endl << ""
            << endl << "    vec3 R = reflect(-V, N);"
            << endl << ""
            << endl << "    EnvTexData data = descMaterial.irradiance;"
            << endl << ""
            ;
            if (_info.textureEnvMapIsCubeMap[TextureDesc::PRE_FILTER_TEXTURE])
            {
                ost
                << endl << "    return EvaluateCubeTexture(data, R, lod).rgb;"
                ;
            }
            else
            {
                ost
                << endl << "    return EvaluateEquirectangularTexture(data, R, lod).rgb;"
                ;
            }
            ost
            << endl << "}"
            << endl << ""
            ;
            break;
    }
}

void DescMaterial::getFragmentProgramMaterialBrdf(std::stringstream& ost) const
{
    using namespace std;

    if (!hasMaterialMember(BrdfMaterialMember)) return;

    switch (evalFragtProgTexType(TextureDesc::BRDF_LUT_TEXTURE))
    {
        case DISCARD:
            ost
            << endl << "vec2 getMaterialBrdfLUTValue(in vec3 N, in vec3 V, in float roughness)"
            << endl << "{"
            << endl << "    return vec2(0,0);"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_COLOR_DATA:
            OSG_ASSERT(false);
            break;
        case IS_SINGLE_DATA:
            ost
            << endl << "vec2 getMaterialBrdfLUTValue(in vec3 N, in vec3 V, in float roughness)"
            << endl << "{"
            << endl << "    bool  isSRGB = descMaterial.brdf.isSRGB;"
            << endl << "    int   idx    = descMaterial.brdf.index;"
            << endl << ""
            << endl << "    vec2  uv     = vec2(max(dot(N, V), 0.0), roughness);"
            << endl << "    return EvaluateTexture(isSRGB, 0, 1.0, idx, uv).rg;"
            << endl << "}"
            << endl << ""
            ;
            break;
        case IS_STACK_DATA:
            OSG_ASSERT(false);
            break;
        case IS_ENV_DATA:
            OSG_ASSERT(false);
            break;
    }
}

void DescMaterial::getFragmentProgramMaterialF0(std::stringstream& ost) const
{
    using namespace std;

    if (!hasMaterialMember(SpecularMaterialMember)) return;

    if (hasMetalnessRoughnessWorkflow())
    {
        ost
        << endl << "vec3 getMaterialF0(in vec3 albedo, in float metalness, in float reflectance)"
        << endl << "{"
        << endl << "    vec3 F0 = maximumDielectricSpecular * reflectance * reflectance;"
        << endl << "    return mix(F0, albedo, metalness);"
        << endl << "}"
        << endl << ""
        ;
    }
}

void DescMaterial::getFragmentProgramMaterialInitialization(std::stringstream& ost) const
{
    using namespace std;

    ost
    << endl << "void InitializeMaterial()"
    << endl << "{"
    ;

    if (_info.numUVTextures > 0)
    {
        if (_info.vertOptVariant == OptOnlyChannel0)
        {
            ost
            << endl << "    material.texCoord          = vTexCoord;"
            ;
        }
        else
        {
            ost
            << endl << "    for (int i = 0; i < ciNumUVTextures; ++i)"
            << endl << "        material.texCoords[i] = vTexCoords[i];"
            << endl << ""
            ;
        }
    }

    if (needTangentSpace())
    {
        if (_info.matDesc->getHasTangentsAndBitangentsMode())
        {
            ost
            << endl << "    geomContext.matESFromTS    = OSGGetCoTangentFrame(geomContext.T, geomContext.B, geomContext.N);"
            << endl << "    geomContext.matTSFromES    = transpose(geomContext.matESFromTS);"
            << endl << ""
            ;
        }
        else
        {
            if (_info.vertOptVariant == OptOnlyChannel0)
            {
                ost
                << endl << "    vec2 uv = material.texCoord;"
                ;
            }
            else
            {
                ost
                << endl << "    // Hack: Assume that all textures share the same texture channel."
                << endl << "    vec2 uv = material.texCoords[0];"
                ;
            }
            ost
            << endl << ""
            << endl << "    geomContext.matESFromTS    = OSGGetCoTangentFrame(geomContext.N, geomContext.P, uv);"
            << endl << "    geomContext.matTSFromES    = transpose(geomContext.matESFromTS);"
            << endl << ""
            << endl << "    geomContext.T              = normalize(geomContext.matESFromTS[0]);"
            << endl << "    geomContext.B              = normalize(geomContext.matESFromTS[1]);"
            << endl << ""
            ;
        }
    }

    MaterialDesc* matDesc = getMaterialDesc();
    if (hasTexMapDetail(DisplacementTextures) && matDesc->getFrontMode()==GL_FILL)
    {
        ost
        << endl << "    ParallaxRemapTexureCoords();"
        << endl << ""
        ;
    }

    if (hasTexMapDetail(HeightTextures))
    {
        ost
        << endl << "    geomContext.N = HeighMapping(geomContext.N);"
        << endl << ""
        ;
    }

    ost
    << endl << "    material.emissive          = getMaterialEmissive();"
    << endl << "    material.albedo            = getMaterialAlbedo();"
    ;

    if (hasSpecularGlossinessTexture())
    {
        ost
        << endl << "    vec4 specularGlossiness    = getMaterialSpecularGlossiness();"
        << endl << "    material.specular          = specularGlossiness.rgb;"
        ;
    }
    else if (hasMetalnessRoughnessWorkflow())
    {
    }
    else
    {
        ost
        << endl << "    material.specular          = getMaterialSpecular();"
        ;
    }

    ost
    << endl << "    material.shininess         = getMaterialShininess();"
    ;

    if (hasTexMapDetail(StandardMaterialTextures))
    {
        ost
        << endl << "    material.emissive          = getMaterialStandard(material.emissive);"
        << endl << "    material.albedo            = getMaterialStandard(material.albedo);"
        ;
    }

    if (hasMatBlockMember(EmissiveStrengthBlockMember))
    {
        ost
        << endl << "    material.emissive         *= descMaterial.emissiveStrength;"
        ;
    }

    if (hasMatBlockMember(SpecularStrengthBlockMember))
    {
        ost
        << endl << "    material.specular         *= descMaterial.specularStrength;"
        ;
    }

    if (hasTexMapDetail(RoughMetalTextures))
    {
        ost
        << endl << ""
        << endl << "    vec2 roughMetal            = getMaterialRoughMetal();"
        << endl << "    material.roughness         = clamp(roughMetal.x, 0.04, 1.0);"
        << endl << "    material.metalness         = roughMetal.y;"
        ;
    }
    else
    if (hasTexMapDetail(OcclRoughMetalTextures))
    {
        ost
        << endl << ""
        << endl << "    vec3 occlRoughMetal        = getMaterialOcclRoughMetal();"
        << endl << "    material.ambientOcclusion  = occlRoughMetal.x;"
        << endl << "    material.roughness         = clamp(occlRoughMetal.y, 0.04, 1.0);"
        << endl << "    material.metalness         = occlRoughMetal.z;"
        ;
    }
    else
    {
        if (hasMaterialMember(RoughnessMaterialMember))
        {
            ost
            << endl << "    material.roughness         = clamp(getMaterialRoughness(), 0.04, 1.0);"
            ;
        }
        if (hasMaterialMember(MetalnessMaterialMember))
        {
            ost
            << endl << "    material.metalness         = getMaterialMetalness();"
            ;
        }
    }

    //
    // Iff no roughness texture is given, we evaluate the specularGlossiness.a value!!!
    //
    if (hasSpecularGlossinessTexture())
    {
        ost
        << endl << "    material.roughness         = saturate(1.0 - (1.0 - material.roughness) * specularGlossiness.a);"
        ;
    }

    if (hasMaterialMember(RoughnessMaterialMember))
    {
        ost
            << endl << "    material.alphaRoughness    = OSGPow2(material.roughness);"    // See https://github.com/KhronosGroup/glTF/tree/master/specification/2.0#materials
        ;
    }

    if (hasMaterialMember(SpecularMaterialMember))
    {
        if (hasMetalnessRoughnessWorkflow())
        {
            ost
            << endl << "    material.specular          = getMaterialF0(material.albedo, material.metalness, descMaterial.reflectance);"
            ;
        }
    }

    if (hasMaterialMember(DiffuseMaterialMember))
    {
        if (hasSpecularGlossinessWorkflow())
        {
            ost
            //<< endl << "    material.diffuse           = material.albedo * (1.0 - OSGMaxOf(material.specular));"
            << endl << "    material.diffuse           = material.albedo;"

            ;
        }
        else if (hasMetalnessRoughnessWorkflow())
        {
            ost
            //<< endl << "    material.diffuse           = mix(material.albedo * (1.0 - defaultDielectricSpecular), OSG_BLACK, material.metalness);"
            << endl << "    material.diffuse           = mix(material.albedo, OSG_BLACK, material.metalness);"
            ;
        }
        else
        {
            ost
            << endl << "    material.diffuse           = material.albedo;"
            ;
        }
    }

    if (hasTexMapDetail(ReflectionTextures) || hasTexMapDetail(RefractionTextures))
    {
        ost
        << endl << ""
        << endl << "    vec3 V_WS     = normalize(OSGCameraPosition - vPositionWS);"
        << endl << "    vec3 fragN_WS = normalize(vNormalWS);"
        << endl << ""
        ;
    }

    if (hasTexMapDetail(ReflectionTextures))
    {
        ost
        << endl << "    material.reflection        = getMaterialReflection(fragN_WS, V_WS);"
        ;
    }

    if (hasTexMapDetail(RefractionTextures))
    {
        ost
        << endl << "    material.refraction        = getMaterialRefraction(fragN_WS, V_WS);"
        ;
    }

    if (hasTexMapDetail(AnisotropyUVTextures))
    {
        ost
        << endl << ""
        << endl << "    vec2 materialAnisotropyUV getMaterialAnisotropyUV();"
        << endl << "    material.anisotropyU       = materialAnisotropyUV.x;"
        << endl << "    material.anisotropyV       = materialAnisotropyUV.y;"
        << endl << ""
        ;
    }
    else
    {
        if (hasMaterialMember(AnisotropyUMaterialMember))
        {
            ost
            << endl << "    material.anisotropyU       = getMaterialAnisotropyU();"
            ;
        }

        if (hasMaterialMember(AnisotropyVMaterialMember))
        {
            ost
            << endl << "    material.anisotropyV       = getMaterialAnisotropyV();"
            ;
        }
    }

    if (hasMaterialMember(ToonScaleMaterialMember))
    {
        ost
        << endl << "    material.toonScale         = 1.0 / descMaterial.toonLevels;"
        ;
    }

    if (hasTexMapDetail(NormalsTextures))
    {
        ost
        << endl << "    geomContext.N              = getMaterialNormal();"
        ;
    }

    if (hasMaterialMember(IrradianceMaterialMember))
    {
        ost
        << endl << "    material.irradiance        = getMaterialIrradiance(geomContext.N);"
        ;
    }

    if (hasMaterialMember(PreFilterColorMaterialMember))
    {
        ost
        << endl << "    material.preFilterColor    = getMaterialPreFilterColor(geomContext.N, V, material.roughness);"
        ;
    }

    if (hasMaterialMember(BrdfMaterialMember))
    {
        ost
        << endl << "    material.brdf              = getMaterialBrdfLUTValue(geomContext.N, V, material.roughness);"
        ;
    }

    ost
    << endl << ""
    << endl << "    material.opacity           = getMaterialOpacity();"
    ;

    if (matDesc->getOpacityMode()==MaterialDesc::MASK_OPACITY_MODE)
    {
        ost
        << endl << "    if (material.opacity < descMaterial.opacityCutOff)"
        << endl << "        discard;"
        ;
    }

    ost
    << endl << "}"
    << endl << ""
    ;
}

void DescMaterial::getFragmentProgramMaterialShadingModel(std::stringstream& ost) const
{
    using namespace std;

    switch (_info.getShadingModel())
    {
        case MaterialDesc::NO_SHADING_MODEL:                getFragmentProgramMaterialModelNo           (ost); break;
        case MaterialDesc::GOURAUD_SHADING_MODEL:           getFragmentProgramMaterialModelGouraud      (ost); break;
        case MaterialDesc::PHONG_SHADING_MODEL:             getFragmentProgramMaterialModelPhong        (ost); break;
        case MaterialDesc::BLINN_PHONG_SHADING_MODEL:       getFragmentProgramMaterialModelBlinn        (ost); break;
        case MaterialDesc::COOK_TORRANCE_SHADING_MODEL:     getFragmentProgramMaterialModelCookTorrance (ost); break;
        case MaterialDesc::OREN_NAYAR_SHADING_MODEL:        getFragmentProgramMaterialModelOrenNayar    (ost); break;
        case MaterialDesc::TOON_SHADING_MODEL:              getFragmentProgramMaterialModelToon         (ost); break;
        case MaterialDesc::GOOCH_SHADING_MODEL:             getFragmentProgramMaterialModelGooch        (ost); break;
    }
}

void DescMaterial::getFragmentProgramMaterialModelNo(std::stringstream& ost) const
{
    using namespace std;

    ost
    << endl << "void DirectShading(in vec3 I)"
    << endl << "{"
    << endl << "}"
    << endl << ""
    ;

    getFragmentProgramImageBasedLightEmpty(ost);
}

void DescMaterial::getFragmentProgramMaterialModelGouraud(std::stringstream& ost) const
{
    using namespace std;

    ost
    << endl << "vec3 BRDF_Diffuse_Lambert(const in vec3 diffColor)"
    << endl << "{"
    << endl << "    return OSG_INV_PI * diffColor;"
    << endl << "}"
    << endl << ""
    << endl << "void DirectShading(in vec3 I)"
    << endl << "{"
    << endl << "    geomContext.NdotL = saturate(dot(geomContext.N, geomContext.L));"
    << endl << ""
    << endl << "    vec3 irradiance = I * geomContext.NdotL;"
    << endl << ""
    << endl << "    outLight.directDiffuse  += irradiance * BRDF_Diffuse_Lambert(material.diffuse);"
    << endl << "}"
    << endl << ""
    ;

    getFragmentProgramImageBasedLightEmpty(ost);
}

void DescMaterial::getFragmentProgramMaterialModelPhong(std::stringstream& ost) const
{
    using namespace std;

    ost
    << endl << "vec3 F_Schlick(in vec3 F0)"
    << endl << "{"
    << endl << "    // Original approximation by Christophe Schlick '94"
    << endl << "    // float fresnel = pow( 1.0 - LdotH, 5.0 );"
    << endl << ""
    << endl << "    // Optimized variant (presented by Epic at SIGGRAPH '13)"
    << endl << "    // https://cdn2.unrealengine.com/Resources/files/2013SiggraphPresentationsNotes-26915738.pdf"
    << endl << "    float fresnel = exp2( ( -5.55473 * geomContext.LdotH - 6.98316 ) * geomContext.LdotH );"
    << endl << ""
    << endl << "    return (vec3(1.0) - F0) * fresnel + F0;"
    << endl << "}"
    << endl << ""
    << endl << "float G_Phong()"
    << endl << "{"
    << endl << "    // geometry term is (NdotL)(NdotV) / 4(NdotL)(NdotV)"
    << endl << "    return 0.25;"
    << endl << "}"
    << endl << ""
    << endl << "float D_Phong(const in float shininess)"
    << endl << "{"
    << endl << "    vec3 R = reflect(-geomContext.L, geomContext.N);"
    << endl << "    float RdotV = saturate(dot(R, geomContext.V));"
    << endl << ""
    << endl << "    return OSG_INV_2PI * (2.0 + shininess) * pow(RdotV, shininess);"
    << endl << "}"
    << endl << ""
    << endl << "vec3 BRDF_Diffuse_Lambert(const in vec3 diffColor)"
    << endl << "{"
    << endl << "    return OSG_INV_PI * diffColor;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 BRDF_Specular_Phong(const in vec3 specColor, const in float shininess)"
    << endl << "{"
    << endl << "    geomContext.H = normalize(geomContext.L + geomContext.V);"
    << endl << ""
    << endl << "    geomContext.NdotH = saturate(dot(geomContext.N, geomContext.H));"
    << endl << "    geomContext.LdotH = saturate(dot(geomContext.L, geomContext.H));"
    << endl << ""
    << endl << "    vec3  F = F_Schlick(specColor);"
    << endl << "    float G = G_Phong  ();"
    << endl << "    float D = D_Phong  (shininess);"
    << endl << ""
    << endl << "    return F * ( G * D );"
    << endl << "}"
    << endl << ""
    << endl << "void DirectShading(in vec3 I)"
    << endl << "{"
    << endl << "    geomContext.NdotL = saturate(dot(geomContext.N, geomContext.L));"
    << endl << ""
    << endl << "    vec3 irradiance = I * geomContext.NdotL;"
    << endl << ""
    << endl << "    outLight.directDiffuse  += irradiance * BRDF_Diffuse_Lambert(material.diffuse);"
    << endl << "    outLight.directSpecular += irradiance * BRDF_Specular_Phong (material.specular, material.shininess);"
    << endl << "}"
    << endl << ""
    ;

    getFragmentProgramImageBasedLightEmpty(ost);
}

void DescMaterial::getFragmentProgramMaterialModelBlinn(std::stringstream& ost) const
{
    using namespace std;

    ost
    << endl << "vec3 F_Schlick(in vec3 F0)"
    << endl << "{"
    << endl << "    // Original approximation by Christophe Schlick '94"
    << endl << "    // float fresnel = pow( 1.0 - LdotH, 5.0 );"
    << endl << ""
    << endl << "    // Optimized variant (presented by Epic at SIGGRAPH '13)"
    << endl << "    // https://cdn2.unrealengine.com/Resources/files/2013SiggraphPresentationsNotes-26915738.pdf"
    << endl << "    float fresnel = exp2( ( -5.55473 * geomContext.LdotH - 6.98316 ) * geomContext.LdotH );"
    << endl << ""
    << endl << "    return (vec3(1.0) - F0) * fresnel + F0;"
    << endl << "}"
    << endl << ""
    << endl << "float G_BlinnPhong()"
    << endl << "{"
    << endl << "    // geometry term is (NdotL)(NdotV) / 4(NdotL)(NdotV)"
    << endl << "    return 0.25;"
    << endl << "}"
    << endl << ""
    << endl << "float D_BlinnPhong(const in float shininess)"
    << endl << "{"
    << endl << "    return OSG_INV_PI * ( material.shininess * 0.5 + 1.0 ) * pow(geomContext.NdotH, shininess);"
    << endl << "}"
    << endl << ""
    << endl << "vec3 BRDF_Diffuse_Lambert(const in vec3 diffColor)"
    << endl << "{"
    << endl << "    return OSG_INV_PI * diffColor;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 BRDF_Specular_BlinnPhong(const in vec3 specColor, const in float shininess)"
    << endl << "{"
    << endl << "    geomContext.H = normalize(geomContext.L + geomContext.V);"
    << endl << ""
    << endl << "    geomContext.NdotH = saturate(dot(geomContext.N, geomContext.H));"
    << endl << "    geomContext.LdotH = saturate(dot(geomContext.L, geomContext.H));"
    << endl << ""
    << endl << "    vec3  F = F_Schlick   (specColor);"
    << endl << "    float G = G_BlinnPhong();"
    << endl << "    float D = D_BlinnPhong(shininess);"
    << endl << ""
    << endl << "    return F * ( G * D );"
    << endl << "}"
    << endl << ""
    << endl << "void DirectShading(in vec3 I)"
    << endl << "{"
    << endl << "    geomContext.NdotL = saturate(dot(geomContext.N, geomContext.L));"
    << endl << ""
    << endl << "    vec3 irradiance = I * geomContext.NdotL;"
    << endl << ""
    << endl << "    outLight.directDiffuse  += irradiance * BRDF_Diffuse_Lambert    (material.diffuse);"
    << endl << "    outLight.directSpecular += irradiance * BRDF_Specular_BlinnPhong(material.specular, material.shininess);"
    << endl << "}"
    << endl << ""
    ;

    getFragmentProgramImageBasedLightEmpty(ost);
}

void DescMaterial::getFragmentProgramMaterialModelCookTorrance(std::stringstream& ost) const
{
    using namespace std;

    // See https://github.com/KhronosGroup/glTF/tree/master/specification/2.0#appendix-b-brdf-implementation

    ost

    //
    // 1. Surface Reflection Ratio (F) Term (Fresnel Law)
    //
    << endl << "//"
    << endl << "// Surface Reflection Ratio (F): Fresnel Schlick: Optimized by Epic at SIGGRAPH '13"
    << endl << "//"

    << endl << "vec3 F_Schlick(in vec3 F0, in float f90, in float cosFac)"
    << endl << "{"
    << endl << "    // float fresnel = pow(1.0 - cosFac, 5.0);"                         // Original approximation by Christophe Schlick '94
    << endl << "    float fresnel = exp2(( -5.55473 * cosFac - 6.98316 ) * cosFac);"    // Optimized variant: (presented by Epic at SIGGRAPH '13) https://cdn2.unrealengine.com/Resources/files/2013SiggraphPresentationsNotes-26915738.pdf
    << endl << "    return (vec3(f90) - F0) * fresnel + F0;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 F_Schlick(in vec3 F0, in float f90, in float cosFac, in float alpha)"
    << endl << "{"
    << endl << "    // float fresnel = pow(1.0 - cosFac, 5.0);"                         // Original approximation by Christophe Schlick '94
    << endl << "    float fresnel = exp2(( -5.55473 * cosFac - 6.98316 ) * cosFac);"    // Optimized variant: (presented by Epic at SIGGRAPH '13) https://cdn2.unrealengine.com/Resources/files/2013SiggraphPresentationsNotes-26915738.pdf
    << endl << "    return (max(vec3(vec3(f90) - alpha), F0) - F0) * fresnel + F0;"
    << endl << "}"
    << endl << ""

    //
    // 2. Geometric Occlusion/Shadowing/Visibility (G) Term
    //
    << endl << "//"
    << endl << "// Geometric Occlusion (G): Smith Joint GGX height-correlated function by Heitz"
    << endl << "//"

    //
    // I. Frostbite alternative
    //
    //<< endl << "float GeometrySchlickGGX(const in float cosFac, const in float k)"
    //<< endl << "{"
    //<< endl << "    return 1.0 / (cosFac * (1.0 - k) + k);"
    //<< endl << "}"
    //<< endl << ""
    //<< endl << "float V_SmithCorrelatedFrostbite(const in float alpha)"
    //<< endl << "{"
    //<< endl << "    float r = alpha + 1.0;"
    //<< endl << "    float k = (r*r) / 8.0;"
    //<< endl << ""
    //<< endl << "    float NdotL = max(0.001, geomContext.NdotL);"
    //<< endl << "    float NdotV = geomContext.NdotV;"
    //<< endl << ""
    //<< endl << "    float ggx1  = GeometrySchlickGGX(NdotL, k);"
    //<< endl << "    float ggx2  = GeometrySchlickGGX(NdotV, k);"
    //<< endl << ""
    //<< endl << "    return ggx1 * ggx2 * 0.25;"
    //<< endl << "}"
    //<< endl << ""
    //<< endl << "float GGX_Smith_Lambda(in float a2, in float cosFac2)"
    //<< endl << "{"
    //<< endl << "    return 0.5 * (-1.0 + sqrt(1.0 + a2 * (1.0 - cosFac2) / cosFac2));"
    //<< endl << "}"
    //<< endl << ""
    //
    // II. Correct Smith Joint GGX height-correlated function by Heitz
    //
    //<< endl << "float V_SmithGGXCorrelatedOrg(const in float alpha)"
    //<< endl << "{"
    //<< endl << "    float a2 = alpha * alpha;"
    //<< endl << "    float cosFacV2 = geomContext.NdotV * geomContext.NdotV;"
    //<< endl << "    float cosFacL2 = geomContext.NdotL * geomContext.NdotL;"
    //<< endl << ""
    //<< endl << "    float nominator   = step(0.0, geomContext.NdotV) * step(0.0, geomContext.NdotL);"
    //<< endl << "    float denominator = 1.0 + GGX_Smith_Lambda(a2, cosFacV2) + GGX_Smith_Lambda(a2, cosFacL2);"
    //<< endl << ""
    //<< endl << "    denominator *= 4.0 * geomContext.NdotV * geomContext.NdotL;"
    //<< endl << ""
    //<< endl << "    return nominator / max(denominator, OSG_EPS);"
    //<< endl << "}"
    //<< endl << ""

    //
    // III. Optimized Correct Smith Joint GGX height-correlated function by Heitz. Aquivalent to II.
    //

    //
    // Moving Frostbite to Physically Based Rendering 3.0 - page 12, listing 2"
    // https://seblagarde.files.wordpress.com/2015/07/course_notes_moving_frostbite_to_pbr_v32.pdf"
    //
    << endl << "float V_SmithGGXCorrelated(const in float alpha)"
    << endl << "{"
    << endl << "    float a2 = alpha * alpha;"
    << endl << "    float GGXV = geomContext.NdotL * sqrt(geomContext.NdotV * geomContext.NdotV * (1.0 - a2) + a2);"
    << endl << "    float GGXL = geomContext.NdotV * sqrt(geomContext.NdotL * geomContext.NdotL * (1.0 - a2) + a2);"
    << endl << "    return 0.5 / max(GGXV + GGXL, OSG_EPS);"
    << endl << "}"
    << endl << ""

    //
    // IV. Approximation of the correct Smith Joint GGX height-correlated function by Heitz.
    //
    //    We can optimize this visibility function by using an approximation after noticing that all the
    //    terms under the square roots are squares and that all the terms are in the range.
    //    This approximation is mathematically wrong but saves two square root operations and is good
    //    enough for real-time mobile applications.
    //
    //<< endl << "float V_SmithGGXCorrelated(const in float alpha)"
    //<< endl << "{"
    //<< endl << "    float a = alpha;"
    //<< endl << "    float GGXV = geomContext.NdotL * (geomContext.NdotV * (1.0 - a) + a);"
    //<< endl << "    float GGXL = geomContext.NdotV * (geomContext.NdotL * (1.0 - a) + a);"
    //<< endl << "    return 0.5 / max(GGXV + GGXL, OSG_EPS);"
    //<< endl << "}"
    //<< endl << ""


    //
    // 3. Microfacet Normnal Distribution (D) Term
    //
    << endl << "//"
    << endl << "// Microfacet Distribution (D) : GGX Trowbridge-Reitz"
    << endl << "//"

    //
    // Microfacet Models for Refraction through Rough Surfaces - equation (33)
    // http://graphicrants.blogspot.com/2013/08/specular-brdf-reference.html
    // alpha is 'roughness squared' in Disney's reparameterization
    //
    //<< endl << "float D_GGX(const in float alpha)"    // original
    //<< endl << "{"
    //<< endl << "    float alpha2 = alpha * alpha;"
    //<< endl << "    float nominator   = alpha2;"
    //<< endl << "    float denominator = OSGPow2(geomContext.NdotH) * (alpha2 - 1.0) + 1.0;"
    //<< endl << ""
    //<< endl << "    denominator = OSGPow2(denominator);"      // OSG_PI * is done in the BRDF_Specular_GGX
    //<< endl << ""
    //<< endl << "    return nominator / denominator;"
    //<< endl << "}"
    << endl << "float D_GGX(const in float alpha)"  // idenditcal but optimized!
    << endl << "{"
    << endl << "    float a = geomContext.NdotH * alpha;"
    << endl << "    float k = alpha / (1.0 - geomContext.NdotH * geomContext.NdotH + a * a);"
    << endl << "    return k * k;"                  // * OSG_INV_PI done later in the BRDF_Specular_GGX"
    << endl << "}"
    << endl << ""

    //
    // 4. Diffuse BRDF
    //

    << endl << "//"
    << endl << "// Diffuse BRDF"
    << endl << "//"
    << endl << "vec3 BRDF_Diffuse_Lambert(const in vec3 diffColor)"
    << endl << "{"
    << endl << "    return OSG_INV_PI * diffColor;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 BRDF_Diffuse_Disney(const in vec3 diffColor, const in float roughness)"
    << endl << "{"
    << endl << "    float energyBias   = lerp(0.0, 0.5, roughness);"
    << endl << "    float energyFactor = lerp(1.0, 1.0 / 1.51, roughness);"
    << endl << "    float f90          = energyBias + 2.0 * OSGPow2(geomContext.LdotH) * roughness;"
    << endl << "    vec3  F0           = vec3(1.0f, 1.0f, 1.0f);"
    << endl << "    float lightScatter = F_Schlick(F0, f90, geomContext.NdotL).r;"
    << endl << "    float viewScatter  = F_Schlick(F0, f90, geomContext.NdotV).r;"
    << endl << ""
    << endl << "    return OSG_INV_PI * lightScatter * viewScatter * energyFactor * diffColor;"
    << endl << "}"
    << endl << ""

    //
    // 5. Specular BRDF
    //

    << endl << "//"
    << endl << "// Specular BRDF"
    << endl << "//"
    << endl << "vec3 BRDF_Specular_GGX(const in vec3 F0, const in float alpha)"
    << endl << "{"
    << endl << "    float f90 = 1.0;"
    << endl << ""
    << endl << "    float D = D_GGX                 (alpha);"
    << endl << "    float V = V_SmithGGXCorrelated  (alpha);"
    << endl << "    vec3  F = F_Schlick             (F0, f90, geomContext.LdotH);"
    << endl << ""
    << endl << "    return OSG_INV_PI * (D * V) * F;"
    << endl << "}"
    << endl << ""

    //
    // 6. Lighing calculation
    //

    << endl << "void DirectShading(in vec3 I)"
    << endl << "{"
    << endl << "    geomContext.H = normalize(geomContext.L + geomContext.V);"
    << endl << ""
    << endl << "    //geomContext.NdotV =      abs(dot(geomContext.N, geomContext.V)) + 1e-5;"
    << endl << "    geomContext.NdotV =    clamp(dot(geomContext.N, geomContext.V), 0.001, 1.0);"
    << endl << "    //geomContext.NdotV = saturate(dot(geomContext.N, geomContext.V));"

    << endl << "    geomContext.NdotL = saturate(dot(geomContext.N, geomContext.L));"
    << endl << "    geomContext.NdotH = saturate(dot(geomContext.N, geomContext.H));"
    << endl << "    geomContext.LdotH = saturate(dot(geomContext.L, geomContext.H));"
    << endl << ""
    << endl << "    vec3 irradiance = I * geomContext.NdotL;"
    << endl << ""
    << endl << "    float one_minus_clearCoat = 1.0 - 0.0; // 1.0 - getClearCoatDHRApprox();"
    << endl << "    float clearCoat           = 0.0;       // material.clearCoat;"
    << endl << ""
    << endl << "    //outLight.directDiffuse  += one_minus_clearCoat * irradiance * BRDF_Diffuse_Lambert(material.diffuse);"
    << endl << "    outLight.directDiffuse  += one_minus_clearCoat * irradiance * BRDF_Diffuse_Disney (material.diffuse,  material.alphaRoughness);"
    << endl << "    outLight.directSpecular += one_minus_clearCoat * irradiance * BRDF_Specular_GGX   (material.specular, material.alphaRoughness);"
    //<< endl << "    outLight.directSpecular +=           clearCoat * irradiance * BRDF_Specular_GGX(defaultDielectricSpecular, material.clearCoatRoughness);"
    << endl << "}"
    << endl << ""
    ;

    //
    // 7. Image base lighting (IBL)
    //

    if (getHasImageBasedLight())
    {
        ost
        << endl << "vec3 ImageBasedLight(in vec3 N, in vec3 V)"
        << endl << "{"
        << endl << "    float NdotV = clamp(abs(dot(N, V)), 0.001, 1.0);"
        << endl << ""
        << endl << "    vec3 kS = FresnelSchlickRoughness(NdotV, material.specular, material.roughness); "
        ;
        if (hasSpecularGlossinessWorkflow())
        {
            ost
        << endl << "    vec3 kD = (1.0 - kS);"
            ;
        }
        else
        {
            ost
        << endl << "    vec3 kD = (1.0 - kS) * (1.0 - material.metalness);"
            ;
        }
        ost
        << endl << ""
        << endl << "    return kD * material.irradiance * material.albedo;"
        << endl << "}"
        << endl << ""
        ;
    }
}

void DescMaterial::getFragmentProgramMaterialModelOrenNayar(std::stringstream& ost) const
{
    using namespace std;

    ost
    << endl << "//"
    << endl << "// http://blog.selfshadow.com/publications/s2012-shading-course/#course_content"
    << endl << "// http://blog.selfshadow.com/publications/s2012-shading-course/gotanda/s2012_pbs_beyond_blinn_notes_v3.pdf"
    << endl << "// http://blog.selfshadow.com/publications/s2012-shading-course/gotanda/s2012_pbs_beyond_blinn_slides_v3.pdf"
    << endl << "//"
    << endl << "vec3 BRDF_Diffuse_OrenNayar(const in vec3 diffColor, const in float roughness)"
    << endl << "{"
    << endl << "    float NdotL = dot(geomContext.N, geomContext.L);"
    << endl << "    float NdotV = dot(geomContext.N, geomContext.V);"
    << endl << ""
    << endl << "    vec3 vp = geomContext.V - geomContext.N * NdotV;    // projected view vector"
    << endl << "    vec3 lp = geomContext.L - geomContext.N * NdotL;    // projected light vector"
    << endl << ""
    << endl << "    vp = normalize(vp);"
    << endl << "    lp = normalize(lp);"
    << endl << ""
    << endl << "    float sigma   = roughness;"
    << endl << "    float sigma_2 = sigma*sigma;"
    << endl << ""
    << endl << "    float A = 1 - 0.50 * sigma_2/(sigma_2+0.33);"
    << endl << "    float B =     0.45 * sigma_2/(sigma_2+0.09);"
    << endl << ""
    << endl << "    float t1 = acos(NdotV);"
    << endl << "    float t2 = acos(NdotL);"
    << endl << ""
    << endl << "    float alpha = max(t1, t2);"
    << endl << "    float beta  = min(t1, t2);"
    << endl << "    "
    << endl << "    float D = max(0.0, dot(vp, lp));"
    << endl << ""
    << endl << "    float T = A + B * D * sin(alpha) * tan(beta);"
    << endl << ""
    << endl << "    return OSG_INV_PI * T * diffColor;"
    << endl << "}"
    << endl << ""
    << endl << "void DirectShading(in vec3 I)"
    << endl << "{"
    << endl << "    geomContext.NdotL = saturate(dot(geomContext.N, geomContext.L));"
    << endl << ""
    << endl << "    vec3 irradiance = I * geomContext.NdotL;"
    << endl << ""
    << endl << "    outLight.directDiffuse  += irradiance * BRDF_Diffuse_OrenNayar(material.diffuse, material.roughness);"
    << endl << "}"
    << endl << ""
    ;
/*
    ost
    << endl << "vec3 BRDF_Diffuse_OrenNayar(const in vec3 diffColor, const in float shininess)"
    << endl << "{"
    << endl << "    float NdotL = max(0.0, dot(geomContext.N, geomContext.L));"
    << endl << "    float VdotL = max(0.0, dot(geomContext.V, geomContext.L));"
    << endl << "    float NdotV = max(0.0, dot(geomContext.N, geomContext.V));"
    << endl << ""
    << endl << "    float A = 1.0 - 1.0 / (2.00000 + 0.65 * shininess);"
    << endl << "    float B =       1.0 / (2.22222 + 0.10 * shininess);"
    << endl << "    float C = VdotL - NdotV * NdotL;"
    << endl << "    float D = min(1.0, NdotL / NdotV);"
    << endl << ""
    << endl << "    float T = 0.0;"
    << endl << ""
    << endl << "    if (C >= 0.0)"
    << endl << "    {"
    << endl << "        T = A * NdotL + (B * C * D);"
    << endl << "    }"
    << endl << "    else"
    << endl << "    {"
    << endl << "        T = (A + B * C) * NdotL;"
    << endl << "    }"
    << endl << ""
    << endl << "    return OSG_INV_PI * T * diffColor;"
    << endl << "}"
    << endl << ""
    << endl << "void DirectShading(in vec3 I)"
    << endl << "{"
    << endl << "    geomContext.NdotL = saturate(dot(geomContext.N, geomContext.L));"
    << endl << ""
    << endl << "    vec3 irradiance = I;"
    << endl << ""
    << endl << "    outLight.directDiffuse  += irradiance * BRDF_Diffuse_OrenNayar(material.diffuse, material.shininess);"
    << endl << "}"
    << endl << ""
    ;
*/
    getFragmentProgramImageBasedLightEmpty(ost);
}

void DescMaterial::getFragmentProgramMaterialModelToon(std::stringstream& ost) const
{
    using namespace std;

    ost
    << endl << "vec3 F_Schlick(in vec3 F0)"
    << endl << "{"
    << endl << "    // Original approximation by Christophe Schlick '94"
    << endl << "    // float fresnel = pow( 1.0 - LdotH, 5.0 );"
    << endl << ""
    << endl << "    // Optimized variant (presented by Epic at SIGGRAPH '13)"
    << endl << "    // https://cdn2.unrealengine.com/Resources/files/2013SiggraphPresentationsNotes-26915738.pdf"
    << endl << "    float fresnel = exp2( ( -5.55473 * geomContext.LdotH - 6.98316 ) * geomContext.LdotH );"
    << endl << ""
    << endl << "    return (vec3(1.0) - F0) * fresnel + F0;"
    << endl << "}"
    << endl << ""
    << endl << "float G_BlinnPhong()"
    << endl << "{"
    << endl << "    // geometry term is (NdotL)(NdotV) / 4(NdotL)(NdotV)"
    << endl << "    return 0.25;"
    << endl << "}"
    << endl << ""
    << endl << "float D_BlinnPhong(const in float shininess)"
    << endl << "{"
    << endl << "    return OSG_INV_PI * ( shininess * 0.5 + 1.0 ) * pow(geomContext.NdotH, shininess);"
    << endl << "}"
    << endl << ""
    << endl << "vec3 BRDF_Diffuse_Lambert(const in vec3 diffColor)"
    << endl << "{"
    << endl << "    return OSG_INV_PI * diffColor;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 BRDF_Specular_BlinnPhong(const in vec3 specColor, const in float shininess)"
    << endl << "{"
    << endl << "    geomContext.H = normalize(geomContext.L + geomContext.V);"
    << endl << ""
    << endl << "    geomContext.NdotH = saturate(dot(geomContext.N, geomContext.H));"
    << endl << "    geomContext.LdotH = saturate(dot(geomContext.L, geomContext.H));"
    << endl << ""
    << endl << "    vec3  F = F_Schlick   (specColor);"
    << endl << "    float G = G_BlinnPhong();"
    << endl << "    float D = D_BlinnPhong(shininess);"
    << endl << ""
    << endl << "    return F * ( G * D );"
    << endl << "}"
    << endl << ""
    << endl << "void DirectShading(in vec3 I)"
    << endl << "{"
    << endl << "    geomContext.NdotL = saturate(dot(geomContext.N, geomContext.L));"
    << endl << ""
    << endl << "    int   levels      = descMaterial.toonLevels;"
    << endl << "    float scaleFactor = floor(geomContext.NdotL * levels) * material.toonScale;"
    << endl << ""
    << endl << "    vec3 irradiance = I * scaleFactor;"
    << endl << ""
    << endl << "    outLight.directDiffuse  += irradiance * BRDF_Diffuse_Lambert    (material.diffuse);"
    << endl << "    outLight.directSpecular += irradiance * BRDF_Specular_BlinnPhong(material.specular, material.shininess);"
    << endl << "}"
    << endl << ""
    ;

    getFragmentProgramImageBasedLightEmpty(ost);
}

void DescMaterial::getFragmentProgramMaterialModelGooch(std::stringstream& ost) const
{
    using namespace std;

    ost
    << endl << "vec3 GoochShading(in float dnl, in float NdotL, in vec3 C)"
    << endl << "{"
    << endl << "    vec3  cool       = descMaterial.goochCool;"
    << endl << "    vec3  warm       = descMaterial.goochWarm;"
    << endl << "    float mixin      = descMaterial.goochMixin;"
    << endl << "    float cool_mixin = descMaterial.goochCoolMixin;"
    << endl << "    float warm_mixin = descMaterial.goochWarmMixin;"
    << endl << ""
    << endl << "    cool = clamp(cool_mixin * cool + (1.0 - cool_mixin) * C, 0.0, 1.0);"
    << endl << "    warm = clamp(warm_mixin * warm + (1.0 - warm_mixin) * C, 0.0, 1.0);"
    << endl << ""
    << endl << "    return min(mixin * (dnl * cool + (1.0 - dnl) * warm) + (1.0 - mixin) * C * NdotL, 1.0);"
    << endl << "}"
    << endl << ""
    << endl << "vec3 F_Schlick(in vec3 F0)"
    << endl << "{"
    << endl << "    // Original approximation by Christophe Schlick '94"
    << endl << "    // float fresnel = pow( 1.0 - LdotH, 5.0 );"
    << endl << ""
    << endl << "    // Optimized variant (presented by Epic at SIGGRAPH '13)"
    << endl << "    // https://cdn2.unrealengine.com/Resources/files/2013SiggraphPresentationsNotes-26915738.pdf"
    << endl << "    float fresnel = exp2( ( -5.55473 * geomContext.LdotH - 6.98316 ) * geomContext.LdotH );"
    << endl << ""
    << endl << "    return (vec3(1.0) - F0) * fresnel + F0;"
    << endl << "}"
    << endl << ""
    << endl << "float G_BlinnPhong()"
    << endl << "{"
    << endl << "    // geometry term is (NdotL)(NdotV) / 4(NdotL)(NdotV)"
    << endl << "    return 0.25;"
    << endl << "}"
    << endl << ""
    << endl << "float D_BlinnPhong(const in float shininess)"
    << endl << "{"
    << endl << "    return OSG_INV_PI * ( shininess * 0.5 + 1.0 ) * pow(geomContext.NdotH, shininess);"
    << endl << "}"
    << endl << ""
    << endl << "vec3 BRDF_Diffuse_Lambert(const in vec3 diffColor)"
    << endl << "{"
    << endl << "    return OSG_INV_PI * diffColor;"
    << endl << "}"
    << endl << ""
    << endl << "vec3 BRDF_Specular_BlinnPhong(const in vec3 specColor, const in float shininess)"
    << endl << "{"
    << endl << "    geomContext.H = normalize(geomContext.L + geomContext.V);"
    << endl << ""
    << endl << "    geomContext.NdotH = saturate(dot(geomContext.N, geomContext.H));"
    << endl << "    geomContext.LdotH = saturate(dot(geomContext.L, geomContext.H));"
    << endl << ""
    << endl << "    vec3  F = F_Schlick   (specColor);"
    << endl << "    float G = G_BlinnPhong();"
    << endl << "    float D = D_BlinnPhong(shininess);"
    << endl << ""
    << endl << "    return F * ( G * D );"
    << endl << "}"
    << endl << ""
    << endl << "void DirectShading(in vec3 I)"
    << endl << "{"
    << endl << "    float ndotl = dot(geomContext.N, geomContext.L);"
    << endl << "    float dnl   = 0.5 * (1.0 + ndotl);"
    << endl << ""
    << endl << "    geomContext.NdotL = saturate(ndotl);"
    << endl << ""
    << endl << "    vec3 irradiance = I;"
    << endl << ""
    << endl << "    outLight.directDiffuse  += irradiance * GoochShading(dnl, geomContext.NdotL, material.diffuse)  * OSG_INV_PI;"
    << endl << "    outLight.directSpecular += irradiance * GoochShading(dnl, geomContext.NdotL, material.specular) * BRDF_Specular_BlinnPhong(material.specular, material.shininess);"
    << endl << "}"
    << endl << ""
    ;

    getFragmentProgramImageBasedLightEmpty(ost);
}

void DescMaterial::getFragmentProgramImageBasedLightEmpty(std::stringstream& ost) const
{
    using namespace std;

    if (getHasImageBasedLight())
    {
        ost
        << endl << "vec3 ImageBasedLight(in vec3 N, in vec3 V)"
        << endl << "{"
        << endl << "    return vec3(0);"
        << endl << "}"
        << endl << ""
        ;
    }
}

void DescMaterial::getFragmentProgramPostProcessing(std::stringstream& ost) const
{
    using namespace std;

    ost
    << endl << "vec3 PostProcessColor(in vec3 color)"
    << endl << "{"
    ;
    if (hasTexMapDetail(ReflectionTextures))
    {
        if (hasMaterialMember(ReflectiveMaterialMember))
        {
            ost
            << endl << "    color = descMaterial.reflective * mix(color, material.reflection, vec3(descMaterial.reflectivity));"
            << endl << ""
            ;
        }
        else
        {
            ost
            << endl << "    color = mix(color, material.reflection, vec3(descMaterial.reflectivity));"
            << endl << ""
            ;
        }
    }
    if (hasTexMapDetail(RefractionTextures))
    {
        if (hasMaterialMember(ReflectiveMaterialMember))
        {
            ost
            << endl << "    color = descMaterial.reflective * mix(color, material.refraction, vec3(descMaterial.reflectivity));"
            << endl << ""
            ;
        }
        else
        {
            ost
            << endl << "    color = mix(color, material.refraction, vec3(descMaterial.reflectivity));"
            << endl << ""
            ;
        }
    }

    if (hasMatBlockMember(TransparentBlockMember))
    {
        ost
        << endl << "    color *= descMaterial.transparent;"
        << endl << ""
        ;
    }

    ost
    << endl << "    return color;"
    << endl << "}"
    << endl << ""
    ;
}

TextureDesc* DescMaterial::searchNthTextureDesc(const TextureDescStore& textureDescs, UInt32 type, UInt32 N)
{
    TextureDesc* result = NULL;

    TextureDescStore::const_iterator iter = textureDescs.begin();
    TextureDescStore::const_iterator  end = textureDescs.end  ();

    UInt32 cnt = 0;

    for (; iter != end; ++iter)
    {
        TextureDesc* texDesc = *iter;

        if (texDesc->getTextureType() == type)
        {
            cnt++;
            if (N == cnt)
                return texDesc;
        }
    }

    return result;
}

TextureDesc* DescMaterial::searchNthTextureDesc(const TextureDescStore& textureDescs, std::vector<UInt32> types, UInt32 N)
{
    TextureDesc* result = NULL;

    TextureDescStore::const_iterator iter = textureDescs.begin();
    TextureDescStore::const_iterator  end = textureDescs.end  ();

    std::vector<UInt32> cnts(types.size(), 0);

    for (; iter != end; ++iter)
    {
        TextureDesc* texDesc = *iter;

        for (std::size_t i = 0; i < types.size(); ++i)
        {
            if (texDesc->getTextureType() == types[i])
            {
                cnts[i]++;

                if (N == cnts[i])
                    return texDesc;
            }
        }
    }

    return result;
}

OSG_END_NAMESPACE
