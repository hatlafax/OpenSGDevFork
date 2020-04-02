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
void MultiLightShadowStageData::setTechnique(Technique* pTechnique)
{
    _pTechnique = pTechnique;
}

inline
MultiLightShadowStageData::Technique* MultiLightShadowStageData::getTechnique()
{
    return _pTechnique;
}

inline
MultiLightShadowStageData::NodeStore& MultiLightShadowStageData::getTransparents()
{
    return _vTransparents;
}

inline
MultiLightShadowStageData::TravMaskStore& MultiLightShadowStageData::getExcludeNodeTravMask()
{
    return _vExcludeNodeTravMask;
}

inline
MultiLightShadowStageData::TravMaskStore& MultiLightShadowStageData::getTransparentNodeTravMask()
{
    return _vTransparentNodeTravMask;
}

inline
MultiLightShadowStageData::LightAssocStore& MultiLightShadowStageData::getLightAssocData()
{
    return _vLightAssocData;
}

inline
MultiLightShadowStageData::LightIndexStore& MultiLightShadowStageData::getPointLightIndices()
{
    return _vPointLightIndices;
}

inline
MultiLightShadowStageData::LightIndexStore& MultiLightShadowStageData::getSpotLightIndices()
{
    return _vSpotLightIndices;
}

inline
MultiLightShadowStageData::LightIndexStore& MultiLightShadowStageData::getDirLightIndices()
{
    return _vDirLightIndices;
}

OSG_END_NAMESPACE
