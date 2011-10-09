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


#ifndef _OSGINTERFACEOPTIONSFIELDS_H_
#define _OSGINTERFACEOPTIONSFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribCSMDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class InterfaceOptions;

OSG_GEN_CONTAINERPTR(InterfaceOptions);
/*! \ingroup GrpContribCSMFieldTraits
    \ingroup GrpLibOSGContribCSM
 */
template <>
struct FieldTraits<InterfaceOptions *, nsOSG> :
    public FieldTraitsFCPtrBase<InterfaceOptions *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<InterfaceOptions *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBCSM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

};

template<> inline
const Char8 *FieldTraits<InterfaceOptions *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecInterfaceOptionsPtr"; 
}

template<> inline
const Char8 *FieldTraits<InterfaceOptions *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecInterfaceOptionsPtr"; 
}

template<> inline
const Char8 *FieldTraits<InterfaceOptions *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakInterfaceOptionsPtr"; 
}

template<> inline
const Char8 *FieldTraits<InterfaceOptions *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdInterfaceOptionsPtr"; 
}



/*! \ingroup GrpContribCSMFieldTraits
 */
template <>
struct FieldTraits<InterfaceOptions *, nsOSG + 1> :
    public FieldTraitsFCPtrBase<InterfaceOptions *, nsOSG + 1>
{
  private:

  public:
    typedef FieldTraits<InterfaceOptions *, nsOSG + 1>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBCSM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);
};

template<> inline
const Char8 *FieldTraits<InterfaceOptions *, nsOSG + 1>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecChildInterfaceOptionsPtr"; 
}

template<> inline
const Char8 *FieldTraits<InterfaceOptions *, nsOSG + 1>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecChildInterfaceOptionsPtr"; 
}

template<> inline
const Char8 *FieldTraits<InterfaceOptions *, nsOSG + 1>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakChildInterfaceOptionsPtr"; 
}

template<> inline
const Char8 *FieldTraits<InterfaceOptions *, nsOSG + 1>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdChildInterfaceOptionsPtr"; 
}



#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribCSMFieldSFields */
typedef PointerSField<InterfaceOptions *,
                      RecordedRefCountPolicy, nsOSG  > SFRecInterfaceOptionsPtr;
/*! \ingroup GrpContribCSMFieldSFields */
typedef PointerSField<InterfaceOptions *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecInterfaceOptionsPtr;
/*! \ingroup GrpContribCSMFieldSFields */
typedef PointerSField<InterfaceOptions *,
                      WeakRefCountPolicy, nsOSG      > SFWeakInterfaceOptionsPtr;
/*! \ingroup GrpContribCSMFieldSFields */
typedef PointerSField<InterfaceOptions *,
                      NoRefCountPolicy, nsOSG        > SFUncountedInterfaceOptionsPtr;



/*! \ingroup GrpContribCSMFieldSFields */
typedef ChildPointerSField<
          InterfaceOptions *, 
          UnrecordedRefCountPolicy,
          nsOSG + 1             > SFUnrecChildInterfaceOptionsPtr;



#else // these are the doxygen hacks

/*! \ingroup GrpContribCSMFieldSFields \ingroup GrpLibOSGContribCSM */
struct SFRecInterfaceOptionsPtr : 
    public PointerSField<InterfaceOptions *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribCSMFieldSFields \ingroup GrpLibOSGContribCSM */
struct SFUnrecInterfaceOptionsPtr : 
    public PointerSField<InterfaceOptions *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribCSMFieldSFields \ingroup GrpLibOSGContribCSM */
struct SFWeakInterfaceOptionsPtr :
    public PointerSField<InterfaceOptions *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribCSMFieldSFields \ingroup GrpLibOSGContribCSM */
struct SFUncountedInterfaceOptionsPtr :
    public PointerSField<InterfaceOptions *,
                         NoRefCountPolicy> {};



/*! \ingroup GrpContribCSMFieldSFields \ingroup GrpLibOSGContribCSM */
struct SFUnrecChildInterfaceOptionsPtr :
    public ChildPointerSField<
        InterfaceOptions *, 
        UnrecordedRefCountPolicy,
        nsOSG + 1             > {};


#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGINTERFACEOPTIONSFIELDS_H_ */
