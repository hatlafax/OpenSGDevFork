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

#ifndef _OSGORTHOGRAPHICPROJECTION_H_
#define _OSGORTHOGRAPHICPROJECTION_H_

#include "OSGBaseTypes.h"
#include "OSGMatrix.h"
#include "OSGProjection.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBase
    \ingroup GrpBaseBaseMathObj
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

class OSG_BASE_DLLMAPPING OrthographicProjection : public Projection
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    OrthographicProjection();

    OrthographicProjection(
                            Real32 left,
                            Real32 right,
                            Real32 bottom,
                            Real32 top,
                            Real32 zNear,
                            Real32 zFar
                         );
  
    OrthographicProjection(const Matrix& matProjection);

    OrthographicProjection(const OrthographicProjection& rhs);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~OrthographicProjection();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */
    OrthographicProjection& operator= ( const OrthographicProjection& rhs);
    bool                    operator==(
                                        const OrthographicProjection& rhs
                                      ) const;
    bool                    equals    (
                                        const OrthographicProjection& rhs, 
                                        Real32 tol
                                      ) const;
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get/Set                                   */
    /*! \{                                                                 */
    virtual Type        getType         () const;

    Real32              getLeft         () const;
    void                setLeft         (Real32 left);

    Real32              getRight        () const;
    void                setRight        (Real32 right);

    Real32              getBottom       () const;
    void                setBottom       (Real32 bottom);

    Real32              getTop          () const;
    void                setTop          (Real32 top);
    
    void                setValue        (
                                            Real32 left,
                                            Real32 right,
                                            Real32 bottom,
                                            Real32 top,
                                            Real32 zNear,
                                            Real32 zFar
                                         );
                                         
    void                setValue        (const Matrix& matProjection);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operations                                */
    /*! \{                                                                 */
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Specific                            */
    /*! \{                                                                 */
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef Projection Inherited;

    /*==========================  PRIVATE  ================================*/

  private:
    Real32  _left;
    Real32  _right;
    Real32  _bottom;
    Real32  _top;
};

OSG_END_NAMESPACE

#include "OSGOrthographicProjection.inl"

#endif // _OSGORTHOGRAPHICPROJECTION_H_
