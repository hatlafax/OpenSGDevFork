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


#ifndef _OSGSHADERPROGRAMMANAGERFIELDS_H_
#define _OSGSHADERPROGRAMMANAGERFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTechniquesDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class ShaderProgramManager;

OSG_GEN_CONTAINERPTR(ShaderProgramManager);
/*! \ingroup GrpContribTechniquesFieldTraits
    \ingroup GrpLibOSGContribTechniques
 */
template <>
struct FieldTraits<ShaderProgramManager *, nsOSG> :
    public FieldTraitsFCPtrBase<ShaderProgramManager *, nsOSG>
{
  private:

    static PointerType             _type;

  public:

    typedef FieldTraits<ShaderProgramManager *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBTECHNIQUES_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<ShaderProgramManager *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecShaderProgramManagerPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderProgramManager *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecShaderProgramManagerPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderProgramManager *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakShaderProgramManagerPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderProgramManager *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdShaderProgramManagerPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderProgramManager *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecShaderProgramManagerPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderProgramManager *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecShaderProgramManagerPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderProgramManager *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakShaderProgramManagerPtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderProgramManager *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdShaderProgramManagerPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribTechniquesFieldSFields */
typedef PointerSField<ShaderProgramManager *,
                      RecordedRefCountPolicy, nsOSG  > SFRecShaderProgramManagerPtr;
/*! \ingroup GrpContribTechniquesFieldSFields */
typedef PointerSField<ShaderProgramManager *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecShaderProgramManagerPtr;
/*! \ingroup GrpContribTechniquesFieldSFields */
typedef PointerSField<ShaderProgramManager *,
                      WeakRefCountPolicy, nsOSG      > SFWeakShaderProgramManagerPtr;
/*! \ingroup GrpContribTechniquesFieldSFields */
typedef PointerSField<ShaderProgramManager *,
                      NoRefCountPolicy, nsOSG        > SFUncountedShaderProgramManagerPtr;


/*! \ingroup GrpContribTechniquesFieldMFields */
typedef PointerMField<ShaderProgramManager *,
                      RecordedRefCountPolicy, nsOSG  > MFRecShaderProgramManagerPtr;
/*! \ingroup GrpContribTechniquesFieldMFields */
typedef PointerMField<ShaderProgramManager *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecShaderProgramManagerPtr;
/*! \ingroup GrpContribTechniquesFieldMFields */
typedef PointerMField<ShaderProgramManager *,
                      WeakRefCountPolicy, nsOSG      > MFWeakShaderProgramManagerPtr;
/*! \ingroup GrpContribTechniquesFieldMFields */
typedef PointerMField<ShaderProgramManager *,
                      NoRefCountPolicy, nsOSG        > MFUncountedShaderProgramManagerPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribTechniquesFieldSFields \ingroup GrpLibOSGContribTechniques */
struct SFRecShaderProgramManagerPtr : 
    public PointerSField<ShaderProgramManager *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribTechniquesFieldSFields \ingroup GrpLibOSGContribTechniques */
struct SFUnrecShaderProgramManagerPtr : 
    public PointerSField<ShaderProgramManager *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribTechniquesFieldSFields \ingroup GrpLibOSGContribTechniques */
struct SFWeakShaderProgramManagerPtr :
    public PointerSField<ShaderProgramManager *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribTechniquesFieldSFields \ingroup GrpLibOSGContribTechniques */
struct SFUncountedShaderProgramManagerPtr :
    public PointerSField<ShaderProgramManager *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribTechniquesFieldMFields \ingroup GrpLibOSGContribTechniques */
struct MFRecShaderProgramManagerPtr :
    public PointerMField<ShaderProgramManager *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribTechniquesFieldMFields \ingroup GrpLibOSGContribTechniques */
struct MFUnrecShaderProgramManagerPtr :
    public PointerMField<ShaderProgramManager *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribTechniquesFieldMFields \ingroup GrpLibOSGContribTechniques */
struct MFWeakShaderProgramManagerPtr :
    public PointerMField<ShaderProgramManager *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribTechniquesFieldMFields \ingroup GrpLibOSGContribTechniques */
struct MFUncountedShaderProgramManagerPtr :
    public PointerMField<ShaderProgramManager *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGSHADERPROGRAMMANAGERFIELDS_H_ */
