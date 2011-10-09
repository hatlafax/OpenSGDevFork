/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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


#ifndef _OSGDISPLAYFILTERGROUPFIELDS_H_
#define _OSGDISPLAYFILTERGROUPFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGEffectGroupsDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class DisplayFilterGroup;

OSG_GEN_CONTAINERPTR(DisplayFilterGroup);
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldTraits
    \ingroup GrpLibOSGEffectGroups
 */
template <>
struct FieldTraits<DisplayFilterGroup *, nsOSG> :
    public FieldTraitsFCPtrBase<DisplayFilterGroup *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<DisplayFilterGroup *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_EFFECTGROUPS_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<DisplayFilterGroup *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecDisplayFilterGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<DisplayFilterGroup *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecDisplayFilterGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<DisplayFilterGroup *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakDisplayFilterGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<DisplayFilterGroup *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdDisplayFilterGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<DisplayFilterGroup *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecDisplayFilterGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<DisplayFilterGroup *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecDisplayFilterGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<DisplayFilterGroup *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakDisplayFilterGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<DisplayFilterGroup *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdDisplayFilterGroupPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields */
typedef PointerSField<DisplayFilterGroup *,
                      RecordedRefCountPolicy, nsOSG  > SFRecDisplayFilterGroupPtr;
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields */
typedef PointerSField<DisplayFilterGroup *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecDisplayFilterGroupPtr;
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields */
typedef PointerSField<DisplayFilterGroup *,
                      WeakRefCountPolicy, nsOSG      > SFWeakDisplayFilterGroupPtr;
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields */
typedef PointerSField<DisplayFilterGroup *,
                      NoRefCountPolicy, nsOSG        > SFUncountedDisplayFilterGroupPtr;


/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields */
typedef PointerMField<DisplayFilterGroup *,
                      RecordedRefCountPolicy, nsOSG  > MFRecDisplayFilterGroupPtr;
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields */
typedef PointerMField<DisplayFilterGroup *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecDisplayFilterGroupPtr;
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields */
typedef PointerMField<DisplayFilterGroup *,
                      WeakRefCountPolicy, nsOSG      > MFWeakDisplayFilterGroupPtr;
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields */
typedef PointerMField<DisplayFilterGroup *,
                      NoRefCountPolicy, nsOSG        > MFUncountedDisplayFilterGroupPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields \ingroup GrpLibOSGEffectGroups */
struct SFRecDisplayFilterGroupPtr : 
    public PointerSField<DisplayFilterGroup *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields \ingroup GrpLibOSGEffectGroups */
struct SFUnrecDisplayFilterGroupPtr : 
    public PointerSField<DisplayFilterGroup *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields \ingroup GrpLibOSGEffectGroups */
struct SFWeakDisplayFilterGroupPtr :
    public PointerSField<DisplayFilterGroup *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields \ingroup GrpLibOSGEffectGroups */
struct SFUncountedDisplayFilterGroupPtr :
    public PointerSField<DisplayFilterGroup *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields \ingroup GrpLibOSGEffectGroups */
struct MFRecDisplayFilterGroupPtr :
    public PointerMField<DisplayFilterGroup *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields \ingroup GrpLibOSGEffectGroups */
struct MFUnrecDisplayFilterGroupPtr :
    public PointerMField<DisplayFilterGroup *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields \ingroup GrpLibOSGEffectGroups */
struct MFWeakDisplayFilterGroupPtr :
    public PointerMField<DisplayFilterGroup *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields \ingroup GrpLibOSGEffectGroups */
struct MFUncountedDisplayFilterGroupPtr :
    public PointerMField<DisplayFilterGroup *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGDISPLAYFILTERGROUPFIELDS_H_ */
