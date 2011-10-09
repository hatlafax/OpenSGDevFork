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


#ifndef _OSGPOLYGONCHUNKFIELDS_H_
#define _OSGPOLYGONCHUNKFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class PolygonChunk;

OSG_GEN_CONTAINERPTR(PolygonChunk);
/*! \ingroup GrpSystemStateFieldTraits
    \ingroup GrpLibOSGSystem
 */
template <>
struct FieldTraits<PolygonChunk *, nsOSG> :
    public FieldTraitsFCPtrBase<PolygonChunk *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<PolygonChunk *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_SYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<PolygonChunk *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecPolygonChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<PolygonChunk *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecPolygonChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<PolygonChunk *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakPolygonChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<PolygonChunk *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdPolygonChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<PolygonChunk *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecPolygonChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<PolygonChunk *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecPolygonChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<PolygonChunk *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakPolygonChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<PolygonChunk *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdPolygonChunkPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpSystemStateFieldSFields */
typedef PointerSField<PolygonChunk *,
                      RecordedRefCountPolicy, nsOSG  > SFRecPolygonChunkPtr;
/*! \ingroup GrpSystemStateFieldSFields */
typedef PointerSField<PolygonChunk *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecPolygonChunkPtr;
/*! \ingroup GrpSystemStateFieldSFields */
typedef PointerSField<PolygonChunk *,
                      WeakRefCountPolicy, nsOSG      > SFWeakPolygonChunkPtr;
/*! \ingroup GrpSystemStateFieldSFields */
typedef PointerSField<PolygonChunk *,
                      NoRefCountPolicy, nsOSG        > SFUncountedPolygonChunkPtr;


/*! \ingroup GrpSystemStateFieldMFields */
typedef PointerMField<PolygonChunk *,
                      RecordedRefCountPolicy, nsOSG  > MFRecPolygonChunkPtr;
/*! \ingroup GrpSystemStateFieldMFields */
typedef PointerMField<PolygonChunk *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecPolygonChunkPtr;
/*! \ingroup GrpSystemStateFieldMFields */
typedef PointerMField<PolygonChunk *,
                      WeakRefCountPolicy, nsOSG      > MFWeakPolygonChunkPtr;
/*! \ingroup GrpSystemStateFieldMFields */
typedef PointerMField<PolygonChunk *,
                      NoRefCountPolicy, nsOSG        > MFUncountedPolygonChunkPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpSystemStateFieldSFields \ingroup GrpLibOSGSystem */
struct SFRecPolygonChunkPtr : 
    public PointerSField<PolygonChunk *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpSystemStateFieldSFields \ingroup GrpLibOSGSystem */
struct SFUnrecPolygonChunkPtr : 
    public PointerSField<PolygonChunk *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemStateFieldSFields \ingroup GrpLibOSGSystem */
struct SFWeakPolygonChunkPtr :
    public PointerSField<PolygonChunk *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpSystemStateFieldSFields \ingroup GrpLibOSGSystem */
struct SFUncountedPolygonChunkPtr :
    public PointerSField<PolygonChunk *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpSystemStateFieldMFields \ingroup GrpLibOSGSystem */
struct MFRecPolygonChunkPtr :
    public PointerMField<PolygonChunk *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpSystemStateFieldMFields \ingroup GrpLibOSGSystem */
struct MFUnrecPolygonChunkPtr :
    public PointerMField<PolygonChunk *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemStateFieldMFields \ingroup GrpLibOSGSystem */
struct MFWeakPolygonChunkPtr :
    public PointerMField<PolygonChunk *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpSystemStateFieldMFields \ingroup GrpLibOSGSystem */
struct MFUncountedPolygonChunkPtr :
    public PointerMField<PolygonChunk *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGPOLYGONCHUNKFIELDS_H_ */
