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
#include "OSGView.h"

//#define CHECK_MATH_CALCULATIONS
#if CHECK_MATH_CALCULATIONS
#include "OSGMatrixUtility.h"
#endif

OSG_BEGIN_NAMESPACE

/*! \class OSG::View
    abstracts a view or vantage point part of a camera.
*/

View::View()
: _eye   ()
, _center()
, _up    ()
{
}

View::View(
    const Pnt3f& eye, 
    const Pnt3f& center, 
    const Vec3f& up)
: _eye   (eye)
, _center(center)
, _up    (up)
{
}

View::View(const Matrix& mat, bool isMatWSFromES)
{
    if (isMatWSFromES)
        setByMatWSFromES(mat);
    else
        setByMatESFromWS(mat);
}

View::View(const View& rhs)
: _eye   (rhs._eye)
, _center(rhs._center)
, _up    (rhs._up)
{
}

View::~View()
{
}

View& View::operator=(const View& rhs)
{
    if (&rhs == this) return *this;

    _eye    = rhs._eye;
    _center = rhs._center;
    _up     = rhs._up;

    return *this;
}

void View::setByMatWSFromES(const Matrix& mat)
{
    Pnt3f new_eye (mat[3]);
    Vec3f new_up  (mat[1]);
    Vec3f new_look(mat[2]);

    Real32 L = new_eye.subZero().length();
    Pnt3f new_center = new_eye - L*new_look;

#if CHECK_MATH_CALCULATIONS
    Matrix matWSFromES;
    bool result = MatrixLookAt(matWSFromES, new_eye, new_center, new_up);
    OSG_ASSERT(matWSFromES.equals(mat, 1.E-4f));
#endif

    _eye    = new_eye;
    _center = new_center;
    _up     = new_up;
}

void View::setByMatESFromWS(const Matrix& mat)
{
    Matrix tmp;
    mat.inverse(tmp);

    Pnt3f new_eye(0,0,0);
    tmp.mult(new_eye, new_eye);

    Vec3f new_up  (mat[0][1], mat[1][1],mat[2][1]);
    Vec3f new_look(mat[0][2], mat[1][2],mat[2][2]);

    Real32 L = new_eye.subZero().length();
    Pnt3f new_center = new_eye - L*new_look;

#if CHECK_MATH_CALCULATIONS
    Matrix matESFromWS;
    bool result = MatrixLookAtGL(matESFromWS, new_eye, new_center, new_up);
    OSG_ASSERT(matESFromWS.equals(mat, 1.E-4f));
#endif
    
    _eye    = new_eye;
    _center = new_center;
    _up     = new_up;
}

OSG_END_NAMESPACE
