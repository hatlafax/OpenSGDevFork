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


#ifndef _OSGSHADERPROGRAMFIELDS_H_
#define _OSGSHADERPROGRAMFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class ShaderProgram;

OSG_GEN_CONTAINERPTR(ShaderProgram);
/*! \ingroup GrpSystemShaderFieldTraits
    \ingroup GrpLibOSGSystem
 */
template <>
struct FieldTraits<ShaderProgram *, nsOSG> :
    public FieldTraitsFCPtrBase<ShaderProgram *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<ShaderProgram *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_SYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<ShaderProgram *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecShaderProgramPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderProgram *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecShaderProgramPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderProgram *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakShaderProgramPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderProgram *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdShaderProgramPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderProgram *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecShaderProgramPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderProgram *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecShaderProgramPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderProgram *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakShaderProgramPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderProgram *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdShaderProgramPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpSystemShaderFieldSFields */
typedef PointerSField<ShaderProgram *,
                      RecordedRefCountPolicy, nsOSG  > SFRecShaderProgramPtr;
/*! \ingroup GrpSystemShaderFieldSFields */
typedef PointerSField<ShaderProgram *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecShaderProgramPtr;
/*! \ingroup GrpSystemShaderFieldSFields */
typedef PointerSField<ShaderProgram *,
                      WeakRefCountPolicy, nsOSG      > SFWeakShaderProgramPtr;
/*! \ingroup GrpSystemShaderFieldSFields */
typedef PointerSField<ShaderProgram *,
                      NoRefCountPolicy, nsOSG        > SFUncountedShaderProgramPtr;


/*! \ingroup GrpSystemShaderFieldMFields */
typedef PointerMField<ShaderProgram *,
                      RecordedRefCountPolicy, nsOSG  > MFRecShaderProgramPtr;
/*! \ingroup GrpSystemShaderFieldMFields */
typedef PointerMField<ShaderProgram *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecShaderProgramPtr;
/*! \ingroup GrpSystemShaderFieldMFields */
typedef PointerMField<ShaderProgram *,
                      WeakRefCountPolicy, nsOSG      > MFWeakShaderProgramPtr;
/*! \ingroup GrpSystemShaderFieldMFields */
typedef PointerMField<ShaderProgram *,
                      NoRefCountPolicy, nsOSG        > MFUncountedShaderProgramPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpSystemShaderFieldSFields \ingroup GrpLibOSGSystem */
struct SFRecShaderProgramPtr : 
    public PointerSField<ShaderProgram *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpSystemShaderFieldSFields \ingroup GrpLibOSGSystem */
struct SFUnrecShaderProgramPtr : 
    public PointerSField<ShaderProgram *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemShaderFieldSFields \ingroup GrpLibOSGSystem */
struct SFWeakShaderProgramPtr :
    public PointerSField<ShaderProgram *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpSystemShaderFieldSFields \ingroup GrpLibOSGSystem */
struct SFUncountedShaderProgramPtr :
    public PointerSField<ShaderProgram *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpSystemShaderFieldMFields \ingroup GrpLibOSGSystem */
struct MFRecShaderProgramPtr :
    public PointerMField<ShaderProgram *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpSystemShaderFieldMFields \ingroup GrpLibOSGSystem */
struct MFUnrecShaderProgramPtr :
    public PointerMField<ShaderProgram *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemShaderFieldMFields \ingroup GrpLibOSGSystem */
struct MFWeakShaderProgramPtr :
    public PointerMField<ShaderProgram *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpSystemShaderFieldMFields \ingroup GrpLibOSGSystem */
struct MFUncountedShaderProgramPtr :
    public PointerMField<ShaderProgram *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGSHADERPROGRAMFIELDS_H_ */
