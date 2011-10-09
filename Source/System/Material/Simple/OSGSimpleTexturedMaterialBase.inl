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
 **     class SimpleTexturedMaterial!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &SimpleTexturedMaterialBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 SimpleTexturedMaterialBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 SimpleTexturedMaterialBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/


//! Get the value of the SimpleTexturedMaterial::_sfImage field.
inline
Image * SimpleTexturedMaterialBase::getImage(void) const
{
    return _sfImage.getValue();
}

//! Set the value of the SimpleTexturedMaterial::_sfImage field.
inline
void SimpleTexturedMaterialBase::setImage(Image * const value)
{
    editSField(ImageFieldMask);

    _sfImage.setValue(value);
}
//! Get the value of the SimpleTexturedMaterial::_sfMinFilter field.

inline
GLenum &SimpleTexturedMaterialBase::editMinFilter(void)
{
    editSField(MinFilterFieldMask);

    return _sfMinFilter.getValue();
}

//! Get the value of the SimpleTexturedMaterial::_sfMinFilter field.
inline
const GLenum &SimpleTexturedMaterialBase::getMinFilter(void) const
{
    return _sfMinFilter.getValue();
}

//! Set the value of the SimpleTexturedMaterial::_sfMinFilter field.
inline
void SimpleTexturedMaterialBase::setMinFilter(const GLenum &value)
{
    editSField(MinFilterFieldMask);

    _sfMinFilter.setValue(value);
}
//! Get the value of the SimpleTexturedMaterial::_sfMagFilter field.

inline
GLenum &SimpleTexturedMaterialBase::editMagFilter(void)
{
    editSField(MagFilterFieldMask);

    return _sfMagFilter.getValue();
}

//! Get the value of the SimpleTexturedMaterial::_sfMagFilter field.
inline
const GLenum &SimpleTexturedMaterialBase::getMagFilter(void) const
{
    return _sfMagFilter.getValue();
}

//! Set the value of the SimpleTexturedMaterial::_sfMagFilter field.
inline
void SimpleTexturedMaterialBase::setMagFilter(const GLenum &value)
{
    editSField(MagFilterFieldMask);

    _sfMagFilter.setValue(value);
}
//! Get the value of the SimpleTexturedMaterial::_sfEnvMode field.

inline
GLenum &SimpleTexturedMaterialBase::editEnvMode(void)
{
    editSField(EnvModeFieldMask);

    return _sfEnvMode.getValue();
}

//! Get the value of the SimpleTexturedMaterial::_sfEnvMode field.
inline
const GLenum &SimpleTexturedMaterialBase::getEnvMode(void) const
{
    return _sfEnvMode.getValue();
}

//! Set the value of the SimpleTexturedMaterial::_sfEnvMode field.
inline
void SimpleTexturedMaterialBase::setEnvMode(const GLenum &value)
{
    editSField(EnvModeFieldMask);

    _sfEnvMode.setValue(value);
}
//! Get the value of the SimpleTexturedMaterial::_sfEnvMap field.

inline
bool &SimpleTexturedMaterialBase::editEnvMap(void)
{
    editSField(EnvMapFieldMask);

    return _sfEnvMap.getValue();
}

//! Get the value of the SimpleTexturedMaterial::_sfEnvMap field.
inline
      bool  SimpleTexturedMaterialBase::getEnvMap(void) const
{
    return _sfEnvMap.getValue();
}

//! Set the value of the SimpleTexturedMaterial::_sfEnvMap field.
inline
void SimpleTexturedMaterialBase::setEnvMap(const bool value)
{
    editSField(EnvMapFieldMask);

    _sfEnvMap.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void SimpleTexturedMaterialBase::execSync (      SimpleTexturedMaterialBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (ImageFieldMask & whichField))
        _sfImage.syncWith(pFrom->_sfImage);

    if(FieldBits::NoField != (MinFilterFieldMask & whichField))
        _sfMinFilter.syncWith(pFrom->_sfMinFilter);

    if(FieldBits::NoField != (MagFilterFieldMask & whichField))
        _sfMagFilter.syncWith(pFrom->_sfMagFilter);

    if(FieldBits::NoField != (EnvModeFieldMask & whichField))
        _sfEnvMode.syncWith(pFrom->_sfEnvMode);

    if(FieldBits::NoField != (EnvMapFieldMask & whichField))
        _sfEnvMap.syncWith(pFrom->_sfEnvMap);
}
#endif


inline
const Char8 *SimpleTexturedMaterialBase::getClassname(void)
{
    return "SimpleTexturedMaterial";
}
OSG_GEN_CONTAINERPTR(SimpleTexturedMaterial);

OSG_END_NAMESPACE

