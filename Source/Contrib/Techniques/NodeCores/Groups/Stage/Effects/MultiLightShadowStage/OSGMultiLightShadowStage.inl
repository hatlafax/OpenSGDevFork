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
UInt32 MultiLightShadowStage::getRequiredMultiLightFeatures() const
{
    return getRequiredMultiLightFeatures(getShadowMode());
}

inline
bool MultiLightShadowStage::getUpdateOffset() const
{
    return _bUpdateOffset;
}

inline
bool MultiLightShadowStage::getUpdateUniformData() const
{
    return _bUpdateUniformData;
}

inline
bool MultiLightShadowStage::getUpdateShadowParameter() const
{
    return _bUpdateShadowParameter;
}

inline
UInt32 MultiLightShadowStage::getNumShadowParameters() const
{
    return static_cast<Int32>(_mfShadowParameter.size());
}

inline
bool MultiLightShadowStage::getUpdateDistribution() const
{
    return _bUpdateDistribution;
}

inline
void MultiLightShadowStage::clearUpdate()
{
    _bUpdateOffset          = false;
    _bUpdateUniformData     = false;
    _bUpdateShadowParameter = false;
    _bUpdateDistribution    = false;
}

inline
MultiLightShadowParameter* MultiLightShadowStage::getShadowParameter(
    const UInt32 index) const
{
    return Inherited::getShadowParameter(index);
}

inline
void MultiLightShadowStage::setMapSize(UInt32 size)
{
    setShadowMapWidth   (size);
    setShadowMapHeight  (size);
}

inline
Int32 MultiLightShadowStage::getMapSize() const
{
    UInt32 width  = getShadowMapWidth();
    UInt32 height = getShadowMapWidth();

    if (width == height)
        return Int32(width);
    else
        return -1;

}

OSG_END_NAMESPACE
