/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
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
 **     Do not change this file, changes should be done in the derived      **
 **     class FrameBufferObject!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &FrameBufferObjectBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 FrameBufferObjectBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 FrameBufferObjectBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the FrameBufferObject::_sfGLId field.

inline
GLenum &FrameBufferObjectBase::editGLId(void)
{
    editSField(GLIdFieldMask);

    return _sfGLId.getValue();
}

//! Get the value of the FrameBufferObject::_sfGLId field.
inline
const GLenum &FrameBufferObjectBase::getGLId(void) const
{
    return _sfGLId.getValue();
}

//! Set the value of the FrameBufferObject::_sfGLId field.
inline
void FrameBufferObjectBase::setGLId(const GLenum &value)
{
    editSField(GLIdFieldMask);

    _sfGLId.setValue(value);
}
//! Get the value of the FrameBufferObject::_sfMultiSampleGLId field.

inline
GLenum &FrameBufferObjectBase::editMultiSampleGLId(void)
{
    editSField(MultiSampleGLIdFieldMask);

    return _sfMultiSampleGLId.getValue();
}

//! Get the value of the FrameBufferObject::_sfMultiSampleGLId field.
inline
const GLenum &FrameBufferObjectBase::getMultiSampleGLId(void) const
{
    return _sfMultiSampleGLId.getValue();
}

//! Set the value of the FrameBufferObject::_sfMultiSampleGLId field.
inline
void FrameBufferObjectBase::setMultiSampleGLId(const GLenum &value)
{
    editSField(MultiSampleGLIdFieldMask);

    _sfMultiSampleGLId.setValue(value);
}
//! Get the value of the FrameBufferObject::_sfWidth field.

inline
UInt16 &FrameBufferObjectBase::editWidth(void)
{
    editSField(WidthFieldMask);

    return _sfWidth.getValue();
}

//! Get the value of the FrameBufferObject::_sfWidth field.
inline
      UInt16  FrameBufferObjectBase::getWidth(void) const
{
    return _sfWidth.getValue();
}

//! Set the value of the FrameBufferObject::_sfWidth field.
inline
void FrameBufferObjectBase::setWidth(const UInt16 value)
{
    editSField(WidthFieldMask);

    _sfWidth.setValue(value);
}
//! Get the value of the FrameBufferObject::_sfHeight field.

inline
UInt16 &FrameBufferObjectBase::editHeight(void)
{
    editSField(HeightFieldMask);

    return _sfHeight.getValue();
}

//! Get the value of the FrameBufferObject::_sfHeight field.
inline
      UInt16  FrameBufferObjectBase::getHeight(void) const
{
    return _sfHeight.getValue();
}

//! Set the value of the FrameBufferObject::_sfHeight field.
inline
void FrameBufferObjectBase::setHeight(const UInt16 value)
{
    editSField(HeightFieldMask);

    _sfHeight.setValue(value);
}
//! Get the value of the FrameBufferObject::_sfPostProcessOnDeactivate field.

inline
bool &FrameBufferObjectBase::editPostProcessOnDeactivate(void)
{
    editSField(PostProcessOnDeactivateFieldMask);

    return _sfPostProcessOnDeactivate.getValue();
}

//! Get the value of the FrameBufferObject::_sfPostProcessOnDeactivate field.
inline
      bool  FrameBufferObjectBase::getPostProcessOnDeactivate(void) const
{
    return _sfPostProcessOnDeactivate.getValue();
}

//! Set the value of the FrameBufferObject::_sfPostProcessOnDeactivate field.
inline
void FrameBufferObjectBase::setPostProcessOnDeactivate(const bool value)
{
    editSField(PostProcessOnDeactivateFieldMask);

    _sfPostProcessOnDeactivate.setValue(value);
}
//! Get the value of the FrameBufferObject::_sfEnableMultiSample field.

inline
bool &FrameBufferObjectBase::editEnableMultiSample(void)
{
    editSField(EnableMultiSampleFieldMask);

    return _sfEnableMultiSample.getValue();
}

//! Get the value of the FrameBufferObject::_sfEnableMultiSample field.
inline
      bool  FrameBufferObjectBase::getEnableMultiSample(void) const
{
    return _sfEnableMultiSample.getValue();
}

//! Set the value of the FrameBufferObject::_sfEnableMultiSample field.
inline
void FrameBufferObjectBase::setEnableMultiSample(const bool value)
{
    editSField(EnableMultiSampleFieldMask);

    _sfEnableMultiSample.setValue(value);
}
//! Get the value of the FrameBufferObject::_sfColorSamples field.

inline
UInt32 &FrameBufferObjectBase::editColorSamples(void)
{
    editSField(ColorSamplesFieldMask);

    return _sfColorSamples.getValue();
}

//! Get the value of the FrameBufferObject::_sfColorSamples field.
inline
      UInt32  FrameBufferObjectBase::getColorSamples(void) const
{
    return _sfColorSamples.getValue();
}

