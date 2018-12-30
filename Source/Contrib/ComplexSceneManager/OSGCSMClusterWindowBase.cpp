/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
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
 **     class CSMClusterWindow!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#ifdef WIN32 
#pragma warning(disable: 4355) // turn off 'this' : used in base member initializer list warning
#pragma warning(disable: 4290) // disable exception specification warning
#endif

#include "OSGConfig.h"



#include "OSGCSMWindow.h"               // ClientWindow Class
#include "OSGImageComposer.h"           // Composer Class
#include "OSGCSMClusterWinOptions.h"    // Options Class

#include "OSGCSMClusterWindowBase.h"
#include "OSGCSMClusterWindow.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::CSMClusterWindow
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var CSMWindow *     CSMClusterWindowBase::_sfClientWindow
    
*/

/*! \var bool            CSMClusterWindowBase::_sfRenderClient
    
*/

/*! \var std::string     CSMClusterWindowBase::_mfServers
    
*/

/*! \var UInt32          CSMClusterWindowBase::_mfServerIds
    
*/

/*! \var UInt32          CSMClusterWindowBase::_sfServerRows
    
*/

/*! \var std::string     CSMClusterWindowBase::_sfConnectionType
    
*/

/*! \var std::string     CSMClusterWindowBase::_sfClusterMode
    
*/

/*! \var ImageComposer * CSMClusterWindowBase::_sfComposer
    
*/

