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


#ifndef _OSGPROGRAMCHUNKFIELDS_H_
#define _OSGPROGRAMCHUNKFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGStateDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class ProgramChunk;

OSG_GEN_CONTAINERPTR(ProgramChunk);
/*! \ingroup GrpStateARBProgramFieldTraits
    \ingroup GrpLibOSGState
 */
template <>
struct FieldTraits<ProgramChunk *, nsOSG> :
    public FieldTraitsFCPtrBase<ProgramChunk *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<ProgramChunk *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_STATE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<ProgramChunk *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecProgramChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<ProgramChunk *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecProgramChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<ProgramChunk *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakProgramChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<ProgramChunk *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdProgramChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<ProgramChunk *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecProgramChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<ProgramChunk *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecProgramChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<ProgramChunk *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakProgramChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<ProgramChunk *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdProgramChunkPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpStateARBProgramFieldSFields */
typedef PointerSField<ProgramChunk *,
                      RecordedRefCountPolicy, nsOSG  > SFRecProgramChunkPtr;
/*! \ingroup GrpStateARBProgramFieldSFields */
typedef PointerSField<ProgramChunk *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecProgramChunkPtr;
/*! \ingroup GrpStateARBProgramFieldSFields */
typedef PointerSField<ProgramChunk *,
                      WeakRefCountPolicy, nsOSG      > SFWeakProgramChunkPtr;
/*! \ingroup GrpStateARBProgramFieldSFields */
typedef PointerSField<ProgramChunk *,
                      NoRefCountPolicy, nsOSG        > SFUncountedProgramChunkPtr;


/*! \ingroup GrpStateARBProgramFieldMFields */
typedef PointerMField<ProgramChunk *,
                      RecordedRefCountPolicy, nsOSG  > MFRecProgramChunkPtr;
/*! \ingroup GrpStateARBProgramFieldMFields */
typedef PointerMField<ProgramChunk *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecProgramChunkPtr;
/*! \ingroup GrpStateARBProgramFieldMFields */
typedef PointerMField<ProgramChunk *,
                      WeakRefCountPolicy, nsOSG      > MFWeakProgramChunkPtr;
/*! \ingroup GrpStateARBProgramFieldMFields */
typedef PointerMField<ProgramChunk *,
                      NoRefCountPolicy, nsOSG        > MFUncountedProgramChunkPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpStateARBProgramFieldSFields \ingroup GrpLibOSGState */
struct SFRecProgramChunkPtr : 
    public PointerSField<ProgramChunk *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpStateARBProgramFieldSFields \ingroup GrpLibOSGState */
struct SFUnrecProgramChunkPtr : 
    public PointerSField<ProgramChunk *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpStateARBProgramFieldSFields \ingroup GrpLibOSGState */
struct SFWeakProgramChunkPtr :
    public PointerSField<ProgramChunk *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpStateARBProgramFieldSFields \ingroup GrpLibOSGState */
struct SFUncountedProgramChunkPtr :
    public PointerSField<ProgramChunk *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpStateARBProgramFieldMFields \ingroup GrpLibOSGState */
struct MFRecProgramChunkPtr :
    public PointerMField<ProgramChunk *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpStateARBProgramFieldMFields \ingroup GrpLibOSGState */
struct MFUnrecProgramChunkPtr :
    public PointerMField<ProgramChunk *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpStateARBProgramFieldMFields \ingroup GrpLibOSGState */
struct MFWeakProgramChunkPtr :
    public PointerMField<ProgramChunk *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpStateARBProgramFieldMFields \ingroup GrpLibOSGState */
struct MFUncountedProgramChunkPtr :
    public PointerMField<ProgramChunk *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGPROGRAMCHUNKFIELDS_H_ */
