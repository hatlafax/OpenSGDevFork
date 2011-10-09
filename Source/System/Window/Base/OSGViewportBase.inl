/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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
 **     Do not change this file, changes should be done in the derived      **
 **     class Viewport!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &ViewportBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 ViewportBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 ViewportBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the Viewport::_sfLeft field.

inline
Real32 &ViewportBase::editLeft(void)
{
    editSField(LeftFieldMask);

    return _sfLeft.getValue();
}

//! Get the value of the Viewport::_sfLeft field.
inline
      Real32  ViewportBase::getLeft(void) const
{
    return _sfLeft.getValue();
}

//! Set the value of the Viewport::_sfLeft field.
inline
void ViewportBase::setLeft(const Real32 value)
{
    editSField(LeftFieldMask);

    _sfLeft.setValue(value);
}
//! Get the value of the Viewport::_sfRight field.

inline
Real32 &ViewportBase::editRight(void)
{
    editSField(RightFieldMask);

    return _sfRight.getValue();
}

//! Get the value of the Viewport::_sfRight field.
inline
      Real32  ViewportBase::getRight(void) const
{
    return _sfRight.getValue();
}

//! Set the value of the Viewport::_sfRight field.
inline
void ViewportBase::setRight(const Real32 value)
{
    editSField(RightFieldMask);

    _sfRight.setValue(value);
}
//! Get the value of the Viewport::_sfBottom field.

inline
Real32 &ViewportBase::editBottom(void)
{
    editSField(BottomFieldMask);

    return _sfBottom.getValue();
}

//! Get the value of the Viewport::_sfBottom field.
inline
      Real32  ViewportBase::getBottom(void) const
{
    return _sfBottom.getValue();
}

//! Set the value of the Viewport::_sfBottom field.
inline
void ViewportBase::setBottom(const Real32 value)
{
    editSField(BottomFieldMask);

    _sfBottom.setValue(value);
}
//! Get the value of the Viewport::_sfTop field.

inline
Real32 &ViewportBase::editTop(void)
{
    editSField(TopFieldMask);

    return _sfTop.getValue();
}

//! Get the value of the Viewport::_sfTop field.
inline
      Real32  ViewportBase::getTop(void) const
{
    return _sfTop.getValue();
}

//! Set the value of the Viewport::_sfTop field.
inline
void ViewportBase::setTop(const Real32 value)
{
    editSField(TopFieldMask);

    _sfTop.setValue(value);
}

//! Get the value of the Viewport::_sfCamera field.
inline
Camera * ViewportBase::getCamera(void) const
{
    return _sfCamera.getValue();
}

//! Set the value of the Viewport::_sfCamera field.
inline
void ViewportBase::setCamera(Camera * const value)
{
    editSField(CameraFieldMask);

    _sfCamera.setValue(value);
}

//! Get the value of the Viewport::_sfRoot field.
inline
Node * ViewportBase::getRoot(void) const
{
    return _sfRoot.getValue();
}

//! Set the value of the Viewport::_sfRoot field.
inline
void ViewportBase::setRoot(Node * const value)
{
    editSField(RootFieldMask);

    _sfRoot.setValue(value);
}

//! Get the value of the Viewport::_sfBackground field.
inline
Background * ViewportBase::getBackground(void) const
{
    return _sfBackground.getValue();
}

//! Set the value of the Viewport::_sfBackground field.
inline
void ViewportBase::setBackground(Background * const value)
{
    editSField(BackgroundFieldMask);

    _sfBackground.setValue(value);
}
//! Get the value of the Viewport::_sfTravMask field.

inline
UInt32 &ViewportBase::editTravMask(void)
{
    editSField(TravMaskFieldMask);

    return _sfTravMask.getValue();
}

//! Get the value of the Viewport::_sfTravMask field.
inline
      UInt32  ViewportBase::getTravMask(void) const
{
    return _sfTravMask.getValue();
}

