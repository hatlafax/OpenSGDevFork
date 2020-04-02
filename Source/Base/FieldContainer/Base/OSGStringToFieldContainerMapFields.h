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


#ifndef _OSGSTRINGTOFIELDCONTAINERMAPFIELDS_H_
#define _OSGSTRINGTOFIELDCONTAINERMAPFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGBaseDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class StringToFieldContainerMap;

OSG_GEN_CONTAINERPTR(StringToFieldContainerMap);
/*! \ingroup GrpBaseFieldContainerFieldTraits
    \ingroup GrpLibOSGBase
 */
template <>
struct FieldTraits<StringToFieldContainerMap *, nsOSG> :
    public FieldTraitsFCPtrBase<StringToFieldContainerMap *, nsOSG>
{
  private:

    static PointerType             _type;

  public:

    typedef FieldTraits<StringToFieldContainerMap *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_BASE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<StringToFieldContainerMap *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecStringToFieldContainerMapPtr"; 
}

template<> inline
const Char8 *FieldTraits<StringToFieldContainerMap *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecStringToFieldContainerMapPtr"; 
}

template<> inline
const Char8 *FieldTraits<StringToFieldContainerMap *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakStringToFieldContainerMapPtr"; 
}

template<> inline
const Char8 *FieldTraits<StringToFieldContainerMap *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdStringToFieldContainerMapPtr"; 
}

template<> inline
const Char8 *FieldTraits<StringToFieldContainerMap *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecStringToFieldContainerMapPtr"; 
}

template<> inline
const Char8 *FieldTraits<StringToFieldContainerMap *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecStringToFieldContainerMapPtr"; 
}

template<> inline
const Char8 *FieldTraits<StringToFieldContainerMap *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakStringToFieldContainerMapPtr"; 
}

template<> inline
const Char8 *FieldTraits<StringToFieldContainerMap *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdStringToFieldContainerMapPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField<StringToFieldContainerMap *,
                      RecordedRefCountPolicy, nsOSG  > SFRecStringToFieldContainerMapPtr;
/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField<StringToFieldContainerMap *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecStringToFieldContainerMapPtr;
/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField<StringToFieldContainerMap *,
                      WeakRefCountPolicy, nsOSG      > SFWeakStringToFieldContainerMapPtr;
/*! \ingroup GrpBaseFieldContainerFieldSFields */
typedef PointerSField<StringToFieldContainerMap *,
                      NoRefCountPolicy, nsOSG        > SFUncountedStringToFieldContainerMapPtr;


/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField<StringToFieldContainerMap *,
                      RecordedRefCountPolicy, nsOSG  > MFRecStringToFieldContainerMapPtr;
/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField<StringToFieldContainerMap *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecStringToFieldContainerMapPtr;
/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField<StringToFieldContainerMap *,
                      WeakRefCountPolicy, nsOSG      > MFWeakStringToFieldContainerMapPtr;
/*! \ingroup GrpBaseFieldContainerFieldMFields */
typedef PointerMField<StringToFieldContainerMap *,
                      NoRefCountPolicy, nsOSG        > MFUncountedStringToFieldContainerMapPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldContainerFieldSFields \ingroup GrpLibOSGBase */
struct SFRecStringToFieldContainerMapPtr : 
    public PointerSField<StringToFieldContainerMap *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpBaseFieldContainerFieldSFields \ingroup GrpLibOSGBase */
struct SFUnrecStringToFieldContainerMapPtr : 
    public PointerSField<StringToFieldContainerMap *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpBaseFieldContainerFieldSFields \ingroup GrpLibOSGBase */
struct SFWeakStringToFieldContainerMapPtr :
    public PointerSField<StringToFieldContainerMap *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpBaseFieldContainerFieldSFields \ingroup GrpLibOSGBase */
struct SFUncountedStringToFieldContainerMapPtr :
    public PointerSField<StringToFieldContainerMap *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpBaseFieldContainerFieldMFields \ingroup GrpLibOSGBase */
struct MFRecStringToFieldContainerMapPtr :
    public PointerMField<StringToFieldContainerMap *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpBaseFieldContainerFieldMFields \ingroup GrpLibOSGBase */
struct MFUnrecStringToFieldContainerMapPtr :
    public PointerMField<StringToFieldContainerMap *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpBaseFieldContainerFieldMFields \ingroup GrpLibOSGBase */
struct MFWeakStringToFieldContainerMapPtr :
    public PointerMField<StringToFieldContainerMap *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpBaseFieldContainerFieldMFields \ingroup GrpLibOSGBase */
struct MFUncountedStringToFieldContainerMapPtr :
    public PointerMField<StringToFieldContainerMap *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGSTRINGTOFIELDCONTAINERMAPFIELDS_H_ */
