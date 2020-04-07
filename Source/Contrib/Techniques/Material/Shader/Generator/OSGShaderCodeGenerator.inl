/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
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

OSG_BEGIN_NAMESPACE

inline
void ShaderCodeGenerator::setPlatformCapabilities(const UInt32 value)
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    getCapabilitiesDesc()->setPlatformCapabilities(value);
}

inline
void ShaderCodeGenerator::setRequestedCapabilities(const UInt32 value)
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    getCapabilitiesDesc()->setRequestedCapabilities(value);
}

inline
void ShaderCodeGenerator::setRuntimeCapabilities(const UInt32 value)
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    getCapabilitiesDesc()->setRuntimeCapabilities(value);
}

inline
UInt32 ShaderCodeGenerator::getPlatformCapabilities() const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->getPlatformCapabilities();
}

inline
UInt32 ShaderCodeGenerator::getRequestedCapabilities() const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->getRequestedCapabilities();
}

inline
UInt32 ShaderCodeGenerator::getRuntimeCapabilities() const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->getRuntimeCapabilities();
}

inline
bool ShaderCodeGenerator::bUseCapabilities(UInt32 capabilities) const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->bUseCapabilities(capabilities);
}

inline
bool ShaderCodeGenerator::bUsePlatformCapabilities(UInt32 capabilities) const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->bUsePlatformCapabilities(capabilities);
}

inline
bool ShaderCodeGenerator::bUseRequestedCapabilities(UInt32 capabilities) const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->bUseRequestedCapabilities(capabilities);
}

inline
bool ShaderCodeGenerator::isValidHDR2Stage() const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->hasHDRSupport();
}

inline
bool ShaderCodeGenerator::isValidClusterShadingStage() const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->hasClusterShadingSupport();
}

inline
bool ShaderCodeGenerator::isValidMultiLightShadowStage() const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->hasMultiLightShadowSupport();
}

inline
bool ShaderCodeGenerator::isValidSSAOStage() const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->hasSSAOSupport();
}

inline
bool ShaderCodeGenerator::isValidIBLStage() const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->hasIBLSupport();
}

inline
bool ShaderCodeGenerator::isValidMultiLight() const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->hasMultiLightSupport();
}

inline
bool ShaderCodeGenerator::isValidModernShaderSupport() const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->hasModernShaderSupport();
}

inline
bool ShaderCodeGenerator::isValidFull440ShaderSupport() const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->hasFull440ShaderSupport();
}

inline
bool ShaderCodeGenerator::isValidClipPlanes() const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->hasdClipPlanesSupport();
}

inline
bool ShaderCodeGenerator::isValidBitOperations() const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->hasBitOpsSupport();
}

inline
bool ShaderCodeGenerator::isValidSwitchStatement() const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->hasSwitchSupport();
}

inline
bool ShaderCodeGenerator::isFallbackFixedFunction() const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->isFallbackFixedFunction();
}

inline
bool ShaderCodeGenerator::isFallbackShader2() const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->isFallbackShader2();
}

inline
bool ShaderCodeGenerator::isFallbackShader3() const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->isFallbackShader3();
}

inline
bool ShaderCodeGenerator::isFallbackShader4() const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->isFallbackShader4();
}

inline
const ShaderCodeGenerator::ExtensionStore& ShaderCodeGenerator::getExtensions() const
{
    return _extensions;
}

inline
UInt32 ShaderCodeGenerator::getGLSLVersion() const
{
    return _glslVersion;
}

inline
bool ShaderCodeGenerator::hasSwitchSupport() const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->hasSwitchSupport();
}

inline
bool ShaderCodeGenerator::hasBitOpsSupport() const
{
    OSG_ASSERT(getCapabilitiesDesc() != NULL);

    return getCapabilitiesDesc()->hasBitOpsSupport();
}

inline
bool ShaderCodeGenerator::hasGLSL130Support() const
{
    return _glslVersion >= ((1 << 8) + 30);
}

OSG_END_NAMESPACE
