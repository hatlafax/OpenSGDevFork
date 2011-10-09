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


#ifndef _OSGFRAMEBUFFERATTACHMENTFIELDS_H_
#define _OSGFRAMEBUFFERATTACHMENTFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE


class FrameBufferAttachment;

OSG_GEN_CONTAINERPTR(FrameBufferAttachment);
/*! \ingroup GrpSystemWindowFBOFieldTraits
    \ingroup GrpLibOSGSystem
 */
template <>
struct FieldTraits<FrameBufferAttachment *, nsOSG> :
    public FieldTraitsFCPtrBase<FrameBufferAttachment *, nsOSG>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<FrameBufferAttachment *, nsOSG>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_SYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<FrameBufferAttachment *, nsOSG>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecFrameBufferAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<FrameBufferAttachment *, nsOSG>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecFrameBufferAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<FrameBufferAttachment *, nsOSG>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakFrameBufferAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<FrameBufferAttachment *, nsOSG>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdFrameBufferAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<FrameBufferAttachment *, nsOSG>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecFrameBufferAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<FrameBufferAttachment *, nsOSG>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecFrameBufferAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<FrameBufferAttachment *, nsOSG>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakFrameBufferAttachmentPtr"; 
}

template<> inline
const Char8 *FieldTraits<FrameBufferAttachment *, nsOSG>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdFrameBufferAttachmentPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpSystemWindowFBOFieldSFields */
typedef PointerSField<FrameBufferAttachment *,
                      RecordedRefCountPolicy, nsOSG  > SFRecFrameBufferAttachmentPtr;
/*! \ingroup GrpSystemWindowFBOFieldSFields */
typedef PointerSField<FrameBufferAttachment *,
                      UnrecordedRefCountPolicy, nsOSG> SFUnrecFrameBufferAttachmentPtr;
/*! \ingroup GrpSystemWindowFBOFieldSFields */
typedef PointerSField<FrameBufferAttachment *,
                      WeakRefCountPolicy, nsOSG      > SFWeakFrameBufferAttachmentPtr;
/*! \ingroup GrpSystemWindowFBOFieldSFields */
typedef PointerSField<FrameBufferAttachment *,
                      NoRefCountPolicy, nsOSG        > SFUncountedFrameBufferAttachmentPtr;


/*! \ingroup GrpSystemWindowFBOFieldMFields */
typedef PointerMField<FrameBufferAttachment *,
                      RecordedRefCountPolicy, nsOSG  > MFRecFrameBufferAttachmentPtr;
/*! \ingroup GrpSystemWindowFBOFieldMFields */
typedef PointerMField<FrameBufferAttachment *,
                      UnrecordedRefCountPolicy, nsOSG> MFUnrecFrameBufferAttachmentPtr;
/*! \ingroup GrpSystemWindowFBOFieldMFields */
typedef PointerMField<FrameBufferAttachment *,
                      WeakRefCountPolicy, nsOSG      > MFWeakFrameBufferAttachmentPtr;
/*! \ingroup GrpSystemWindowFBOFieldMFields */
typedef PointerMField<FrameBufferAttachment *,
                      NoRefCountPolicy, nsOSG        > MFUncountedFrameBufferAttachmentPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpSystemWindowFBOFieldSFields \ingroup GrpLibOSGSystem */
struct SFRecFrameBufferAttachmentPtr : 
    public PointerSField<FrameBufferAttachment *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpSystemWindowFBOFieldSFields \ingroup GrpLibOSGSystem */
struct SFUnrecFrameBufferAttachmentPtr : 
    public PointerSField<FrameBufferAttachment *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemWindowFBOFieldSFields \ingroup GrpLibOSGSystem */
struct SFWeakFrameBufferAttachmentPtr :
    public PointerSField<FrameBufferAttachment *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpSystemWindowFBOFieldSFields \ingroup GrpLibOSGSystem */
struct SFUncountedFrameBufferAttachmentPtr :
    public PointerSField<FrameBufferAttachment *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpSystemWindowFBOFieldMFields \ingroup GrpLibOSGSystem */
struct MFRecFrameBufferAttachmentPtr :
    public PointerMField<FrameBufferAttachment *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpSystemWindowFBOFieldMFields \ingroup GrpLibOSGSystem */
struct MFUnrecFrameBufferAttachmentPtr :
    public PointerMField<FrameBufferAttachment *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpSystemWindowFBOFieldMFields \ingroup GrpLibOSGSystem */
struct MFWeakFrameBufferAttachmentPtr :
    public PointerMField<FrameBufferAttachment *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpSystemWindowFBOFieldMFields \ingroup GrpLibOSGSystem */
struct MFUncountedFrameBufferAttachmentPtr :
    public PointerMField<FrameBufferAttachment *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGFRAMEBUFFERATTACHMENTFIELDS_H_ */
