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

#ifndef _OSGCONSTANTSIZETRANSFORM_H_
#define _OSGCONSTANTSIZETRANSFORM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConstantSizeTransformBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ConstantSizeTransform class. See \ref
           PageContribTechniquesConstantSizeTransform for a description.
*/

class OSG_CONTRIBTECHNIQUES_DLLMAPPING ConstantSizeTransform : public ConstantSizeTransformBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ConstantSizeTransformBase Inherited;
    typedef ConstantSizeTransform     Self;

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
    /*---------------------------------------------------------------------*/
    /*! \name                   Transformation                             */
    /*! \{                                                                 */
    virtual void accumulateMatrix(Matrix &result);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ConstantSizeTransformBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ConstantSizeTransform(void);
    ConstantSizeTransform(const ConstantSizeTransform &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ConstantSizeTransform(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Matrix                                  */
    /*! \{                                                                 */

    void calcMatrix(Action* action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Volume                                  */
    /*! \{                                                                 */

    virtual void adjustVolume    (Volume &volume);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Intersect and Render                     */
    /*! \{                                                                 */
    Action::ResultE     intersectEnter(Action *action);
    Action::ResultE     intersectLeave(Action *action);

    Action::ResultE     renderEnter   (Action *action);
    Action::ResultE     renderLeave   (Action *action);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ConstantSizeTransformBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ConstantSizeTransform &source);
};

typedef ConstantSizeTransform *ConstantSizeTransformP;

OSG_END_NAMESPACE

#include "OSGConstantSizeTransformBase.inl"
#include "OSGConstantSizeTransform.inl"

#endif /* _OSGCONSTANTSIZETRANSFORM_H_ */
