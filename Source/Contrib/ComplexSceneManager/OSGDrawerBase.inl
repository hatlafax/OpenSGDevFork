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
 **     class Drawer!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &DrawerBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 DrawerBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 DrawerBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the Drawer::_sfDisplayString field.

inline
std::string &DrawerBase::editDisplayString(void)
{
    editSField(DisplayStringFieldMask);

    return _sfDisplayString.getValue();
}

//! Get the value of the Drawer::_sfDisplayString field.
inline
const std::string &DrawerBase::getDisplayString(void) const
{
    return _sfDisplayString.getValue();
}

//! Set the value of the Drawer::_sfDisplayString field.
inline
void DrawerBase::setDisplayString(const std::string &value)
{
    editSField(DisplayStringFieldMask);

    _sfDisplayString.setValue(value);
}
//! Get the value of the Drawer::_sfAspect field.

inline
UInt32 &DrawerBase::editAspect(void)
{
    editSField(AspectFieldMask);

    return _sfAspect.getValue();
}

//! Get the value of the Drawer::_sfAspect field.
inline
      UInt32  DrawerBase::getAspect(void) const
{
    return _sfAspect.getValue();
}

//! Set the value of the Drawer::_sfAspect field.
inline
void DrawerBase::setAspect(const UInt32 value)
{
    editSField(AspectFieldMask);

    _sfAspect.setValue(value);
}

//! Get the value of the \a index element the Drawer::_mfWindows field.
inline
CSMWindow * DrawerBase::getWindows(const UInt32 index) const
{
    return _mfWindows[index];
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void DrawerBase::execSync (      DrawerBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (WindowsFieldMask & whichField))
        _mfWindows.syncWith(pFrom->_mfWindows,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (DisplayStringFieldMask & whichField))
        _sfDisplayString.syncWith(pFrom->_sfDisplayString);

    if(FieldBits::NoField != (AspectFieldMask & whichField))
        _sfAspect.syncWith(pFrom->_sfAspect);
}
#endif


inline
Char8 *DrawerBase::getClassname(void)
{
    return "Drawer";
}
OSG_GEN_CONTAINERPTR(Drawer);

OSG_END_NAMESPACE

