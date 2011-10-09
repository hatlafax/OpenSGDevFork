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
 **     class SolidBackground!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &SolidBackgroundBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 SolidBackgroundBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 SolidBackgroundBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the SolidBackground::_sfColor field.

inline
Color3f &SolidBackgroundBase::editColor(void)
{
    editSField(ColorFieldMask);

    return _sfColor.getValue();
}

//! Get the value of the SolidBackground::_sfColor field.
inline
const Color3f &SolidBackgroundBase::getColor(void) const
{
    return _sfColor.getValue();
}

//! Set the value of the SolidBackground::_sfColor field.
inline
void SolidBackgroundBase::setColor(const Color3f &value)
{
    editSField(ColorFieldMask);

    _sfColor.setValue(value);
}
//! Get the value of the SolidBackground::_sfAlpha field.

inline
Real32 &SolidBackgroundBase::editAlpha(void)
{
    editSField(AlphaFieldMask);

    return _sfAlpha.getValue();
}

//! Get the value of the SolidBackground::_sfAlpha field.
inline
      Real32  SolidBackgroundBase::getAlpha(void) const
{
    return _sfAlpha.getValue();
}

//! Set the value of the SolidBackground::_sfAlpha field.
inline
void SolidBackgroundBase::setAlpha(const Real32 value)
{
    editSField(AlphaFieldMask);

    _sfAlpha.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void SolidBackgroundBase::execSync (      SolidBackgroundBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (ColorFieldMask & whichField))
        _sfColor.syncWith(pFrom->_sfColor);

    if(FieldBits::NoField != (AlphaFieldMask & whichField))
        _sfAlpha.syncWith(pFrom->_sfAlpha);
}
#endif


inline
const Char8 *SolidBackgroundBase::getClassname(void)
{
    return "SolidBackground";
}
OSG_GEN_CONTAINERPTR(SolidBackground);

OSG_END_NAMESPACE

