/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

#ifndef _OSGDYNAMICATTACHMENTMIXIN_H_
#define _OSGDYNAMICATTACHMENTMIXIN_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseDef.h"

#include "OSGFieldContainerSFields.h"
#include "OSGFieldContainerMFields.h"
#include "OSGContainerDefines.h"

#include <boost/bind/bind.hpp>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseFieldContainerMixins
    \ingroup GrpLibOSGBase
 */

template <class AttachmentDescT>
class DynFieldAttachment : public AttachmentDescT::Parent
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef          AttachmentDescT                      Desc;
    typedef typename AttachmentDescT::Parent              Inherited;
    typedef typename AttachmentDescT::Parent              ParentContainer;

    typedef          DynFieldAttachment<AttachmentDescT>  Self;

    OSG_GEN_INTERNALPTR(Self);

    typedef typename Inherited::TypeObject                TypeObject;
    typedef typename TypeObject::InitPhase                InitPhase;

    /*---------------------------------------------------------------------*/
    /*! \name        General Fieldcontainer Declaration                    */
    /*! \{                                                                 */

    OSG_FIELD_CONTAINER_TMPL_DECL;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Dynamic Field Access                            */
    /*! \{                                                                 */

    UInt32 addField(const FieldDescriptionBase &fieldDesc    );
    UInt32 addField(const UInt32                uiFieldTypeId,
                    const Char8                *szFieldName  );
    void   subField(      UInt32                fieldId      );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Dynamic Field Access                            */
    /*! \{                                                                 */

    GetFieldHandlePtr  getDynamicField      (       UInt32  index ) const;
    EditFieldHandlePtr editDynamicField     (       UInt32  index );

    GetFieldHandlePtr  getDynamicFieldByName (const Char8  *szName) const;
    EditFieldHandlePtr editDynamicFieldByName(const Char8  *szName);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Clone                                   */
    /*! \{                                                                 */

    FieldContainer *emptyCopy(void);
    FieldContainer *clone    (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static TypeObject _type;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    TypeObject           _localType;

    std::vector<Field *> _dynFieldsV;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    DynFieldAttachment(      void                      );
    DynFieldAttachment(const DynFieldAttachment &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DynFieldAttachment(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual ObjCPtr createAspectCopy(const FieldContainer *pRefAspect) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual void execSyncV(      FieldContainer     &oFrom,
                                 ConstFieldMaskArg   whichField,
                                 AspectOffsetStore  &oOffsets,
                                 ConstFieldMaskArg   syncMode  ,
                           const UInt32              uiSyncInfo);

            void execSync (      DynFieldAttachment *pFrom,
                                 ConstFieldMaskArg   whichField,
                                 AspectOffsetStore  &oOffsets,
                                 ConstFieldMaskArg   syncMode  ,
                           const UInt32              uiSyncInfo);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);
    static void exitMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
 
  private:

    friend class FieldContainer;
    
    /*!\brief prohibit default functions (move to 'public' if needed) */
    void operator =(const DynFieldAttachment &source);

    void addPointerValue(FieldContainer *pVal, UInt32 uiFieldId);
    void setPointerValue(FieldContainer *pVal, UInt32 uiFieldId);
};

OSG_END_NAMESPACE

#define OSG_DYNFIELDATTACHMENT_INST(DESC)                                     \
template <>                                                                   \
DynFieldAttachment< DESC >::TypeObject                                        \
    DynFieldAttachment< DESC >::_type(                                        \
        Desc::getTypeName      (),                                            \
        Desc::getParentTypeName(),                                            \
        Desc::getGroupName     (),                                            \
        0,                                                                    \
        reinterpret_cast<PrototypeCreateF>(&Self::createEmptyLocal),          \
        NULL,                                                                 \
        NULL,                                                                 \
        NULL,                                                                 \
        true,                                                                 \
        0);                                                                   \
                                                                              \
template<> OSG_DLL_EXPORT                                                     \
DynFieldAttachment< DESC >::TypeObject &                                      \
    DynFieldAttachment< DESC >::getClassType(void)                            \
{                                                                             \
    return Self::_type;                                                       \
}

#include "OSGDynamicAttachmentMixin.inl"

#endif /* _OSGDYNAMICATTACHMENTMIXIN_H_ */
