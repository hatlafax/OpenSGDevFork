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

#include "OSGDescMaterialManager.h"
#include "OSGHashKeyToFieldContainerMap.h"
#include "OSGMaterialFactory.h"
#include "OSGDescMaterial.h"

#include "OSGDescMaterialShaderCodeGenerator.h"
#include "OSGDescMaterialFactory.h"
#include "OSGShaderManager.h"
#include "OSGShaderProgramManager.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDescMaterialManagerBase.cpp file.
// To modify it, please change the .fcd file (OSGDescMaterialManager.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DescMaterialManager::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

DescMaterialManagerTransitPtr DescMaterialManager::createDefault()
{
    ShaderProgramManagerUnrecPtr shaderProgManager = ShaderProgramManager::createLocal();
    DescMaterialShaderCodeGeneratorUnrecPtr generator = DescMaterialShaderCodeGenerator::createLocal();

    ShaderManagerUnrecPtr shaderManager = ShaderManager::createLocal();
    shaderManager->setProgramManager(shaderProgManager);
    shaderManager->setCodeGenerator(generator);

    DescMaterialFactoryUnrecPtr factory = DescMaterialFactory::createLocal();
    factory->setShaderManager(shaderManager);

    DescMaterialManagerUnrecPtr manager = DescMaterialManager::createLocal();
    manager->setMaterialFactory(factory);

    return DescMaterialManagerTransitPtr(manager);
}

