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
bool View::operator==(const View& rhs) const
{
    if (&rhs == this)
        return true;

    return _eye    == rhs._eye
        && _center == rhs._center
        && _up     == rhs._up;
}

inline
bool View::equals(const View& rhs, Real32 tol) const
{
    if (&rhs == this)
        return true;

    return _eye   .equals(rhs._eye,    tol)
        && _center.equals(rhs._center, tol)
        && _up    .equals(rhs._up,     tol);
}

inline
const Pnt3f& View::getEye() const
{
    return _eye;
}

inline
void View::setEye(const Pnt3f& eye)
{
    _eye = eye;
}

inline
const Pnt3f& View::getCenter() const
{
    return _center;
}

inline
void View::setCenter(const Pnt3f& center)
{
    _center = center;
}

inline
const Vec3f& View::getUp() const
{
    return _up;
}

inline
void View::setUp(const Vec3f& up)
{
    _up = up;
}

inline
Vec3f View::getDirection() const
{
    Vec3f dir = _center - _eye;
    dir.normalize();
    return dir;
}

inline
void View::setValue(
    const Pnt3f& eye, 
    const Pnt3f& center, 
    const Vec3f& up)
{
    _eye    = eye;
    _center = center;
    _up     = up;
}

inline
void View::setValue(
    const Matrix& mat, 
    bool isMatWSFromES)
{
    if (isMatWSFromES)
        setByMatWSFromES(mat);
    else
        setByMatESFromWS(mat);
}


OSG_END_NAMESPACE

