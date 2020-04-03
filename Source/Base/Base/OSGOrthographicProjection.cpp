/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
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
#include "OSGOrthographicProjection.h"

OSG_BEGIN_NAMESPACE

/*! \class OSG::Projection
    abstracts the projection type of a camera.
*/
OrthographicProjection::OrthographicProjection()
: Inherited()
, _left  (0.f)
, _right (0.f)
, _bottom(0.f)
, _top   (0.f)
{
}

OrthographicProjection::OrthographicProjection(const OrthographicProjection& rhs)
: Inherited()
, _left  (rhs._left)
, _right (rhs._right)
, _bottom(rhs._bottom)
, _top   (rhs._top)
{
}

OrthographicProjection::OrthographicProjection(
    Real32 left,
    Real32 right,
    Real32 bottom,
    Real32 top,
    Real32 zNear,
    Real32 zFar)
: Projection(zNear, zFar)
, _left     (left)
, _right    (right)
, _bottom   (bottom)
, _top      (top)
{
}

OrthographicProjection::OrthographicProjection(const Matrix& matProjection)
: Projection()
{
    setValue(matProjection);
}

OrthographicProjection::~OrthographicProjection()
{
}

OrthographicProjection& OrthographicProjection::operator=(const OrthographicProjection& rhs)
{
    if (&rhs == this) return *this;

    Projection::operator=(rhs);

    _left   = rhs._left;
    _right  = rhs._right;
    _bottom = rhs._bottom;
    _top    = rhs._top;

    return *this;
}

Projection::Type OrthographicProjection::getType() const
{
    return Projection::ORTHOGRAPHIC;
}

void OrthographicProjection::setValue(const Matrix& matProjection)
{
    Real32 m00 = matProjection[0][0];
    Real32 m03 = matProjection[3][0];
    Real32 m11 = matProjection[1][1];
    Real32 m13 = matProjection[3][1];
    Real32 m22 = matProjection[2][2];
    Real32 m23 = matProjection[3][2];
    
    Real32 left   = -(m03 + 1)/m00;
    Real32 right  =  (1 - m03)/m00;
    Real32 bottom = -(m13 + 1)/m11;
    Real32 top    =  (1 - m13)/m11;
    Real32 zNear  =  (m23 + 1)/m22;
    Real32 zFar   = -(1 - m23)/m22;
    
    setValue(left, right, bottom, top, zNear, zFar);
}

OSG_END_NAMESPACE
