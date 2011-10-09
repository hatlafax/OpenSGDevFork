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


#ifndef _OSGROOTGROUPFIELDS_H_
#define _OSGROOTGROUPFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class RootGroup;

OSG_GEN_CONTAINERPTR(RootGroup);
/*! \ingroup GrpSystemNodeCoreGroupsFieldTraits
    \ingroup GrpLibOSGSystem
 */
template <>
struct FieldTraits<RootGroup *, nsOSG> :
    public FieldTraitsFCPtrBase<RootGroup *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<RootGroup *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_SYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<RootGroup *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecRootGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<RootGroup *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecRootGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<RootGroup *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakRootGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<RootGroup *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdRootGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<RootGroup *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecRootGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<RootGroup *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecRootGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<RootGroup *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakRootGroupPtr"; 
}

template<> inline
const Char8 *FieldTraits<RootGroup *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdRootGroupPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpSystemNodeCoreGroupsFieldSFields */
typedef PointerSField<RootGroup *,
                      RecordedRefCountPolicy, nsOSG  > SFRecRootGroupPtr;
/*! \ingroup GrpSystemNodeCoreGroupsFieldSFields */
typedef PointerSField<RootGroup *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecRootGroupPtr;
/*! \ingroup GrpSystemNodeCoreGroupsFieldSFields */
typedef PointerSField<RootGroup *,
                      WeakRefCountPolicy, nsOSG      > SFWeakRootGroupPtr;
/*! \ingroup GrpSystemNodeCoreGroupsFieldSFields */
typedef PointerSField<RootGroup *,
                      NoRefCountPolicy, nsOSG        > SFUncountedRootGroupPtr;


/*! \ingroup GrpSystemNodeCoreGroupsFieldMFields */
typedef PointerMField<RootGroup *,
                      RecordedRefCountPolicy, nsOSG  > MFRecRootGroupPtr;
/*! \ingroup GrpSystemNodeCoreGroupsFieldMFields */
typedef PointerMField<RootGroup *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecRootGroupPtr;
/*! \ingroup GrpSystemNodeCoreGroupsFieldMFields */
typedef PointerMField<RootGroup *,
                      WeakRefCountPolicy, nsOSG      > MFWeakRootGroupPtr;
/*! \ingroup GrpSystemNodeCoreGroupsFieldMFields */
typedef PointerMField<RootGroup *,
                      NoRefCountPolicy, nsOSG        > MFUncountedRootGroupPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpSystemNodeCoreGroupsFieldSFields \ingroup GrpLibOSGSystem */
struct SFRecRootGroupPtr : 
    public PointerSField<RootGroup *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpSystemNodeCoreGroupsFieldSFields \ingroup GrpLibOSGSystem */
struct SFUnrecRootGroupPtr : 
    public PointerSField<RootGroup *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemNodeCoreGroupsFieldSFields \ingroup GrpLibOSGSystem */
struct SFWeakRootGroupPtr :
    public PointerSField<RootGroup *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpSystemNodeCoreGroupsFieldSFields \ingroup GrpLibOSGSystem */
struct SFUncountedRootGroupPtr :
    public PointerSField<RootGroup *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpSystemNodeCoreGroupsFieldMFields \ingroup GrpLibOSGSystem */
struct MFRecRootGroupPtr :
    public PointerMField<RootGroup *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpSystemNodeCoreGroupsFieldMFields \ingroup GrpLibOSGSystem */
struct MFUnrecRootGroupPtr :
    public PointerMField<RootGroup *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemNodeCoreGroupsFieldMFields \ingroup GrpLibOSGSystem */
struct MFWeakRootGroupPtr :
    public PointerMField<RootGroup *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpSystemNodeCoreGroupsFieldMFields \ingroup GrpLibOSGSystem */
struct MFUncountedRootGroupPtr :
    public PointerMField<RootGroup *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGROOTGROUPFIELDS_H_ */
