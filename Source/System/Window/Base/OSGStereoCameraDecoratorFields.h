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


#ifndef _OSGSTEREOCAMERADECORATORFIELDS_H_
#define _OSGSTEREOCAMERADECORATORFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class StereoCameraDecorator;

OSG_GEN_CONTAINERPTR(StereoCameraDecorator);
/*! \ingroup GrpSystemWindowFieldTraits
    \ingroup GrpLibOSGSystem
 */
template <>
struct FieldTraits<StereoCameraDecorator *, nsOSG> :
    public FieldTraitsFCPtrBase<StereoCameraDecorator *, nsOSG>
{
  private:

    static PointerType             _type;

  public:

    typedef FieldTraits<StereoCameraDecorator *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_SYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<StereoCameraDecorator *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecStereoCameraDecoratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<StereoCameraDecorator *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecStereoCameraDecoratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<StereoCameraDecorator *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakStereoCameraDecoratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<StereoCameraDecorator *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdStereoCameraDecoratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<StereoCameraDecorator *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecStereoCameraDecoratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<StereoCameraDecorator *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecStereoCameraDecoratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<StereoCameraDecorator *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakStereoCameraDecoratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<StereoCameraDecorator *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdStereoCameraDecoratorPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpSystemWindowFieldSFields */
typedef PointerSField<StereoCameraDecorator *,
                      RecordedRefCountPolicy, nsOSG  > SFRecStereoCameraDecoratorPtr;
/*! \ingroup GrpSystemWindowFieldSFields */
typedef PointerSField<StereoCameraDecorator *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecStereoCameraDecoratorPtr;
/*! \ingroup GrpSystemWindowFieldSFields */
typedef PointerSField<StereoCameraDecorator *,
                      WeakRefCountPolicy, nsOSG      > SFWeakStereoCameraDecoratorPtr;
/*! \ingroup GrpSystemWindowFieldSFields */
typedef PointerSField<StereoCameraDecorator *,
                      NoRefCountPolicy, nsOSG        > SFUncountedStereoCameraDecoratorPtr;


/*! \ingroup GrpSystemWindowFieldMFields */
typedef PointerMField<StereoCameraDecorator *,
                      RecordedRefCountPolicy, nsOSG  > MFRecStereoCameraDecoratorPtr;
/*! \ingroup GrpSystemWindowFieldMFields */
typedef PointerMField<StereoCameraDecorator *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecStereoCameraDecoratorPtr;
/*! \ingroup GrpSystemWindowFieldMFields */
typedef PointerMField<StereoCameraDecorator *,
                      WeakRefCountPolicy, nsOSG      > MFWeakStereoCameraDecoratorPtr;
/*! \ingroup GrpSystemWindowFieldMFields */
typedef PointerMField<StereoCameraDecorator *,
                      NoRefCountPolicy, nsOSG        > MFUncountedStereoCameraDecoratorPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpSystemWindowFieldSFields \ingroup GrpLibOSGSystem */
struct SFRecStereoCameraDecoratorPtr : 
    public PointerSField<StereoCameraDecorator *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpSystemWindowFieldSFields \ingroup GrpLibOSGSystem */
struct SFUnrecStereoCameraDecoratorPtr : 
    public PointerSField<StereoCameraDecorator *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemWindowFieldSFields \ingroup GrpLibOSGSystem */
struct SFWeakStereoCameraDecoratorPtr :
    public PointerSField<StereoCameraDecorator *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpSystemWindowFieldSFields \ingroup GrpLibOSGSystem */
struct SFUncountedStereoCameraDecoratorPtr :
    public PointerSField<StereoCameraDecorator *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpSystemWindowFieldMFields \ingroup GrpLibOSGSystem */
struct MFRecStereoCameraDecoratorPtr :
    public PointerMField<StereoCameraDecorator *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpSystemWindowFieldMFields \ingroup GrpLibOSGSystem */
struct MFUnrecStereoCameraDecoratorPtr :
    public PointerMField<StereoCameraDecorator *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemWindowFieldMFields \ingroup GrpLibOSGSystem */
struct MFWeakStereoCameraDecoratorPtr :
    public PointerMField<StereoCameraDecorator *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpSystemWindowFieldMFields \ingroup GrpLibOSGSystem */
struct MFUncountedStereoCameraDecoratorPtr :
    public PointerMField<StereoCameraDecorator *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGSTEREOCAMERADECORATORFIELDS_H_ */
