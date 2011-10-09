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


#ifndef _OSGCGFXMATERIALFIELDS_H_
#define _OSGCGFXMATERIALFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribCgFXDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class CgFXMaterial;

OSG_GEN_CONTAINERPTR(CgFXMaterial);
/*! \ingroup GrpContribCgFXFieldTraits
    \ingroup GrpLibOSGContribCgFX
 */
template <>
struct FieldTraits<CgFXMaterial *, nsOSG> :
    public FieldTraitsFCPtrBase<CgFXMaterial *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<CgFXMaterial *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBCGFX_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<CgFXMaterial *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecCgFXMaterialPtr"; 
}

template<> inline
const Char8 *FieldTraits<CgFXMaterial *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecCgFXMaterialPtr"; 
}

template<> inline
const Char8 *FieldTraits<CgFXMaterial *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakCgFXMaterialPtr"; 
}

template<> inline
const Char8 *FieldTraits<CgFXMaterial *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdCgFXMaterialPtr"; 
}

template<> inline
const Char8 *FieldTraits<CgFXMaterial *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecCgFXMaterialPtr"; 
}

template<> inline
const Char8 *FieldTraits<CgFXMaterial *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecCgFXMaterialPtr"; 
}

template<> inline
const Char8 *FieldTraits<CgFXMaterial *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakCgFXMaterialPtr"; 
}

template<> inline
const Char8 *FieldTraits<CgFXMaterial *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdCgFXMaterialPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribCgFXFieldSFields */
typedef PointerSField<CgFXMaterial *,
                      RecordedRefCountPolicy, nsOSG  > SFRecCgFXMaterialPtr;
/*! \ingroup GrpContribCgFXFieldSFields */
typedef PointerSField<CgFXMaterial *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecCgFXMaterialPtr;
/*! \ingroup GrpContribCgFXFieldSFields */
typedef PointerSField<CgFXMaterial *,
                      WeakRefCountPolicy, nsOSG      > SFWeakCgFXMaterialPtr;
/*! \ingroup GrpContribCgFXFieldSFields */
typedef PointerSField<CgFXMaterial *,
                      NoRefCountPolicy, nsOSG        > SFUncountedCgFXMaterialPtr;


/*! \ingroup GrpContribCgFXFieldMFields */
typedef PointerMField<CgFXMaterial *,
                      RecordedRefCountPolicy, nsOSG  > MFRecCgFXMaterialPtr;
/*! \ingroup GrpContribCgFXFieldMFields */
typedef PointerMField<CgFXMaterial *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecCgFXMaterialPtr;
/*! \ingroup GrpContribCgFXFieldMFields */
typedef PointerMField<CgFXMaterial *,
                      WeakRefCountPolicy, nsOSG      > MFWeakCgFXMaterialPtr;
/*! \ingroup GrpContribCgFXFieldMFields */
typedef PointerMField<CgFXMaterial *,
                      NoRefCountPolicy, nsOSG        > MFUncountedCgFXMaterialPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribCgFXFieldSFields \ingroup GrpLibOSGContribCgFX */
struct SFRecCgFXMaterialPtr : 
    public PointerSField<CgFXMaterial *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribCgFXFieldSFields \ingroup GrpLibOSGContribCgFX */
struct SFUnrecCgFXMaterialPtr : 
    public PointerSField<CgFXMaterial *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribCgFXFieldSFields \ingroup GrpLibOSGContribCgFX */
struct SFWeakCgFXMaterialPtr :
    public PointerSField<CgFXMaterial *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribCgFXFieldSFields \ingroup GrpLibOSGContribCgFX */
struct SFUncountedCgFXMaterialPtr :
    public PointerSField<CgFXMaterial *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribCgFXFieldMFields \ingroup GrpLibOSGContribCgFX */
struct MFRecCgFXMaterialPtr :
    public PointerMField<CgFXMaterial *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribCgFXFieldMFields \ingroup GrpLibOSGContribCgFX */
struct MFUnrecCgFXMaterialPtr :
    public PointerMField<CgFXMaterial *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribCgFXFieldMFields \ingroup GrpLibOSGContribCgFX */
struct MFWeakCgFXMaterialPtr :
    public PointerMField<CgFXMaterial *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribCgFXFieldMFields \ingroup GrpLibOSGContribCgFX */
struct MFUncountedCgFXMaterialPtr :
    public PointerMField<CgFXMaterial *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGCGFXMATERIALFIELDS_H_ */
