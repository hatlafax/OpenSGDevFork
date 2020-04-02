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
const Char8* DescMaterial::getFragEnvUniformBlockName() const
{
    return "FragEnvironmentBlock";
}

inline
const Char8* DescMaterial::getFragUniformBlockName() const
{
    return "FragDescMaterialBlock";
}

inline
const Char8* DescMaterial::getVertUniformBlockName() const
{
    return "VertDescMaterialBlock";
}

inline
Int32 DescMaterial::getTexUnitOffsetRT() const
{
    if (isFallbackFixedFunction() || isFallbackShader2())
    {
        return 0;
    }
    else
    {
        return getTexUnitOffset();
    }
}

inline
bool DescMaterial::DescriptionInfo::needTangentSpace() const
{
    bool result = false;

    if (hasTexMapDetail(NormalsTextures) 
     || hasTexMapDetail(HeightTextures)
     || hasTexMapDetail(DisplacementTextures))
    {
        result = true;
    }

    return result;
}

inline
bool DescMaterial::needTangentSpace() const
{
    return _info.needTangentSpace();
}

inline
bool DescMaterial::DescriptionInfo::hasTexMapDetail(TexMapDetails val) const
{
    return (texMapDetails & val) == val;
}

inline
bool DescMaterial::DescriptionInfo::hasMatBlockMember(MatBlockMemberDetails val) const
{
    return (blockMemDetails & val) == val;
}

inline
bool DescMaterial::DescriptionInfo::hasEnvBlockMember(EnvBlockMemberDetails val) const
{
    return (blockMemDetailsEnv & val) == val;
}

inline
bool DescMaterial::DescriptionInfo::hasMaterialMember(MaterialMemberDetails val) const
{
    return (matMemDetails & val) == val;
}

inline
bool DescMaterial::DescriptionInfo::anyTexMapDetail(TexMapDetails val) const
{
    return (texMapDetails & val) != 0;
}

inline
bool DescMaterial::DescriptionInfo::anyMatBlockMember(MatBlockMemberDetails val) const
{
    return (blockMemDetails & val) != 0;
}

inline
bool DescMaterial::DescriptionInfo::anyEnvBlockMember(EnvBlockMemberDetails val) const
{
    return (blockMemDetailsEnv & val) != 0;
}

inline
bool DescMaterial::DescriptionInfo::anyMaterialMember(MaterialMemberDetails val) const
{
    return (matMemDetails & val) != 0;
}

inline
bool DescMaterial::hasSpecularGlossinessTexture() const
{
    return _info.hasSpecularGlossinessTexture();
}

inline
bool DescMaterial::hasSpecularGlossinessWorkflow() const
{
    return _info.hasSpecularGlossinessWorkflow();
}

inline
bool DescMaterial::hasMetalnessRoughnessWorkflow() const
{
    return _info.hasMetalnessRoughnessWorkflow();
}

inline
bool DescMaterial::hasAmbientOcclusion() const
{
    return _info.hasAmbientOcclusion();
}

inline
bool DescMaterial::hasTexMapDetail(TexMapDetails val) const
{
    return _info.hasTexMapDetail(val);
}

inline
bool DescMaterial::hasMatBlockMember(MatBlockMemberDetails val) const
{
    return _info.hasMatBlockMember(val);
}

inline
bool DescMaterial::hasEnvBlockMember(EnvBlockMemberDetails val) const
{
    return _info.hasEnvBlockMember(val);
}

inline
bool DescMaterial::hasMaterialMember(MaterialMemberDetails val) const
{
    return _info.hasMaterialMember(val);
}

inline
bool DescMaterial::anyTexMapDetail(TexMapDetails val) const
{
    return _info.anyTexMapDetail(val);
}

inline
bool DescMaterial::anyMatBlockMember(MatBlockMemberDetails val) const
{
    return _info.anyMatBlockMember(val);
}

inline
bool DescMaterial::anyEnvBlockMember(EnvBlockMemberDetails val) const
{
    return _info.anyEnvBlockMember(val);
}

inline
bool DescMaterial::anyMaterialMember(MaterialMemberDetails val) const
{
    return _info.anyMaterialMember(val);
}

inline
UInt32 DescMaterial::getNumUVTextures() const
{
    if (_info.invalid)
        _info.initialize(getMaterialDesc(), getEnvironmentDesc(), getTexUnitOffsetRT(), getCapabilitiesDesc());

    return _info.numUVTextures;
}

inline
bool DescMaterial::getHasAmbientOcclusion  () const
{
    if (_info.invalid)
        _info.initialize(getMaterialDesc(), getEnvironmentDesc(), getTexUnitOffsetRT(), getCapabilitiesDesc());

    return hasAmbientOcclusion();
}

inline
bool DescMaterial::getHasPostProcessColor() const
{
    if (_info.invalid)
        _info.initialize(getMaterialDesc(), getEnvironmentDesc(), getTexUnitOffsetRT(), getCapabilitiesDesc());

    return hasMatBlockMember(TransparentBlockMember) || hasTexMapDetail(ReflectionTextures) || hasTexMapDetail(RefractionTextures);
}

inline
bool DescMaterial::getHasImageBasedLight() const
{
    if (_info.invalid)
        _info.initialize(getMaterialDesc(), getEnvironmentDesc(), getTexUnitOffsetRT(), getCapabilitiesDesc());

    return hasTexMapDetail(IrradianceTextures) || (hasTexMapDetail(PreFilterTextures) && hasTexMapDetail(BrdfLutTextures));
}

inline
bool DescMaterial::getNeedTangentSpace() const
{
    if (_info.invalid)
        _info.initialize(getMaterialDesc(), getEnvironmentDesc(), getTexUnitOffsetRT(), getCapabilitiesDesc());

    return needTangentSpace();
}

inline
UInt32 DescMaterial::getMaxNumClipPlanes() const
{
    // ToDo: Should come from the CapabilitiesDesc object
    const UInt32 maxSupportedClipPlanes = 8;
    return maxSupportedClipPlanes;
}

inline
bool DescMaterial::isFallbackFixedFunction() const
{
    return getCapabilitiesDesc()->isFallbackFixedFunction();
}

inline
bool DescMaterial::isFallbackShader2() const
{
    return getCapabilitiesDesc()->isFallbackShader2();
}

inline
bool DescMaterial::hasSwitchSupport() const
{
    return getCapabilitiesDesc()->hasSwitchSupport();
}

inline
bool DescMaterial::hasBitOpsSupport() const
{
    return getCapabilitiesDesc()->hasBitOpsSupport();
}

inline const DescMaterial::TextureDescStore& DescMaterial::getActiveTextureDescs() const
{
    if (_info.invalid)
        _info.initialize(getMaterialDesc(), getEnvironmentDesc(), getTexUnitOffsetRT(), getCapabilitiesDesc());

    return _info.textureDescs;
}

inline const DescMaterial::TextureDescStore& DescMaterial::getActiveTextureDescsEnv() const
{
    if (_info.invalid)
        _info.initialize(getMaterialDesc(), getEnvironmentDesc(), getTexUnitOffsetRT(), getCapabilitiesDesc());

    return _info.textureDescsEnv;
}

OSG_END_NAMESPACE
