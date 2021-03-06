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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGMULTILIGHTSHADOWSTAGEFIELDS_H_
#define _OSGMULTILIGHTSHADOWSTAGEFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTechniquesDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class MultiLightShadowStage;

OSG_GEN_CONTAINERPTR(MultiLightShadowStage);
/*! \ingroup GrpContribTechniquesFieldTraits
    \ingroup GrpLibOSGContribTechniques
 */
template <>
struct FieldTraits<MultiLightShadowStage *, nsOSG> :
    public FieldTraitsFCPtrBase<MultiLightShadowStage *, nsOSG>
{
  private:

    static PointerType             _type;

  public:

    typedef FieldTraits<MultiLightShadowStage *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBTECHNIQUES_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<MultiLightShadowStage *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecMultiLightShadowStagePtr"; 
}

template<> inline
const Char8 *FieldTraits<MultiLightShadowStage *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecMultiLightShadowStagePtr"; 
}

template<> inline
const Char8 *FieldTraits<MultiLightShadowStage *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakMultiLightShadowStagePtr"; 
}

template<> inline
const Char8 *FieldTraits<MultiLightShadowStage *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdMultiLightShadowStagePtr"; 
}

template<> inline
const Char8 *FieldTraits<MultiLightShadowStage *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecMultiLightShadowStagePtr"; 
}

template<> inline
const Char8 *FieldTraits<MultiLightShadowStage *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecMultiLightShadowStagePtr"; 
}

template<> inline
const Char8 *FieldTraits<MultiLightShadowStage *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakMultiLightShadowStagePtr"; 
}

template<> inline
const Char8 *FieldTraits<MultiLightShadowStage *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdMultiLightShadowStagePtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribTechniquesFieldSFields */
typedef PointerSField<MultiLightShadowStage *,
                      RecordedRefCountPolicy, nsOSG  > SFRecMultiLightShadowStagePtr;
/*! \ingroup GrpContribTechniquesFieldSFields */
typedef PointerSField<MultiLightShadowStage *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecMultiLightShadowStagePtr;
/*! \ingroup GrpContribTechniquesFieldSFields */
typedef PointerSField<MultiLightShadowStage *,
                      WeakRefCountPolicy, nsOSG      > SFWeakMultiLightShadowStagePtr;
/*! \ingroup GrpContribTechniquesFieldSFields */
typedef PointerSField<MultiLightShadowStage *,
                      NoRefCountPolicy, nsOSG        > SFUncountedMultiLightShadowStagePtr;


/*! \ingroup GrpContribTechniquesFieldMFields */
typedef PointerMField<MultiLightShadowStage *,
                      RecordedRefCountPolicy, nsOSG  > MFRecMultiLightShadowStagePtr;
/*! \ingroup GrpContribTechniquesFieldMFields */
typedef PointerMField<MultiLightShadowStage *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecMultiLightShadowStagePtr;
/*! \ingroup GrpContribTechniquesFieldMFields */
typedef PointerMField<MultiLightShadowStage *,
                      WeakRefCountPolicy, nsOSG      > MFWeakMultiLightShadowStagePtr;
/*! \ingroup GrpContribTechniquesFieldMFields */
typedef PointerMField<MultiLightShadowStage *,
                      NoRefCountPolicy, nsOSG        > MFUncountedMultiLightShadowStagePtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribTechniquesFieldSFields \ingroup GrpLibOSGContribTechniques */
struct SFRecMultiLightShadowStagePtr : 
    public PointerSField<MultiLightShadowStage *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribTechniquesFieldSFields \ingroup GrpLibOSGContribTechniques */
struct SFUnrecMultiLightShadowStagePtr : 
    public PointerSField<MultiLightShadowStage *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribTechniquesFieldSFields \ingroup GrpLibOSGContribTechniques */
struct SFWeakMultiLightShadowStagePtr :
    public PointerSField<MultiLightShadowStage *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribTechniquesFieldSFields \ingroup GrpLibOSGContribTechniques */
struct SFUncountedMultiLightShadowStagePtr :
    public PointerSField<MultiLightShadowStage *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribTechniquesFieldMFields \ingroup GrpLibOSGContribTechniques */
struct MFRecMultiLightShadowStagePtr :
    public PointerMField<MultiLightShadowStage *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribTechniquesFieldMFields \ingroup GrpLibOSGContribTechniques */
struct MFUnrecMultiLightShadowStagePtr :
    public PointerMField<MultiLightShadowStage *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribTechniquesFieldMFields \ingroup GrpLibOSGContribTechniques */
struct MFWeakMultiLightShadowStagePtr :
    public PointerMField<MultiLightShadowStage *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribTechniquesFieldMFields \ingroup GrpLibOSGContribTechniques */
struct MFUncountedMultiLightShadowStagePtr :
    public PointerMField<MultiLightShadowStage *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGMULTILIGHTSHADOWSTAGEFIELDS_H_ */
