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
bool CapabilitiesDesc::bUseCapabilities(UInt32 capabilities) const
{
    return (getRuntimeCapabilities  () & capabilities) == capabilities 
        && (getRequestedCapabilities() & capabilities) == capabilities
        ;
}

inline
bool CapabilitiesDesc::bUsePlatformCapabilities(UInt32 capabilities) const
{
    return (getPlatformCapabilities () & capabilities) == capabilities;
}

inline
bool CapabilitiesDesc::bUseRequestedCapabilities(UInt32 capabilities) const
{
    return (getRequestedCapabilities () & capabilities) == capabilities;
}

inline
bool CapabilitiesDesc::hasHDRSupport() const
{
    return bUseCapabilities(CapabilitiesDesc::HDR);
}

inline
bool CapabilitiesDesc::hasClusterShadingSupport() const
{
    return bUseCapabilities(CapabilitiesDesc::CLUSTER_SHADING);
}

inline
bool CapabilitiesDesc::hasMultiLightShadowSupport() const
{
    return bUseCapabilities(CapabilitiesDesc::MULTILIGHT_SHADOW);
}

inline
bool CapabilitiesDesc::hasSSAOSupport() const
{
    return bUseCapabilities(CapabilitiesDesc::SSAO);
}

inline
bool CapabilitiesDesc::hasIBLSupport() const
{
    return bUseCapabilities(CapabilitiesDesc::IBL);
}

inline
bool CapabilitiesDesc::hasMultiLightSupport() const
{
    return bUseCapabilities(CapabilitiesDesc::MULTILIGHT);
}

inline
bool CapabilitiesDesc::hasModernShaderSupport() const
{
    return bUseCapabilities(CapabilitiesDesc::SHADER_MATERIAL_3);
}

inline
bool CapabilitiesDesc::hasFull440ShaderSupport() const
{
    return bUseCapabilities(CapabilitiesDesc::SHADER_MATERIAL_4);
}

inline
bool CapabilitiesDesc::hasdClipPlanesSupport() const
{
    return bUseCapabilities(CapabilitiesDesc::CLIP_PLANES);
}

inline
bool CapabilitiesDesc::isFallbackFixedFunction() const
{
    return bUseCapabilities(CapabilitiesDesc::FIXED_FUNCTION_PIPELINE)
       && !bUseCapabilities(CapabilitiesDesc::SHADER_MATERIAL_2)
       && !bUseCapabilities(CapabilitiesDesc::SHADER_MATERIAL_3)
       && !bUseCapabilities(CapabilitiesDesc::SHADER_MATERIAL_4);
}

inline
bool CapabilitiesDesc::isFallbackShader2() const
{
    return bUseCapabilities(CapabilitiesDesc::FIXED_FUNCTION_PIPELINE)
       &&  bUseCapabilities(CapabilitiesDesc::SHADER_MATERIAL_2)
       && !bUseCapabilities(CapabilitiesDesc::SHADER_MATERIAL_3)
       && !bUseCapabilities(CapabilitiesDesc::SHADER_MATERIAL_4);
}

inline
bool CapabilitiesDesc::isFallbackShader3() const
{
    return bUseCapabilities(CapabilitiesDesc::FIXED_FUNCTION_PIPELINE)
       &&  bUseCapabilities(CapabilitiesDesc::SHADER_MATERIAL_2)
       &&  bUseCapabilities(CapabilitiesDesc::SHADER_MATERIAL_3)
       && !bUseCapabilities(CapabilitiesDesc::SHADER_MATERIAL_4);
}

inline
bool CapabilitiesDesc::isFallbackShader4() const
{
    return bUseCapabilities(CapabilitiesDesc::FIXED_FUNCTION_PIPELINE)
       &&  bUseCapabilities(CapabilitiesDesc::SHADER_MATERIAL_2)
       &&  bUseCapabilities(CapabilitiesDesc::SHADER_MATERIAL_3)
       &&  bUseCapabilities(CapabilitiesDesc::SHADER_MATERIAL_4);
}

inline
bool CapabilitiesDesc::hasSwitchSupport() const
{
    return bUseCapabilities(CapabilitiesDesc::SWITCH_STATEMENT);
}

inline
bool CapabilitiesDesc::hasBitOpsSupport() const
{
    return bUseCapabilities(CapabilitiesDesc::BIT_OPERATIONS);
}

OSG_END_NAMESPACE
