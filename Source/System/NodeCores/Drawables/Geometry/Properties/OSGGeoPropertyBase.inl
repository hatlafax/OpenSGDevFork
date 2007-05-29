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
 **     class GeoProperty!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &GeoPropertyBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 GeoPropertyBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 GeoPropertyBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the GeoProperty::_sfUseVBO field.

inline
bool &GeoPropertyBase::editUseVBO(void)
{
    editSField(UseVBOFieldMask);

    return _sfUseVBO.getValue();
}

//! Get the value of the GeoProperty::_sfUseVBO field.
inline
const bool &GeoPropertyBase::getUseVBO(void) const
{
    return _sfUseVBO.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
bool                &GeoPropertyBase::getUseVBO         (void)
{
    return this->editUseVBO         ();
}
#endif

//! Set the value of the GeoProperty::_sfUseVBO field.
inline
void GeoPropertyBase::setUseVBO(const bool &value)
{
    editSField(UseVBOFieldMask);

    _sfUseVBO.setValue(value);
}
//! Get the value of the GeoProperty::_sfGLId field.

inline
UInt32 &GeoPropertyBase::editGLId(void)
{
    editSField(GLIdFieldMask);

    return _sfGLId.getValue();
}

//! Get the value of the GeoProperty::_sfGLId field.
inline
const UInt32 &GeoPropertyBase::getGLId(void) const
{
    return _sfGLId.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
UInt32              &GeoPropertyBase::getGLId           (void)
{
    return this->editGLId           ();
}
#endif

//! Set the value of the GeoProperty::_sfGLId field.
inline
void GeoPropertyBase::setGLId(const UInt32 &value)
{
    editSField(GLIdFieldMask);

    _sfGLId.setValue(value);
}
//! Get the value of the GeoProperty::_sfUsage field.

inline
Int32 &GeoPropertyBase::editUsage(void)
{
    editSField(UsageFieldMask);

    return _sfUsage.getValue();
}

//! Get the value of the GeoProperty::_sfUsage field.
inline
const Int32 &GeoPropertyBase::getUsage(void) const
{
    return _sfUsage.getValue();
}

#ifdef OSG_1_GET_COMPAT
inline
Int32               &GeoPropertyBase::getUsage          (void)
{
    return this->editUsage          ();
}
#endif

//! Set the value of the GeoProperty::_sfUsage field.
inline
void GeoPropertyBase::setUsage(const Int32 &value)
{
    editSField(UsageFieldMask);

    _sfUsage.setValue(value);
}


#ifdef OSG_MT_FIELDCONTAINERPTR
inline
void GeoPropertyBase::execSync(      GeoPropertyBase *pOther,
                                       ConstFieldMaskArg  whichField,
                                       ConstFieldMaskArg  syncMode,
                                 const UInt32             uiSyncInfo,
                                       UInt32             uiCopyOffset)
{
    Inherited::execSync(pOther, whichField, syncMode, uiSyncInfo, uiCopyOffset);

    if(FieldBits::NoField != (UseVBOFieldMask & whichField))
        _sfUseVBO.syncWith(pOther->_sfUseVBO);

    if(FieldBits::NoField != (GLIdFieldMask & whichField))
        _sfGLId.syncWith(pOther->_sfGLId);

    if(FieldBits::NoField != (UsageFieldMask & whichField))
        _sfUsage.syncWith(pOther->_sfUsage);
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
inline
void GeoPropertyBase::execSync (      GeoPropertyBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (UseVBOFieldMask & whichField))
        _sfUseVBO.syncWith(pFrom->_sfUseVBO);

    if(FieldBits::NoField != (GLIdFieldMask & whichField))
        _sfGLId.syncWith(pFrom->_sfGLId);

    if(FieldBits::NoField != (UsageFieldMask & whichField))
        _sfUsage.syncWith(pFrom->_sfUsage);
}
#endif

#if 0
inline
void GeoPropertyBase::execBeginEdit(ConstFieldMaskArg whichField,
                                      UInt32            uiAspect,
                                      UInt32            uiContainerSize)
{
    Inherited::execBeginEdit(whichField, uiAspect, uiContainerSize);
}
#endif


inline
Char8 *GeoPropertyBase::getClassname(void)
{
    return "GeoProperty";
}

typedef PointerBuilder<GeoProperty>::ObjPtr          GeoPropertyPtr;
typedef PointerBuilder<GeoProperty>::ObjPtrConst     GeoPropertyPtrConst;
typedef PointerBuilder<GeoProperty>::ObjConstPtr     GeoPropertyConstPtr;

typedef PointerBuilder<GeoProperty>::ObjPtrArg       GeoPropertyPtrArg;
typedef PointerBuilder<GeoProperty>::ObjConstPtrArg  GeoPropertyConstPtrArg;
typedef PointerBuilder<GeoProperty>::ObjPtrConstArg  GeoPropertyPtrConstArg;

OSG_END_NAMESPACE

