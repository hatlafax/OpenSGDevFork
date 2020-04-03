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

OSG_BEGIN_NAMESPACE

inline
bool PerspectiveProjection::operator==(
    const PerspectiveProjection& rhs) const
{
    if (&rhs == this)
        return true;

    return Projection::operator==(rhs) 
        && _fov    == rhs._fov
        && _aspect == rhs._aspect;
}

inline
bool PerspectiveProjection::equals(
    const PerspectiveProjection& rhs, 
    Real32 tol) const
{
    if (&rhs == this)
        return true;

    return Projection::equals(rhs, tol) 
        && (_fov    - rhs._fov    <= tol) && (rhs._fov    - _fov    <= tol)
        && (_aspect - rhs._aspect <= tol) && (rhs._aspect - _aspect <= tol);
}

inline
Real32 PerspectiveProjection::getFov() const
{
    return _fov;
}

inline
void PerspectiveProjection::setFov(Real32 fov)
{
    _fov = fov;
}

inline
Real32 PerspectiveProjection::getAspect() const
{
    return _aspect;
}

inline
void PerspectiveProjection::setAspect(Real32 aspect)
{
    _aspect = aspect;
}

inline
void PerspectiveProjection::setValue(
    Real32 fov,
    Real32 aspect,
    Real32 zNear,
    Real32 zFar)
{
    _fov    = fov;
    _aspect = aspect;
    
    setZNear(zNear);
    setZFar (zFar);
}

OSG_END_NAMESPACE
