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


#ifndef _OSGSHADERSHADOWMAPENGINEFIELDS_H_
#define _OSGSHADERSHADOWMAPENGINEFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGGroupDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class ShaderShadowMapEngine;

OSG_GEN_CONTAINERPTR(ShaderShadowMapEngine);
/*! \ingroup GrpGroupLightShadowEnginesFieldTraits
    \ingroup GrpLibOSGGroup
 */
template <>
struct FieldTraits<ShaderShadowMapEngine *, nsOSG> :
    public FieldTraitsFCPtrBase<ShaderShadowMapEngine *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<ShaderShadowMapEngine *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_GROUP_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<ShaderShadowMapEngine *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecShaderShadowMapEnginePtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderShadowMapEngine *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecShaderShadowMapEnginePtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderShadowMapEngine *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakShaderShadowMapEnginePtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderShadowMapEngine *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdShaderShadowMapEnginePtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderShadowMapEngine *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecShaderShadowMapEnginePtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderShadowMapEngine *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecShaderShadowMapEnginePtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderShadowMapEngine *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakShaderShadowMapEnginePtr"; 
}

template<> inline
const Char8 *FieldTraits<ShaderShadowMapEngine *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdShaderShadowMapEnginePtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpGroupLightShadowEnginesFieldSFields */
typedef PointerSField<ShaderShadowMapEngine *,
                      RecordedRefCountPolicy, nsOSG  > SFRecShaderShadowMapEnginePtr;
/*! \ingroup GrpGroupLightShadowEnginesFieldSFields */
typedef PointerSField<ShaderShadowMapEngine *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecShaderShadowMapEnginePtr;
/*! \ingroup GrpGroupLightShadowEnginesFieldSFields */
typedef PointerSField<ShaderShadowMapEngine *,
                      WeakRefCountPolicy, nsOSG      > SFWeakShaderShadowMapEnginePtr;
/*! \ingroup GrpGroupLightShadowEnginesFieldSFields */
typedef PointerSField<ShaderShadowMapEngine *,
                      NoRefCountPolicy, nsOSG        > SFUncountedShaderShadowMapEnginePtr;


/*! \ingroup GrpGroupLightShadowEnginesFieldMFields */
typedef PointerMField<ShaderShadowMapEngine *,
                      RecordedRefCountPolicy, nsOSG  > MFRecShaderShadowMapEnginePtr;
/*! \ingroup GrpGroupLightShadowEnginesFieldMFields */
typedef PointerMField<ShaderShadowMapEngine *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecShaderShadowMapEnginePtr;
/*! \ingroup GrpGroupLightShadowEnginesFieldMFields */
typedef PointerMField<ShaderShadowMapEngine *,
                      WeakRefCountPolicy, nsOSG      > MFWeakShaderShadowMapEnginePtr;
/*! \ingroup GrpGroupLightShadowEnginesFieldMFields */
typedef PointerMField<ShaderShadowMapEngine *,
                      NoRefCountPolicy, nsOSG        > MFUncountedShaderShadowMapEnginePtr;




#else // these are the doxygen hacks

/*! \ingroup GrpGroupLightShadowEnginesFieldSFields \ingroup GrpLibOSGGroup */
struct SFRecShaderShadowMapEnginePtr : 
    public PointerSField<ShaderShadowMapEngine *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpGroupLightShadowEnginesFieldSFields \ingroup GrpLibOSGGroup */
struct SFUnrecShaderShadowMapEnginePtr : 
    public PointerSField<ShaderShadowMapEngine *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpGroupLightShadowEnginesFieldSFields \ingroup GrpLibOSGGroup */
struct SFWeakShaderShadowMapEnginePtr :
    public PointerSField<ShaderShadowMapEngine *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpGroupLightShadowEnginesFieldSFields \ingroup GrpLibOSGGroup */
struct SFUncountedShaderShadowMapEnginePtr :
    public PointerSField<ShaderShadowMapEngine *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpGroupLightShadowEnginesFieldMFields \ingroup GrpLibOSGGroup */
struct MFRecShaderShadowMapEnginePtr :
    public PointerMField<ShaderShadowMapEngine *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpGroupLightShadowEnginesFieldMFields \ingroup GrpLibOSGGroup */
struct MFUnrecShaderShadowMapEnginePtr :
    public PointerMField<ShaderShadowMapEngine *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpGroupLightShadowEnginesFieldMFields \ingroup GrpLibOSGGroup */
struct MFWeakShaderShadowMapEnginePtr :
    public PointerMField<ShaderShadowMapEngine *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpGroupLightShadowEnginesFieldMFields \ingroup GrpLibOSGGroup */
struct MFUncountedShaderShadowMapEnginePtr :
    public PointerMField<ShaderShadowMapEngine *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGSHADERSHADOWMAPENGINEFIELDS_H_ */
