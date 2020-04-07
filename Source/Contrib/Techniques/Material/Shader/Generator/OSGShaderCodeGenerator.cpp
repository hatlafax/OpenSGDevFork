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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGShaderCodeGenerator.h"

#include "OSGHDR2Stage.h"
#include "OSGClusterShadingStage.h"
#include "OSGMultiLightShadowStage.h"
#include "OSGSSAOStage.h"
#include "OSGIBLStage.h"
#include "OSGMultiLightChunk.h"
#include "OSGMultiLightGroup.h"
#include "OSGWindow.h"

#include "OSGBaseHash.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGShaderCodeGeneratorBase.cpp file.
// To modify it, please change the .fcd file (OSGShaderCodeGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

UInt32 ShaderCodeGenerator::_extUniformBufferObject         = Window::invalidExtensionID;
UInt32 ShaderCodeGenerator::_extVertexBufferObject          = Window::invalidExtensionID;
UInt32 ShaderCodeGenerator::_extProgramInterfaceQuery       = Window::invalidExtensionID;
UInt32 ShaderCodeGenerator::_extShaderStorageBufferObject   = Window::invalidExtensionID;
UInt32 ShaderCodeGenerator::_extFramebufferObject           = Window::invalidExtensionID;
UInt32 ShaderCodeGenerator::_extFramebufferBlit             = Window::invalidExtensionID;
UInt32 ShaderCodeGenerator::_extPackedDepthStencil          = Window::invalidExtensionID;
UInt32 ShaderCodeGenerator::_extShaderProgram               = Window::invalidExtensionID;
UInt32 ShaderCodeGenerator::_extTextureCubeMapArray         = Window::invalidExtensionID;
UInt32 ShaderCodeGenerator::_extTextureArray                = Window::invalidExtensionID;
UInt32 ShaderCodeGenerator::_extGeometryShader4             = Window::invalidExtensionID;
UInt32 ShaderCodeGenerator::_extComputeShader               = Window::invalidExtensionID;
UInt32 ShaderCodeGenerator::_extShaderImageLoadStore        = Window::invalidExtensionID;
UInt32 ShaderCodeGenerator::_extShadingLanguage420Pack      = Window::invalidExtensionID;
UInt32 ShaderCodeGenerator::_extGPUShader4                  = Window::invalidExtensionID;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderCodeGenerator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _extVertexBufferObject        = Window::registerExtension("GL_ARB_vertex_buffer_object");
        _extUniformBufferObject       = Window::registerExtension("GL_ARB_uniform_buffer_object");
        _extProgramInterfaceQuery     = Window::registerExtension("GL_ARB_program_interface_query");
        _extShaderStorageBufferObject = Window::registerExtension("GL_ARB_shader_storage_buffer_object");
        _extFramebufferObject         = Window::registerExtension("GL_ARB_framebuffer_object");
        _extFramebufferBlit           = Window::registerExtension("GL_EXT_framebuffer_blit");
        _extPackedDepthStencil        = Window::registerExtension("GL_EXT_packed_depth_stencil");
        _extShaderProgram             = Window::registerExtension("GL_ARB_shading_language_100");
        _extTextureCubeMapArray       = Window::registerExtension("GL_ARB_texture_cube_map_array");
        _extTextureArray              = Window::registerExtension("GL_EXT_texture_array");
        _extGeometryShader4           = Window::registerExtension("GL_ARB_geometry_shader4");
        _extComputeShader             = Window::registerExtension("GL_ARB_compute_shader");
        _extShaderImageLoadStore      = Window::registerExtension("GL_ARB_shader_image_load_store");
        _extShadingLanguage420Pack    = Window::registerExtension("GL_ARB_shading_language_420pack");
        _extGPUShader4                = Window::registerExtension("GL_EXT_gpu_shader4");
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShaderCodeGenerator::ShaderCodeGenerator(void)
: Inherited                  (     )
, _extensions                (     )
, _glslVersion               (0    )
{
}

