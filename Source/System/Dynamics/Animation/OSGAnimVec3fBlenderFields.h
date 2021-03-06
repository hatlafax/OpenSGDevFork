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


#ifndef _OSGANIMVEC3FBLENDERFIELDS_H_
#define _OSGANIMVEC3FBLENDERFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGDynamicsDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class AnimVec3fBlender;

OSG_GEN_CONTAINERPTR(AnimVec3fBlender);
/*! \ingroup GrpDynamicsFieldTraits
    \ingroup GrpLibOSGDynamics
 */
template <>
struct FieldTraits<AnimVec3fBlender *, nsOSG> :
    public FieldTraitsFCPtrBase<AnimVec3fBlender *, nsOSG>
{
  private:

    static PointerType             _type;

  public:

    typedef FieldTraits<AnimVec3fBlender *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_DYNAMICS_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<AnimVec3fBlender *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecAnimVec3fBlenderPtr"; 
}

template<> inline
const Char8 *FieldTraits<AnimVec3fBlender *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecAnimVec3fBlenderPtr"; 
}

template<> inline
const Char8 *FieldTraits<AnimVec3fBlender *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakAnimVec3fBlenderPtr"; 
}

template<> inline
const Char8 *FieldTraits<AnimVec3fBlender *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdAnimVec3fBlenderPtr"; 
}

template<> inline
const Char8 *FieldTraits<AnimVec3fBlender *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecAnimVec3fBlenderPtr"; 
}

template<> inline
const Char8 *FieldTraits<AnimVec3fBlender *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecAnimVec3fBlenderPtr"; 
}

template<> inline
const Char8 *FieldTraits<AnimVec3fBlender *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakAnimVec3fBlenderPtr"; 
}

template<> inline
const Char8 *FieldTraits<AnimVec3fBlender *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdAnimVec3fBlenderPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpDynamicsFieldSFields */
typedef PointerSField<AnimVec3fBlender *,
                      RecordedRefCountPolicy, nsOSG  > SFRecAnimVec3fBlenderPtr;
/*! \ingroup GrpDynamicsFieldSFields */
typedef PointerSField<AnimVec3fBlender *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecAnimVec3fBlenderPtr;
/*! \ingroup GrpDynamicsFieldSFields */
typedef PointerSField<AnimVec3fBlender *,
                      WeakRefCountPolicy, nsOSG      > SFWeakAnimVec3fBlenderPtr;
/*! \ingroup GrpDynamicsFieldSFields */
typedef PointerSField<AnimVec3fBlender *,
                      NoRefCountPolicy, nsOSG        > SFUncountedAnimVec3fBlenderPtr;


/*! \ingroup GrpDynamicsFieldMFields */
typedef PointerMField<AnimVec3fBlender *,
                      RecordedRefCountPolicy, nsOSG  > MFRecAnimVec3fBlenderPtr;
/*! \ingroup GrpDynamicsFieldMFields */
typedef PointerMField<AnimVec3fBlender *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecAnimVec3fBlenderPtr;
/*! \ingroup GrpDynamicsFieldMFields */
typedef PointerMField<AnimVec3fBlender *,
                      WeakRefCountPolicy, nsOSG      > MFWeakAnimVec3fBlenderPtr;
/*! \ingroup GrpDynamicsFieldMFields */
typedef PointerMField<AnimVec3fBlender *,
                      NoRefCountPolicy, nsOSG        > MFUncountedAnimVec3fBlenderPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpDynamicsFieldSFields \ingroup GrpLibOSGDynamics */
struct SFRecAnimVec3fBlenderPtr : 
    public PointerSField<AnimVec3fBlender *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpDynamicsFieldSFields \ingroup GrpLibOSGDynamics */
struct SFUnrecAnimVec3fBlenderPtr : 
    public PointerSField<AnimVec3fBlender *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpDynamicsFieldSFields \ingroup GrpLibOSGDynamics */
struct SFWeakAnimVec3fBlenderPtr :
    public PointerSField<AnimVec3fBlender *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpDynamicsFieldSFields \ingroup GrpLibOSGDynamics */
struct SFUncountedAnimVec3fBlenderPtr :
    public PointerSField<AnimVec3fBlender *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpDynamicsFieldMFields \ingroup GrpLibOSGDynamics */
struct MFRecAnimVec3fBlenderPtr :
    public PointerMField<AnimVec3fBlender *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpDynamicsFieldMFields \ingroup GrpLibOSGDynamics */
struct MFUnrecAnimVec3fBlenderPtr :
    public PointerMField<AnimVec3fBlender *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpDynamicsFieldMFields \ingroup GrpLibOSGDynamics */
struct MFWeakAnimVec3fBlenderPtr :
    public PointerMField<AnimVec3fBlender *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpDynamicsFieldMFields \ingroup GrpLibOSGDynamics */
struct MFUncountedAnimVec3fBlenderPtr :
    public PointerMField<AnimVec3fBlender *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGANIMVEC3FBLENDERFIELDS_H_ */
