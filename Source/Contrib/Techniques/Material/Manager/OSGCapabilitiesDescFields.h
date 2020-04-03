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


#ifndef _OSGCAPABILITIESDESCFIELDS_H_
#define _OSGCAPABILITIESDESCFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTechniquesDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class CapabilitiesDesc;

OSG_GEN_CONTAINERPTR(CapabilitiesDesc);
/*! \ingroup GrpContribTechniquesFieldTraits
    \ingroup GrpLibOSGContribTechniques
 */
template <>
struct FieldTraits<CapabilitiesDesc *, nsOSG> :
    public FieldTraitsFCPtrBase<CapabilitiesDesc *, nsOSG>
{
  private:

    static PointerType             _type;

  public:

    typedef FieldTraits<CapabilitiesDesc *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBTECHNIQUES_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<CapabilitiesDesc *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecCapabilitiesDescPtr"; 
}

template<> inline
const Char8 *FieldTraits<CapabilitiesDesc *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecCapabilitiesDescPtr"; 
}

template<> inline
const Char8 *FieldTraits<CapabilitiesDesc *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakCapabilitiesDescPtr"; 
}

template<> inline
const Char8 *FieldTraits<CapabilitiesDesc *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdCapabilitiesDescPtr"; 
}

template<> inline
const Char8 *FieldTraits<CapabilitiesDesc *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecCapabilitiesDescPtr"; 
}

template<> inline
const Char8 *FieldTraits<CapabilitiesDesc *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecCapabilitiesDescPtr"; 
}

template<> inline
const Char8 *FieldTraits<CapabilitiesDesc *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakCapabilitiesDescPtr"; 
}

template<> inline
const Char8 *FieldTraits<CapabilitiesDesc *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdCapabilitiesDescPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribTechniquesFieldSFields */
typedef PointerSField<CapabilitiesDesc *,
                      RecordedRefCountPolicy, nsOSG  > SFRecCapabilitiesDescPtr;
/*! \ingroup GrpContribTechniquesFieldSFields */
typedef PointerSField<CapabilitiesDesc *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecCapabilitiesDescPtr;
/*! \ingroup GrpContribTechniquesFieldSFields */
typedef PointerSField<CapabilitiesDesc *,
                      WeakRefCountPolicy, nsOSG      > SFWeakCapabilitiesDescPtr;
/*! \ingroup GrpContribTechniquesFieldSFields */
typedef PointerSField<CapabilitiesDesc *,
                      NoRefCountPolicy, nsOSG        > SFUncountedCapabilitiesDescPtr;


/*! \ingroup GrpContribTechniquesFieldMFields */
typedef PointerMField<CapabilitiesDesc *,
                      RecordedRefCountPolicy, nsOSG  > MFRecCapabilitiesDescPtr;
/*! \ingroup GrpContribTechniquesFieldMFields */
typedef PointerMField<CapabilitiesDesc *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecCapabilitiesDescPtr;
/*! \ingroup GrpContribTechniquesFieldMFields */
typedef PointerMField<CapabilitiesDesc *,
                      WeakRefCountPolicy, nsOSG      > MFWeakCapabilitiesDescPtr;
/*! \ingroup GrpContribTechniquesFieldMFields */
typedef PointerMField<CapabilitiesDesc *,
                      NoRefCountPolicy, nsOSG        > MFUncountedCapabilitiesDescPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribTechniquesFieldSFields \ingroup GrpLibOSGContribTechniques */
struct SFRecCapabilitiesDescPtr : 
    public PointerSField<CapabilitiesDesc *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribTechniquesFieldSFields \ingroup GrpLibOSGContribTechniques */
struct SFUnrecCapabilitiesDescPtr : 
    public PointerSField<CapabilitiesDesc *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribTechniquesFieldSFields \ingroup GrpLibOSGContribTechniques */
struct SFWeakCapabilitiesDescPtr :
    public PointerSField<CapabilitiesDesc *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribTechniquesFieldSFields \ingroup GrpLibOSGContribTechniques */
struct SFUncountedCapabilitiesDescPtr :
    public PointerSField<CapabilitiesDesc *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribTechniquesFieldMFields \ingroup GrpLibOSGContribTechniques */
struct MFRecCapabilitiesDescPtr :
    public PointerMField<CapabilitiesDesc *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribTechniquesFieldMFields \ingroup GrpLibOSGContribTechniques */
struct MFUnrecCapabilitiesDescPtr :
    public PointerMField<CapabilitiesDesc *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribTechniquesFieldMFields \ingroup GrpLibOSGContribTechniques */
struct MFWeakCapabilitiesDescPtr :
    public PointerMField<CapabilitiesDesc *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribTechniquesFieldMFields \ingroup GrpLibOSGContribTechniques */
struct MFUncountedCapabilitiesDescPtr :
    public PointerMField<CapabilitiesDesc *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGCAPABILITIESDESCFIELDS_H_ */
