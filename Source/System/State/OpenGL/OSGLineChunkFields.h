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


#ifndef _OSGLINECHUNKFIELDS_H_
#define _OSGLINECHUNKFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGStateDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class LineChunk;

OSG_GEN_CONTAINERPTR(LineChunk);
/*! \ingroup GrpStateOpenGLFieldTraits
    \ingroup GrpLibOSGState
 */
template <>
struct FieldTraits<LineChunk *, nsOSG> :
    public FieldTraitsFCPtrBase<LineChunk *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<LineChunk *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_STATE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<LineChunk *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecLineChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<LineChunk *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecLineChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<LineChunk *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakLineChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<LineChunk *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdLineChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<LineChunk *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecLineChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<LineChunk *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecLineChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<LineChunk *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakLineChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<LineChunk *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdLineChunkPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpStateOpenGLFieldSFields */
typedef PointerSField<LineChunk *,
                      RecordedRefCountPolicy, nsOSG  > SFRecLineChunkPtr;
/*! \ingroup GrpStateOpenGLFieldSFields */
typedef PointerSField<LineChunk *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecLineChunkPtr;
/*! \ingroup GrpStateOpenGLFieldSFields */
typedef PointerSField<LineChunk *,
                      WeakRefCountPolicy, nsOSG      > SFWeakLineChunkPtr;
/*! \ingroup GrpStateOpenGLFieldSFields */
typedef PointerSField<LineChunk *,
                      NoRefCountPolicy, nsOSG        > SFUncountedLineChunkPtr;


/*! \ingroup GrpStateOpenGLFieldMFields */
typedef PointerMField<LineChunk *,
                      RecordedRefCountPolicy, nsOSG  > MFRecLineChunkPtr;
/*! \ingroup GrpStateOpenGLFieldMFields */
typedef PointerMField<LineChunk *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecLineChunkPtr;
/*! \ingroup GrpStateOpenGLFieldMFields */
typedef PointerMField<LineChunk *,
                      WeakRefCountPolicy, nsOSG      > MFWeakLineChunkPtr;
/*! \ingroup GrpStateOpenGLFieldMFields */
typedef PointerMField<LineChunk *,
                      NoRefCountPolicy, nsOSG        > MFUncountedLineChunkPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpStateOpenGLFieldSFields \ingroup GrpLibOSGState */
struct SFRecLineChunkPtr : 
    public PointerSField<LineChunk *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpStateOpenGLFieldSFields \ingroup GrpLibOSGState */
struct SFUnrecLineChunkPtr : 
    public PointerSField<LineChunk *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpStateOpenGLFieldSFields \ingroup GrpLibOSGState */
struct SFWeakLineChunkPtr :
    public PointerSField<LineChunk *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpStateOpenGLFieldSFields \ingroup GrpLibOSGState */
struct SFUncountedLineChunkPtr :
    public PointerSField<LineChunk *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpStateOpenGLFieldMFields \ingroup GrpLibOSGState */
struct MFRecLineChunkPtr :
    public PointerMField<LineChunk *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpStateOpenGLFieldMFields \ingroup GrpLibOSGState */
struct MFUnrecLineChunkPtr :
    public PointerMField<LineChunk *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpStateOpenGLFieldMFields \ingroup GrpLibOSGState */
struct MFWeakLineChunkPtr :
    public PointerMField<LineChunk *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpStateOpenGLFieldMFields \ingroup GrpLibOSGState */
struct MFUncountedLineChunkPtr :
    public PointerMField<LineChunk *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGLINECHUNKFIELDS_H_ */
