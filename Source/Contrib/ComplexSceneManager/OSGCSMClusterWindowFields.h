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


#ifndef _OSGCSMCLUSTERWINDOWFIELDS_H_
#define _OSGCSMCLUSTERWINDOWFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribCSMDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class CSMClusterWindow;

OSG_GEN_CONTAINERPTR(CSMClusterWindow);
/*! \ingroup GrpContribCSMFieldTraits
    \ingroup GrpLibOSGContribCSM
 */
template <>
struct FieldTraits<CSMClusterWindow *, nsOSG> :
    public FieldTraitsFCPtrBase<CSMClusterWindow *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<CSMClusterWindow *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBCSM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<CSMClusterWindow *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecCSMClusterWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<CSMClusterWindow *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecCSMClusterWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<CSMClusterWindow *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakCSMClusterWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<CSMClusterWindow *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdCSMClusterWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<CSMClusterWindow *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecCSMClusterWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<CSMClusterWindow *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecCSMClusterWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<CSMClusterWindow *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakCSMClusterWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<CSMClusterWindow *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdCSMClusterWindowPtr"; 
}


/*! \ingroup GrpContribCSMFieldTraits
 */
template <>
struct FieldTraits<CSMClusterWindow *, nsOSG + 1> : 
    public FieldTraitsFCPtrBase<CSMClusterWindow *, nsOSG + 1>
{
  private:

    static  DataType                                _type;

  public:

    static const bool bIsPointerField = true;

    typedef FieldTraits<CSMClusterWindow *, nsOSG + 1> Self;


    enum             { Convertible = Self::NotConvertible };
    
    static OSG_CONTRIBCSM_DLLMAPPING
                 DataType &getType (void);

    static const Char8    *getSName(void) 
    {
        return "SFParentCSMClusterWindowPtr"; 
    }

    static const Char8    *getMName(void) 
    { 
        return "MFParentCSMClusterWindowPtr"; 
    }
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribCSMFieldSFields */
typedef PointerSField<CSMClusterWindow *,
                      RecordedRefCountPolicy, nsOSG  > SFRecCSMClusterWindowPtr;
/*! \ingroup GrpContribCSMFieldSFields */
typedef PointerSField<CSMClusterWindow *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecCSMClusterWindowPtr;
/*! \ingroup GrpContribCSMFieldSFields */
typedef PointerSField<CSMClusterWindow *,
                      WeakRefCountPolicy, nsOSG      > SFWeakCSMClusterWindowPtr;
/*! \ingroup GrpContribCSMFieldSFields */
typedef PointerSField<CSMClusterWindow *,
                      NoRefCountPolicy, nsOSG        > SFUncountedCSMClusterWindowPtr;


/*! \ingroup GrpContribCSMFieldMFields */
typedef PointerMField<CSMClusterWindow *,
                      RecordedRefCountPolicy, nsOSG  > MFRecCSMClusterWindowPtr;
/*! \ingroup GrpContribCSMFieldMFields */
typedef PointerMField<CSMClusterWindow *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecCSMClusterWindowPtr;
/*! \ingroup GrpContribCSMFieldMFields */
typedef PointerMField<CSMClusterWindow *,
                      WeakRefCountPolicy, nsOSG      > MFWeakCSMClusterWindowPtr;
/*! \ingroup GrpContribCSMFieldMFields */
typedef PointerMField<CSMClusterWindow *,
                      NoRefCountPolicy, nsOSG        > MFUncountedCSMClusterWindowPtr;



/*! \ingroup GrpContribCSMFieldSFields */
typedef ParentPointerSField<
          CSMClusterWindow *, 
          NoRefCountPolicy,
          nsOSG + 1    > SFParentCSMClusterWindowPtr;


#else // these are the doxygen hacks

/*! \ingroup GrpContribCSMFieldSFields \ingroup GrpLibOSGContribCSM */
struct SFRecCSMClusterWindowPtr : 
    public PointerSField<CSMClusterWindow *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribCSMFieldSFields \ingroup GrpLibOSGContribCSM */
struct SFUnrecCSMClusterWindowPtr : 
    public PointerSField<CSMClusterWindow *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribCSMFieldSFields \ingroup GrpLibOSGContribCSM */
struct SFWeakCSMClusterWindowPtr :
    public PointerSField<CSMClusterWindow *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribCSMFieldSFields \ingroup GrpLibOSGContribCSM */
struct SFUncountedCSMClusterWindowPtr :
    public PointerSField<CSMClusterWindow *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribCSMFieldMFields \ingroup GrpLibOSGContribCSM */
struct MFRecCSMClusterWindowPtr :
    public PointerMField<CSMClusterWindow *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribCSMFieldMFields \ingroup GrpLibOSGContribCSM */
struct MFUnrecCSMClusterWindowPtr :
    public PointerMField<CSMClusterWindow *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribCSMFieldMFields \ingroup GrpLibOSGContribCSM */
struct MFWeakCSMClusterWindowPtr :
    public PointerMField<CSMClusterWindow *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribCSMFieldMFields \ingroup GrpLibOSGContribCSM */
struct MFUncountedCSMClusterWindowPtr :
    public PointerMField<CSMClusterWindow *,
                         NoRefCountPolicy        > {};



/*! \ingroup GrpContribCSMFieldSFields \ingroup GrpLibOSGContribCSM */
struct SFParentCSMClusterWindowPtr :
    public ParentPointerSField<
        CSMClusterWindow *, 
        NoRefCountPolicy,
        nsOSG + 1    > {};

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGCSMCLUSTERWINDOWFIELDS_H_ */