ShaderCodeGenerator::ShaderCodeGenerator(const ShaderCodeGenerator &source)
: Inherited                  (source)
, _extensions                (      )
, _glslVersion               (0     )
{
}

ShaderCodeGenerator::~ShaderCodeGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ShaderCodeGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ShaderCodeGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ShaderCodeGenerator NI" << std::endl;
}

/*--------------------------- Create --------------------------------------*/

void ShaderCodeGenerator::onCreate(const ShaderCodeGenerator *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
        return;

    CapabilitiesDescUnrecPtr capabilitiesDesc = CapabilitiesDesc::createLocal();
    setCapabilitiesDesc(capabilitiesDesc);
}

void ShaderCodeGenerator::onCreateAspect(
    const ShaderCodeGenerator *createAspect,
    const ShaderCodeGenerator *source      )
{
    Inherited::onCreateAspect(createAspect, source);
}

void ShaderCodeGenerator::onDestroy(UInt32 uiContainerId)
{
    setCapabilitiesDesc(NULL);

    Inherited::onDestroy(uiContainerId);
}

/*-------------------------------- Helper ---------------------------------*/

MultiLightChunk* ShaderCodeGenerator::findMultiLightChunk() const
{
    MultiLightChunk* pChunk   = NULL;
    MultiLightGroup* pMLGroup = getMultiLightGroup();
    if (pMLGroup)
    {
        pChunk = pMLGroup->getMultiLightChunk();
    }
    else
    {
        ClusterShadingStage* pClusterShadingStage = getClusterShadingStage();
    
        if (pClusterShadingStage)
        {
            pChunk = pClusterShadingStage->getMultiLightChunk();

            if (!pChunk)
            {
                MultiLightShadowStage* pMLShadowStage = getMultiLightShadowStage();

                if (pMLShadowStage)
                {
                    pChunk = pMLShadowStage->getMultiLightChunk();
                }
            }
        }
    }

    return pChunk;
}

void ShaderCodeGenerator::updateEnvironment(Window* win)
{
    _extensions.clear();

    //
    // Remark: OpenGL version: major.minor -> major << 8 + minor e.g. 4.5  -> 1024 +  5 = 1029 = 0x400 + 0x05 = 0x405
    //                                                                3.3  ->  768 +  3 =  771 = 0x300 + 0x03 = 0x303
    //
    //         GLSL version:   major.minor -> major << 8 + minor e.g. 4.50 -> 1024 + 50 = 1074 = 0x400 + 0x32 = 0x432
    //                                                                3.30 ->  768 + 30 =  798 = 0x300 + 0x1e = 0x31e
    //
    _glslVersion = ((3 << 8) + 30);

    UInt32 platform_capabilities  = getPlatformCapabilities();

    if (platform_capabilities == 0)
    {
        initFixedFunctionPipeline   (win);
        initShaderMaterial2         (win);
        initShaderMaterial3         (win);
        initShaderMaterial4         (win);
        initHDR2Stage               (win);
        initSSAOStage               (win);
        initIBLStage                (win);
        initMultiLight              (win);
        initMultiLightShadowStage   (win);
        initClusterShadingStage     (win);
        initClipPlanes              (win);
        initBitOperations           (win);
        initSwitchStatement         (win);
    }

    setRuntimeCapabilities(getPlatformCapabilities());

    validateFixedFunctionPipeline   ();
    validateShaderMaterial2         ();
    validateShaderMaterial3         ();
    validateShaderMaterial4         ();
    validateHDR2Stage               ();
    validateSSAOStage               ();
    validateIBLStage                ();
    validateMultiLight              ();
    validateMultiLightShadowStage   ();
    validateClusterShadingStage     ();
    validateClipPlanes              ();
    validateBitOperations           ();
    validateSwitchStatement         ();
}