DescMaterialManagerTransitPtr DescMaterialManager::createDefault(
    ShaderProgramFunctor   initFunctor, const std::string&   initSymbol,
    ShaderProgramFunctor updateFunctor, const std::string& updateSymbol)
{
    DescMaterialManagerUnrecPtr manager = DescMaterialManager::createDefault();

    MaterialFactory*      factory          = manager->getMaterialFactory();
    ShaderManager*        shaderManager    = factory->getShaderManager();
    ShaderProgramManager* shaderPrgManager = shaderManager->getProgramManager();

    shaderPrgManager->setInitCallback  (  initFunctor,   initSymbol);
    shaderPrgManager->setUpdateCallback(updateFunctor, updateSymbol);

    return DescMaterialManagerTransitPtr(manager);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DescMaterialManager::DescMaterialManager(void) :
    Inherited()
{
}

DescMaterialManager::DescMaterialManager(const DescMaterialManager &source) :
    Inherited(source)
{
}

DescMaterialManager::~DescMaterialManager(void)
{
}

/*--------------------------- Create --------------------------------------*/

void DescMaterialManager::onCreate(const DescMaterialManager *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
        return;

    HashKeyToFieldContainerMapUnrecPtr materialMap = HashKeyToFieldContainerMap::createLocal();
    HashKeyToFieldContainerMapUnrecPtr imageMap    = HashKeyToFieldContainerMap::createLocal();

    setMaterialMap(materialMap);
    setImageMap   (imageMap);
}

void DescMaterialManager::onCreateAspect(
    const DescMaterialManager *createAspect,
    const DescMaterialManager *source      )
{
    Inherited::onCreateAspect(createAspect, source);
}

void DescMaterialManager::onDestroy(UInt32 uiContainerId)
{
    setMaterialMap(NULL);
    setImageMap   (NULL);

    Inherited::onDestroy(uiContainerId);
}

/*--------------------------- Utilities -----------------------------------*/

ShaderCodeGenerator* DescMaterialManager::getShaderCodeGenerator() const
{
    MaterialFactory* factory = getMaterialFactory();
    if (factory)
    {
        ShaderManager* shaderManager = factory->getShaderManager();
        if (shaderManager)
        {
            return shaderManager->getCodeGenerator();
        }
    }
    return NULL;
}

bool DescMaterialManager::setCapabilities(const UInt32 platform, const UInt32 requested) const
{
    ShaderCodeGenerator* generator = getShaderCodeGenerator();
    if (generator)
    {
        generator->setPlatformCapabilities (platform );
        generator->setRequestedCapabilities(requested);

        generator->updateEnvironment(getWindow());

        return true;
    }

    return false;
}

bool DescMaterialManager::setEnvironmentDesc(EnvironmentDesc* envDesc) const
{
    DescMaterialFactory* factory = dynamic_cast<DescMaterialFactory*>(getMaterialFactory());
    if (factory)
    {
        factory->setEnvironmentDesc(envDesc);

        return true;
    }

    return false;
}

bool DescMaterialManager::setHDR2Stage(HDR2Stage* stage) const
{
    ShaderCodeGenerator* generator = getShaderCodeGenerator();
    if (generator)
    {
        generator->setHDR2Stage(stage);
        return true;
    }

    return false;
}

bool DescMaterialManager::setClusterShadingStage(ClusterShadingStage* stage) const
{
    ShaderCodeGenerator* generator = getShaderCodeGenerator();
    if (generator)
    {
        generator->setClusterShadingStage(stage);
        return true;
    }

    return false;
}

bool DescMaterialManager::setMultiLightShadowStage(MultiLightShadowStage* stage) const
{
    ShaderCodeGenerator* generator = getShaderCodeGenerator();
    if (generator)
    {
        generator->setMultiLightShadowStage(stage);
        return true;
    }

    return false;
}

bool DescMaterialManager::setSSAOStage(SSAOStage* stage) const
{
    ShaderCodeGenerator* generator = getShaderCodeGenerator();
    if (generator)
    {
        generator->setSSAOStage(stage);
        return true;
    }

    return false;
}

bool DescMaterialManager::setIBLStage(IBLStage* stage) const
{
    ShaderCodeGenerator* generator = getShaderCodeGenerator();
    if (generator)
    {
        generator->setIBLStage(stage);
        return true;
    }

    return false;
}

bool DescMaterialManager::setMultiLightGroup(MultiLightGroup* group) const
{
    ShaderCodeGenerator* generator = getShaderCodeGenerator();
    if (generator)
    {
        generator->setMultiLightGroup(group);
        return true;
    }

    return false;
}

bool DescMaterialManager::setLightBindingPnt(UInt32 idx) const
{
    ShaderCodeGenerator* generator = getShaderCodeGenerator();
    if (generator)
    {
        generator->setLightBindingPnt(idx);
        return true;
    }

    return false;
}

bool DescMaterialManager::setHasClipPlanes(bool flag ) const
{
    ShaderCodeGenerator* generator = getShaderCodeGenerator();
    if (generator)
    {
        generator->setHasClipPlanes(flag);
        return true;
    }

    return false;
}

/*----------------------------- class specific ----------------------------*/

void DescMaterialManager::changed(ConstFieldMaskArg whichField, 
                                  UInt32            origin,
                                  BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DescMaterialManager::dump(      UInt32    ,
                               const BitVector ) const
{
    SLOG << "Dump DescMaterialManager NI" << std::endl;
}

/*----------------------------- Interface ---------------------------------*/

DescMaterialManager::ManagedMaterialT DescMaterialManager::addMaterial(MaterialDesc* matDesc)
{
    ManagedMaterialT result = std::make_pair(0, nullptr);

    if (matDesc)
    {
        ShaderCodeGenerator* generator = getShaderCodeGenerator();

        //
        // Inject the exclude hashing mask into the material description. All managed
        // materials should behave equal
        //
        matDesc->setExcludeHashingMask(getExcludeHashingMask());

        //
        // The generator environment state decides over the actual material shader setup.
        //
        if (generator)
        {
            //
            // The resulting environment hash might be used for further update checking.
            // However, our first implementation does not do this. The MaterialDesc::descHash
            // field is not taken into account on generating the hash value by function
            // MaterialDesc::getHashValue().
            //
            KeyType envHash = generator->getEnvironmentHash(getWindow());

            if (getEvalEnvironmentHash() == true)
            {
                matDesc->setDescHash(envHash);
            }
        }

        KeyType hash = matDesc->getHashValue();

        if (hash > 0)
        {
            //
            // Do we already have the requested material?
            //
            ChunkMaterial* mat = getMaterial(hash);
            if (mat)
            {
                result = std::make_pair(hash, mat);
            }
            else
            {
                //
                // Build a new material and track it in the manager.
                //
                MaterialFactory* factory = getMaterialFactory();
                if (factory)
                {
                    ChunkMaterialUnrecPtr material = factory->getMaterial(matDesc);
                    getMaterialMap()->insert(hash, material);

                    result = std::make_pair(hash, material);
                }
            }
        }
    }

    return result;
}

bool DescMaterialManager::addMaterial(KeyParamType key, ChunkMaterial* mat)
{
    //
    // Add the given material only, if it not already found in the manager.
    //
    if (mat == NULL || key == 0 || hasMaterial(key))
    {
        return false;
    }

    //
    // Only add valid materials
    //
    DescMaterial* descMaterial = dynamic_cast<DescMaterial*>(mat);

    if (descMaterial == NULL || descMaterial->getMaterialDesc() == NULL)
    {
        return false;
    }

    //
    // Consistency check!
    //
    KeyType hash = descMaterial->getMaterialDesc()->getHashValue();

    if (key != hash)
    {
        return false;
    }

    //
    // Track the provided material
    // 
    getMaterialMap()->insert(hash, descMaterial);

    //
    // By updating, the shader programs and the shader program chunk are recreated
    // if necessary and added to the shader managers, respectively.
    //
    ManagedMaterialT result = updateMaterial(key);

    OSG_ASSERT(key == result.first);

    return true;
}

DescMaterialManager::ManagedMaterialT DescMaterialManager::updateMaterial(KeyParamType key)
{
    ManagedMaterialT result = std::make_pair(0, nullptr);

    //
    // We are interested only in existing ...
    //
    DescMaterial* descMaterial = dynamic_cast<DescMaterial*>(getMaterialMap()->find(key));
    if (descMaterial)
    {
        // ... valid description materials
        MaterialDesc* matDesc = descMaterial->getMaterialDesc();

        if (matDesc)
        {
            //
            // If the matDesc hash is unequal to the key we basically need to add a new
            // material. In this case only, the  result contains a pointer to the new
            // ChunkMaterial in its second slot.
            //
            KeyType hash = matDesc->getHashValue();

            if (hash != key)
            {
                result = addMaterial(matDesc);

                //
                // After the creation process, we try to remove the old material entry.
                // The entry can savely be removed if the ChunkMaterial reference count
                // equals one.
                //
                removeMaterial(key);

                return result;
            }
            else
            {
                //
                // The generator environment state decides over the actual material shader setup.
                //
                ShaderCodeGenerator* generator = getShaderCodeGenerator();
                if (generator)
                {
                    if (generator)
                    {
                        //
                        // The resulting environment hash might be used for further update checking.
                        // However, our first implementation does not do this. The MaterialDesc::descHash
                        // field is not taken into account on generating the hash value by function
                        // MaterialDesc::getHashValue().
                        //
                        KeyType envHash = generator->getEnvironmentHash(getWindow());

                        if (getEvalEnvironmentHash() == true)
                        {
                            matDesc->setDescHash(envHash);
                        }
                    }

                    MaterialFactory* factory = getMaterialFactory();
                    if (factory)
                    {
                        //
                        // The factory updateMaterial call performs exactly the same actions as the 
                        // the factory getMaterial(matDesc) call in the addMaterial function. The only
                        // difference is, that no new ChunkMaterial is created!
                        //
                        factory->updateMaterial(descMaterial);
                    }
                    
                    //
                    // We signal success by returning the key back to caller.
                    //
                    result.first = key;

                    return result;
                }
            }
        }
    }
    return result;
}

DescMaterialManager::KeyTypeStore DescMaterialManager::updateMaterials()
{
    KeyTypeStore failures;

    HashKeyToFieldContainerMap* materialMap = getMaterialMap();
    
    UInt32 sz = materialMap->size();
    for (UInt32 idx = 0; idx < sz; ++idx)
    {
        KeyParamType    key = materialMap->key(idx);
        FieldContainer* fc  = materialMap->at(idx);

        DescMaterial* descMaterial = dynamic_cast<DescMaterial*>(fc);

        if (descMaterial)
        {
            // ... valid description materials
            MaterialDesc* matDesc = descMaterial->getMaterialDesc();

            if (matDesc)
            {
                //
                // If the matDesc hash is unequal to the key we basically need to add a new
                // material. That can't be handled by this function
                //
                KeyType hash = matDesc->getHashValue();

                if (hash != key)
                {
                    failures.push_back(key);
                }
                else
                {
                    //
                    // The generator environment state decides over the actual material shader setup.
                    //
                    ShaderCodeGenerator* generator = getShaderCodeGenerator();
                    if (generator)
                    {
                        if (generator)
                        {
                            //
                            // The resulting environment hash might be used for further update checking.
                            // However, our first implementation does not do this. The MaterialDesc::descHash
                            // field is not taken into account on generating the hash value by function
                            // MaterialDesc::getHashValue().
                            //
                            KeyType envHash = generator->getEnvironmentHash(getWindow());

                            if (getEvalEnvironmentHash() == true)
                            {
                                matDesc->setDescHash(envHash);
                            }
                        }

                        MaterialFactory* factory = getMaterialFactory();
                        if (factory)
                        {
                            //
                            // The factory updateMaterial call performs exactly the same actions as the 
                            // the factory getMaterial(matDesc) call in the addMaterial function. The only
                            // difference is, that no new ChunkMaterial is created!
                            //
                            factory->updateMaterial(descMaterial);
                        }
                    }
                }
            }
        }
    }

    return failures;
}

bool DescMaterialManager::removeMaterial(KeyParamType key)
{
    //
    // Only remove material from manager if nobody is 
    // anymore interested in it
    //
    ChunkMaterial* m = getMaterial(key);
    if (m->getRefCount() == 1)
    {
        bool result = getMaterialMap()->erase(key);
        return result;
    }

    return false;
}

void DescMaterialManager::clear()
{
    //
    // Be aware that this operation completely clears the
    // manager inclusive the associated shader managers.
    //
    getMaterialMap()->clear();
    getImageMap()   ->clear();

    MaterialFactory* factory = getMaterialFactory();
    factory->clearShaders();
}

void DescMaterialManager::recycle()
{
    std::stack<KeyType> dispose;

    HashKeyToFieldContainerMap* materialMap = getMaterialMap();
    
    UInt32 sz = materialMap->size();
    for (UInt32 idx = 0; idx < sz; ++idx)
    {
        KeyParamType    key = materialMap->key(idx);
        FieldContainer* fc  = materialMap->at(idx);

        if (fc && fc->getRefCount() == 1)
        {
            dispose.push(key);
        }
    }

    while (!dispose.empty())
    {
        KeyParamType key = dispose.top();
        materialMap->erase(key);
        dispose.pop();
    }
}

ChunkMaterial* DescMaterialManager::getMaterial(KeyParamType key) const
{
    return dynamic_cast<ChunkMaterial*>(getMaterialMap()->find(key));
}

const MaterialDesc* DescMaterialManager::getMaterialDesc(KeyParamType key) const
{
    DescMaterial* descMaterial = dynamic_cast<DescMaterial*>(getMaterial(key));
    if (descMaterial)
    {
        return descMaterial->getMaterialDesc();
    }

    return NULL;
}

bool DescMaterialManager::hasMaterial(KeyParamType key) const
{
    return getMaterial(key) != NULL;
}

void DescMaterialManager::updateProgram()
{
    MaterialFactory* factory = getMaterialFactory();
    if (factory)
    {
        ShaderManager* shaderManager = factory->getShaderManager();
        if (shaderManager)
        {
            ShaderProgramManager* shaderPrgManager = shaderManager->getProgramManager();
            if (shaderPrgManager)
            {
                shaderPrgManager->updateProgram();
            }
        }
    }
}

OSG_END_NAMESPACE
