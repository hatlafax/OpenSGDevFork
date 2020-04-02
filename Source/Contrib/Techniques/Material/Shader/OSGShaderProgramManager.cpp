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

#include "OSGShaderProgramManager.h"

#include "OSGShaderCodeGenerator.h"
#include "OSGShaderDesc.h"
#include "OSGShaderProgram.h"

#include "OSGHashKeyToFieldContainerMap.h"

#include "OSGBaseHash.h"

#ifdef _DEBUG
#define OSG_READ_SHADER_CODE_FROM_FILE
#define OSG_WRITE_SHADER_CODE_TO_FILE
#define OSG_SHADER_CODE_FILE    "Shader"

int shader_code_filename_counter = 0;
int requested_shader_code_filename_counter = 0;
#endif

OSG_BEGIN_NAMESPACE

#if defined(OSG_READ_SHADER_CODE_FROM_FILE) || defined(OSG_WRITE_SHADER_CODE_TO_FILE)
static std::string getShaderCodeFile()
{
    std::string file;
    const Char8* name  =  getenv(OSG_NAMESPACE_PREFIX"_LOG_FILE");
    if (name)
    {
        file = name;
        const std::size_t pos = file.find_last_of("/\\");
        if (pos != std::string::npos && file.size() > pos+1)
        {
            file = file.substr(0, pos+1);
            file += OSG_SHADER_CODE_FILE;
        }
    }

    if (file.empty())
    {
        file = OSG_SHADER_CODE_FILE;
    }

    return file;
}
#endif

// Documentation for this class is emitted in the
// OSGShaderProgramManagerBase.cpp file.
// To modify it, please change the .fcd file (OSGShaderProgramManager.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderProgramManager::initMethod(InitPhase ePhase)
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

ShaderProgramManager::ShaderProgramManager(void) :
    Inherited()
{
}

ShaderProgramManager::ShaderProgramManager(const ShaderProgramManager &source) :
    Inherited(source)
{
}

ShaderProgramManager::~ShaderProgramManager(void)
{
}

/*--------------------------- Create --------------------------------------*/

void ShaderProgramManager::onCreate(const ShaderProgramManager *source)
{
    Inherited::onCreate(source);

    if(GlobalSystemState == Startup)
        return;

    HashKeyToFieldContainerMapUnrecPtr programMap = HashKeyToFieldContainerMap::createLocal();
    setProgramMap(programMap);
}

void ShaderProgramManager::onCreateAspect(
    const ShaderProgramManager *createAspect,
    const ShaderProgramManager *source      )
{
    Inherited::onCreateAspect(createAspect, source);
}

void ShaderProgramManager::onDestroy(UInt32 uiContainerId)
{
    setProgramMap(NULL);

    Inherited::onDestroy(uiContainerId);
}

/*----------------------------- class specific ----------------------------*/

void ShaderProgramManager::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ShaderProgramManager::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ShaderProgramManager NI" << std::endl;
}

/*------------------------------- Interface -------------------------------*/

void ShaderProgramManager::clearPrograms()
{
    getProgramMap()->clear();
}

void ShaderProgramManager::createProgram(ShaderDesc* shaderDesc, ShaderCodeGenerator* generator)
{
    if (shaderDesc)
    {
        const std::string& prg = shaderDesc->getProgram();
        if (!prg.empty())
        {
            KeyType hash = Hash64::hash(&prg[0], prg.size());

            ShaderProgram* shaderProgram = getShaderProgram(hash);
            if (shaderProgram)
            {
                shaderDesc->setShaderProgram(shaderProgram);
                shaderDesc->setHash(hash);
            }
            else
            {
                switch(shaderDesc->getShaderType())
                {
                    case GL_VERTEX_SHADER:
                        createVertexProgram  (shaderDesc, hash, generator);
                        break;
                    case GL_FRAGMENT_SHADER:
                        createFragmentProgram(shaderDesc, hash, generator);
                        break;
                }
            }
        }
    }
}