ShaderCodeGenerator::HashKeyType ShaderCodeGenerator::getEnvironmentHash(Window* win)
{
    updateEnvironment(win);

    UInt32 runtime_capabilities = (getRuntimeCapabilities() & getRequestedCapabilities());

    Hash64 hasher;
    hasher.update(reinterpret_cast<const void*>(&runtime_capabilities), sizeof(UInt32));

    return hasher.finish();
}

void ShaderCodeGenerator::initFixedFunctionPipeline(Window* pWin)
{
    if (pWin)
    {
        bool hasGL1 = pWin->hasGLVersionNum(1,0);

        if (hasGL1)
        {
            setPlatformCapabilities(getPlatformCapabilities() | CapabilitiesDesc::FIXED_FUNCTION_PIPELINE);
        }    
    }
}

void ShaderCodeGenerator::initShaderMaterial2(Window* pWin)
{
    if (pWin)
    {
        bool hasGL   = pWin->hasGLVersionNum(2,1);
        bool hasGLSL = pWin->hasGLSLVersionNum(1,20);

        if (hasGL && hasGLSL)
        {
            bool hasSHP = pWin->hasExtOrVersion(_extShaderProgram, 0x0200);

            if (hasSHP)
            {
                setPlatformCapabilities(getPlatformCapabilities() | CapabilitiesDesc::SHADER_MATERIAL_2);
            }
        }
    }
}

void ShaderCodeGenerator::initShaderMaterial3(Window* pWin)
{
    if (pWin)
    {
        bool hasGL   = pWin->hasGLVersionNum(3,3);
        bool hasGLSL = pWin->hasGLSLVersionNum(3,30);

        if (hasGL && hasGLSL)
        {
            bool hasSHP   = pWin->hasExtOrVersion(_extShaderProgram,          0x0200);
            bool hasSLP42 = pWin->hasExtOrVersion(_extShadingLanguage420Pack, 0x0402);
            bool hasUBO   = pWin->hasExtOrVersion(_extUniformBufferObject,    0x0301);

            if (hasSHP && hasSLP42 && hasUBO)
            {
                setPlatformCapabilities(getPlatformCapabilities() | CapabilitiesDesc::SHADER_MATERIAL_3);
            }
        }
    }
}

void ShaderCodeGenerator::initShaderMaterial4(Window* pWin)
{
    if (pWin)
    {
        bool hasGL   = pWin->hasGLVersionNum(4,4);
        bool hasGLSL = pWin->hasGLSLVersionNum(4,40);

        if (hasGL && hasGLSL)
        {
            bool hasSHP   = pWin->hasExtOrVersion(_extShaderProgram,          0x0200);
            bool hasSLP42 = pWin->hasExtOrVersion(_extShadingLanguage420Pack, 0x0402);
            bool hasUBO   = pWin->hasExtOrVersion(_extUniformBufferObject,    0x0301);

            if (hasSHP && hasSLP42 && hasUBO)
            {
                setPlatformCapabilities(getPlatformCapabilities() | CapabilitiesDesc::SHADER_MATERIAL_4);
            }
        }
    }
}

void ShaderCodeGenerator::initHDR2Stage(Window* pWin)
{
    if (pWin)
    {
        bool hasGL   = pWin->hasGLVersionNum(3,3);
        bool hasGLSL = pWin->hasGLSLVersionNum(4,30);

        if (hasGL && hasGLSL)
        {
            bool hasSHP  = pWin->hasExtOrVersion(_extShaderProgram,        0x0200);
            bool hasSILS = pWin->hasExtOrVersion(_extShaderImageLoadStore, 0x0402);
            bool hasFBO  = pWin->hasExtOrVersion(_extFramebufferObject,    0x0300);
            bool hasFBB  = pWin->hasExtOrVersion(_extFramebufferBlit,      0x0300);
            bool hasVBO  = pWin->hasExtOrVersion(_extVertexBufferObject,   0x0105);
            bool hasUBO  = pWin->hasExtOrVersion(_extUniformBufferObject,  0x0301);

            if (hasSHP && hasSILS && hasFBO && hasFBB && hasVBO && hasUBO)
            {
                setPlatformCapabilities(getPlatformCapabilities() | CapabilitiesDesc::HDR);
            }
        }
    }
}

