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
 **     class MultiDisplayWindow!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &MultiDisplayWindowBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 MultiDisplayWindowBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 MultiDisplayWindowBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the MultiDisplayWindow::_sfHServers field.

inline
UInt32 &MultiDisplayWindowBase::editHServers(void)
{
    editSField(HServersFieldMask);

    return _sfHServers.getValue();
}

//! Get the value of the MultiDisplayWindow::_sfHServers field.
inline
      UInt32  MultiDisplayWindowBase::getHServers(void) const
{
    return _sfHServers.getValue();
}

//! Set the value of the MultiDisplayWindow::_sfHServers field.
inline
void MultiDisplayWindowBase::setHServers(const UInt32 value)
{
    editSField(HServersFieldMask);

    _sfHServers.setValue(value);
}
//! Get the value of the MultiDisplayWindow::_sfVServers field.

inline
UInt32 &MultiDisplayWindowBase::editVServers(void)
{
    editSField(VServersFieldMask);

    return _sfVServers.getValue();
}

//! Get the value of the MultiDisplayWindow::_sfVServers field.
inline
      UInt32  MultiDisplayWindowBase::getVServers(void) const
{
    return _sfVServers.getValue();
}

//! Set the value of the MultiDisplayWindow::_sfVServers field.
inline
void MultiDisplayWindowBase::setVServers(const UInt32 value)
{
    editSField(VServersFieldMask);

    _sfVServers.setValue(value);
}
//! Get the value of the MultiDisplayWindow::_sfManageClientViewports field.

inline
bool &MultiDisplayWindowBase::editManageClientViewports(void)
{
    editSField(ManageClientViewportsFieldMask);

    return _sfManageClientViewports.getValue();
}

//! Get the value of the MultiDisplayWindow::_sfManageClientViewports field.
inline
      bool  MultiDisplayWindowBase::getManageClientViewports(void) const
{
    return _sfManageClientViewports.getValue();
}

//! Set the value of the MultiDisplayWindow::_sfManageClientViewports field.
inline
void MultiDisplayWindowBase::setManageClientViewports(const bool value)
{
    editSField(ManageClientViewportsFieldMask);

    _sfManageClientViewports.setValue(value);
}
//! Get the value of the MultiDisplayWindow::_sfXOverlap field.

inline
Int32 &MultiDisplayWindowBase::editXOverlap(void)
{
    editSField(XOverlapFieldMask);

    return _sfXOverlap.getValue();
}

//! Get the value of the MultiDisplayWindow::_sfXOverlap field.
inline
      Int32  MultiDisplayWindowBase::getXOverlap(void) const
{
    return _sfXOverlap.getValue();
}

//! Set the value of the MultiDisplayWindow::_sfXOverlap field.
inline
void MultiDisplayWindowBase::setXOverlap(const Int32 value)
{
    editSField(XOverlapFieldMask);

    _sfXOverlap.setValue(value);
}
//! Get the value of the MultiDisplayWindow::_sfYOverlap field.

inline
Int32 &MultiDisplayWindowBase::editYOverlap(void)
{
    editSField(YOverlapFieldMask);

    return _sfYOverlap.getValue();
}

//! Get the value of the MultiDisplayWindow::_sfYOverlap field.
inline
      Int32  MultiDisplayWindowBase::getYOverlap(void) const
{
    return _sfYOverlap.getValue();
}

//! Set the value of the MultiDisplayWindow::_sfYOverlap field.
inline
void MultiDisplayWindowBase::setYOverlap(const Int32 value)
{
    editSField(YOverlapFieldMask);

    _sfYOverlap.setValue(value);
}
//! Get the value of the MultiDisplayWindow::_sfMaxDepth field.

inline
Int32 &MultiDisplayWindowBase::editMaxDepth(void)
{
    editSField(MaxDepthFieldMask);

    return _sfMaxDepth.getValue();
}

//! Get the value of the MultiDisplayWindow::_sfMaxDepth field.
inline
      Int32  MultiDisplayWindowBase::getMaxDepth(void) const
{
    return _sfMaxDepth.getValue();
}

//! Set the value of the MultiDisplayWindow::_sfMaxDepth field.
inline
void MultiDisplayWindowBase::setMaxDepth(const Int32 value)
{
    editSField(MaxDepthFieldMask);

    _sfMaxDepth.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void MultiDisplayWindowBase::execSync (      MultiDisplayWindowBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (HServersFieldMask & whichField))
        _sfHServers.syncWith(pFrom->_sfHServers);

    if(FieldBits::NoField != (VServersFieldMask & whichField))
        _sfVServers.syncWith(pFrom->_sfVServers);

    if(FieldBits::NoField != (ManageClientViewportsFieldMask & whichField))
        _sfManageClientViewports.syncWith(pFrom->_sfManageClientViewports);

    if(FieldBits::NoField != (XOverlapFieldMask & whichField))
        _sfXOverlap.syncWith(pFrom->_sfXOverlap);

    if(FieldBits::NoField != (YOverlapFieldMask & whichField))
        _sfYOverlap.syncWith(pFrom->_sfYOverlap);

    if(FieldBits::NoField != (MaxDepthFieldMask & whichField))
        _sfMaxDepth.syncWith(pFrom->_sfMaxDepth);
}
#endif


inline
const Char8 *MultiDisplayWindowBase::getClassname(void)
{
    return "MultiDisplayWindow";
}
OSG_GEN_CONTAINERPTR(MultiDisplayWindow);

OSG_END_NAMESPACE