//! Set the value of the FrameBufferObject::_sfColorSamples field.
inline
void FrameBufferObjectBase::setColorSamples(const UInt32 value)
{
    editSField(ColorSamplesFieldMask);

    _sfColorSamples.setValue(value);
}
//! Get the value of the FrameBufferObject::_sfCoverageSamples field.

inline
UInt32 &FrameBufferObjectBase::editCoverageSamples(void)
{
    editSField(CoverageSamplesFieldMask);

    return _sfCoverageSamples.getValue();
}

//! Get the value of the FrameBufferObject::_sfCoverageSamples field.
inline
      UInt32  FrameBufferObjectBase::getCoverageSamples(void) const
{
    return _sfCoverageSamples.getValue();
}

//! Set the value of the FrameBufferObject::_sfCoverageSamples field.
inline
void FrameBufferObjectBase::setCoverageSamples(const UInt32 value)
{
    editSField(CoverageSamplesFieldMask);

    _sfCoverageSamples.setValue(value);
}
//! Get the value of the FrameBufferObject::_sfFixedSampleLocation field.

inline
bool &FrameBufferObjectBase::editFixedSampleLocation(void)
{
    editSField(FixedSampleLocationFieldMask);

    return _sfFixedSampleLocation.getValue();
}

//! Get the value of the FrameBufferObject::_sfFixedSampleLocation field.
inline
      bool  FrameBufferObjectBase::getFixedSampleLocation(void) const
{
    return _sfFixedSampleLocation.getValue();
}

//! Set the value of the FrameBufferObject::_sfFixedSampleLocation field.
inline
void FrameBufferObjectBase::setFixedSampleLocation(const bool value)
{
    editSField(FixedSampleLocationFieldMask);

    _sfFixedSampleLocation.setValue(value);
}


//! Get the value of the \a index element the FrameBufferObject::_mfDrawBuffers field.
inline
const GLenum &FrameBufferObjectBase::getDrawBuffers(const UInt32 index) const
{
    return _mfDrawBuffers[index];
}

inline
MFGLenum           ::reference FrameBufferObjectBase::editDrawBuffers(const UInt32 index)
{
    editMField(DrawBuffersFieldMask, _mfDrawBuffers);

    return _mfDrawBuffers[index];
}



#ifdef OSG_MT_CPTR_ASPECT
inline
void FrameBufferObjectBase::execSync (      FrameBufferObjectBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (GLIdFieldMask & whichField))
        _sfGLId.syncWith(pFrom->_sfGLId);

    if(FieldBits::NoField != (MultiSampleGLIdFieldMask & whichField))
        _sfMultiSampleGLId.syncWith(pFrom->_sfMultiSampleGLId);

    if(FieldBits::NoField != (ColorAttachmentsFieldMask & whichField))
        _mfColorAttachments.syncWith(pFrom->_mfColorAttachments,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (DrawBuffersFieldMask & whichField))
        _mfDrawBuffers.syncWith(pFrom->_mfDrawBuffers,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (DepthAttachmentFieldMask & whichField))
        _sfDepthAttachment.syncWith(pFrom->_sfDepthAttachment);

    if(FieldBits::NoField != (StencilAttachmentFieldMask & whichField))
        _sfStencilAttachment.syncWith(pFrom->_sfStencilAttachment);

    if(FieldBits::NoField != (WidthFieldMask & whichField))
        _sfWidth.syncWith(pFrom->_sfWidth);

    if(FieldBits::NoField != (HeightFieldMask & whichField))
        _sfHeight.syncWith(pFrom->_sfHeight);

    if(FieldBits::NoField != (PostProcessOnDeactivateFieldMask & whichField))
        _sfPostProcessOnDeactivate.syncWith(pFrom->_sfPostProcessOnDeactivate);

    if(FieldBits::NoField != (EnableMultiSampleFieldMask & whichField))
        _sfEnableMultiSample.syncWith(pFrom->_sfEnableMultiSample);

    if(FieldBits::NoField != (ColorSamplesFieldMask & whichField))
        _sfColorSamples.syncWith(pFrom->_sfColorSamples);

    if(FieldBits::NoField != (CoverageSamplesFieldMask & whichField))
        _sfCoverageSamples.syncWith(pFrom->_sfCoverageSamples);

    if(FieldBits::NoField != (FixedSampleLocationFieldMask & whichField))
        _sfFixedSampleLocation.syncWith(pFrom->_sfFixedSampleLocation);

    if(FieldBits::NoField != (MsaaColorAttachmentsFieldMask & whichField))
        _mfMsaaColorAttachments.syncWith(pFrom->_mfMsaaColorAttachments,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (MsaaDepthAttachmentFieldMask & whichField))
        _sfMsaaDepthAttachment.syncWith(pFrom->_sfMsaaDepthAttachment);

    if(FieldBits::NoField != (MsaaStencilAttachmentFieldMask & whichField))
        _sfMsaaStencilAttachment.syncWith(pFrom->_sfMsaaStencilAttachment);
}
#endif


inline
const Char8 *FrameBufferObjectBase::getClassname(void)
{
    return "FrameBufferObject";
}
OSG_GEN_CONTAINERPTR(FrameBufferObject);

OSG_END_NAMESPACE

