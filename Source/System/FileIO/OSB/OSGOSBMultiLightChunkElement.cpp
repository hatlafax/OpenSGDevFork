/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                   Copyright (C) 2009 by the OpenSG Forum                  *
 *                                                                           *
 *                            www.opensg.org                                 *
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

#include "OSGOSBMultiLightChunkElement.h"

#include "OSGOSBRootElement.h"

#include "OSGGroup.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBMultiLightChunkElement                                               */
/*-------------------------------------------------------------------------*/

/*! Reads the mofified MultiLightChunk from an osb and converts it to a
    descent MultiLightChunk object.
 */

/*-------------------------------------------------------------------------*/
/* Static members                                                          */

OSBElementRegistrationHelper<OSBMultiLightChunkElement>
    OSBMultiLightChunkElement::_regHelper =
        OSBElementRegistrationHelper<OSBMultiLightChunkElement>("MultiLightChunk");

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

OSBMultiLightChunkElement::OSBMultiLightChunkElement(OSBRootElement *root) :

     Inherited  (root, OSGOSBHeaderVersion200)
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

OSBMultiLightChunkElement::~OSBMultiLightChunkElement(void)
{
}

/*-------------------------------------------------------------------------*/
/* Reading                                                                 */

void
OSBMultiLightChunkElement::read(const std::string &typeName)
{
    OSG_OSB_LOG(("OSBMultiLightChunkElement::read: [%s]\n", typeName.c_str()));

    BinaryReadHandler *rh = editRoot()->getReadHandler();
    
    UInt8  ptrTypeTag;
    UInt16 version;

    rh->getValue(ptrTypeTag);
    rh->getValue(version   );

    OSG_OSB_LOG(("OSBMultiLightChunkElement::read: version: [%u] ptrTypeTag [%u]\n",
                 version, ptrTypeTag));

    setContainer(FieldContainerUnrecPtr(
        FieldContainerFactory::the()->createContainer(typeName.c_str())));

    if(getContainer() == NULL)
    {
        FWARNING(("OSBMultiLightChunkElement::read: Skipping unknown "
                  "FieldContainer [%s].\n", typeName.c_str()));

        skipFields();

        setContainer(FieldContainerUnrecPtr(createReplacementFC(ptrTypeTag)));
        return;
    }

    readFields("", "");
}

void
OSBMultiLightChunkElement::postRead(void)
{
    Inherited::postRead();
}

/*-------------------------------------------------------------------------*/
/* Writing                                                                 */

void
OSBMultiLightChunkElement::preWrite(FieldContainer * const fc)
{
    OSG_OSB_LOG(("OSBMultiLightChunkElement::preWrite\n"));

    preWriteFieldContainer(fc, "");
}

void
OSBMultiLightChunkElement::write(void)
{
    OSG_OSB_LOG(("OSBMultiLightChunkElement::write\n"));
    
    if(getContainer() == NULL)
    {
        FWARNING(("OSBMultiLightChunkElement::write: Attempt to write NULL.\n"));
        return;
    }

    BinaryWriteHandler *wh = editRoot()->getWriteHandler();

    wh->putValue(getFCPtrType(getContainer()));
    wh->putValue(getVersion()                );

    writeFields("", true);
}

std::string
OSBMultiLightChunkElement::readFields(const std::string &excludeFields,
                                      const std::string &endMarkers    )
{
    std::string         fieldName  = "";
    PtrFieldListIt      ptrFieldIt;

    while(true)
    {
        std::string fieldTypeName;
        UInt32      fieldSize;

        if(!readFieldHeader(endMarkers, fieldName,
                            fieldTypeName, fieldSize))
        {
            OSG_OSB_LOG(("OSBCommonElement::readFields: "
                    "Reading stopped at field: [%s].\n", fieldName.c_str() ));
            break;
        }

        //
        // MultiLightChunk just changed the name of the MFUInt8 from "type" to "typeOfLight".
        // The layout stayed fixed.
        //
        if (fieldName == "type")
        {
            fieldName = "typeOfLight";
        }

        readFieldContent(fieldName, fieldTypeName, fieldSize,
                         excludeFields, ptrFieldIt           );
    }

    return fieldName;
}