void ShaderCodeGenerator::initSSAOStage(Window* pWin)
{
    if (pWin)
    {
        bool hasGL   = pWin->hasGLVersionNum(3,3);
        bool hasGLSL = pWin->hasGLSLVersionNum(3,30);

        if (hasGL && hasGLSL)
        {
            bool hasVBO  = pWin->hasExtOrVersion(_extVertexBufferObject,  0x0105);
            bool hasUBO  = pWin->hasExtOrVersion(_extUniformBufferObject, 0x0301);
            bool hasFBO  = pWin->hasExtOrVersion(_extFramebufferObject,   0x0300);
            bool hasFBB  = pWin->hasExtOrVersion(_extFramebufferBlit,     0x0300);
            bool hasPDS  = pWin->hasExtOrVersion(_extPackedDepthStencil,  0x0101);
            bool hasSHP  = pWin->hasExtOrVersion(_extShaderProgram,       0x0200);

            if (hasVBO && hasUBO && hasFBO && hasFBB && hasPDS && hasSHP)
            {
                setPlatformCapabilities(getPlatformCapabilities() | CapabilitiesDesc::SSAO);
            }
        }
    }
}

void ShaderCodeGenerator::initIBLStage(Window* pWin)
{
    if (pWin)
    {
        bool hasGL   = pWin->hasGLVersionNum(3,3);
        bool hasGLSL = pWin->hasGLSLVersionNum(3,30);

        if (hasGL && hasGLSL)
        {
            bool hasSHP  = pWin->hasExtOrVersion(_extShaderProgram,       0x0200);

            if (hasSHP)
            {
                setPlatformCapabilities(getPlatformCapabilities() | CapabilitiesDesc::IBL);
            }
        }
    }
}

void ShaderCodeGenerator::initMultiLight(Window* pWin)
{
    if (pWin)
    {
        bool hasGL   = pWin->hasGLVersionNum(3,3);
        bool hasGLSL = pWin->hasGLSLVersionNum(3,30);

        if (hasGL && hasGLSL)
        {
            bool hasVBO  = pWin->hasExtOrVersion(_extVertexBufferObject,        0x0105);
            bool hasUBO  = pWin->hasExtOrVersion(_extUniformBufferObject,       0x0301);
            bool hasPIQ  = pWin->hasExtOrVersion(_extProgramInterfaceQuery,     0x0402);
            bool hasSSBO = pWin->hasExtOrVersion(_extShaderStorageBufferObject, 0x0403);

            if (hasVBO && hasUBO && hasPIQ && hasSSBO)
            {
                setPlatformCapabilities(getPlatformCapabilities() | CapabilitiesDesc::MULTILIGHT);
            }
        }
    }
}