//! Set the value of the Viewport::_sfTravMask field.
inline
void ViewportBase::setTravMask(const UInt32 value)
{
    editSField(TravMaskFieldMask);

    _sfTravMask.setValue(value);
}
//! Get the value of the Viewport::_sfDrawTime field.

inline
Real32 &ViewportBase::editDrawTime(void)
{
    editSField(DrawTimeFieldMask);

    return _sfDrawTime.getValue();
}

//! Get the value of the Viewport::_sfDrawTime field.
inline
      Real32  ViewportBase::getDrawTime(void) const
{
    return _sfDrawTime.getValue();
}

//! Set the value of the Viewport::_sfDrawTime field.
inline
void ViewportBase::setDrawTime(const Real32 value)
{
    editSField(DrawTimeFieldMask);

    _sfDrawTime.setValue(value);
}
//! Get the value of the Viewport::_sfDrawableId field.

inline
Int32 &ViewportBase::editDrawableId(void)
{
    editSField(DrawableIdFieldMask);

    return _sfDrawableId.getValue();
}

//! Get the value of the Viewport::_sfDrawableId field.
inline
      Int32  ViewportBase::getDrawableId(void) const
{
    return _sfDrawableId.getValue();
}

//! Set the value of the Viewport::_sfDrawableId field.
inline
void ViewportBase::setDrawableId(const Int32 value)
{
    editSField(DrawableIdFieldMask);

    _sfDrawableId.setValue(value);
}

//! Get the value of the Viewport::_sfRenderOptions field.
inline
RenderOptions * ViewportBase::getRenderOptions(void) const
{
    return _sfRenderOptions.getValue();
}

//! Set the value of the Viewport::_sfRenderOptions field.
inline
void ViewportBase::setRenderOptions(RenderOptions * const value)
{
    editSField(RenderOptionsFieldMask);

    _sfRenderOptions.setValue(value);
}

//! Get the value of the \a index element the Viewport::_mfForegrounds field.
inline
Foreground * ViewportBase::getForegrounds(const UInt32 index) const
{
    return _mfForegrounds[index];
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void ViewportBase::execSync (      ViewportBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (LeftFieldMask & whichField))
        _sfLeft.syncWith(pFrom->_sfLeft);

    if(FieldBits::NoField != (RightFieldMask & whichField))
        _sfRight.syncWith(pFrom->_sfRight);

    if(FieldBits::NoField != (BottomFieldMask & whichField))
        _sfBottom.syncWith(pFrom->_sfBottom);

    if(FieldBits::NoField != (TopFieldMask & whichField))
        _sfTop.syncWith(pFrom->_sfTop);

    if(FieldBits::NoField != (ParentFieldMask & whichField))
        _sfParent.syncWith(pFrom->_sfParent);

    if(FieldBits::NoField != (CameraFieldMask & whichField))
        _sfCamera.syncWith(pFrom->_sfCamera);

    if(FieldBits::NoField != (RootFieldMask & whichField))
        _sfRoot.syncWith(pFrom->_sfRoot);

    if(FieldBits::NoField != (BackgroundFieldMask & whichField))
        _sfBackground.syncWith(pFrom->_sfBackground);

    if(FieldBits::NoField != (ForegroundsFieldMask & whichField))
        _mfForegrounds.syncWith(pFrom->_mfForegrounds,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (TravMaskFieldMask & whichField))
        _sfTravMask.syncWith(pFrom->_sfTravMask);

    if(FieldBits::NoField != (DrawTimeFieldMask & whichField))
        _sfDrawTime.syncWith(pFrom->_sfDrawTime);

    if(FieldBits::NoField != (DrawableIdFieldMask & whichField))
        _sfDrawableId.syncWith(pFrom->_sfDrawableId);

    if(FieldBits::NoField != (RenderOptionsFieldMask & whichField))
        _sfRenderOptions.syncWith(pFrom->_sfRenderOptions);
}
#endif


inline
const Char8 *ViewportBase::getClassname(void)
{
    return "Viewport";
}
OSG_GEN_CONTAINERPTR(Viewport);

OSG_END_NAMESPACE

