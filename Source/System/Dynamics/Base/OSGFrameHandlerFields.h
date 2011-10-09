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


#ifndef _OSGFRAMEHANDLERFIELDS_H_
#define _OSGFRAMEHANDLERFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGDynamicsDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class FrameHandler;

OSG_GEN_CONTAINERPTR(FrameHandler);
/*! \ingroup GrpDynamicsBaseFieldTraits
    \ingroup GrpLibOSGDynamics
 */
template <>
struct FieldTraits<FrameHandler *, nsOSG> :
    public FieldTraitsFCPtrBase<FrameHandler *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<FrameHandler *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_DYNAMICS_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

};

template<> inline
const Char8 *FieldTraits<FrameHandler *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecFrameHandlerPtr"; 
}

template<> inline
const Char8 *FieldTraits<FrameHandler *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecFrameHandlerPtr"; 
}

template<> inline
const Char8 *FieldTraits<FrameHandler *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakFrameHandlerPtr"; 
}

template<> inline
const Char8 *FieldTraits<FrameHandler *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdFrameHandlerPtr"; 
}



#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpDynamicsBaseFieldSFields */
typedef PointerSField<FrameHandler *,
                      RecordedRefCountPolicy, nsOSG  > SFRecFrameHandlerPtr;
/*! \ingroup GrpDynamicsBaseFieldSFields */
typedef PointerSField<FrameHandler *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecFrameHandlerPtr;
/*! \ingroup GrpDynamicsBaseFieldSFields */
typedef PointerSField<FrameHandler *,
                      WeakRefCountPolicy, nsOSG      > SFWeakFrameHandlerPtr;
/*! \ingroup GrpDynamicsBaseFieldSFields */
typedef PointerSField<FrameHandler *,
                      NoRefCountPolicy, nsOSG        > SFUncountedFrameHandlerPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpDynamicsBaseFieldSFields \ingroup GrpLibOSGDynamics */
struct SFRecFrameHandlerPtr : 
    public PointerSField<FrameHandler *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpDynamicsBaseFieldSFields \ingroup GrpLibOSGDynamics */
struct SFUnrecFrameHandlerPtr : 
    public PointerSField<FrameHandler *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpDynamicsBaseFieldSFields \ingroup GrpLibOSGDynamics */
struct SFWeakFrameHandlerPtr :
    public PointerSField<FrameHandler *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpDynamicsBaseFieldSFields \ingroup GrpLibOSGDynamics */
struct SFUncountedFrameHandlerPtr :
    public PointerSField<FrameHandler *,
                         NoRefCountPolicy> {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGFRAMEHANDLERFIELDS_H_ */