/*! \var CSMClusterWinOptions * CSMClusterWindowBase::_sfOptions
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<CSMClusterWindow *, nsOSG>::_type(
    "CSMClusterWindowPtr", 
    "CSMWindowPtr", 
    CSMClusterWindow::getClassType(),
    nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(CSMClusterWindow *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           CSMClusterWindow *,
                           nsOSG)

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           CSMClusterWindow *,
                           nsOSG)

DataType &FieldTraits<CSMClusterWindow *, nsOSG + 1 >::getType(void)
{
    return FieldTraits<CSMClusterWindow *, nsOSG>::getType();
}


OSG_SFIELDTYPE_INST(ParentPointerSField,
                    CSMClusterWindow *,
                    NoRefCountPolicy,
                    nsOSG + 1);

OSG_FIELD_DLLEXPORT_DEF3(ParentPointerSField,
                         CSMClusterWindow *,
                         NoRefCountPolicy,
                         nsOSG + 1)


/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void CSMClusterWindowBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFUnrecChildCSMWindowPtr::Description(
        SFUnrecChildCSMWindowPtr::getClassType(),
        "clientWindow",
        "",
        ClientWindowFieldId, ClientWindowFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMClusterWindow::editHandleClientWindow),
        static_cast<FieldGetMethodSig >(&CSMClusterWindow::getHandleClientWindow));

    oType.addInitialDesc(pDesc);

    pDesc = new SFBool::Description(
        SFBool::getClassType(),
        "renderClient",
        "",
        RenderClientFieldId, RenderClientFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMClusterWindow::editHandleRenderClient),
        static_cast<FieldGetMethodSig >(&CSMClusterWindow::getHandleRenderClient));

    oType.addInitialDesc(pDesc);

    pDesc = new MFString::Description(
        MFString::getClassType(),
        "servers",
        "",
        ServersFieldId, ServersFieldMask,
        true,
        (Field::MFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMClusterWindow::editHandleServers),
        static_cast<FieldGetMethodSig >(&CSMClusterWindow::getHandleServers));

    oType.addInitialDesc(pDesc);

    pDesc = new MFUInt32::Description(
        MFUInt32::getClassType(),
        "serverIds",
        "",
        ServerIdsFieldId, ServerIdsFieldMask,
        false,
        (Field::MFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMClusterWindow::editHandleServerIds),
        static_cast<FieldGetMethodSig >(&CSMClusterWindow::getHandleServerIds));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(),
        "serverRows",
        "",
        ServerRowsFieldId, ServerRowsFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMClusterWindow::editHandleServerRows),
        static_cast<FieldGetMethodSig >(&CSMClusterWindow::getHandleServerRows));

    oType.addInitialDesc(pDesc);

    pDesc = new SFString::Description(
        SFString::getClassType(),
        "connectionType",
        "",
        ConnectionTypeFieldId, ConnectionTypeFieldMask,
        true,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMClusterWindow::editHandleConnectionType),
        static_cast<FieldGetMethodSig >(&CSMClusterWindow::getHandleConnectionType));

    oType.addInitialDesc(pDesc);

    pDesc = new SFString::Description(
        SFString::getClassType(),
        "clusterMode",
        "",
        ClusterModeFieldId, ClusterModeFieldMask,
        true,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMClusterWindow::editHandleClusterMode),
        static_cast<FieldGetMethodSig >(&CSMClusterWindow::getHandleClusterMode));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecImageComposerPtr::Description(
        SFUnrecImageComposerPtr::getClassType(),
        "composer",
        "",
        ComposerFieldId, ComposerFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMClusterWindow::editHandleComposer),
        static_cast<FieldGetMethodSig >(&CSMClusterWindow::getHandleComposer));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecChildCSMClusterWinOptionsPtr::Description(
        SFUnrecChildCSMClusterWinOptionsPtr::getClassType(),
        "options",
        "",
        OptionsFieldId, OptionsFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&CSMClusterWindow::editHandleOptions),
        static_cast<FieldGetMethodSig >(&CSMClusterWindow::getHandleOptions));

    oType.addInitialDesc(pDesc);
}


CSMClusterWindowBase::TypeObject CSMClusterWindowBase::_type(
    CSMClusterWindowBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&CSMClusterWindowBase::createEmptyLocal),
    reinterpret_cast<InitContainerF>(&CSMClusterWindow::initMethod),
    reinterpret_cast<ExitContainerF>(&CSMClusterWindow::exitMethod),
    reinterpret_cast<InitalInsertDescFunc>(
        reinterpret_cast<void *>(&CSMClusterWindow::classDescInserter)),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"CSMClusterWindow\"\n"
    "    parent=\"CSMWindow\"\n"
    "    library=\"ContribCSM\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    structure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "    isBundle=\"true\"\n"
    "    parentFields=\"single\"\n"
    ">\n"
    "\t<Field\n"
    "\t\tname=\"clientWindow\"\n"
    "\t\ttype=\"CSMWindow\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "        category=\"childpointer\"\n"
    "        childParentType=\"CSMClusterWindow\"\n"
    "        linkParentField=\"Parent\"\n"
    "\t>\n"
    "\t</Field>\n"
    "    <Field\n"
    "       name=\"renderClient\"\n"
    "       type=\"bool\"\n"
    "       cardinality=\"single\"\n"
    "       visibility=\"external\"\n"
    "       access=\"public\"\n"
    "       defaultValue=\"true\"\n"
    "    >\n"
    "    </Field>\n"
    "\n"
    "\t<Field\n"
    "\t\tname=\"servers\"\n"
    "\t\ttype=\"std::string\"\n"
    "\t\tcardinality=\"multi\"\n"
    "\t\tvisibility=\"internal\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"serverIds\"\n"
    "\t\ttype=\"UInt32\"\n"
    "\t\tcardinality=\"multi\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "\t</Field>\n"
    "    <Field\n"
    "       name=\"serverRows\"\n"
    "       type=\"UInt32\"\n"
    "       cardinality=\"single\"\n"
    "       visibility=\"external\"\n"
    "       access=\"public\"\n"
    "    >\n"
    "    </Field>\n"
    "\n"
    "\t<Field\n"
    "\t\tname=\"connectionType\"\n"
    "\t\ttype=\"std::string\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"internal\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"clusterMode\"\n"
    "\t\ttype=\"std::string\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"internal\"\n"
    "\t\taccess=\"public\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\n"
    "\n"
    "\t<Field\n"
    "\t\tname=\"composer\"\n"
    "\t\ttype=\"ImageComposer\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "        category=\"pointer\"\n"
    "\t>\n"
    "\t</Field>\n"
    "\t<Field\n"
    "\t\tname=\"options\"\n"
    "\t\ttype=\"CSMClusterWinOptions\"\n"
    "\t\tcardinality=\"single\"\n"
    "\t\tvisibility=\"external\"\n"
    "\t\taccess=\"public\"\n"
    "        category=\"childpointer\"\n"
    "        childParentType=\"CSMClusterWindow\"\n"
    "        linkParentField=\"Parent\"\n"
    "\t>\n"
    "\t</Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &CSMClusterWindowBase::getType(void)
{
    return _type;
}

const FieldContainerType &CSMClusterWindowBase::getType(void) const
{
    return _type;
}

UInt32 CSMClusterWindowBase::getContainerSize(void) const
{
    return sizeof(CSMClusterWindow);
}

/*------------------------- decorator get ------------------------------*/


//! Get the CSMClusterWindow::_sfClientWindow field.
const SFUnrecChildCSMWindowPtr *CSMClusterWindowBase::getSFClientWindow(void) const
{
    return &_sfClientWindow;
}

SFUnrecChildCSMWindowPtr *CSMClusterWindowBase::editSFClientWindow   (void)
{
    editSField(ClientWindowFieldMask);

    return &_sfClientWindow;
}

//! Get the value of the CSMClusterWindow::_sfClientWindow field.
CSMWindow * CSMClusterWindowBase::getClientWindow(void) const
{
    return _sfClientWindow.getValue();
}

//! Set the value of the CSMClusterWindow::_sfClientWindow field.
void CSMClusterWindowBase::setClientWindow(CSMWindow * const value)
{
    editSField(ClientWindowFieldMask);

    _sfClientWindow.setValue(value);
}


SFBool *CSMClusterWindowBase::editSFRenderClient(void)
{
    editSField(RenderClientFieldMask);

    return &_sfRenderClient;
}

const SFBool *CSMClusterWindowBase::getSFRenderClient(void) const
{
    return &_sfRenderClient;
}


MFString *CSMClusterWindowBase::editMFServers(void)
{
    editMField(ServersFieldMask, _mfServers);

    return &_mfServers;
}

const MFString *CSMClusterWindowBase::getMFServers(void) const
{
    return &_mfServers;
}


MFUInt32 *CSMClusterWindowBase::editMFServerIds(void)
{
    editMField(ServerIdsFieldMask, _mfServerIds);

    return &_mfServerIds;
}

const MFUInt32 *CSMClusterWindowBase::getMFServerIds(void) const
{
    return &_mfServerIds;
}


SFUInt32 *CSMClusterWindowBase::editSFServerRows(void)
{
    editSField(ServerRowsFieldMask);

    return &_sfServerRows;
}

const SFUInt32 *CSMClusterWindowBase::getSFServerRows(void) const
{
    return &_sfServerRows;
}


SFString *CSMClusterWindowBase::editSFConnectionType(void)
{
    editSField(ConnectionTypeFieldMask);

    return &_sfConnectionType;
}

const SFString *CSMClusterWindowBase::getSFConnectionType(void) const
{
    return &_sfConnectionType;
}


SFString *CSMClusterWindowBase::editSFClusterMode(void)
{
    editSField(ClusterModeFieldMask);

    return &_sfClusterMode;
}

const SFString *CSMClusterWindowBase::getSFClusterMode(void) const
{
    return &_sfClusterMode;
}


//! Get the CSMClusterWindow::_sfComposer field.
const SFUnrecImageComposerPtr *CSMClusterWindowBase::getSFComposer(void) const
{
    return &_sfComposer;
}

SFUnrecImageComposerPtr *CSMClusterWindowBase::editSFComposer       (void)
{
    editSField(ComposerFieldMask);

    return &_sfComposer;
}

//! Get the value of the CSMClusterWindow::_sfComposer field.
ImageComposer * CSMClusterWindowBase::getComposer(void) const
{
    return _sfComposer.getValue();
}

//! Set the value of the CSMClusterWindow::_sfComposer field.
void CSMClusterWindowBase::setComposer(ImageComposer * const value)
{
    editSField(ComposerFieldMask);

    _sfComposer.setValue(value);
}


//! Get the CSMClusterWindow::_sfOptions field.
const SFUnrecChildCSMClusterWinOptionsPtr *CSMClusterWindowBase::getSFOptions(void) const
{
    return &_sfOptions;
}

SFUnrecChildCSMClusterWinOptionsPtr *CSMClusterWindowBase::editSFOptions        (void)
{
    editSField(OptionsFieldMask);

    return &_sfOptions;
}

//! Get the value of the CSMClusterWindow::_sfOptions field.
CSMClusterWinOptions * CSMClusterWindowBase::getOptions(void) const
{
    return _sfOptions.getValue();
}

//! Set the value of the CSMClusterWindow::_sfOptions field.
void CSMClusterWindowBase::setOptions(CSMClusterWinOptions * const value)
{
    editSField(OptionsFieldMask);

    _sfOptions.setValue(value);
}






/*------------------------------ access -----------------------------------*/

SizeT CSMClusterWindowBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ClientWindowFieldMask & whichField))
    {
        returnValue += _sfClientWindow.getBinSize();
    }
    if(FieldBits::NoField != (RenderClientFieldMask & whichField))
    {
        returnValue += _sfRenderClient.getBinSize();
    }
    if(FieldBits::NoField != (ServersFieldMask & whichField))
    {
        returnValue += _mfServers.getBinSize();
    }
    if(FieldBits::NoField != (ServerIdsFieldMask & whichField))
    {
        returnValue += _mfServerIds.getBinSize();
    }
    if(FieldBits::NoField != (ServerRowsFieldMask & whichField))
    {
        returnValue += _sfServerRows.getBinSize();
    }
    if(FieldBits::NoField != (ConnectionTypeFieldMask & whichField))
    {
        returnValue += _sfConnectionType.getBinSize();
    }
    if(FieldBits::NoField != (ClusterModeFieldMask & whichField))
    {
        returnValue += _sfClusterMode.getBinSize();
    }
    if(FieldBits::NoField != (ComposerFieldMask & whichField))
    {
        returnValue += _sfComposer.getBinSize();
    }
    if(FieldBits::NoField != (OptionsFieldMask & whichField))
    {
        returnValue += _sfOptions.getBinSize();
    }

    return returnValue;
}

void CSMClusterWindowBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ClientWindowFieldMask & whichField))
    {
        _sfClientWindow.copyToBin(pMem);
    }
    if(FieldBits::NoField != (RenderClientFieldMask & whichField))
    {
        _sfRenderClient.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ServersFieldMask & whichField))
    {
        _mfServers.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ServerIdsFieldMask & whichField))
    {
        _mfServerIds.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ServerRowsFieldMask & whichField))
    {
        _sfServerRows.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ConnectionTypeFieldMask & whichField))
    {
        _sfConnectionType.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ClusterModeFieldMask & whichField))
    {
        _sfClusterMode.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ComposerFieldMask & whichField))
    {
        _sfComposer.copyToBin(pMem);
    }
    if(FieldBits::NoField != (OptionsFieldMask & whichField))
    {
        _sfOptions.copyToBin(pMem);
    }
}

void CSMClusterWindowBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ClientWindowFieldMask & whichField))
    {
        editSField(ClientWindowFieldMask);
        _sfClientWindow.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (RenderClientFieldMask & whichField))
    {
        editSField(RenderClientFieldMask);
        _sfRenderClient.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ServersFieldMask & whichField))
    {
        editMField(ServersFieldMask, _mfServers);
        _mfServers.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ServerIdsFieldMask & whichField))
    {
        editMField(ServerIdsFieldMask, _mfServerIds);
        _mfServerIds.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ServerRowsFieldMask & whichField))
    {
        editSField(ServerRowsFieldMask);
        _sfServerRows.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ConnectionTypeFieldMask & whichField))
    {
        editSField(ConnectionTypeFieldMask);
        _sfConnectionType.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ClusterModeFieldMask & whichField))
    {
        editSField(ClusterModeFieldMask);
        _sfClusterMode.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ComposerFieldMask & whichField))
    {
        editSField(ComposerFieldMask);
        _sfComposer.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (OptionsFieldMask & whichField))
    {
        editSField(OptionsFieldMask);
        _sfOptions.copyFromBin(pMem);
    }
}

