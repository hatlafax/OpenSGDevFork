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
void EnvironmentDesc::setFeatureImpl(UInt32 feature)
{
    if (feature != getFeature())
    {
        setFeature(feature);
    }
}

inline
void EnvironmentDesc::setHasFeatureTonemapping(bool value)
{
    UInt32 feature = value ? getFeature() |  FEATURE_TONEMAPPING
                           : getFeature() & ~FEATURE_TONEMAPPING;

    setFeatureImpl(feature);
}

inline
void EnvironmentDesc::setHasFeatureGammaCorrection(bool value)
{
    UInt32 feature = value ? getFeature() |  FEATURE_GAMMA_CORRECTION
                           : getFeature() & ~FEATURE_GAMMA_CORRECTION;

    setFeatureImpl(feature);
}

inline
void EnvironmentDesc::setHasFeatureClassicLightExtension(bool value)
{
    UInt32 feature = value ? getFeature() |  FEATURE_CLASSIC_LIGHT_EXTENSIONS
                           : getFeature() & ~FEATURE_CLASSIC_LIGHT_EXTENSIONS;

    setFeatureImpl(feature);
}

inline
void EnvironmentDesc::setHasFeatureFog(bool value)
{
    UInt32 feature = value ? getFeature() |  FEATURE_FOG
                           : getFeature() & ~FEATURE_FOG;

    setFeatureImpl(feature);
}

inline
void EnvironmentDesc::setHasFeatureClipPlanes(bool value)
{
    UInt32 feature = value ? getFeature() |  FEATURE_CLIP_PLANES
                           : getFeature() & ~FEATURE_CLIP_PLANES;

    setFeatureImpl(feature);
}

inline
bool EnvironmentDesc::getHasFeatureTonemapping() const
{
    return (getFeature() & FEATURE_TONEMAPPING) != 0;
}

inline
bool EnvironmentDesc::getHasFeatureGammaCorrection() const
{
    return (getFeature() & FEATURE_GAMMA_CORRECTION) != 0;
}

inline
bool EnvironmentDesc::getHasFeatureClassicLightExtension() const
{
    return (getFeature() & FEATURE_CLASSIC_LIGHT_EXTENSIONS) != 0;
}

inline
bool EnvironmentDesc::getHasFeatureFog() const
{
    return (getFeature() & FEATURE_FOG) != 0;
}

inline
bool EnvironmentDesc::getHasFeatureClipPlanes() const
{
    return (getFeature() & FEATURE_CLIP_PLANES) != 0;
}

OSG_END_NAMESPACE
