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
#include "OSGPerspectiveProjection.h"

OSG_BEGIN_NAMESPACE

/*! \class OSG::Projection
    abstracts the projection type of a camera.
*/
PerspectiveProjection::PerspectiveProjection()
: Inherited()
, _fov   (0.f)
, _aspect(1.f)
{
}

PerspectiveProjection::PerspectiveProjection(const PerspectiveProjection& rhs)
: Inherited()
, _fov   (rhs._fov)
, _aspect(rhs._aspect)
{
}

PerspectiveProjection::PerspectiveProjection(
    Real32 fov,
    Real32 aspect,
    Real32 zNear,
    Real32 zFar)
: Projection(zNear, zFar)
, _fov      (fov)
, _aspect   (aspect)
{
}

PerspectiveProjection::PerspectiveProjection(const Matrix& matProjection)
: Projection()
{
    setValue(matProjection);
}

PerspectiveProjection::~PerspectiveProjection()
{
}

PerspectiveProjection& PerspectiveProjection::operator=(const PerspectiveProjection& rhs)
{
    if (&rhs == this) return *this;

    Projection::operator=(rhs);

    _fov    = rhs._fov;
    _aspect = rhs._aspect;

    return *this;
}

Projection::Type PerspectiveProjection::getType() const
{
    return Projection::PERSPECTIVE;
}

void PerspectiveProjection::setValue(const Matrix& matProjection)
{
    Real32 m00 = matProjection[0][0];
    Real32 m02 = matProjection[2][0];
    Real32 m11 = matProjection[1][1];
    Real32 m12 = matProjection[2][1];
    Real32 m22 = matProjection[2][2];
    Real32 m23 = matProjection[3][2];

    //Real32 left   = m23/m00 * (m02 - 1)/(m22 - 1);
    Real32 right  = m23/m00 * (m02 + 1)/(m22 - 1);
    //Real32 bottom = m23/m11 * (m12 - 1)/(m22 - 1);
    Real32 top    = m23/m11 * (m12 + 1)/(m22 - 1);
    Real32 zNear  = m23 / (m22 - 1);
    Real32 zFar   = m23 / (m22 + 1);

    Real32 ct     = top/zNear;
    Real32 fov    = OSG::osgATan(ct);
    Real32 aspect = right /(zNear * ct);
    
    setValue(fov, aspect, zNear, zFar);
}

OSG_END_NAMESPACE
