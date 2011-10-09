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


#ifndef _OSGSHADEREXECUTABLECHUNKFIELDS_H_
#define _OSGSHADEREXECUTABLECHUNKFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class ShaderExecutableChunk;

OSG_GEN_CONTAINERPTR(ShaderExecutableChunk);
/*! \ingroup GrpSystemShaderFieldTraits
    \ingroup GrpLibOSGSystem
 */
template <>
struct FieldTraits<ShaderExecutableChunk *, nsOSG> :
    public FieldTraitsFCPtrBase<ShaderExecutableChunk *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<ShaderExecutableChunk *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_SYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<ShaderExecutableChunk *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecShaderExecutableChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderExecutableChunk *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecShaderExecutableChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderExecutableChunk *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakShaderExecutableChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderExecutableChunk *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdShaderExecutableChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderExecutableChunk *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecShaderExecutableChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderExecutableChunk *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecShaderExecutableChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderExecutableChunk *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakShaderExecutableChunkPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderExecutableChunk *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdShaderExecutableChunkPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpSystemShaderFieldSFields */
typedef PointerSField<ShaderExecutableChunk *,
                      RecordedRefCountPolicy, nsOSG  > SFRecShaderExecutableChunkPtr;
/*! \ingroup GrpSystemShaderFieldSFields */
typedef PointerSField<ShaderExecutableChunk *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecShaderExecutableChunkPtr;
/*! \ingroup GrpSystemShaderFieldSFields */
typedef PointerSField<ShaderExecutableChunk *,
                      WeakRefCountPolicy, nsOSG      > SFWeakShaderExecutableChunkPtr;
/*! \ingroup GrpSystemShaderFieldSFields */
typedef PointerSField<ShaderExecutableChunk *,
                      NoRefCountPolicy, nsOSG        > SFUncountedShaderExecutableChunkPtr;


/*! \ingroup GrpSystemShaderFieldMFields */
typedef PointerMField<ShaderExecutableChunk *,
                      RecordedRefCountPolicy, nsOSG  > MFRecShaderExecutableChunkPtr;
/*! \ingroup GrpSystemShaderFieldMFields */
typedef PointerMField<ShaderExecutableChunk *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecShaderExecutableChunkPtr;
/*! \ingroup GrpSystemShaderFieldMFields */
typedef PointerMField<ShaderExecutableChunk *,
                      WeakRefCountPolicy, nsOSG      > MFWeakShaderExecutableChunkPtr;
/*! \ingroup GrpSystemShaderFieldMFields */
typedef PointerMField<ShaderExecutableChunk *,
                      NoRefCountPolicy, nsOSG        > MFUncountedShaderExecutableChunkPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpSystemShaderFieldSFields \ingroup GrpLibOSGSystem */
struct SFRecShaderExecutableChunkPtr : 
    public PointerSField<ShaderExecutableChunk *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpSystemShaderFieldSFields \ingroup GrpLibOSGSystem */
struct SFUnrecShaderExecutableChunkPtr : 
    public PointerSField<ShaderExecutableChunk *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemShaderFieldSFields \ingroup GrpLibOSGSystem */
struct SFWeakShaderExecutableChunkPtr :
    public PointerSField<ShaderExecutableChunk *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpSystemShaderFieldSFields \ingroup GrpLibOSGSystem */
struct SFUncountedShaderExecutableChunkPtr :
    public PointerSField<ShaderExecutableChunk *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpSystemShaderFieldMFields \ingroup GrpLibOSGSystem */
struct MFRecShaderExecutableChunkPtr :
    public PointerMField<ShaderExecutableChunk *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpSystemShaderFieldMFields \ingroup GrpLibOSGSystem */
struct MFUnrecShaderExecutableChunkPtr :
    public PointerMField<ShaderExecutableChunk *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemShaderFieldMFields \ingroup GrpLibOSGSystem */
struct MFWeakShaderExecutableChunkPtr :
    public PointerMField<ShaderExecutableChunk *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpSystemShaderFieldMFields \ingroup GrpLibOSGSystem */
struct MFUncountedShaderExecutableChunkPtr :
    public PointerMField<ShaderExecutableChunk *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGSHADEREXECUTABLECHUNKFIELDS_H_ */