void ShaderCodeGenerator::initMultiLightShadowStage(Window* pWin)
{
    if (pWin)
    {
        bool hasGL   = pWin->hasGLVersionNum(3,3);
        bool hasGLSL = pWin->hasGLSLVersionNum(3,30);

        if (hasGL && hasGLSL)
        {
            // MULTILIGHT
            bool hasVBO  = pWin->hasExtOrVersion(_extVertexBufferObject,        0x0105);
            bool hasUBO  = pWin->hasExtOrVersion(_extUniformBufferObject,       0x0301);
            bool hasPIQ  = pWin->hasExtOrVersion(_extProgramInterfaceQuery,     0x0402);
            bool hasSSBO = pWin->hasExtOrVersion(_extShaderStorageBufferObject, 0x0403);
            // MULTILIGHT_SHADOW
            bool hasSHP  = pWin->hasExtOrVersion(_extShaderProgram,             0x0200);
            bool hasFBO  = pWin->hasExtOrVersion(_extFramebufferObject,         0x0300);
            bool hasTCMA = pWin->hasExtOrVersion(_extTextureCubeMapArray,       0x0400);
            bool hasTA   = pWin->hasExtOrVersion(_extTextureArray,              0x0300);
            bool hasGS4  = pWin->hasExtOrVersion(_extGeometryShader4,           0x0302);

            if (hasVBO && hasUBO && hasPIQ && hasSSBO && hasSHP && hasFBO && hasTCMA && hasTA && hasGS4)
            {
                setPlatformCapabilities(getPlatformCapabilities() | CapabilitiesDesc::MULTILIGHT_SHADOW);
            }
        }
    }
}

void ShaderCodeGenerator::initClusterShadingStage(Window* pWin)
{
    if (pWin)
    {
        bool hasGL   = pWin->hasGLVersionNum(4,3);
        bool hasGLSL = pWin->hasGLSLVersionNum(4,30);

        if (hasGL && hasGLSL)
        {
            // MULTILIGHT
            bool hasVBO  = pWin->hasExtOrVersion(_extVertexBufferObject,        0x0105);
            bool hasUBO  = pWin->hasExtOrVersion(_extUniformBufferObject,       0x0301);
            bool hasPIQ  = pWin->hasExtOrVersion(_extProgramInterfaceQuery,     0x0402);
            bool hasSSBO = pWin->hasExtOrVersion(_extShaderStorageBufferObject, 0x0403);
            // CLUSTER_SHADING
            bool hasCS   = pWin->hasExtOrVersion(_extComputeShader,             0x0403);
            bool hasSILS = pWin->hasExtOrVersion(_extShaderImageLoadStore,      0x0402);
            bool hasFBO  = pWin->hasExtOrVersion(_extFramebufferObject,         0x0300);

            if (hasVBO && hasUBO && hasPIQ && hasSSBO && hasCS && hasSILS && hasFBO)
            {
                setPlatformCapabilities(getPlatformCapabilities() | CapabilitiesDesc::CLUSTER_SHADING);
            }
        }
    }
}

void ShaderCodeGenerator::initClipPlanes(Window* pWin)
{
    // nothing to do
}

void ShaderCodeGenerator::initBitOperations(Window* pWin)
{
    if (pWin)
    {
        bool hasGL   = pWin->hasGLVersionNum(2,1);
        bool hasGLSL = pWin->hasGLSLVersionNum(1,20);

        if (hasGL && hasGLSL)
        {
            bool hasSH4 = (pWin->hasExtOrVersion(_extGPUShader4, 0x303) || pWin->hasGLSLVersionNum(1,30));

            if (hasSH4)
            {
                setPlatformCapabilities(getPlatformCapabilities() | CapabilitiesDesc::BIT_OPERATIONS);
            }
        }
    }
}

void ShaderCodeGenerator::initSwitchStatement(Window* pWin)
{
    if (pWin)
    {
        bool hasGL   = pWin->hasGLVersionNum(2,1);
        bool hasGLSL = pWin->hasGLSLVersionNum(1,30);

        if (hasGL && hasGLSL)
        {
            setPlatformCapabilities(getPlatformCapabilities() | CapabilitiesDesc::SWITCH_STATEMENT);
        }
    }
}

void ShaderCodeGenerator::validateFixedFunctionPipeline()
{
}

void ShaderCodeGenerator::validateShaderMaterial2()
{
}

void ShaderCodeGenerator::validateShaderMaterial3()
{
    if (bUseCapabilities(CapabilitiesDesc::SHADER_MATERIAL_3))
    {
        UInt32 requiredGLSLVersion = ((3 << 8) + 30);

        if (_glslVersion < requiredGLSLVersion) _glslVersion = requiredGLSLVersion;

        _extensions.insert("GL_ARB_shading_language_100");
        _extensions.insert("GL_ARB_shading_language_420pack");
        _extensions.insert("GL_ARB_uniform_buffer_object");
    }
}

