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


#ifndef _OSGMATERIALFIELDS_H_
#define _OSGMATERIALFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class Material;

OSG_GEN_CONTAINERPTR(Material);
/*! \ingroup GrpSystemMaterialFieldTraits
    \ingroup GrpLibOSGSystem
 */
template <>
struct FieldTraits<Material *, nsOSG> :
    public FieldTraitsFCPtrBase<Material *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<Material *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_SYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<Material *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecMaterialPtr"; 
}

template<> inline
const Char8 *FieldTraits<Material *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecMaterialPtr"; 
}

template<> inline
const Char8 *FieldTraits<Material *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakMaterialPtr"; 
}

template<> inline
const Char8 *FieldTraits<Material *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdMaterialPtr"; 
}

template<> inline
const Char8 *FieldTraits<Material *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecMaterialPtr"; 
}

template<> inline
const Char8 *FieldTraits<Material *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecMaterialPtr"; 
}

template<> inline
const Char8 *FieldTraits<Material *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakMaterialPtr"; 
}

template<> inline
const Char8 *FieldTraits<Material *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdMaterialPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpSystemMaterialFieldSFields */
typedef PointerSField<Material *,
                      RecordedRefCountPolicy, nsOSG  > SFRecMaterialPtr;
/*! \ingroup GrpSystemMaterialFieldSFields */
typedef PointerSField<Material *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecMaterialPtr;
/*! \ingroup GrpSystemMaterialFieldSFields */
typedef PointerSField<Material *,
                      WeakRefCountPolicy, nsOSG      > SFWeakMaterialPtr;
/*! \ingroup GrpSystemMaterialFieldSFields */
typedef PointerSField<Material *,
                      NoRefCountPolicy, nsOSG        > SFUncountedMaterialPtr;


/*! \ingroup GrpSystemMaterialFieldMFields */
typedef PointerMField<Material *,
                      RecordedRefCountPolicy, nsOSG  > MFRecMaterialPtr;
/*! \ingroup GrpSystemMaterialFieldMFields */
typedef PointerMField<Material *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecMaterialPtr;
/*! \ingroup GrpSystemMaterialFieldMFields */
typedef PointerMField<Material *,
                      WeakRefCountPolicy, nsOSG      > MFWeakMaterialPtr;
/*! \ingroup GrpSystemMaterialFieldMFields */
typedef PointerMField<Material *,
                      NoRefCountPolicy, nsOSG        > MFUncountedMaterialPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpSystemMaterialFieldSFields \ingroup GrpLibOSGSystem */
struct SFRecMaterialPtr : 
    public PointerSField<Material *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpSystemMaterialFieldSFields \ingroup GrpLibOSGSystem */
struct SFUnrecMaterialPtr : 
    public PointerSField<Material *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemMaterialFieldSFields \ingroup GrpLibOSGSystem */
struct SFWeakMaterialPtr :
    public PointerSField<Material *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpSystemMaterialFieldSFields \ingroup GrpLibOSGSystem */
struct SFUncountedMaterialPtr :
    public PointerSField<Material *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpSystemMaterialFieldMFields \ingroup GrpLibOSGSystem */
struct MFRecMaterialPtr :
    public PointerMField<Material *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpSystemMaterialFieldMFields \ingroup GrpLibOSGSystem */
struct MFUnrecMaterialPtr :
    public PointerMField<Material *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemMaterialFieldMFields \ingroup GrpLibOSGSystem */
struct MFWeakMaterialPtr :
    public PointerMField<Material *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpSystemMaterialFieldMFields \ingroup GrpLibOSGSystem */
struct MFUncountedMaterialPtr :
    public PointerMField<Material *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGMATERIALFIELDS_H_ */
