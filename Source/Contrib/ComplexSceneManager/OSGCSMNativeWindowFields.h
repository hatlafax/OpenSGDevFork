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


#ifndef _OSGCSMNATIVEWINDOWFIELDS_H_
#define _OSGCSMNATIVEWINDOWFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribCSMDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class CSMNativeWindow;

OSG_GEN_CONTAINERPTR(CSMNativeWindow);
/*! \ingroup GrpContribCSMFieldTraits
    \ingroup GrpLibOSGContribCSM
 */
template <>
struct FieldTraits<CSMNativeWindow *, nsOSG> :
    public FieldTraitsFCPtrBase<CSMNativeWindow *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<CSMNativeWindow *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBCSM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<CSMNativeWindow *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecCSMNativeWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<CSMNativeWindow *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecCSMNativeWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<CSMNativeWindow *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakCSMNativeWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<CSMNativeWindow *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdCSMNativeWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<CSMNativeWindow *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecCSMNativeWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<CSMNativeWindow *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecCSMNativeWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<CSMNativeWindow *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakCSMNativeWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<CSMNativeWindow *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdCSMNativeWindowPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribCSMFieldSFields */
typedef PointerSField<CSMNativeWindow *,
                      RecordedRefCountPolicy, nsOSG  > SFRecCSMNativeWindowPtr;
/*! \ingroup GrpContribCSMFieldSFields */
typedef PointerSField<CSMNativeWindow *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecCSMNativeWindowPtr;
/*! \ingroup GrpContribCSMFieldSFields */
typedef PointerSField<CSMNativeWindow *,
                      WeakRefCountPolicy, nsOSG      > SFWeakCSMNativeWindowPtr;
/*! \ingroup GrpContribCSMFieldSFields */
typedef PointerSField<CSMNativeWindow *,
                      NoRefCountPolicy, nsOSG        > SFUncountedCSMNativeWindowPtr;


/*! \ingroup GrpContribCSMFieldMFields */
typedef PointerMField<CSMNativeWindow *,
                      RecordedRefCountPolicy, nsOSG  > MFRecCSMNativeWindowPtr;
/*! \ingroup GrpContribCSMFieldMFields */
typedef PointerMField<CSMNativeWindow *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecCSMNativeWindowPtr;
/*! \ingroup GrpContribCSMFieldMFields */
typedef PointerMField<CSMNativeWindow *,
                      WeakRefCountPolicy, nsOSG      > MFWeakCSMNativeWindowPtr;
/*! \ingroup GrpContribCSMFieldMFields */
typedef PointerMField<CSMNativeWindow *,
                      NoRefCountPolicy, nsOSG        > MFUncountedCSMNativeWindowPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribCSMFieldSFields \ingroup GrpLibOSGContribCSM */
struct SFRecCSMNativeWindowPtr : 
    public PointerSField<CSMNativeWindow *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribCSMFieldSFields \ingroup GrpLibOSGContribCSM */
struct SFUnrecCSMNativeWindowPtr : 
    public PointerSField<CSMNativeWindow *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribCSMFieldSFields \ingroup GrpLibOSGContribCSM */
struct SFWeakCSMNativeWindowPtr :
    public PointerSField<CSMNativeWindow *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribCSMFieldSFields \ingroup GrpLibOSGContribCSM */
struct SFUncountedCSMNativeWindowPtr :
    public PointerSField<CSMNativeWindow *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribCSMFieldMFields \ingroup GrpLibOSGContribCSM */
struct MFRecCSMNativeWindowPtr :
    public PointerMField<CSMNativeWindow *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribCSMFieldMFields \ingroup GrpLibOSGContribCSM */
struct MFUnrecCSMNativeWindowPtr :
    public PointerMField<CSMNativeWindow *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribCSMFieldMFields \ingroup GrpLibOSGContribCSM */
struct MFWeakCSMNativeWindowPtr :
    public PointerMField<CSMNativeWindow *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribCSMFieldMFields \ingroup GrpLibOSGContribCSM */
struct MFUncountedCSMNativeWindowPtr :
    public PointerMField<CSMNativeWindow *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGCSMNATIVEWINDOWFIELDS_H_ */