void ShaderCodeGenerator::validateShaderMaterial4()
{
    if (bUseCapabilities(CapabilitiesDesc::SHADER_MATERIAL_4))
    {
        UInt32 requiredGLSLVersion = ((4 << 8) + 40);

        if (_glslVersion < requiredGLSLVersion) _glslVersion = requiredGLSLVersion;
    }
}

void ShaderCodeGenerator::validateHDR2Stage()
{

    if (bUseCapabilities(CapabilitiesDesc::HDR))
    {
        if (
                getHDR2Stage() == NULL
            || !getHDR2Stage()->getActivate() 
            || isFallbackShader2())
        {
            UInt32 runtime_capabilities = getRuntimeCapabilities();
            runtime_capabilities &= ~CapabilitiesDesc::HDR;
            setRuntimeCapabilities(runtime_capabilities);
        }
    }
}

void ShaderCodeGenerator::validateSSAOStage()
{
    if (bUseCapabilities(CapabilitiesDesc::SSAO))
    {
        if (
                getSSAOStage() == NULL
            || !getSSAOStage()->getActivate()
            || isFallbackShader2())
        {
            UInt32 runtime_capabilities = getRuntimeCapabilities();
            runtime_capabilities &= ~CapabilitiesDesc::SSAO;
            setRuntimeCapabilities(runtime_capabilities);
        }
    }

    if (bUseCapabilities(CapabilitiesDesc::SSAO))
    {
        UInt32 requiredGLSLVersion = ((3 << 8) + 30);

        if (_glslVersion < requiredGLSLVersion) _glslVersion = requiredGLSLVersion;

        _extensions.insert("GL_ARB_vertex_buffer_object");
        _extensions.insert("GL_ARB_uniform_buffer_object");
        _extensions.insert("GL_ARB_framebuffer_object");
        _extensions.insert("GL_EXT_framebuffer_blit");
        _extensions.insert("GL_EXT_packed_depth_stencil");
        _extensions.insert("GL_ARB_shading_language_100");
    }
}

void ShaderCodeGenerator::validateIBLStage()
{
    if (bUseCapabilities(CapabilitiesDesc::IBL))
    {
        if (
                getIBLStage() == NULL
            || !getIBLStage()->getActivate()
            || isFallbackShader2())
        {
            UInt32 runtime_capabilities = getRuntimeCapabilities();
            runtime_capabilities &= ~CapabilitiesDesc::IBL;
            setRuntimeCapabilities(runtime_capabilities);
        }
    }

    if (bUseCapabilities(CapabilitiesDesc::IBL))
    {
        UInt32 requiredGLSLVersion = ((3 << 8) + 30);

        if (_glslVersion < requiredGLSLVersion) _glslVersion = requiredGLSLVersion;
    }
}

void ShaderCodeGenerator::validateMultiLight()
{
    if (bUseCapabilities(CapabilitiesDesc::MULTILIGHT))
    {
        MultiLightChunk* pChunk = findMultiLightChunk();

        if (
                (getMultiLightGroup() == NULL && pChunk == NULL)
             || (getMultiLightGroup() != NULL && !getMultiLightGroup()->getActivate())
             || isFallbackShader2()
           )
        {
            UInt32 runtime_capabilities = getRuntimeCapabilities();
            runtime_capabilities &= ~CapabilitiesDesc::MULTILIGHT;
            setRuntimeCapabilities(runtime_capabilities);
        }
    }

    if (bUseCapabilities(CapabilitiesDesc::MULTILIGHT))
    {
        UInt32 requiredGLSLVersion = ((3 << 8) + 30);

        if (_glslVersion < requiredGLSLVersion) _glslVersion = requiredGLSLVersion;

        _extensions.insert("GL_ARB_vertex_buffer_object");
        _extensions.insert("GL_ARB_uniform_buffer_object");
        _extensions.insert("GL_ARB_program_interface_query");
        _extensions.insert("GL_ARB_shader_storage_buffer_object");
    }
}

