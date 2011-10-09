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


#ifndef _OSGATTACHMENTFIELDS_H_
#define _OSGATTACHMENTFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGBaseDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class Attachment;

OSG_GEN_CONTAINERPTR(Attachment);
/*! \ingroup GrpBaseFieldContainerBaseFieldTraits
    \ingroup GrpLibOSGBase
 */
template <>
struct FieldTraits<Attachment *, nsOSG> :
    public FieldTraitsFCPtrBase<Attachment *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<Attachment *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_BASE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<Attachment *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<Attachment *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<Attachment *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<Attachment *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<Attachment *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<Attachment *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<Attachment *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<Attachment *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdAttachmentPtr"; 
}


/*! \ingroup GrpBaseFieldContainerBaseFieldTraits
 */
template <>
struct FieldTraits<Attachment *, nsOSG + 1> :
    public FieldTraitsFCPtrBase<Attachment *, nsOSG + 1>
{
  private:

  public:
    typedef FieldTraits<Attachment *, nsOSG + 1>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_BASE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);
};

template<> inline
const Char8 *FieldTraits<Attachment *, nsOSG + 1>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecChildAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<Attachment *, nsOSG + 1>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecChildAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<Attachment *, nsOSG + 1>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakChildAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<Attachment *, nsOSG + 1>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdChildAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<Attachment *, nsOSG + 1>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecChildAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<Attachment *, nsOSG + 1>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecChildAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<Attachment *, nsOSG + 1>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakChildAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<Attachment *, nsOSG + 1>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdChildAttachmentPtr"; 
}


/*! \ingroup GrpBaseFieldContainerBaseFieldTraits
 */
template <>
struct FieldTraits<Attachment *, nsOSG + 2> : 
    public FieldTraitsFCPtrBase<Attachment *, nsOSG + 2>
{
  private:

    static  DataType                                _type;

  public:

    static const bool bIsPointerField = true;

    typedef FieldTraits<Attachment *, nsOSG + 2> Self;


    enum             { Convertible = Self::NotConvertible };
    
    static OSG_BASE_DLLMAPPING
                 DataType &getType (void);

    static const Char8    *getSName(void) 
    {
        return "SFParentAttachmentPtr"; 
    }

    static const Char8    *getMName(void) 
    { 
        return "MFParentAttachmentPtr"; 
    }
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpBaseFieldContainerBaseFieldSFields */
typedef PointerSField<Attachment *,
                      RecordedRefCountPolicy, nsOSG  > SFRecAttachmentPtr;
/*! \ingroup GrpBaseFieldContainerBaseFieldSFields */
typedef PointerSField<Attachment *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecAttachmentPtr;
/*! \ingroup GrpBaseFieldContainerBaseFieldSFields */
typedef PointerSField<Attachment *,
                      WeakRefCountPolicy, nsOSG      > SFWeakAttachmentPtr;
/*! \ingroup GrpBaseFieldContainerBaseFieldSFields */
typedef PointerSField<Attachment *,
                      NoRefCountPolicy, nsOSG        > SFUncountedAttachmentPtr;


/*! \ingroup GrpBaseFieldContainerBaseFieldMFields */
typedef PointerMField<Attachment *,
                      RecordedRefCountPolicy, nsOSG  > MFRecAttachmentPtr;
/*! \ingroup GrpBaseFieldContainerBaseFieldMFields */
typedef PointerMField<Attachment *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecAttachmentPtr;
/*! \ingroup GrpBaseFieldContainerBaseFieldMFields */
typedef PointerMField<Attachment *,
                      WeakRefCountPolicy, nsOSG      > MFWeakAttachmentPtr;
/*! \ingroup GrpBaseFieldContainerBaseFieldMFields */
typedef PointerMField<Attachment *,
                      NoRefCountPolicy, nsOSG        > MFUncountedAttachmentPtr;



/*! \ingroup GrpBaseFieldContainerBaseFieldSFields */
typedef ChildPointerSField<
          Attachment *, 
          UnrecordedRefCountPolicy,
          nsOSG + 1             > SFUnrecChildAttachmentPtr;


/*! \ingroup GrpBaseFieldContainerBaseFieldMFields */
typedef ChildPointerMField<
          Attachment *, 
          UnrecordedRefCountPolicy,
          nsOSG + 1             > MFUnrecChildAttachmentPtr;


/*! \ingroup GrpBaseFieldContainerBaseFieldSFields */
typedef ParentPointerSField<
          Attachment *, 
          NoRefCountPolicy,
          nsOSG + 2    > SFParentAttachmentPtr;

/*! \ingroup GrpBaseFieldContainerBaseFieldMFields */
typedef ParentPointerMField<
          Attachment *, 
          NoRefCountPolicy,
          nsOSG + 2    > MFParentAttachmentPtr;



#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldContainerBaseFieldSFields \ingroup GrpLibOSGBase */
struct SFRecAttachmentPtr : 
    public PointerSField<Attachment *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpBaseFieldContainerBaseFieldSFields \ingroup GrpLibOSGBase */
struct SFUnrecAttachmentPtr : 
    public PointerSField<Attachment *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpBaseFieldContainerBaseFieldSFields \ingroup GrpLibOSGBase */
struct SFWeakAttachmentPtr :
    public PointerSField<Attachment *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpBaseFieldContainerBaseFieldSFields \ingroup GrpLibOSGBase */
struct SFUncountedAttachmentPtr :
    public PointerSField<Attachment *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpBaseFieldContainerBaseFieldMFields \ingroup GrpLibOSGBase */
struct MFRecAttachmentPtr :
    public PointerMField<Attachment *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpBaseFieldContainerBaseFieldMFields \ingroup GrpLibOSGBase */
struct MFUnrecAttachmentPtr :
    public PointerMField<Attachment *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpBaseFieldContainerBaseFieldMFields \ingroup GrpLibOSGBase */
struct MFWeakAttachmentPtr :
    public PointerMField<Attachment *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpBaseFieldContainerBaseFieldMFields \ingroup GrpLibOSGBase */
struct MFUncountedAttachmentPtr :
    public PointerMField<Attachment *,
                         NoRefCountPolicy        > {};



/*! \ingroup GrpBaseFieldContainerBaseFieldSFields \ingroup GrpLibOSGBase */
struct SFUnrecChildAttachmentPtr :
    public ChildPointerSField<
        Attachment *, 
        UnrecordedRefCountPolicy,
        nsOSG + 1             > {};


/*! \ingroup GrpBaseFieldContainerBaseFieldMFields \ingroup GrpLibOSGBase */
struct MFUnrecChildAttachmentPtr :
    public ChildPointerMField<
        Attachment *, 
        UnrecordedRefCountPolicy,
        nsOSG + 1             > {};


/*! \ingroup GrpBaseFieldContainerBaseFieldSFields \ingroup GrpLibOSGBase */
struct SFParentAttachmentPtr :
    public ParentPointerSField<
        Attachment *, 
        NoRefCountPolicy,
        nsOSG + 2    > {};

/*! \ingroup GrpBaseFieldContainerBaseFieldMFields \ingroup GrpLibOSGBase */
struct MFParentAttachmentPtr :
    public  ParentPointerMField<
        Attachment *, 
        NoRefCountPolicy,
        nsOSG + 2    > {};


#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGATTACHMENTFIELDS_H_ */
