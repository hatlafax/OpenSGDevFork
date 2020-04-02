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
 **     class CapabilitiesDesc!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE



//! access the type of the class
inline
OSG::FieldContainerType &CapabilitiesDescBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 CapabilitiesDescBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 CapabilitiesDescBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the CapabilitiesDesc::_sfPlatformCapabilities field.

inline
UInt32 &CapabilitiesDescBase::editPlatformCapabilities(void)
{
    editSField(PlatformCapabilitiesFieldMask);

    return _sfPlatformCapabilities.getValue();
}

//! Get the value of the CapabilitiesDesc::_sfPlatformCapabilities field.
inline
      UInt32  CapabilitiesDescBase::getPlatformCapabilities(void) const
{
    return _sfPlatformCapabilities.getValue();
}

//! Set the value of the CapabilitiesDesc::_sfPlatformCapabilities field.
inline
void CapabilitiesDescBase::setPlatformCapabilities(const UInt32 value)
{
    editSField(PlatformCapabilitiesFieldMask);

    _sfPlatformCapabilities.setValue(value);
}
//! Get the value of the CapabilitiesDesc::_sfRequestedCapabilities field.

inline
UInt32 &CapabilitiesDescBase::editRequestedCapabilities(void)
{
    editSField(RequestedCapabilitiesFieldMask);

    return _sfRequestedCapabilities.getValue();
}

//! Get the value of the CapabilitiesDesc::_sfRequestedCapabilities field.
inline
      UInt32  CapabilitiesDescBase::getRequestedCapabilities(void) const
{
    return _sfRequestedCapabilities.getValue();
}

//! Set the value of the CapabilitiesDesc::_sfRequestedCapabilities field.
inline
void CapabilitiesDescBase::setRequestedCapabilities(const UInt32 value)
{
    editSField(RequestedCapabilitiesFieldMask);

    _sfRequestedCapabilities.setValue(value);
}
//! Get the value of the CapabilitiesDesc::_sfRuntimeCapabilities field.

inline
UInt32 &CapabilitiesDescBase::editRuntimeCapabilities(void)
{
    editSField(RuntimeCapabilitiesFieldMask);

    return _sfRuntimeCapabilities.getValue();
}

//! Get the value of the CapabilitiesDesc::_sfRuntimeCapabilities field.
inline
      UInt32  CapabilitiesDescBase::getRuntimeCapabilities(void) const
{
    return _sfRuntimeCapabilities.getValue();
}

//! Set the value of the CapabilitiesDesc::_sfRuntimeCapabilities field.
inline
void CapabilitiesDescBase::setRuntimeCapabilities(const UInt32 value)
{
    editSField(RuntimeCapabilitiesFieldMask);

    _sfRuntimeCapabilities.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void CapabilitiesDescBase::execSync (      CapabilitiesDescBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (PlatformCapabilitiesFieldMask & whichField))
        _sfPlatformCapabilities.syncWith(pFrom->_sfPlatformCapabilities);

    if(FieldBits::NoField != (RequestedCapabilitiesFieldMask & whichField))
        _sfRequestedCapabilities.syncWith(pFrom->_sfRequestedCapabilities);

    if(FieldBits::NoField != (RuntimeCapabilitiesFieldMask & whichField))
        _sfRuntimeCapabilities.syncWith(pFrom->_sfRuntimeCapabilities);
}
#endif


inline
const Char8 *CapabilitiesDescBase::getClassname(void)
{
    return "CapabilitiesDesc";
}
OSG_GEN_CONTAINERPTR(CapabilitiesDesc);

OSG_END_NAMESPACE

