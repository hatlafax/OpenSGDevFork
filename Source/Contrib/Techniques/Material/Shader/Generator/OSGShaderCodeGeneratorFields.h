/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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


#ifndef _OSGSHADERCODEGENERATORFIELDS_H_
#define _OSGSHADERCODEGENERATORFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTechniquesDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class ShaderCodeGenerator;

OSG_GEN_CONTAINERPTR(ShaderCodeGenerator);
/*! \ingroup GrpContribTechniquesFieldTraits
    \ingroup GrpLibOSGContribTechniques
 */
template <>
struct FieldTraits<ShaderCodeGenerator *, nsOSG> :
    public FieldTraitsFCPtrBase<ShaderCodeGenerator *, nsOSG>
{
  private:

    static PointerType             _type;

  public:

    typedef FieldTraits<ShaderCodeGenerator *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBTECHNIQUES_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<ShaderCodeGenerator *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecShaderCodeGeneratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderCodeGenerator *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecShaderCodeGeneratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderCodeGenerator *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakShaderCodeGeneratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderCodeGenerator *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdShaderCodeGeneratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderCodeGenerator *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecShaderCodeGeneratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderCodeGenerator *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecShaderCodeGeneratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderCodeGenerator *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakShaderCodeGeneratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderCodeGenerator *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdShaderCodeGeneratorPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribTechniquesFieldSFields */
typedef PointerSField<ShaderCodeGenerator *,
                      RecordedRefCountPolicy, nsOSG  > SFRecShaderCodeGeneratorPtr;
/*! \ingroup GrpContribTechniquesFieldSFields */
typedef PointerSField<ShaderCodeGenerator *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecShaderCodeGeneratorPtr;
/*! \ingroup GrpContribTechniquesFieldSFields */
typedef PointerSField<ShaderCodeGenerator *,
                      WeakRefCountPolicy, nsOSG      > SFWeakShaderCodeGeneratorPtr;
/*! \ingroup GrpContribTechniquesFieldSFields */
typedef PointerSField<ShaderCodeGenerator *,
                      NoRefCountPolicy, nsOSG        > SFUncountedShaderCodeGeneratorPtr;


/*! \ingroup GrpContribTechniquesFieldMFields */
typedef PointerMField<ShaderCodeGenerator *,
                      RecordedRefCountPolicy, nsOSG  > MFRecShaderCodeGeneratorPtr;
/*! \ingroup GrpContribTechniquesFieldMFields */
typedef PointerMField<ShaderCodeGenerator *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecShaderCodeGeneratorPtr;
/*! \ingroup GrpContribTechniquesFieldMFields */
typedef PointerMField<ShaderCodeGenerator *,
                      WeakRefCountPolicy, nsOSG      > MFWeakShaderCodeGeneratorPtr;
/*! \ingroup GrpContribTechniquesFieldMFields */
typedef PointerMField<ShaderCodeGenerator *,
                      NoRefCountPolicy, nsOSG        > MFUncountedShaderCodeGeneratorPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribTechniquesFieldSFields \ingroup GrpLibOSGContribTechniques */
struct SFRecShaderCodeGeneratorPtr : 
    public PointerSField<ShaderCodeGenerator *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribTechniquesFieldSFields \ingroup GrpLibOSGContribTechniques */
struct SFUnrecShaderCodeGeneratorPtr : 
    public PointerSField<ShaderCodeGenerator *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribTechniquesFieldSFields \ingroup GrpLibOSGContribTechniques */
struct SFWeakShaderCodeGeneratorPtr :
    public PointerSField<ShaderCodeGenerator *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribTechniquesFieldSFields \ingroup GrpLibOSGContribTechniques */
struct SFUncountedShaderCodeGeneratorPtr :
    public PointerSField<ShaderCodeGenerator *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribTechniquesFieldMFields \ingroup GrpLibOSGContribTechniques */
struct MFRecShaderCodeGeneratorPtr :
    public PointerMField<ShaderCodeGenerator *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribTechniquesFieldMFields \ingroup GrpLibOSGContribTechniques */
struct MFUnrecShaderCodeGeneratorPtr :
    public PointerMField<ShaderCodeGenerator *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribTechniquesFieldMFields \ingroup GrpLibOSGContribTechniques */
struct MFWeakShaderCodeGeneratorPtr :
    public PointerMField<ShaderCodeGenerator *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribTechniquesFieldMFields \ingroup GrpLibOSGContribTechniques */
struct MFUncountedShaderCodeGeneratorPtr :
    public PointerMField<ShaderCodeGenerator *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGSHADERCODEGENERATORFIELDS_H_ */
