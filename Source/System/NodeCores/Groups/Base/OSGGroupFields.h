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


#ifndef _OSGGROUPFIELDS_H_
#define _OSGGROUPFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class Group;

OSG_GEN_CONTAINERPTR(Group);
/*! \ingroup GrpSystemNodeCoreGroupsFieldTraits
    \ingroup GrpLibOSGSystem
 */
template <>
struct FieldTraits<Group *, nsOSG> :
    public FieldTraitsFCPtrBase<Group *, nsOSG>
{
  private:

    static PointerType             _type;

  public:

    typedef FieldTraits<Group *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_SYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<Group *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<Group *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<Group *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<Group *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<Group *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<Group *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<Group *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<Group *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdGroupPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpSystemNodeCoreGroupsFieldSFields */
typedef PointerSField<Group *,
                      RecordedRefCountPolicy, nsOSG  > SFRecGroupPtr;
/*! \ingroup GrpSystemNodeCoreGroupsFieldSFields */
typedef PointerSField<Group *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecGroupPtr;
/*! \ingroup GrpSystemNodeCoreGroupsFieldSFields */
typedef PointerSField<Group *,
                      WeakRefCountPolicy, nsOSG      > SFWeakGroupPtr;
/*! \ingroup GrpSystemNodeCoreGroupsFieldSFields */
typedef PointerSField<Group *,
                      NoRefCountPolicy, nsOSG        > SFUncountedGroupPtr;


/*! \ingroup GrpSystemNodeCoreGroupsFieldMFields */
typedef PointerMField<Group *,
                      RecordedRefCountPolicy, nsOSG  > MFRecGroupPtr;
/*! \ingroup GrpSystemNodeCoreGroupsFieldMFields */
typedef PointerMField<Group *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecGroupPtr;
/*! \ingroup GrpSystemNodeCoreGroupsFieldMFields */
typedef PointerMField<Group *,
                      WeakRefCountPolicy, nsOSG      > MFWeakGroupPtr;
/*! \ingroup GrpSystemNodeCoreGroupsFieldMFields */
typedef PointerMField<Group *,
                      NoRefCountPolicy, nsOSG        > MFUncountedGroupPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpSystemNodeCoreGroupsFieldSFields \ingroup GrpLibOSGSystem */
struct SFRecGroupPtr : 
    public PointerSField<Group *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpSystemNodeCoreGroupsFieldSFields \ingroup GrpLibOSGSystem */
struct SFUnrecGroupPtr : 
    public PointerSField<Group *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemNodeCoreGroupsFieldSFields \ingroup GrpLibOSGSystem */
struct SFWeakGroupPtr :
    public PointerSField<Group *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpSystemNodeCoreGroupsFieldSFields \ingroup GrpLibOSGSystem */
struct SFUncountedGroupPtr :
    public PointerSField<Group *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpSystemNodeCoreGroupsFieldMFields \ingroup GrpLibOSGSystem */
struct MFRecGroupPtr :
    public PointerMField<Group *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpSystemNodeCoreGroupsFieldMFields \ingroup GrpLibOSGSystem */
struct MFUnrecGroupPtr :
    public PointerMField<Group *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemNodeCoreGroupsFieldMFields \ingroup GrpLibOSGSystem */
struct MFWeakGroupPtr :
    public PointerMField<Group *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpSystemNodeCoreGroupsFieldMFields \ingroup GrpLibOSGSystem */
struct MFUncountedGroupPtr :
    public PointerMField<Group *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGGROUPFIELDS_H_ */
