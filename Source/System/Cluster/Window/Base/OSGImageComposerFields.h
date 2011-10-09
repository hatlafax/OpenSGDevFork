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


#ifndef _OSGIMAGECOMPOSERFIELDS_H_
#define _OSGIMAGECOMPOSERFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGClusterDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class ImageComposer;

OSG_GEN_CONTAINERPTR(ImageComposer);
/*! \ingroup GrpClusterWindowFieldTraits
    \ingroup GrpLibOSGCluster
 */
template <>
struct FieldTraits<ImageComposer *, nsOSG> :
    public FieldTraitsFCPtrBase<ImageComposer *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<ImageComposer *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CLUSTER_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<ImageComposer *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecImageComposerPtr"; 
}

template<> inline
const Char8 *FieldTraits<ImageComposer *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecImageComposerPtr"; 
}

template<> inline
const Char8 *FieldTraits<ImageComposer *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakImageComposerPtr"; 
}

template<> inline
const Char8 *FieldTraits<ImageComposer *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdImageComposerPtr"; 
}

template<> inline
const Char8 *FieldTraits<ImageComposer *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecImageComposerPtr"; 
}

template<> inline
const Char8 *FieldTraits<ImageComposer *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecImageComposerPtr"; 
}

template<> inline
const Char8 *FieldTraits<ImageComposer *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakImageComposerPtr"; 
}

template<> inline
const Char8 *FieldTraits<ImageComposer *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdImageComposerPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpClusterWindowFieldSFields */
typedef PointerSField<ImageComposer *,
                      RecordedRefCountPolicy, nsOSG  > SFRecImageComposerPtr;
/*! \ingroup GrpClusterWindowFieldSFields */
typedef PointerSField<ImageComposer *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecImageComposerPtr;
/*! \ingroup GrpClusterWindowFieldSFields */
typedef PointerSField<ImageComposer *,
                      WeakRefCountPolicy, nsOSG      > SFWeakImageComposerPtr;
/*! \ingroup GrpClusterWindowFieldSFields */
typedef PointerSField<ImageComposer *,
                      NoRefCountPolicy, nsOSG        > SFUncountedImageComposerPtr;


/*! \ingroup GrpClusterWindowFieldMFields */
typedef PointerMField<ImageComposer *,
                      RecordedRefCountPolicy, nsOSG  > MFRecImageComposerPtr;
/*! \ingroup GrpClusterWindowFieldMFields */
typedef PointerMField<ImageComposer *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecImageComposerPtr;
/*! \ingroup GrpClusterWindowFieldMFields */
typedef PointerMField<ImageComposer *,
                      WeakRefCountPolicy, nsOSG      > MFWeakImageComposerPtr;
/*! \ingroup GrpClusterWindowFieldMFields */
typedef PointerMField<ImageComposer *,
                      NoRefCountPolicy, nsOSG        > MFUncountedImageComposerPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpClusterWindowFieldSFields \ingroup GrpLibOSGCluster */
struct SFRecImageComposerPtr : 
    public PointerSField<ImageComposer *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpClusterWindowFieldSFields \ingroup GrpLibOSGCluster */
struct SFUnrecImageComposerPtr : 
    public PointerSField<ImageComposer *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpClusterWindowFieldSFields \ingroup GrpLibOSGCluster */
struct SFWeakImageComposerPtr :
    public PointerSField<ImageComposer *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpClusterWindowFieldSFields \ingroup GrpLibOSGCluster */
struct SFUncountedImageComposerPtr :
    public PointerSField<ImageComposer *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpClusterWindowFieldMFields \ingroup GrpLibOSGCluster */
struct MFRecImageComposerPtr :
    public PointerMField<ImageComposer *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpClusterWindowFieldMFields \ingroup GrpLibOSGCluster */
struct MFUnrecImageComposerPtr :
    public PointerMField<ImageComposer *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpClusterWindowFieldMFields \ingroup GrpLibOSGCluster */
struct MFWeakImageComposerPtr :
    public PointerMField<ImageComposer *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpClusterWindowFieldMFields \ingroup GrpLibOSGCluster */
struct MFUncountedImageComposerPtr :
    public PointerMField<ImageComposer *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGIMAGECOMPOSERFIELDS_H_ */
