/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGMATERIALDRAWABLE_H_
#define _OSGMATERIALDRAWABLE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMaterialDrawableBase.h"

#include "OSGAction.h"
#include "OSGDrawActionBase.h"
#include "OSGMaterial.h"

OSG_BEGIN_NAMESPACE

class DrawEnv;

/*! \brief *put brief class description here* 
 */

class OSG_SYSTEM_DLLMAPPING MaterialDrawable : public MaterialDrawableBase
{
  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MaterialDrawableBase                           Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                   action handler                             */
    /*! \{                                                                 */

    // draw the OpenGL primitives

    virtual Action::ResultE drawPrimitives     (DrawEnv *pEnv  );

            Action::ResultE renderActionHandler(Action  *action);

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField, 
                         UInt32            origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in MaterialDrawableBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MaterialDrawable(void);
    MaterialDrawable(const MaterialDrawable &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MaterialDrawable(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class MaterialDrawableBase;

    template<class ContainerFactoryT>
    friend struct CPtrConstructionFunctions;

    template<class ContainerFactoryT>
    friend struct PtrConstructionFunctions;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MaterialDrawable &source);
};

typedef MaterialDrawable *MaterialDrawableP;

OSG_END_NAMESPACE

#include "OSGMaterialDrawableBase.inl"
#include "OSGMaterialDrawable.inl"

#define OSGMATERIALDRAWABLE_HEADER_CVSID "@(#)$Id: OSGMaterialDrawable.h,v 1.3.4.6 2006/07/28 06:21:56 vossg Exp $"

#endif /* _OSGMATERIALDRAWABLE_H_ */
