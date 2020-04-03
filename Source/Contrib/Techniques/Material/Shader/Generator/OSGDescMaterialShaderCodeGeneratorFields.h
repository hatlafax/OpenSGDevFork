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


#ifndef _OSGDESCMATERIALSHADERCODEGENERATORFIELDS_H_
#define _OSGDESCMATERIALSHADERCODEGENERATORFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTechniquesDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class DescMaterialShaderCodeGenerator;

OSG_GEN_CONTAINERPTR(DescMaterialShaderCodeGenerator);
/*! \ingroup GrpContribTechniquesFieldTraits
    \ingroup GrpLibOSGContribTechniques
 */
template <>
struct FieldTraits<DescMaterialShaderCodeGenerator *, nsOSG> :
    public FieldTraitsFCPtrBase<DescMaterialShaderCodeGenerator *, nsOSG>
{
  private:

    static PointerType             _type;

  public:

    typedef FieldTraits<DescMaterialShaderCodeGenerator *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBTECHNIQUES_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<DescMaterialShaderCodeGenerator *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecDescMaterialShaderCodeGeneratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<DescMaterialShaderCodeGenerator *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecDescMaterialShaderCodeGeneratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<DescMaterialShaderCodeGenerator *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakDescMaterialShaderCodeGeneratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<DescMaterialShaderCodeGenerator *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdDescMaterialShaderCodeGeneratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<DescMaterialShaderCodeGenerator *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecDescMaterialShaderCodeGeneratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<DescMaterialShaderCodeGenerator *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecDescMaterialShaderCodeGeneratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<DescMaterialShaderCodeGenerator *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakDescMaterialShaderCodeGeneratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<DescMaterialShaderCodeGenerator *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdDescMaterialShaderCodeGeneratorPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribTechniquesFieldSFields */
typedef PointerSField<DescMaterialShaderCodeGenerator *,
                      RecordedRefCountPolicy, nsOSG  > SFRecDescMaterialShaderCodeGeneratorPtr;
/*! \ingroup GrpContribTechniquesFieldSFields */
typedef PointerSField<DescMaterialShaderCodeGenerator *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecDescMaterialShaderCodeGeneratorPtr;
/*! \ingroup GrpContribTechniquesFieldSFields */
typedef PointerSField<DescMaterialShaderCodeGenerator *,
                      WeakRefCountPolicy, nsOSG      > SFWeakDescMaterialShaderCodeGeneratorPtr;
/*! \ingroup GrpContribTechniquesFieldSFields */
typedef PointerSField<DescMaterialShaderCodeGenerator *,
                      NoRefCountPolicy, nsOSG        > SFUncountedDescMaterialShaderCodeGeneratorPtr;


/*! \ingroup GrpContribTechniquesFieldMFields */
typedef PointerMField<DescMaterialShaderCodeGenerator *,
                      RecordedRefCountPolicy, nsOSG  > MFRecDescMaterialShaderCodeGeneratorPtr;
/*! \ingroup GrpContribTechniquesFieldMFields */
typedef PointerMField<DescMaterialShaderCodeGenerator *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecDescMaterialShaderCodeGeneratorPtr;
/*! \ingroup GrpContribTechniquesFieldMFields */
typedef PointerMField<DescMaterialShaderCodeGenerator *,
                      WeakRefCountPolicy, nsOSG      > MFWeakDescMaterialShaderCodeGeneratorPtr;
/*! \ingroup GrpContribTechniquesFieldMFields */
typedef PointerMField<DescMaterialShaderCodeGenerator *,
                      NoRefCountPolicy, nsOSG        > MFUncountedDescMaterialShaderCodeGeneratorPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribTechniquesFieldSFields \ingroup GrpLibOSGContribTechniques */
struct SFRecDescMaterialShaderCodeGeneratorPtr : 
    public PointerSField<DescMaterialShaderCodeGenerator *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribTechniquesFieldSFields \ingroup GrpLibOSGContribTechniques */
struct SFUnrecDescMaterialShaderCodeGeneratorPtr : 
    public PointerSField<DescMaterialShaderCodeGenerator *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribTechniquesFieldSFields \ingroup GrpLibOSGContribTechniques */
struct SFWeakDescMaterialShaderCodeGeneratorPtr :
    public PointerSField<DescMaterialShaderCodeGenerator *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribTechniquesFieldSFields \ingroup GrpLibOSGContribTechniques */
struct SFUncountedDescMaterialShaderCodeGeneratorPtr :
    public PointerSField<DescMaterialShaderCodeGenerator *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribTechniquesFieldMFields \ingroup GrpLibOSGContribTechniques */
struct MFRecDescMaterialShaderCodeGeneratorPtr :
    public PointerMField<DescMaterialShaderCodeGenerator *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribTechniquesFieldMFields \ingroup GrpLibOSGContribTechniques */
struct MFUnrecDescMaterialShaderCodeGeneratorPtr :
    public PointerMField<DescMaterialShaderCodeGenerator *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribTechniquesFieldMFields \ingroup GrpLibOSGContribTechniques */
struct MFWeakDescMaterialShaderCodeGeneratorPtr :
    public PointerMField<DescMaterialShaderCodeGenerator *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribTechniquesFieldMFields \ingroup GrpLibOSGContribTechniques */
struct MFUncountedDescMaterialShaderCodeGeneratorPtr :
    public PointerMField<DescMaterialShaderCodeGenerator *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGDESCMATERIALSHADERCODEGENERATORFIELDS_H_ */