void ShaderProgramManager::createVertexProgram(
    ShaderDesc*            shaderDesc, 
    KeyParamType           hash, 
    ShaderCodeGenerator*   generator)
{
    ShaderProgramUnrecPtr vertShader = ShaderProgram::createVertexShader();

    createDefaultAttribMapping(vertShader);

#if defined(OSG_READ_SHADER_CODE_FROM_FILE) || defined(OSG_WRITE_SHADER_CODE_TO_FILE)
    std::stringstream shader_file;
    shader_file << getShaderCodeFile() << "_" << shader_code_filename_counter << ".vert" << std::flush;
#endif

#ifdef OSG_WRITE_SHADER_CODE_TO_FILE
    {
        std::ofstream ofs(shader_file.str().c_str());
        ofs << shaderDesc->getProgram() << std::endl << std::flush;
    }
#endif

#ifdef OSG_READ_SHADER_CODE_FROM_FILE
    {
        std::ifstream ifs(shader_file.str().c_str());
        std::stringstream buffer;
        buffer << ifs.rdbuf();
        vertShader->setProgram(buffer.str());
    }
#else
    vertShader->setProgram(shaderDesc->getProgram());
#endif
    
    OSG_ASSERT(shaderDesc->getMFUniformBlockNames      ()->size() == shaderDesc->getMFUniformBindingPnts      ()->size());
    OSG_ASSERT(shaderDesc->getMFShaderStorageBlockNames()->size() == shaderDesc->getMFShaderStorageBindingPnts()->size());

    UInt32 sz = shaderDesc->getMFUniformBlockNames()->size32();

    for (UInt32 i = 0; i < sz; ++i)
    {
        const std::string& blockName  = shaderDesc->getUniformBlockNames (i);
        Int32              bindingPnt = shaderDesc->getUniformBindingPnts(i);

        vertShader->addUniformBlock(blockName.c_str(), bindingPnt);
    }

    sz = shaderDesc->getMFShaderStorageBlockNames()->size32();

    for (UInt32 i = 0; i < sz; ++i)
    {
        const std::string& blockName  = shaderDesc->getShaderStorageBlockNames (i);
        Int32              bindingPnt = shaderDesc->getShaderStorageBindingPnts(i);

        vertShader->addShaderStorageBlock(blockName.c_str(), bindingPnt);
    }

    sz = shaderDesc->getMFOSGVariables()->size32();

    for (UInt32 i = 0; i < sz; ++i)
    {
        const std::string& variable  = shaderDesc->getOSGVariables(i);

        vertShader->addOSGVariable(variable.c_str());
    }

    getProgramMap()->insert(hash, vertShader);

    shaderDesc->setShaderProgram(vertShader);
    shaderDesc->setHash(hash);

    if(_sfInitCallback.getValue()._func)
    {
        _sfInitCallback.getValue()._func(vertShader);
    }
}

void ShaderProgramManager::createFragmentProgram(
    ShaderDesc*            shaderDesc, 
    KeyParamType           hash, 
    ShaderCodeGenerator*   generator)
{
    ShaderProgramUnrecPtr fragShader = ShaderProgram::createFragmentShader();

#if defined(OSG_READ_SHADER_CODE_FROM_FILE) || defined(OSG_WRITE_SHADER_CODE_TO_FILE)
    std::stringstream shader_file;
    shader_file << getShaderCodeFile() << "_" << shader_code_filename_counter << ".frag" << std::flush;
#endif

#ifdef OSG_WRITE_SHADER_CODE_TO_FILE
    {
        std::ofstream ofs(shader_file.str().c_str());
        ofs << shaderDesc->getProgram() << std::endl << std::flush;
    }
#endif

#ifdef OSG_READ_SHADER_CODE_FROM_FILE
    {
        std::ifstream ifs(shader_file.str().c_str());
        std::stringstream buffer;
        buffer << ifs.rdbuf();
        fragShader->setProgram(buffer.str());
    }
#else
    fragShader->setProgram(shaderDesc->getProgram());
#endif

#if defined(OSG_READ_SHADER_CODE_FROM_FILE) || defined(OSG_WRITE_SHADER_CODE_TO_FILE)
    shader_code_filename_counter++;
#endif

    OSG_ASSERT(shaderDesc->getMFUniformBlockNames      ()->size() == shaderDesc->getMFUniformBindingPnts      ()->size());
    OSG_ASSERT(shaderDesc->getMFShaderStorageBlockNames()->size() == shaderDesc->getMFShaderStorageBindingPnts()->size());

    UInt32 sz = shaderDesc->getMFUniformBlockNames()->size32();

    for (UInt32 i = 0; i < sz; ++i)
    {
        const std::string& blockName  = shaderDesc->getUniformBlockNames (i);
        Int32              bindingPnt = shaderDesc->getUniformBindingPnts(i);

        fragShader->addUniformBlock(blockName.c_str(), bindingPnt);
    }

    sz = shaderDesc->getMFShaderStorageBlockNames()->size32();

    for (UInt32 i = 0; i < sz; ++i)
    {
        const std::string& blockName  = shaderDesc->getShaderStorageBlockNames (i);
        Int32              bindingPnt = shaderDesc->getShaderStorageBindingPnts(i);

        fragShader->addShaderStorageBlock(blockName.c_str(), bindingPnt);
    }

    sz = shaderDesc->getMFOSGVariables()->size32();

    for (UInt32 i = 0; i < sz; ++i)
    {
        const std::string& variable  = shaderDesc->getOSGVariables(i);

        fragShader->addOSGVariable(variable.c_str());
    }

    getProgramMap()->insert(hash, fragShader);

    shaderDesc->setShaderProgram(fragShader);
    shaderDesc->setHash(hash);

    if(_sfInitCallback.getValue()._func)
    {
        _sfInitCallback.getValue()._func(fragShader);
    }
}

