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

#include "OSGOSBChunkMaterialElement.h"

#include "OSGOSBRootElement.h"
#include "OSGChunkMaterial.h"

#include "OSGOSBTextureChunkElement.h"
#include "OSGOSBCubeTextureChunkElement.h"
#include "OSGTextureObjChunk.h"
#include "OSGCubeTextureObjChunk.h"
#include "OSGTextureEnvChunk.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/* OSBChunkMaterialElement                                                 */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Static members                                                          */

OSBElementRegistrationHelper<OSBChunkMaterialElement>
    OSBChunkMaterialElement::_regHelper =
        OSBElementRegistrationHelper<OSBChunkMaterialElement>("ChunkMaterial");

OSBElementRegistrationHelper<OSBChunkMaterialElement>
    OSBChunkMaterialElement::_regHelperSimple =
        OSBElementRegistrationHelper<OSBChunkMaterialElement>("SimpleMaterial");

/*-------------------------------------------------------------------------*/
/* Constructor                                                             */

OSBChunkMaterialElement::OSBChunkMaterialElement(OSBRootElement *root) :
     Inherited            (root, 
                           OSGOSBHeaderVersion200),
    _mfSlots              (                      ),
    _chunksPtrFieldIt     (                      ),
    _chunksPtrFieldItValid(false                 )
{
}

/*-------------------------------------------------------------------------*/
/* Destructor                                                              */

OSBChunkMaterialElement::~OSBChunkMaterialElement(void)
{
}

/*-------------------------------------------------------------------------*/
/* Reading                                                                 */

void
OSBChunkMaterialElement::read(const std::string &typeName)
{
    OSG_OSB_LOG(("OSBChunkMaterialElement::read [%s]\n", typeName.c_str()));

    BinaryReadHandler *rh = editRoot()->getReadHandler();

    UInt8  ptrTypeId;
    UInt16 version;

    rh->getValue(ptrTypeId);
    rh->getValue(version  );

    OSG_OSB_LOG(("OSBChunkMaterialElement::read: version: [%u]\n", version));

    std::string    fieldName;
    std::string    fieldTypeName;
    UInt32         fieldSize;
    PtrFieldListIt ptrFieldIt;

    ChunkMaterialUnrecPtr pMat = dynamic_pointer_cast<ChunkMaterial>(
        FieldContainerFactory::the()->createContainer(typeName.c_str()));

    setContainer(pMat);

    while(readFieldHeader("", fieldName, fieldTypeName, fieldSize))
    {
        if(fieldName == "slots")
        {
            // read slots field into separate field - the real field gets
            // filled in postRead
            _mfSlots.copyFromBin(*rh);
        }
        else if(fieldName == "chunks")
        {
            // keep an interator to the _mfChunks field contents
            readFieldContent(fieldName, fieldTypeName, fieldSize, "",
                             _chunksPtrFieldIt);

            _chunksPtrFieldItValid = true;
        }
        else
        {
            readFieldContent(fieldName, fieldTypeName, fieldSize, "",
                             ptrFieldIt);
        }
    }
}

void
OSBChunkMaterialElement::postRead(void)
{
    // _mfChunks and _mfSlots have to be kept consistent for ChunkMaterial.
    // Also TextureChunk is split into TextureObjChunk and TextureObjChunk
    // on load, so the slot info has to be duplicated.
    // TODO:
    // It would be better if that handling could be confined to
    // TextureChunkElement, but I've not found a good way to do that and keep
    // the information in _mfSlots correct. -- cneumann

    const OSBRootElement *root   = getRoot();
    ChunkMaterial        *chkMat = 
        dynamic_cast<ChunkMaterial *>(getContainer());
    
    // No chunks loaded
    if(_chunksPtrFieldItValid == false)
        return;

    PtrFieldInfo::PtrIdStoreConstIt idIt  = 
        _chunksPtrFieldIt->getIdStore().begin();
    PtrFieldInfo::PtrIdStoreConstIt idEnd = 
        _chunksPtrFieldIt->getIdStore().end  ();

    for(UInt32 i = 0; idIt != idEnd; ++idIt, ++i)
    {
        OSBRootElement::IdElemMapConstIt mapIt = 
            root->getIdElemMap().find(*idIt);

        if(mapIt == root->getIdElemMap().end())
            continue;

        OSBElementBase             *chunkElem    = mapIt->second;
        OSBTextureChunkElement     *texChunkElem =
            dynamic_cast<OSBTextureChunkElement *>(chunkElem);
        OSBCubeTextureChunkElement *cubeTexChunkElem =
            dynamic_cast<OSBCubeTextureChunkElement *>(chunkElem);

        if(texChunkElem != NULL)
        {
            // TextureChunk
            TextureObjChunk *texObj = texChunkElem->getTexObjChunk();
            TextureEnvChunk *texEnv = texChunkElem->getTexEnvChunk();

            if(i < _mfSlots.size())
            {
                chkMat->addChunk(texObj, _mfSlots[i]);
                chkMat->addChunk(texEnv, _mfSlots[i]);
            }
            else
            {
                chkMat->addChunk(texObj);
                chkMat->addChunk(texEnv);
            }
        }
        else if(cubeTexChunkElem != NULL)
        {
            // TextureChunk
            CubeTextureObjChunk *cubeTexObj = 
                cubeTexChunkElem->getCubeTexObjChunk();
            TextureEnvChunk     *texEnv     = 
                cubeTexChunkElem->getTexEnvChunk();

            if(i < _mfSlots.size())
            {
                chkMat->addChunk(cubeTexObj, _mfSlots[i]);
                chkMat->addChunk(texEnv,     _mfSlots[i]);
            }
            else
            {
                chkMat->addChunk(cubeTexObj);
                chkMat->addChunk(texEnv    );
            }
        }
        else
        {
            // other chunk
            StateChunk *chunk = dynamic_cast<StateChunk *>(chunkElem->getContainer());

            if(i < _mfSlots.size())
            {
                chkMat->addChunk(chunk, _mfSlots[i]);
            }
            else
            {
                chkMat->addChunk(chunk);
            }
        }
    }

    // pointer mapping is already done here for _mfChunks, clear info
    _chunksPtrFieldIt->editIdStore     ().clear();
    _chunksPtrFieldIt->editBindingStore().clear();
}

/*-------------------------------------------------------------------------*/
/* Writing                                                                 */

void
OSBChunkMaterialElement::preWrite(FieldContainer * const fc)
{
    OSG_OSB_LOG(("OSBChunkMaterialElement::preWrite\n"));

    preWriteFieldContainer(fc, "");
}

void
OSBChunkMaterialElement::write(void)
{
    OSG_OSB_LOG(("OSBChunkMaterialElement::write\n"));

    if(getContainer() == NULL)
    {
        FWARNING(("OSBChunkMaterialElement::write: Attempt to write NULL.\n"));
        return;
    }

    BinaryWriteHandler *wh = editRoot()->getWriteHandler();

    wh->putValue(getFCPtrType(getContainer()));
    wh->putValue(getVersion()                );

    writeFields("", true);
}
