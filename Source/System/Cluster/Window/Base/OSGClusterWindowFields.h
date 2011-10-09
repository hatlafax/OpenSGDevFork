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


#ifndef _OSGCLUSTERWINDOWFIELDS_H_
#define _OSGCLUSTERWINDOWFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGClusterDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class ClusterWindow;

OSG_GEN_CONTAINERPTR(ClusterWindow);
/*! \ingroup GrpClusterWindowFieldTraits
    \ingroup GrpLibOSGCluster
 */
template <>
struct FieldTraits<ClusterWindow *, nsOSG> :
    public FieldTraitsFCPtrBase<ClusterWindow *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<ClusterWindow *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CLUSTER_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<ClusterWindow *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecClusterWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<ClusterWindow *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecClusterWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<ClusterWindow *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakClusterWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<ClusterWindow *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdClusterWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<ClusterWindow *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecClusterWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<ClusterWindow *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecClusterWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<ClusterWindow *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakClusterWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<ClusterWindow *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdClusterWindowPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpClusterWindowFieldSFields */
typedef PointerSField<ClusterWindow *,
                      RecordedRefCountPolicy, nsOSG  > SFRecClusterWindowPtr;
/*! \ingroup GrpClusterWindowFieldSFields */
typedef PointerSField<ClusterWindow *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecClusterWindowPtr;
/*! \ingroup GrpClusterWindowFieldSFields */
typedef PointerSField<ClusterWindow *,
                      WeakRefCountPolicy, nsOSG      > SFWeakClusterWindowPtr;
/*! \ingroup GrpClusterWindowFieldSFields */
typedef PointerSField<ClusterWindow *,
                      NoRefCountPolicy, nsOSG        > SFUncountedClusterWindowPtr;


/*! \ingroup GrpClusterWindowFieldMFields */
typedef PointerMField<ClusterWindow *,
                      RecordedRefCountPolicy, nsOSG  > MFRecClusterWindowPtr;
/*! \ingroup GrpClusterWindowFieldMFields */
typedef PointerMField<ClusterWindow *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecClusterWindowPtr;
/*! \ingroup GrpClusterWindowFieldMFields */
typedef PointerMField<ClusterWindow *,
                      WeakRefCountPolicy, nsOSG      > MFWeakClusterWindowPtr;
/*! \ingroup GrpClusterWindowFieldMFields */
typedef PointerMField<ClusterWindow *,
                      NoRefCountPolicy, nsOSG        > MFUncountedClusterWindowPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpClusterWindowFieldSFields \ingroup GrpLibOSGCluster */
struct SFRecClusterWindowPtr : 
    public PointerSField<ClusterWindow *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpClusterWindowFieldSFields \ingroup GrpLibOSGCluster */
struct SFUnrecClusterWindowPtr : 
    public PointerSField<ClusterWindow *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpClusterWindowFieldSFields \ingroup GrpLibOSGCluster */
struct SFWeakClusterWindowPtr :
    public PointerSField<ClusterWindow *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpClusterWindowFieldSFields \ingroup GrpLibOSGCluster */
struct SFUncountedClusterWindowPtr :
    public PointerSField<ClusterWindow *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpClusterWindowFieldMFields \ingroup GrpLibOSGCluster */
struct MFRecClusterWindowPtr :
    public PointerMField<ClusterWindow *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpClusterWindowFieldMFields \ingroup GrpLibOSGCluster */
struct MFUnrecClusterWindowPtr :
    public PointerMField<ClusterWindow *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpClusterWindowFieldMFields \ingroup GrpLibOSGCluster */
struct MFWeakClusterWindowPtr :
    public PointerMField<ClusterWindow *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpClusterWindowFieldMFields \ingroup GrpLibOSGCluster */
struct MFUncountedClusterWindowPtr :
    public PointerMField<ClusterWindow *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGCLUSTERWINDOWFIELDS_H_ */