//! create a new instance of the class
CSMClusterWindowTransitPtr CSMClusterWindowBase::createLocal(BitVector bFlags)
{
    CSMClusterWindowTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<CSMClusterWindow>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
CSMClusterWindowTransitPtr CSMClusterWindowBase::createDependent(BitVector bFlags)
{
    CSMClusterWindowTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<CSMClusterWindow>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
CSMClusterWindowTransitPtr CSMClusterWindowBase::create(void)
{
    return createLocal();
}

CSMClusterWindow *CSMClusterWindowBase::createEmptyLocal(BitVector bFlags)
{
    CSMClusterWindow *returnValue;

    newPtr<CSMClusterWindow>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
CSMClusterWindow *CSMClusterWindowBase::createEmpty(void)
{
    return createEmptyLocal();
}


FieldContainerTransitPtr CSMClusterWindowBase::shallowCopyLocal(
    BitVector bFlags) const
{
    CSMClusterWindow *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const CSMClusterWindow *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr CSMClusterWindowBase::shallowCopyDependent(
    BitVector bFlags) const
{
    CSMClusterWindow *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const CSMClusterWindow *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr CSMClusterWindowBase::shallowCopy(void) const
{
    return shallowCopyLocal();
}




/*------------------------- constructors ----------------------------------*/

CSMClusterWindowBase::CSMClusterWindowBase(void) :
    Inherited(),
    _sfClientWindow           (this,
                          ClientWindowFieldId,
                          CSMWindow::ParentFieldId),
    _sfRenderClient           (bool(true)),
    _mfServers                (),
    _mfServerIds              (),
    _sfServerRows             (),
    _sfConnectionType         (),
    _sfClusterMode            (),
    _sfComposer               (NULL),
    _sfOptions                (this,
                          OptionsFieldId,
                          CSMClusterWinOptions::ParentFieldId)
{
}

CSMClusterWindowBase::CSMClusterWindowBase(const CSMClusterWindowBase &source) :
    Inherited(source),
    _sfClientWindow           (this,
                          ClientWindowFieldId,
                          CSMWindow::ParentFieldId),
    _sfRenderClient           (source._sfRenderClient           ),
    _mfServers                (source._mfServers                ),
    _mfServerIds              (source._mfServerIds              ),
    _sfServerRows             (source._sfServerRows             ),
    _sfConnectionType         (source._sfConnectionType         ),
    _sfClusterMode            (source._sfClusterMode            ),
    _sfComposer               (NULL),
    _sfOptions                (this,
                          OptionsFieldId,
                          CSMClusterWinOptions::ParentFieldId)
{
}


/*-------------------------- destructors ----------------------------------*/

CSMClusterWindowBase::~CSMClusterWindowBase(void)
{
}

/*-------------------------------------------------------------------------*/
/* Child linking                                                           */

bool CSMClusterWindowBase::unlinkChild(
    FieldContainer * const pChild,
    UInt16           const childFieldId)
{
    if(childFieldId == ClientWindowFieldId)
    {
        CSMWindow * pTypedChild =
            dynamic_cast<CSMWindow *>(pChild);

        if(pTypedChild != NULL)
        {
            if(_sfClientWindow.getValue() == pTypedChild)
            {
                editSField(ClientWindowFieldMask);

                _sfClientWindow.setValue(NULL);

                return true;
            }

            SWARNING << "Parent (["        << this
                     << "] id ["           << this->getId()
                     << "] type ["         << this->getType().getCName()
                     << "] childFieldId [" << childFieldId
                     << "]) - Child (["    << pChild
                     << "] id ["           << pChild->getId()
                     << "] type ["         << pChild->getType().getCName()
                     << "]): link inconsistent!"
                     << std::endl;

            return false;
        }

        return false;
    }

    if(childFieldId == OptionsFieldId)
    {
        CSMClusterWinOptions * pTypedChild =
            dynamic_cast<CSMClusterWinOptions *>(pChild);

        if(pTypedChild != NULL)
        {
            if(_sfOptions.getValue() == pTypedChild)
            {
                editSField(OptionsFieldMask);

                _sfOptions.setValue(NULL);

                return true;
            }

            SWARNING << "Parent (["        << this
                     << "] id ["           << this->getId()
                     << "] type ["         << this->getType().getCName()
                     << "] childFieldId [" << childFieldId
                     << "]) - Child (["    << pChild
                     << "] id ["           << pChild->getId()
                     << "] type ["         << pChild->getType().getCName()
                     << "]): link inconsistent!"
                     << std::endl;

            return false;
        }

        return false;
    }


    return Inherited::unlinkChild(pChild, childFieldId);
}

void CSMClusterWindowBase::onCreate(const CSMClusterWindow *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        CSMClusterWindow *pThis = static_cast<CSMClusterWindow *>(this);

        pThis->setClientWindow(source->getClientWindow());

        pThis->setComposer(source->getComposer());

        pThis->setOptions(source->getOptions());
    }
}

GetFieldHandlePtr CSMClusterWindowBase::getHandleClientWindow    (void) const
{
    SFUnrecChildCSMWindowPtr::GetHandlePtr returnValue(
        new  SFUnrecChildCSMWindowPtr::GetHandle(
             &_sfClientWindow,
             this->getType().getFieldDesc(ClientWindowFieldId),
             const_cast<CSMClusterWindowBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr CSMClusterWindowBase::editHandleClientWindow   (void)
{
    SFUnrecChildCSMWindowPtr::EditHandlePtr returnValue(
        new  SFUnrecChildCSMWindowPtr::EditHandle(
             &_sfClientWindow,
             this->getType().getFieldDesc(ClientWindowFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&CSMClusterWindow::setClientWindow,
                    static_cast<CSMClusterWindow *>(this), _1));

    editSField(ClientWindowFieldMask);

    return returnValue;
}

GetFieldHandlePtr CSMClusterWindowBase::getHandleRenderClient    (void) const
{
    SFBool::GetHandlePtr returnValue(
        new  SFBool::GetHandle(
             &_sfRenderClient,
             this->getType().getFieldDesc(RenderClientFieldId),
             const_cast<CSMClusterWindowBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr CSMClusterWindowBase::editHandleRenderClient   (void)
{
    SFBool::EditHandlePtr returnValue(
        new  SFBool::EditHandle(
             &_sfRenderClient,
             this->getType().getFieldDesc(RenderClientFieldId),
             this));


    editSField(RenderClientFieldMask);

    return returnValue;
}

GetFieldHandlePtr CSMClusterWindowBase::getHandleServers         (void) const
{
    MFString::GetHandlePtr returnValue(
        new  MFString::GetHandle(
             &_mfServers,
             this->getType().getFieldDesc(ServersFieldId),
             const_cast<CSMClusterWindowBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr CSMClusterWindowBase::editHandleServers        (void)
{
    MFString::EditHandlePtr returnValue(
        new  MFString::EditHandle(
             &_mfServers,
             this->getType().getFieldDesc(ServersFieldId),
             this));


    editMField(ServersFieldMask, _mfServers);

    return returnValue;
}

GetFieldHandlePtr CSMClusterWindowBase::getHandleServerIds       (void) const
{
    MFUInt32::GetHandlePtr returnValue(
        new  MFUInt32::GetHandle(
             &_mfServerIds,
             this->getType().getFieldDesc(ServerIdsFieldId),
             const_cast<CSMClusterWindowBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr CSMClusterWindowBase::editHandleServerIds      (void)
{
    MFUInt32::EditHandlePtr returnValue(
        new  MFUInt32::EditHandle(
             &_mfServerIds,
             this->getType().getFieldDesc(ServerIdsFieldId),
             this));


    editMField(ServerIdsFieldMask, _mfServerIds);

    return returnValue;
}

GetFieldHandlePtr CSMClusterWindowBase::getHandleServerRows      (void) const
{
    SFUInt32::GetHandlePtr returnValue(
        new  SFUInt32::GetHandle(
             &_sfServerRows,
             this->getType().getFieldDesc(ServerRowsFieldId),
             const_cast<CSMClusterWindowBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr CSMClusterWindowBase::editHandleServerRows     (void)
{
    SFUInt32::EditHandlePtr returnValue(
        new  SFUInt32::EditHandle(
             &_sfServerRows,
             this->getType().getFieldDesc(ServerRowsFieldId),
             this));


    editSField(ServerRowsFieldMask);

    return returnValue;
}

GetFieldHandlePtr CSMClusterWindowBase::getHandleConnectionType  (void) const
{
    SFString::GetHandlePtr returnValue(
        new  SFString::GetHandle(
             &_sfConnectionType,
             this->getType().getFieldDesc(ConnectionTypeFieldId),
             const_cast<CSMClusterWindowBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr CSMClusterWindowBase::editHandleConnectionType (void)
{
    SFString::EditHandlePtr returnValue(
        new  SFString::EditHandle(
             &_sfConnectionType,
             this->getType().getFieldDesc(ConnectionTypeFieldId),
             this));


    editSField(ConnectionTypeFieldMask);

    return returnValue;
}

GetFieldHandlePtr CSMClusterWindowBase::getHandleClusterMode     (void) const
{
    SFString::GetHandlePtr returnValue(
        new  SFString::GetHandle(
             &_sfClusterMode,
             this->getType().getFieldDesc(ClusterModeFieldId),
             const_cast<CSMClusterWindowBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr CSMClusterWindowBase::editHandleClusterMode    (void)
{
    SFString::EditHandlePtr returnValue(
        new  SFString::EditHandle(
             &_sfClusterMode,
             this->getType().getFieldDesc(ClusterModeFieldId),
             this));


    editSField(ClusterModeFieldMask);

    return returnValue;
}

GetFieldHandlePtr CSMClusterWindowBase::getHandleComposer        (void) const
{
    SFUnrecImageComposerPtr::GetHandlePtr returnValue(
        new  SFUnrecImageComposerPtr::GetHandle(
             &_sfComposer,
             this->getType().getFieldDesc(ComposerFieldId),
             const_cast<CSMClusterWindowBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr CSMClusterWindowBase::editHandleComposer       (void)
{
    SFUnrecImageComposerPtr::EditHandlePtr returnValue(
        new  SFUnrecImageComposerPtr::EditHandle(
             &_sfComposer,
             this->getType().getFieldDesc(ComposerFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&CSMClusterWindow::setComposer,
                    static_cast<CSMClusterWindow *>(this), _1));

    editSField(ComposerFieldMask);

    return returnValue;
}

GetFieldHandlePtr CSMClusterWindowBase::getHandleOptions         (void) const
{
    SFUnrecChildCSMClusterWinOptionsPtr::GetHandlePtr returnValue(
        new  SFUnrecChildCSMClusterWinOptionsPtr::GetHandle(
             &_sfOptions,
             this->getType().getFieldDesc(OptionsFieldId),
             const_cast<CSMClusterWindowBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr CSMClusterWindowBase::editHandleOptions        (void)
{
    SFUnrecChildCSMClusterWinOptionsPtr::EditHandlePtr returnValue(
        new  SFUnrecChildCSMClusterWinOptionsPtr::EditHandle(
             &_sfOptions,
             this->getType().getFieldDesc(OptionsFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&CSMClusterWindow::setOptions,
                    static_cast<CSMClusterWindow *>(this), _1));

    editSField(OptionsFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void CSMClusterWindowBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    CSMClusterWindow *pThis = static_cast<CSMClusterWindow *>(this);

    pThis->execSync(static_cast<CSMClusterWindow *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *CSMClusterWindowBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    CSMClusterWindow *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const CSMClusterWindow *>(pRefAspect),
                  dynamic_cast<const CSMClusterWindow *>(this));

    return returnValue;
}
#endif

void CSMClusterWindowBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<CSMClusterWindow *>(this)->setClientWindow(NULL);

    static_cast<CSMClusterWindow *>(this)->setComposer(NULL);

    static_cast<CSMClusterWindow *>(this)->setOptions(NULL);

#ifdef OSG_MT_CPTR_ASPECT
    AspectOffsetStore oOffsets;

    _pAspectStore->fillOffsetArray(oOffsets, this);
#endif

#ifdef OSG_MT_CPTR_ASPECT
    _mfServers.terminateShare(Thread::getCurrentAspect(),
                                      oOffsets);
#endif
#ifdef OSG_MT_CPTR_ASPECT
    _mfServerIds.terminateShare(Thread::getCurrentAspect(),
                                      oOffsets);
#endif
}


OSG_END_NAMESPACE
