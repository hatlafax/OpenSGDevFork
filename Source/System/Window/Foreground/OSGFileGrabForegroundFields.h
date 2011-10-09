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


#ifndef _OSGFILEGRABFOREGROUNDFIELDS_H_
#define _OSGFILEGRABFOREGROUNDFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGWindowDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class FileGrabForeground;

OSG_GEN_CONTAINERPTR(FileGrabForeground);
/*! \ingroup GrpWindowForegroundFieldTraits
    \ingroup GrpLibOSGWindow
 */
template <>
struct FieldTraits<FileGrabForeground *, nsOSG> :
    public FieldTraitsFCPtrBase<FileGrabForeground *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<FileGrabForeground *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_WINDOW_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<FileGrabForeground *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecFileGrabForegroundPtr"; 
}

template<> inline
const Char8 *FieldTraits<FileGrabForeground *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecFileGrabForegroundPtr"; 
}

template<> inline
const Char8 *FieldTraits<FileGrabForeground *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakFileGrabForegroundPtr"; 
}

template<> inline
const Char8 *FieldTraits<FileGrabForeground *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdFileGrabForegroundPtr"; 
}

template<> inline
const Char8 *FieldTraits<FileGrabForeground *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecFileGrabForegroundPtr"; 
}

template<> inline
const Char8 *FieldTraits<FileGrabForeground *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecFileGrabForegroundPtr"; 
}

template<> inline
const Char8 *FieldTraits<FileGrabForeground *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakFileGrabForegroundPtr"; 
}

template<> inline
const Char8 *FieldTraits<FileGrabForeground *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdFileGrabForegroundPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpWindowForegroundFieldSFields */
typedef PointerSField<FileGrabForeground *,
                      RecordedRefCountPolicy, nsOSG  > SFRecFileGrabForegroundPtr;
/*! \ingroup GrpWindowForegroundFieldSFields */
typedef PointerSField<FileGrabForeground *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecFileGrabForegroundPtr;
/*! \ingroup GrpWindowForegroundFieldSFields */
typedef PointerSField<FileGrabForeground *,
                      WeakRefCountPolicy, nsOSG      > SFWeakFileGrabForegroundPtr;
/*! \ingroup GrpWindowForegroundFieldSFields */
typedef PointerSField<FileGrabForeground *,
                      NoRefCountPolicy, nsOSG        > SFUncountedFileGrabForegroundPtr;


/*! \ingroup GrpWindowForegroundFieldMFields */
typedef PointerMField<FileGrabForeground *,
                      RecordedRefCountPolicy, nsOSG  > MFRecFileGrabForegroundPtr;
/*! \ingroup GrpWindowForegroundFieldMFields */
typedef PointerMField<FileGrabForeground *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecFileGrabForegroundPtr;
/*! \ingroup GrpWindowForegroundFieldMFields */
typedef PointerMField<FileGrabForeground *,
                      WeakRefCountPolicy, nsOSG      > MFWeakFileGrabForegroundPtr;
/*! \ingroup GrpWindowForegroundFieldMFields */
typedef PointerMField<FileGrabForeground *,
                      NoRefCountPolicy, nsOSG        > MFUncountedFileGrabForegroundPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpWindowForegroundFieldSFields \ingroup GrpLibOSGWindow */
struct SFRecFileGrabForegroundPtr : 
    public PointerSField<FileGrabForeground *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpWindowForegroundFieldSFields \ingroup GrpLibOSGWindow */
struct SFUnrecFileGrabForegroundPtr : 
    public PointerSField<FileGrabForeground *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpWindowForegroundFieldSFields \ingroup GrpLibOSGWindow */
struct SFWeakFileGrabForegroundPtr :
    public PointerSField<FileGrabForeground *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpWindowForegroundFieldSFields \ingroup GrpLibOSGWindow */
struct SFUncountedFileGrabForegroundPtr :
    public PointerSField<FileGrabForeground *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpWindowForegroundFieldMFields \ingroup GrpLibOSGWindow */
struct MFRecFileGrabForegroundPtr :
    public PointerMField<FileGrabForeground *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpWindowForegroundFieldMFields \ingroup GrpLibOSGWindow */
struct MFUnrecFileGrabForegroundPtr :
    public PointerMField<FileGrabForeground *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpWindowForegroundFieldMFields \ingroup GrpLibOSGWindow */
struct MFWeakFileGrabForegroundPtr :
    public PointerMField<FileGrabForeground *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpWindowForegroundFieldMFields \ingroup GrpLibOSGWindow */
struct MFUncountedFileGrabForegroundPtr :
    public PointerMField<FileGrabForeground *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGFILEGRABFOREGROUNDFIELDS_H_ */
