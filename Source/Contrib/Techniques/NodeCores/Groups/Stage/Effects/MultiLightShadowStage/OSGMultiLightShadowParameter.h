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

#ifndef _OSGMULTILIGHTSHADOWPARAMETER_H_
#define _OSGMULTILIGHTSHADOWPARAMETER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMultiLightShadowParameterBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief MultiLightShadowParameter class. See \ref
           PageContribTechniquesMultiLightShadowParameter for a description.
*/

class OSG_CONTRIBTECHNIQUES_DLLMAPPING MultiLightShadowParameter : public MultiLightShadowParameterBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MultiLightShadowParameterBase Inherited;
    typedef MultiLightShadowParameter     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in MultiLightShadowParameterBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MultiLightShadowParameter(void);
    MultiLightShadowParameter(const MultiLightShadowParameter &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MultiLightShadowParameter(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MultiLightShadowParameterBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MultiLightShadowParameter &source);
};

typedef MultiLightShadowParameter *MultiLightShadowParameterP;

OSG_END_NAMESPACE

#include "OSGMultiLightShadowParameterBase.inl"
#include "OSGMultiLightShadowParameter.inl"

#endif /* _OSGMULTILIGHTSHADOWPARAMETER_H_ */
