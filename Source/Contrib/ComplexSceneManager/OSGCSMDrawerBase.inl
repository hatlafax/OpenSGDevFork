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
 **     class CSMDrawer!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &CSMDrawerBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 CSMDrawerBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 CSMDrawerBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the CSMDrawer::_sfDisplayString field.

inline
std::string &CSMDrawerBase::editDisplayString(void)
{
    editSField(DisplayStringFieldMask);

    return _sfDisplayString.getValue();
}

//! Get the value of the CSMDrawer::_sfDisplayString field.
inline
const std::string &CSMDrawerBase::getDisplayString(void) const
{
    return _sfDisplayString.getValue();
}

//! Set the value of the CSMDrawer::_sfDisplayString field.
inline
void CSMDrawerBase::setDisplayString(const std::string &value)
{
    editSField(DisplayStringFieldMask);

    _sfDisplayString.setValue(value);
}
//! Get the value of the CSMDrawer::_sfAspect field.

inline
UInt32 &CSMDrawerBase::editAspect(void)
{
    editSField(AspectFieldMask);

    return _sfAspect.getValue();
}

//! Get the value of the CSMDrawer::_sfAspect field.
inline
      UInt32  CSMDrawerBase::getAspect(void) const
{
    return _sfAspect.getValue();
}

//! Set the value of the CSMDrawer::_sfAspect field.
inline
void CSMDrawerBase::setAspect(const UInt32 value)
{
    editSField(AspectFieldMask);

    _sfAspect.setValue(value);
}

//! Get the value of the \a index element the CSMDrawer::_mfWindows field.
inline
CSMWindow * CSMDrawerBase::getWindows(const UInt32 index) const
{
    return _mfWindows[index];
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void CSMDrawerBase::execSync (      CSMDrawerBase *pFrom,
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
const Char8 *CSMDrawerBase::getClassname(void)
{
    return "CSMDrawer";
}
OSG_GEN_CONTAINERPTR(CSMDrawer);

OSG_END_NAMESPACE