void ShaderProgramManager::createDefaultAttribMapping(ShaderProgram* shader)
{
    if (shader && shader->getShaderType() == GL_VERTEX_SHADER)
    {
        shader->setProgramAttribute(ShaderConstants::Attribute0Index, "aVertex"        );
        shader->setProgramAttribute(ShaderConstants::Attribute2Index, "aNormal"        );
        shader->setProgramAttribute(ShaderConstants::Attribute3Index, "aColor"         );
        shader->setProgramAttribute(ShaderConstants::Attribute4Index, "aSecondaryColor");
        shader->setProgramAttribute(ShaderConstants::Attribute5Index, "aTangent"       );
        shader->setProgramAttribute(ShaderConstants::Attribute6Index, "aBitangent"     );
        //shader->setProgramAttribute(ShaderConstants::Attribute7Index, "aUnknown"      );
        shader->setProgramAttribute(ShaderConstants::Attribute8Index, "aTexCoords0"    );
        shader->setProgramAttribute(ShaderConstants::Attribute9Index, "aTexCoords1"    );
        shader->setProgramAttribute(ShaderConstants::Attribute10Index,"aTexCoords2"    );
        shader->setProgramAttribute(ShaderConstants::Attribute11Index,"aTexCoords3"    );
        shader->setProgramAttribute(ShaderConstants::Attribute12Index,"aTexCoords4"    );
        shader->setProgramAttribute(ShaderConstants::Attribute13Index,"aTexCoords5"    );
        shader->setProgramAttribute(ShaderConstants::Attribute14Index,"aTexCoords6"    );
        shader->setProgramAttribute(ShaderConstants::Attribute15Index,"aTexCoords7"    );
    }
}

void ShaderProgramManager::updateProgram()
{
    if(_sfUpdateCallback.getValue()._func)
    {
        UInt32 sz = getProgramMap()->size();

        for(UInt32 idx = 0; idx < sz; ++idx)
        {
            ShaderProgram* shaderProgram = getShaderProgram(idx);
            if (shaderProgram)
            {
                _sfUpdateCallback.getValue()._func(shaderProgram);
            }
        }
    }
}

void ShaderProgramManager::setInitCallback(ShaderProgramFunctor func, const std::string& createSymbol)
{
    ShaderProgramFunctorCallback oTmp;

    oTmp._func         = func;
    oTmp._createSymbol = createSymbol;

    _sfInitCallback.setValue(oTmp);
}

void ShaderProgramManager::setUpdateCallback(ShaderProgramFunctor func, const std::string& createSymbol)
{
    ShaderProgramFunctorCallback oTmp;

    oTmp._func         = func;
    oTmp._createSymbol = createSymbol;

    _sfUpdateCallback.setValue(oTmp);
}

OSG_END_NAMESPACE
