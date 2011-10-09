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


#ifndef _OSGSHADERVARIABLEMMATRIXFIELDS_H_
#define _OSGSHADERVARIABLEMMATRIXFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class ShaderVariableMMatrix;

OSG_GEN_CONTAINERPTR(ShaderVariableMMatrix);
/*! \ingroup GrpSystemShaderFieldTraits
    \ingroup GrpLibOSGSystem
 */
template <>
struct FieldTraits<ShaderVariableMMatrix *, nsOSG> :
    public FieldTraitsFCPtrBase<ShaderVariableMMatrix *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<ShaderVariableMMatrix *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_SYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<ShaderVariableMMatrix *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecShaderVariableMMatrixPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderVariableMMatrix *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecShaderVariableMMatrixPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderVariableMMatrix *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakShaderVariableMMatrixPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderVariableMMatrix *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdShaderVariableMMatrixPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderVariableMMatrix *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecShaderVariableMMatrixPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderVariableMMatrix *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecShaderVariableMMatrixPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderVariableMMatrix *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakShaderVariableMMatrixPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderVariableMMatrix *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdShaderVariableMMatrixPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpSystemShaderFieldSFields */
typedef PointerSField<ShaderVariableMMatrix *,
                      RecordedRefCountPolicy, nsOSG  > SFRecShaderVariableMMatrixPtr;
/*! \ingroup GrpSystemShaderFieldSFields */
typedef PointerSField<ShaderVariableMMatrix *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecShaderVariableMMatrixPtr;
/*! \ingroup GrpSystemShaderFieldSFields */
typedef PointerSField<ShaderVariableMMatrix *,
                      WeakRefCountPolicy, nsOSG      > SFWeakShaderVariableMMatrixPtr;
/*! \ingroup GrpSystemShaderFieldSFields */
typedef PointerSField<ShaderVariableMMatrix *,
                      NoRefCountPolicy, nsOSG        > SFUncountedShaderVariableMMatrixPtr;


/*! \ingroup GrpSystemShaderFieldMFields */
typedef PointerMField<ShaderVariableMMatrix *,
                      RecordedRefCountPolicy, nsOSG  > MFRecShaderVariableMMatrixPtr;
/*! \ingroup GrpSystemShaderFieldMFields */
typedef PointerMField<ShaderVariableMMatrix *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecShaderVariableMMatrixPtr;
/*! \ingroup GrpSystemShaderFieldMFields */
typedef PointerMField<ShaderVariableMMatrix *,
                      WeakRefCountPolicy, nsOSG      > MFWeakShaderVariableMMatrixPtr;
/*! \ingroup GrpSystemShaderFieldMFields */
typedef PointerMField<ShaderVariableMMatrix *,
                      NoRefCountPolicy, nsOSG        > MFUncountedShaderVariableMMatrixPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpSystemShaderFieldSFields \ingroup GrpLibOSGSystem */
struct SFRecShaderVariableMMatrixPtr : 
    public PointerSField<ShaderVariableMMatrix *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpSystemShaderFieldSFields \ingroup GrpLibOSGSystem */
struct SFUnrecShaderVariableMMatrixPtr : 
    public PointerSField<ShaderVariableMMatrix *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemShaderFieldSFields \ingroup GrpLibOSGSystem */
struct SFWeakShaderVariableMMatrixPtr :
    public PointerSField<ShaderVariableMMatrix *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpSystemShaderFieldSFields \ingroup GrpLibOSGSystem */
struct SFUncountedShaderVariableMMatrixPtr :
    public PointerSField<ShaderVariableMMatrix *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpSystemShaderFieldMFields \ingroup GrpLibOSGSystem */
struct MFRecShaderVariableMMatrixPtr :
    public PointerMField<ShaderVariableMMatrix *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpSystemShaderFieldMFields \ingroup GrpLibOSGSystem */
struct MFUnrecShaderVariableMMatrixPtr :
    public PointerMField<ShaderVariableMMatrix *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemShaderFieldMFields \ingroup GrpLibOSGSystem */
struct MFWeakShaderVariableMMatrixPtr :
    public PointerMField<ShaderVariableMMatrix *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpSystemShaderFieldMFields \ingroup GrpLibOSGSystem */
struct MFUncountedShaderVariableMMatrixPtr :
    public PointerMField<ShaderVariableMMatrix *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGSHADERVARIABLEMMATRIXFIELDS_H_ */
