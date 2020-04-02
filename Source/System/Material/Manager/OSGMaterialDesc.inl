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

inline bool MaterialDesc::getSRGBColorMode() const
{
    return getModeFlags() & SRGB_COLOR_MODE ? true : false;
}

inline bool MaterialDesc::getShadowOnlyMode() const
{
    return getModeFlags() & SHADOW_ONLY_MODE ? true : false;
}

inline bool MaterialDesc::getPbrSpecularMode() const
{
    return getModeFlags() & PBR_SPECULAR_MODE ? true : false;
}

inline bool MaterialDesc::getPbrClearCoatMode() const
{
    return getModeFlags() & PBR_CLEAR_COAT_MODE ? true : false;
}

inline bool MaterialDesc::getPbrSheenColorMode() const
{
    return getModeFlags() & PBR_SHEEN_COLOR_MODE ? true : false;
}

inline bool MaterialDesc::getPbrAnisotropyMode() const
{
    return getModeFlags() & PBR_ANISOTROPY_MODE ? true : false;
}

inline bool MaterialDesc::getUnlitMode() const
{
    return getModeFlags() & UNLIT_MODE ? true : false;
}

inline bool MaterialDesc::getHasNormalsMode() const
{
    return getModeFlags() & HAS_NORMALS_MODE ? true : false;
}

inline bool MaterialDesc::getHasTangentsAndBitangentsMode() const
{
    return getModeFlags() & HAS_TANGENTS_AND_BITANGENTS_MODE ? true : false;
}

inline bool MaterialDesc::getFlatShadingMode() const
{
    return getModeFlags() & FLAT_SHADING_MODE ? true : false;
}

inline bool MaterialDesc::getOffsetPointMode() const
{
    return getModeFlags() & OFFSET_POINT_MODE ? true : false;
}

inline bool MaterialDesc::getOffsetLineMode() const
{
    return getModeFlags() & OFFSET_LINE_MODE ? true : false;
}

inline bool MaterialDesc::getOffsetFillMode() const
{
    return getModeFlags() & OFFSET_FILL_MODE ? true : false;
}

inline bool MaterialDesc::getXORMode() const
{
    return getModeFlags() & XOR_MODE ? true : false;
}

inline bool MaterialDesc::getNoDepthTestMode() const
{
    return getModeFlags() & NO_DEPTH_TEST_MODE ? true : false;
}

inline void MaterialDesc::setSRGBColorMode(bool flag)
{
    if (flag)
        setModeFlags(getModeFlags() |  SRGB_COLOR_MODE);
    else
        setModeFlags(getModeFlags() & ~SRGB_COLOR_MODE);
}

inline void MaterialDesc::setShadowOnlyMode(bool flag)
{
    if (flag)
        setModeFlags(getModeFlags() |  SHADOW_ONLY_MODE);
    else
        setModeFlags(getModeFlags() & ~SHADOW_ONLY_MODE);
}

inline void MaterialDesc::setPbrSpecularMode(bool flag)
{
    if (flag)
        setModeFlags(getModeFlags() |  PBR_SPECULAR_MODE);
    else
        setModeFlags(getModeFlags() & ~PBR_SPECULAR_MODE);
}

inline void MaterialDesc::setPbrClearCoatMode(bool flag)
{
    if (flag)
        setModeFlags(getModeFlags() |  PBR_CLEAR_COAT_MODE);
    else
        setModeFlags(getModeFlags() & ~PBR_CLEAR_COAT_MODE);
}

inline void MaterialDesc::setPbrSheenColorMode(bool flag)
{
    if (flag)
        setModeFlags(getModeFlags() |  PBR_SHEEN_COLOR_MODE);
    else
        setModeFlags(getModeFlags() & ~PBR_SHEEN_COLOR_MODE);
}

inline void MaterialDesc::setPbrAnisotropyMode(bool flag)
{
    if (flag)
        setModeFlags(getModeFlags() |  PBR_ANISOTROPY_MODE);
    else
        setModeFlags(getModeFlags() & ~PBR_ANISOTROPY_MODE);
}

inline void MaterialDesc::setUnlitMode(bool flag)
{
    if (flag)
        setModeFlags(getModeFlags() |  UNLIT_MODE);
    else
        setModeFlags(getModeFlags() & ~UNLIT_MODE);
}

inline void MaterialDesc::setHasNormalsMode(bool flag)
{
    if (flag)
        setModeFlags(getModeFlags() |  HAS_NORMALS_MODE);
    else
        setModeFlags(getModeFlags() & ~HAS_NORMALS_MODE);
}

inline void MaterialDesc::setHasTangentsAndBitangentsMode(bool flag)
{
    if (flag)
        setModeFlags(getModeFlags() |  HAS_TANGENTS_AND_BITANGENTS_MODE);
    else
        setModeFlags(getModeFlags() & ~HAS_TANGENTS_AND_BITANGENTS_MODE);
}

inline void MaterialDesc::setFlatShadingMode(bool flag)
{
    if (flag)
        setModeFlags(getModeFlags() |  FLAT_SHADING_MODE);
    else
        setModeFlags(getModeFlags() & ~FLAT_SHADING_MODE);
}
    
inline void MaterialDesc::setOffsetPointMode(bool flag)
{
    if (flag)
        setModeFlags(getModeFlags() |  OFFSET_POINT_MODE);
    else
        setModeFlags(getModeFlags() & ~OFFSET_POINT_MODE);
}

inline void MaterialDesc::setOffsetLineMode(bool flag)
{
    if (flag)
        setModeFlags(getModeFlags() |  OFFSET_LINE_MODE);
    else
        setModeFlags(getModeFlags() & ~OFFSET_LINE_MODE);
}

inline void MaterialDesc::setOffsetFillMode(bool flag)
{
    if (flag)
        setModeFlags(getModeFlags() |  OFFSET_FILL_MODE);
    else
        setModeFlags(getModeFlags() & ~OFFSET_FILL_MODE);
}

inline void MaterialDesc::setXORMode(bool flag)
{
    if (flag)
        setModeFlags(getModeFlags() |  OFFSET_FILL_MODE);
    else
        setModeFlags(getModeFlags() & ~OFFSET_FILL_MODE);
}

inline void MaterialDesc::setNoDepthTestMode(bool flag)
{
    if (flag)
        setModeFlags(getModeFlags() |  NO_DEPTH_TEST_MODE);
    else
        setModeFlags(getModeFlags() & ~NO_DEPTH_TEST_MODE);
}

OSG_END_NAMESPACE
