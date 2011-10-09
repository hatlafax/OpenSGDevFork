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


#ifndef _OSGDISPLAYFILTERSTAGEFIELDS_H_
#define _OSGDISPLAYFILTERSTAGEFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGEffectGroupsDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class DisplayFilterStage;

OSG_GEN_CONTAINERPTR(DisplayFilterStage);
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldTraits
    \ingroup GrpLibOSGEffectGroups
 */
template <>
struct FieldTraits<DisplayFilterStage *, nsOSG> :
    public FieldTraitsFCPtrBase<DisplayFilterStage *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<DisplayFilterStage *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_EFFECTGROUPS_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<DisplayFilterStage *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecDisplayFilterStagePtr"; 
}

template<> inline
const Char8 *FieldTraits<DisplayFilterStage *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecDisplayFilterStagePtr"; 
}

template<> inline
const Char8 *FieldTraits<DisplayFilterStage *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakDisplayFilterStagePtr"; 
}

template<> inline
const Char8 *FieldTraits<DisplayFilterStage *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdDisplayFilterStagePtr"; 
}

template<> inline
const Char8 *FieldTraits<DisplayFilterStage *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecDisplayFilterStagePtr"; 
}

template<> inline
const Char8 *FieldTraits<DisplayFilterStage *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecDisplayFilterStagePtr"; 
}

template<> inline
const Char8 *FieldTraits<DisplayFilterStage *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakDisplayFilterStagePtr"; 
}

template<> inline
const Char8 *FieldTraits<DisplayFilterStage *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdDisplayFilterStagePtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields */
typedef PointerSField<DisplayFilterStage *,
                      RecordedRefCountPolicy, nsOSG  > SFRecDisplayFilterStagePtr;
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields */
typedef PointerSField<DisplayFilterStage *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecDisplayFilterStagePtr;
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields */
typedef PointerSField<DisplayFilterStage *,
                      WeakRefCountPolicy, nsOSG      > SFWeakDisplayFilterStagePtr;
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields */
typedef PointerSField<DisplayFilterStage *,
                      NoRefCountPolicy, nsOSG        > SFUncountedDisplayFilterStagePtr;


/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields */
typedef PointerMField<DisplayFilterStage *,
                      RecordedRefCountPolicy, nsOSG  > MFRecDisplayFilterStagePtr;
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields */
typedef PointerMField<DisplayFilterStage *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecDisplayFilterStagePtr;
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields */
typedef PointerMField<DisplayFilterStage *,
                      WeakRefCountPolicy, nsOSG      > MFWeakDisplayFilterStagePtr;
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields */
typedef PointerMField<DisplayFilterStage *,
                      NoRefCountPolicy, nsOSG        > MFUncountedDisplayFilterStagePtr;




#else // these are the doxygen hacks

/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields \ingroup GrpLibOSGEffectGroups */
struct SFRecDisplayFilterStagePtr : 
    public PointerSField<DisplayFilterStage *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields \ingroup GrpLibOSGEffectGroups */
struct SFUnrecDisplayFilterStagePtr : 
    public PointerSField<DisplayFilterStage *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields \ingroup GrpLibOSGEffectGroups */
struct SFWeakDisplayFilterStagePtr :
    public PointerSField<DisplayFilterStage *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldSFields \ingroup GrpLibOSGEffectGroups */
struct SFUncountedDisplayFilterStagePtr :
    public PointerSField<DisplayFilterStage *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields \ingroup GrpLibOSGEffectGroups */
struct MFRecDisplayFilterStagePtr :
    public PointerMField<DisplayFilterStage *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields \ingroup GrpLibOSGEffectGroups */
struct MFUnrecDisplayFilterStagePtr :
    public PointerMField<DisplayFilterStage *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields \ingroup GrpLibOSGEffectGroups */
struct MFWeakDisplayFilterStagePtr :
    public PointerMField<DisplayFilterStage *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpEffectsGroupsDisplayFilterFieldMFields \ingroup GrpLibOSGEffectGroups */
struct MFUncountedDisplayFilterStagePtr :
    public PointerMField<DisplayFilterStage *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGDISPLAYFILTERSTAGEFIELDS_H_ */
