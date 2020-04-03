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
bool TextureDesc::isEnvironmentMap() const
{
    switch (getTextureType())
    {
        case REFLECTION_TEXTURE:
        case REFRACTION_TEXTURE:
        case IRRADIANCE_TEXTURE:
        case PRE_FILTER_TEXTURE:
            return true;
        default:
            return false;
    }
}

inline
bool TextureDesc::isEquirectangularMap() const
{
    return isEnvironmentMap() && getEnvironmentMapType() == EQUIRECTANGULAR_MAP;
}

inline
bool TextureDesc::isCubeMap() const
{
    return isEnvironmentMap() && getEnvironmentMapType() >= CUBE_MAP;
}

inline
bool TextureDesc::hasSwizzle() const
{
    return getSwizzle() != "rgba";
}

inline
bool TextureDesc::isInverted() const
{
    return (getTextureFlags() & INVERT_FLAG) != 0;
}

OSG_END_NAMESPACE