void ShaderCodeGenerator::validateMultiLightShadowStage()
{
    if (bUseCapabilities(CapabilitiesDesc::MULTILIGHT_SHADOW))
    {
        if (
                !bUseCapabilities(CapabilitiesDesc::MULTILIGHT)
             ||  getMultiLightShadowStage() == NULL 
             || !getMultiLightShadowStage()->getActivate() 
             || isFallbackShader2())
        {
            UInt32 runtime_capabilities = getRuntimeCapabilities();
            runtime_capabilities &= ~CapabilitiesDesc::MULTILIGHT_SHADOW;
            setRuntimeCapabilities(runtime_capabilities);
        }
    }

    if (bUseCapabilities(CapabilitiesDesc::MULTILIGHT_SHADOW))
    {
        UInt32 requiredGLSLVersion = ((3 << 8) + 30);

        if (_glslVersion < requiredGLSLVersion) _glslVersion = requiredGLSLVersion;

        _extensions.insert("GL_ARB_shading_language_100");
        _extensions.insert("GL_ARB_framebuffer_object");
        _extensions.insert("GL_ARB_texture_cube_map_array");
        _extensions.insert("GL_EXT_texture_array");
        _extensions.insert("GL_ARB_geometry_shader4");
    }
}

void ShaderCodeGenerator::validateClusterShadingStage()
{
    if (bUseCapabilities(CapabilitiesDesc::CLUSTER_SHADING))
    {
        if (
                !bUseCapabilities(CapabilitiesDesc::MULTILIGHT)
             ||  getClusterShadingStage() == NULL 
             || !getClusterShadingStage()->getActivate()
             || isFallbackShader2())
        {
            UInt32 runtime_capabilities = getRuntimeCapabilities();
            runtime_capabilities &= ~CapabilitiesDesc::CLUSTER_SHADING;
            setRuntimeCapabilities(runtime_capabilities);
        }
    }

    if (bUseCapabilities(CapabilitiesDesc::CLUSTER_SHADING))
    {
        UInt32 requiredGLSLVersion = ((4 << 8) + 30);

        if (_glslVersion < requiredGLSLVersion) _glslVersion = requiredGLSLVersion;

        _extensions.insert("GL_ARB_compute_shader");
        _extensions.insert("GL_ARB_shader_image_load_store");
        _extensions.insert("GL_ARB_framebuffer_object");
    }
}

void ShaderCodeGenerator::validateClipPlanes()
{
    UInt32 runtime_capabilities = getRuntimeCapabilities();

    if (getHasClipPlanes())
    {
        runtime_capabilities |= CapabilitiesDesc::CLIP_PLANES;
    }
    else
    {
        runtime_capabilities &= ~CapabilitiesDesc::CLIP_PLANES;
    }

    setRuntimeCapabilities(runtime_capabilities);
}

void ShaderCodeGenerator::validateBitOperations()
{
    if (bUseCapabilities(CapabilitiesDesc::BIT_OPERATIONS))
    {
        if (!isFallbackShader2())
        {
            UInt32 runtime_capabilities = getRuntimeCapabilities();
            runtime_capabilities &= ~CapabilitiesDesc::BIT_OPERATIONS;
            setRuntimeCapabilities(runtime_capabilities);
        }
    }

    if (bUseCapabilities(CapabilitiesDesc::BIT_OPERATIONS) && !hasGLSL130Support())
    {
        _extensions.insert("GL_EXT_gpu_shader4");
    }
}

void ShaderCodeGenerator::validateSwitchStatement()
{
}

OSG_END_NAMESPACE
