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


#ifndef _OSGTEXGENCHUNKFIELDS_H_
#define _OSGTEXGENCHUNKFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGStateDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class TexGenChunk;

OSG_GEN_CONTAINERPTR(TexGenChunk);
/*! \ingroup GrpStateOpenGLFieldTraits
    \ingroup GrpLibOSGState
 */
template <>
struct FieldTraits<TexGenChunk *, nsOSG> :
    public FieldTraitsFCPtrBase<TexGenChunk *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<TexGenChunk *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_STATE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<TexGenChunk *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecTexGenChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<TexGenChunk *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecTexGenChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<TexGenChunk *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakTexGenChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<TexGenChunk *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdTexGenChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<TexGenChunk *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecTexGenChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<TexGenChunk *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecTexGenChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<TexGenChunk *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakTexGenChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<TexGenChunk *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdTexGenChunkPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpStateOpenGLFieldSFields */
typedef PointerSField<TexGenChunk *,
                      RecordedRefCountPolicy, nsOSG  > SFRecTexGenChunkPtr;
/*! \ingroup GrpStateOpenGLFieldSFields */
typedef PointerSField<TexGenChunk *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecTexGenChunkPtr;
/*! \ingroup GrpStateOpenGLFieldSFields */
typedef PointerSField<TexGenChunk *,
                      WeakRefCountPolicy, nsOSG      > SFWeakTexGenChunkPtr;
/*! \ingroup GrpStateOpenGLFieldSFields */
typedef PointerSField<TexGenChunk *,
                      NoRefCountPolicy, nsOSG        > SFUncountedTexGenChunkPtr;


/*! \ingroup GrpStateOpenGLFieldMFields */
typedef PointerMField<TexGenChunk *,
                      RecordedRefCountPolicy, nsOSG  > MFRecTexGenChunkPtr;
/*! \ingroup GrpStateOpenGLFieldMFields */
typedef PointerMField<TexGenChunk *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecTexGenChunkPtr;
/*! \ingroup GrpStateOpenGLFieldMFields */
typedef PointerMField<TexGenChunk *,
                      WeakRefCountPolicy, nsOSG      > MFWeakTexGenChunkPtr;
/*! \ingroup GrpStateOpenGLFieldMFields */
typedef PointerMField<TexGenChunk *,
                      NoRefCountPolicy, nsOSG        > MFUncountedTexGenChunkPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpStateOpenGLFieldSFields \ingroup GrpLibOSGState */
struct SFRecTexGenChunkPtr : 
    public PointerSField<TexGenChunk *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpStateOpenGLFieldSFields \ingroup GrpLibOSGState */
struct SFUnrecTexGenChunkPtr : 
    public PointerSField<TexGenChunk *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpStateOpenGLFieldSFields \ingroup GrpLibOSGState */
struct SFWeakTexGenChunkPtr :
    public PointerSField<TexGenChunk *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpStateOpenGLFieldSFields \ingroup GrpLibOSGState */
struct SFUncountedTexGenChunkPtr :
    public PointerSField<TexGenChunk *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpStateOpenGLFieldMFields \ingroup GrpLibOSGState */
struct MFRecTexGenChunkPtr :
    public PointerMField<TexGenChunk *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpStateOpenGLFieldMFields \ingroup GrpLibOSGState */
struct MFUnrecTexGenChunkPtr :
    public PointerMField<TexGenChunk *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpStateOpenGLFieldMFields \ingroup GrpLibOSGState */
struct MFWeakTexGenChunkPtr :
    public PointerMField<TexGenChunk *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpStateOpenGLFieldMFields \ingroup GrpLibOSGState */
struct MFUncountedTexGenChunkPtr :
    public PointerMField<TexGenChunk *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGTEXGENCHUNKFIELDS_H_ */
