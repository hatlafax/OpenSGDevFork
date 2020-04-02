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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGShaderManager.h"
#include "OSGShaderProgramManager.h"

#include "OSGMaterialDesc.h"
#include "OSGShaderDesc.h"
#include "OSGShaderDescStore.h"

#include "OSGHashKeyToFieldContainerMap.h"
#include "OSGShaderProgramChunk.h"
#include "OSGShaderCodeGenerator.h"

#include "OSGDescMaterial.h" // ToDo: Please remove me I'm here only for debugging

#include "OSGBaseHash.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGShaderManagerBase.cpp file.
// To modify it, please change the .fcd file (OSGShaderManager.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderManager::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShaderManager::ShaderManager(void) :
    Inherited()
{
}

ShaderManager::ShaderManager(const ShaderManager &source) :
    Inherited(source)
{
}

ShaderManager::~ShaderManager(void)
{
}

/*--------------------------- Create --------------------------------------*/

void ShaderManager::onCreate(const ShaderManager *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
        return;

    HashKeyToFieldContainerMapUnrecPtr programChunkMap = HashKeyToFieldContainerMap::createLocal();
    setProgramChunkMap(programChunkMap);
}

void ShaderManager::onCreateAspect(
    const ShaderManager *createAspect,
    const ShaderManager *source      )
{
    Inherited::onCreateAspect(createAspect, source);
}

void ShaderManager::onDestroy(UInt32 uiContainerId)
{
    setProgramChunkMap(NULL);

    Inherited::onDestroy(uiContainerId);
}

/*----------------------------- class specific ----------------------------*/

void ShaderManager::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ShaderManager::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ShaderManager NI" << std::endl;
}

/*------------------------------- Interface -------------------------------*/

ShaderProgramChunk* ShaderManager::getShaderProgramChunk(
    ChunkMaterial* chunkMat)
{
    ShaderProgramChunkUnrecPtr shaderProgramChunk = NULL;

    ShaderProgramManager* shaderPrgMan = getProgramManager();

    if (chunkMat && shaderPrgMan)
    {
        ShaderCodeGenerator* generator = getCodeGenerator();

        if (generator && generator->bUseCapabilities(CapabilitiesDesc::SHADER_MATERIAL))
        {
            ShaderDescStoreUnrecPtr shaderDescStore = generator->getShaderDescStore(chunkMat);

            if (shaderDescStore != NULL)
            {
                MFUnrecShaderDescPtr* store = shaderDescStore->editMFStore();

                MFUnrecShaderDescPtr::iterator iter = store->begin();
                MFUnrecShaderDescPtr::iterator end  = store->end  ();

                Hash64 hasher;

                for (; iter != end; ++iter)
                {
                    ShaderDesc* shaderDesc = *iter;
                    shaderPrgMan->createProgram(shaderDesc, generator);

                    if (shaderDesc->getShaderProgram() && shaderDesc->getHash() != 0)
                    {
                        hasher.update(shaderDesc->getHash());
                    }
                }

                KeyType hash = hasher.finish();

                if (hash > 0)
                {
                    shaderProgramChunk = getShaderProgramChunk(hash);

                    if (shaderProgramChunk == NULL)
                    {
                        shaderProgramChunk = ShaderProgramChunk::createLocal();

                        iter = store->begin();
                        end  = store->end  ();

                        for (; iter != end; ++iter)
                        {
                            ShaderDesc* shaderDesc = *iter;
                            shaderProgramChunk->addShader(shaderDesc->getShaderProgram());
                        }

                        getProgramChunkMap()->insert(hash, shaderProgramChunk);
                    }
                }
            }
        }
    }

    return shaderProgramChunk;
}

void ShaderManager::clearShaderProgramChunks()
{
    getProgramChunkMap()->clear();

    ShaderProgramManager* shaderPrgMan = getProgramManager();

    if (shaderPrgMan)
    {
        shaderPrgMan->clearPrograms();
    }
}

OSG_END_NAMESPACE
