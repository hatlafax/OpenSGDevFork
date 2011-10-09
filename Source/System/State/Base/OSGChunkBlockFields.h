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


#ifndef _OSGCHUNKBLOCKFIELDS_H_
#define _OSGCHUNKBLOCKFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class ChunkBlock;

OSG_GEN_CONTAINERPTR(ChunkBlock);
/*! \ingroup GrpSystemFieldTraits
    \ingroup GrpLibOSGSystem
 */
template <>
struct FieldTraits<ChunkBlock *, nsOSG> :
    public FieldTraitsFCPtrBase<ChunkBlock *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<ChunkBlock *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_SYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<ChunkBlock *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecChunkBlockPtr"; 
}

template<> inline
const Char8 *FieldTraits<ChunkBlock *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecChunkBlockPtr"; 
}

template<> inline
const Char8 *FieldTraits<ChunkBlock *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakChunkBlockPtr"; 
}

template<> inline
const Char8 *FieldTraits<ChunkBlock *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdChunkBlockPtr"; 
}

template<> inline
const Char8 *FieldTraits<ChunkBlock *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecChunkBlockPtr"; 
}

template<> inline
const Char8 *FieldTraits<ChunkBlock *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecChunkBlockPtr"; 
}

template<> inline
const Char8 *FieldTraits<ChunkBlock *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakChunkBlockPtr"; 
}

template<> inline
const Char8 *FieldTraits<ChunkBlock *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdChunkBlockPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpSystemFieldSFields */
typedef PointerSField<ChunkBlock *,
                      RecordedRefCountPolicy, nsOSG  > SFRecChunkBlockPtr;
/*! \ingroup GrpSystemFieldSFields */
typedef PointerSField<ChunkBlock *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecChunkBlockPtr;
/*! \ingroup GrpSystemFieldSFields */
typedef PointerSField<ChunkBlock *,
                      WeakRefCountPolicy, nsOSG      > SFWeakChunkBlockPtr;
/*! \ingroup GrpSystemFieldSFields */
typedef PointerSField<ChunkBlock *,
                      NoRefCountPolicy, nsOSG        > SFUncountedChunkBlockPtr;


/*! \ingroup GrpSystemFieldMFields */
typedef PointerMField<ChunkBlock *,
                      RecordedRefCountPolicy, nsOSG  > MFRecChunkBlockPtr;
/*! \ingroup GrpSystemFieldMFields */
typedef PointerMField<ChunkBlock *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecChunkBlockPtr;
/*! \ingroup GrpSystemFieldMFields */
typedef PointerMField<ChunkBlock *,
                      WeakRefCountPolicy, nsOSG      > MFWeakChunkBlockPtr;
/*! \ingroup GrpSystemFieldMFields */
typedef PointerMField<ChunkBlock *,
                      NoRefCountPolicy, nsOSG        > MFUncountedChunkBlockPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpSystemFieldSFields \ingroup GrpLibOSGSystem */
struct SFRecChunkBlockPtr : 
    public PointerSField<ChunkBlock *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpSystemFieldSFields \ingroup GrpLibOSGSystem */
struct SFUnrecChunkBlockPtr : 
    public PointerSField<ChunkBlock *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemFieldSFields \ingroup GrpLibOSGSystem */
struct SFWeakChunkBlockPtr :
    public PointerSField<ChunkBlock *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpSystemFieldSFields \ingroup GrpLibOSGSystem */
struct SFUncountedChunkBlockPtr :
    public PointerSField<ChunkBlock *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpSystemFieldMFields \ingroup GrpLibOSGSystem */
struct MFRecChunkBlockPtr :
    public PointerMField<ChunkBlock *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpSystemFieldMFields \ingroup GrpLibOSGSystem */
struct MFUnrecChunkBlockPtr :
    public PointerMField<ChunkBlock *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemFieldMFields \ingroup GrpLibOSGSystem */
struct MFWeakChunkBlockPtr :
    public PointerMField<ChunkBlock *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpSystemFieldMFields \ingroup GrpLibOSGSystem */
struct MFUncountedChunkBlockPtr :
    public PointerMField<ChunkBlock *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGCHUNKBLOCKFIELDS_H_ */
