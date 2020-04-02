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

#include "OSGConfig.h"

#include "OSGBaseTypes.h"
#include "OSGVector.h"
#include "OSGNode.h"

#include "OSGMultiLight.h"

OSG_BEGIN_NAMESPACE


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

MultiLight::MultiLight(Type e)
    : _position(0.f,0.f,0.f)
    , _direction(0.f,0.f,1.f)
    , _intensity(1.f,1.f,1.f)
    , _ambientIntensity(1.f,1.f,1.f)
    , _diffuseIntensity(1.f,1.f,1.f)
    , _specularIntensity(1.f,1.f,1.f)
    , _attenuation(1.f, 0.0001f, 0.000001f)
    , _decayAttenuation(2.f)
    , _lengthFactor(1.f)
    , _spotlightAngle(20.f)
    , _spotlightParameter(1.f)
    , _innerSuperEllipsesWidth(1.f)
    , _innerSuperEllipsesHeight(1.f)
    , _outerSuperEllipsesWidth(1.3f)
    , _outerSuperEllipsesHeight(1.3f)
    , _superEllipsesRoundness(1.f)
    , _superEllipsesTwist(0.f)
    , _rangeCutOn(0.1f)
    , _rangeCutOff(TypeTraits<Real32>::getMax())
    , _rangeNearZone(0.f)
    , _rangeFarZone(0.f)
    , _projectionMatrix()
    , _type(e)
    , _enabled(true)
    , _shadow(false)
    , _shadowDataIndex(-1)
    , _shadowParameterIndex(-1)
    , _beacon(NULL)
{
}

OSG_END_NAMESPACE
