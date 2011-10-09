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


#ifndef _OSGSHADERPROGRAMCHUNKFIELDS_H_
#define _OSGSHADERPROGRAMCHUNKFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class ShaderProgramChunk;

OSG_GEN_CONTAINERPTR(ShaderProgramChunk);
/*! \ingroup GrpSystemShaderFieldTraits
    \ingroup GrpLibOSGSystem
 */
template <>
struct FieldTraits<ShaderProgramChunk *, nsOSG> :
    public FieldTraitsFCPtrBase<ShaderProgramChunk *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<ShaderProgramChunk *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_SYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<ShaderProgramChunk *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecShaderProgramChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderProgramChunk *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecShaderProgramChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderProgramChunk *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakShaderProgramChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderProgramChunk *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdShaderProgramChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderProgramChunk *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecShaderProgramChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderProgramChunk *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecShaderProgramChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderProgramChunk *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakShaderProgramChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderProgramChunk *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdShaderProgramChunkPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpSystemShaderFieldSFields */
typedef PointerSField<ShaderProgramChunk *,
                      RecordedRefCountPolicy, nsOSG  > SFRecShaderProgramChunkPtr;
/*! \ingroup GrpSystemShaderFieldSFields */
typedef PointerSField<ShaderProgramChunk *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecShaderProgramChunkPtr;
/*! \ingroup GrpSystemShaderFieldSFields */
typedef PointerSField<ShaderProgramChunk *,
                      WeakRefCountPolicy, nsOSG      > SFWeakShaderProgramChunkPtr;
/*! \ingroup GrpSystemShaderFieldSFields */
typedef PointerSField<ShaderProgramChunk *,
                      NoRefCountPolicy, nsOSG        > SFUncountedShaderProgramChunkPtr;


/*! \ingroup GrpSystemShaderFieldMFields */
typedef PointerMField<ShaderProgramChunk *,
                      RecordedRefCountPolicy, nsOSG  > MFRecShaderProgramChunkPtr;
/*! \ingroup GrpSystemShaderFieldMFields */
typedef PointerMField<ShaderProgramChunk *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecShaderProgramChunkPtr;
/*! \ingroup GrpSystemShaderFieldMFields */
typedef PointerMField<ShaderProgramChunk *,
                      WeakRefCountPolicy, nsOSG      > MFWeakShaderProgramChunkPtr;
/*! \ingroup GrpSystemShaderFieldMFields */
typedef PointerMField<ShaderProgramChunk *,
                      NoRefCountPolicy, nsOSG        > MFUncountedShaderProgramChunkPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpSystemShaderFieldSFields \ingroup GrpLibOSGSystem */
struct SFRecShaderProgramChunkPtr : 
    public PointerSField<ShaderProgramChunk *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpSystemShaderFieldSFields \ingroup GrpLibOSGSystem */
struct SFUnrecShaderProgramChunkPtr : 
    public PointerSField<ShaderProgramChunk *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemShaderFieldSFields \ingroup GrpLibOSGSystem */
struct SFWeakShaderProgramChunkPtr :
    public PointerSField<ShaderProgramChunk *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpSystemShaderFieldSFields \ingroup GrpLibOSGSystem */
struct SFUncountedShaderProgramChunkPtr :
    public PointerSField<ShaderProgramChunk *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpSystemShaderFieldMFields \ingroup GrpLibOSGSystem */
struct MFRecShaderProgramChunkPtr :
    public PointerMField<ShaderProgramChunk *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpSystemShaderFieldMFields \ingroup GrpLibOSGSystem */
struct MFUnrecShaderProgramChunkPtr :
    public PointerMField<ShaderProgramChunk *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemShaderFieldMFields \ingroup GrpLibOSGSystem */
struct MFWeakShaderProgramChunkPtr :
    public PointerMField<ShaderProgramChunk *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpSystemShaderFieldMFields \ingroup GrpLibOSGSystem */
struct MFUncountedShaderProgramChunkPtr :
    public PointerMField<ShaderProgramChunk *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGSHADERPROGRAMCHUNKFIELDS_H_ */
