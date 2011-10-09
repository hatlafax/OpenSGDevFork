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


#ifndef _OSGCONTAINERCOLLECTIONFIELDS_H_
#define _OSGCONTAINERCOLLECTIONFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class ContainerCollection;

OSG_GEN_CONTAINERPTR(ContainerCollection);
/*! \ingroup GrpSystemFieldContainerFieldTraits
    \ingroup GrpLibOSGSystem
 */
template <>
struct FieldTraits<ContainerCollection *, nsOSG> :
    public FieldTraitsFCPtrBase<ContainerCollection *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<ContainerCollection *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_SYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<ContainerCollection *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecContainerCollectionPtr"; 
}

template<> inline
const Char8 *FieldTraits<ContainerCollection *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecContainerCollectionPtr"; 
}

template<> inline
const Char8 *FieldTraits<ContainerCollection *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakContainerCollectionPtr"; 
}

template<> inline
const Char8 *FieldTraits<ContainerCollection *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdContainerCollectionPtr"; 
}

template<> inline
const Char8 *FieldTraits<ContainerCollection *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecContainerCollectionPtr"; 
}

template<> inline
const Char8 *FieldTraits<ContainerCollection *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecContainerCollectionPtr"; 
}

template<> inline
const Char8 *FieldTraits<ContainerCollection *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakContainerCollectionPtr"; 
}

template<> inline
const Char8 *FieldTraits<ContainerCollection *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdContainerCollectionPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpSystemFieldContainerFieldSFields */
typedef PointerSField<ContainerCollection *,
                      RecordedRefCountPolicy, nsOSG  > SFRecContainerCollectionPtr;
/*! \ingroup GrpSystemFieldContainerFieldSFields */
typedef PointerSField<ContainerCollection *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecContainerCollectionPtr;
/*! \ingroup GrpSystemFieldContainerFieldSFields */
typedef PointerSField<ContainerCollection *,
                      WeakRefCountPolicy, nsOSG      > SFWeakContainerCollectionPtr;
/*! \ingroup GrpSystemFieldContainerFieldSFields */
typedef PointerSField<ContainerCollection *,
                      NoRefCountPolicy, nsOSG        > SFUncountedContainerCollectionPtr;


/*! \ingroup GrpSystemFieldContainerFieldMFields */
typedef PointerMField<ContainerCollection *,
                      RecordedRefCountPolicy, nsOSG  > MFRecContainerCollectionPtr;
/*! \ingroup GrpSystemFieldContainerFieldMFields */
typedef PointerMField<ContainerCollection *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecContainerCollectionPtr;
/*! \ingroup GrpSystemFieldContainerFieldMFields */
typedef PointerMField<ContainerCollection *,
                      WeakRefCountPolicy, nsOSG      > MFWeakContainerCollectionPtr;
/*! \ingroup GrpSystemFieldContainerFieldMFields */
typedef PointerMField<ContainerCollection *,
                      NoRefCountPolicy, nsOSG        > MFUncountedContainerCollectionPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpSystemFieldContainerFieldSFields \ingroup GrpLibOSGSystem */
struct SFRecContainerCollectionPtr : 
    public PointerSField<ContainerCollection *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpSystemFieldContainerFieldSFields \ingroup GrpLibOSGSystem */
struct SFUnrecContainerCollectionPtr : 
    public PointerSField<ContainerCollection *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemFieldContainerFieldSFields \ingroup GrpLibOSGSystem */
struct SFWeakContainerCollectionPtr :
    public PointerSField<ContainerCollection *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpSystemFieldContainerFieldSFields \ingroup GrpLibOSGSystem */
struct SFUncountedContainerCollectionPtr :
    public PointerSField<ContainerCollection *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpSystemFieldContainerFieldMFields \ingroup GrpLibOSGSystem */
struct MFRecContainerCollectionPtr :
    public PointerMField<ContainerCollection *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpSystemFieldContainerFieldMFields \ingroup GrpLibOSGSystem */
struct MFUnrecContainerCollectionPtr :
    public PointerMField<ContainerCollection *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemFieldContainerFieldMFields \ingroup GrpLibOSGSystem */
struct MFWeakContainerCollectionPtr :
    public PointerMField<ContainerCollection *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpSystemFieldContainerFieldMFields \ingroup GrpLibOSGSystem */
struct MFUncountedContainerCollectionPtr :
    public PointerMField<ContainerCollection *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGCONTAINERCOLLECTIONFIELDS_H_ */
