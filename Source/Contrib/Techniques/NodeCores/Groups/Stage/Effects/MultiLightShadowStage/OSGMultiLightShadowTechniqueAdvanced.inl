/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

inline
MultiLightShadowTechniqueAdvanced::ShadowData::ShadowData()
: nbrOfSplits   (1)
, focused       (false)
, lightPosDir   ()
, matLSFromWS   ()
, matTSFromWS   ()
, frustumSize   ()
, zNear         ()
, zFar          ()
, shadowIndex   ()
, splitPositions()
{
}

inline
MultiLightShadowTechniqueAdvanced::ShadowData::ShadowData(const ShadowData& rhs)
: nbrOfSplits   (rhs.nbrOfSplits)
, focused       (rhs.focused)
, lightPosDir   (rhs.lightPosDir)
, matLSFromWS   (rhs.matLSFromWS)
, matTSFromWS   (rhs.matTSFromWS)
, frustumSize   (rhs.frustumSize)
, zNear         (rhs.zNear)
, zFar          (rhs.zFar)
, shadowIndex   (rhs.shadowIndex)
, splitPositions(rhs.splitPositions)
{
}

inline
MultiLightShadowTechniqueAdvanced::ShadowData& MultiLightShadowTechniqueAdvanced::ShadowData::operator=(const ShadowData& rhs)
{
    if (&rhs == this)
        return *this;

    nbrOfSplits     = rhs.nbrOfSplits;
    focused         = rhs.focused;
    lightPosDir     = rhs.lightPosDir;
    matLSFromWS     = rhs.matLSFromWS;
    matTSFromWS     = rhs.matTSFromWS;
    frustumSize     = rhs.frustumSize;
    zNear           = rhs.zNear;
    zFar            = rhs.zFar;
    shadowIndex     = rhs.shadowIndex;
    splitPositions  = rhs.splitPositions;

    return *this;
}

inline
bool MultiLightShadowTechniqueAdvanced::ShadowData::operator==(const ShadowData& rhs) const
{
    if (&rhs == this)
        return true;

    return nbrOfSplits     == rhs.nbrOfSplits
        && focused         == rhs.focused
        && lightPosDir     == rhs.lightPosDir
        && matLSFromWS     == rhs.matLSFromWS
        && matTSFromWS     == rhs.matTSFromWS
        && frustumSize     == rhs.frustumSize
        && zNear           == rhs.zNear
        && zFar            == rhs.zFar
        && shadowIndex     == rhs.shadowIndex
        && splitPositions  == rhs.splitPositions
        ;
}

inline
bool MultiLightShadowTechniqueAdvanced::ShadowData::equals(const ShadowData& rhs, Real32 tol) const
{
    if (&rhs == this)
        return true;

    bool result =     nbrOfSplits <= static_cast<Int32>(    matLSFromWS.size())
               && rhs.nbrOfSplits <= static_cast<Int32>(rhs.matLSFromWS.size())
               &&     nbrOfSplits <= static_cast<Int32>(    matTSFromWS.size())
               && rhs.nbrOfSplits <= static_cast<Int32>(rhs.matTSFromWS.size())
               && nbrOfSplits == rhs.nbrOfSplits
               && focused     == rhs.focused
               && lightPosDir.equals(rhs.lightPosDir, tol);

    for (Int32 i = 0; result && i < nbrOfSplits; ++i)
    {
        result = result && shadowIndex[i] == rhs.shadowIndex[i];
        result = result && osgIsEqual(          zNear[i], rhs.          zNear[i], tol);
        result = result && osgIsEqual(           zFar[i], rhs.           zFar[i], tol);
        result = result && osgIsEqual( splitPositions[i], rhs. splitPositions[i], tol);
        result = result && frustumSize[i].equals(rhs.frustumSize[i], tol);
        result = result && matLSFromWS[i].equals(rhs.matLSFromWS[i], tol);
        result = result && matTSFromWS[i].equals(rhs.matTSFromWS[i], tol);
    }

    //
    // The vector of split positions does have one additional element: See resize
    //
    result = result && osgIsEqual( splitPositions[nbrOfSplits], rhs. splitPositions[nbrOfSplits], tol);

    return result;
}

inline
void MultiLightShadowTechniqueAdvanced::ShadowData::resize(std::size_t size)
{
    //
    // The storage sizes are always equal with the exceptional extra entry in the split positions.
    //
    if (matTSFromWS.size() != size)
    {
        matLSFromWS    .resize(size);
        matTSFromWS    .resize(size);
        frustumSize    .resize(size);
        zNear          .resize(size);
        zFar           .resize(size);
        shadowIndex    .resize(size);
        splitPositions .resize(size + 1);
    }
}

inline
MultiLightShadowTechniqueAdvanced::AlgorithmData::AlgorithmData()
: lightPositionWS()
, matProjection  ()
{
}

inline
MultiLightShadowTechniqueAdvanced::AlgorithmData::AlgorithmData(const AlgorithmData& rhs)
: lightPositionWS(rhs.lightPositionWS)
, matProjection  (rhs.matProjection)
{
}

inline
MultiLightShadowTechniqueAdvanced::AlgorithmData&  MultiLightShadowTechniqueAdvanced::AlgorithmData::operator=(const AlgorithmData& rhs)
{
    if (&rhs == this)
        return *this;

    lightPositionWS = rhs.lightPositionWS;
    matProjection   = rhs.matProjection;

    return *this;
}

inline
bool MultiLightShadowTechniqueAdvanced::AlgorithmData::operator==(const AlgorithmData& rhs) const
{
    if (&rhs == this)
        return true;

    return lightPositionWS == rhs.lightPositionWS
        && matProjection   == rhs.matProjection
        ;
}

inline
bool MultiLightShadowTechniqueAdvanced::AlgorithmData::equals(const AlgorithmData& rhs, Real32 tol) const
{
    if (&rhs == this)
        return true;

    bool result = lightPositionWS.equals(rhs.lightPositionWS, tol);

    std::size_t sz = matProjection.size();

    result = result && sz == rhs.matProjection.size();

    for (std::size_t i = 0; result && i < sz; ++i)
    {
        result = result && matProjection[i].equals(rhs.matProjection[i], tol);
    }

    return result;
}

inline
void MultiLightShadowTechniqueAdvanced::AlgorithmData::resize(std::size_t size)
{
    if (matProjection.size() != size)
    {
        matProjection.resize(size);
    }
}

inline
void MultiLightShadowTechniqueAdvanced::adaptShadowDataLayout(UInt32 num_lights)
{
    //
    // Force the number of shadow data entries to be the same as the number of lights.
    // In principal we could go with only so many shadow data entries as their are active
    // shadow casting lights. However, that did not work so well and resulted in flickering
    // of the rendered scene when disabeling or enabeling a light, because then all shadow
    // maps would be regenerated. The brute force approach seems to be superior.
    //
    if (num_lights != _shadowData.size())
    {
        _shadowData    .resize(num_lights);
        _shadowDataLast.resize(num_lights);
    }

    //
    // _maxNbrOfSplits is the upper bound of splits of all shadowing lights
    //
    for (UInt32 i = 0; i < num_lights; ++i)
    {
        _shadowData[i].resize(_maxNbrOfSplits);
    }
}

inline
void MultiLightShadowTechniqueAdvanced::adaptAlgorithmDataLayout(UInt32 num_lights)
{
    if (num_lights != _algorithmData.size())
    {
        _algorithmData    .resize(num_lights);
        _algorithmDataLast.resize(num_lights);
    }
}

inline
void MultiLightShadowTechniqueAdvanced::adaptAlgorithmDataSplits(UInt32 lightIdx, Int32 num_splits)
{
    _algorithmData[lightIdx].resize(num_splits);
}

inline
void MultiLightShadowTechniqueAdvanced::initCameraView(const Matrix& matESFromWS)
{
    _camView.setValue(matESFromWS);
}

inline
void MultiLightShadowTechniqueAdvanced::initLightView(const Matrix& matLSFromWS)
{
    _lightView.setValue(matLSFromWS);

    Vec3f lViewDir(_lightView.getCenter() - _lightView.getEye());

    if (lViewDir.equals(Vec3f(0,0,0), 1.E-6f))
    {
        _lightView.setEye(-_direction);
    }
}

OSG_END_NAMESPACE
