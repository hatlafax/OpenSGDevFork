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

#include "OSGDescMaterialFactory.h"

#include "OSGShaderManager.h"
#include "OSGShaderCodeGenerator.h"
#include "OSGShaderProgramChunk.h"

#include "OSGDescMaterial.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDescMaterialFactoryBase.cpp file.
// To modify it, please change the .fcd file (OSGDescMaterialFactory.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DescMaterialFactory::initMethod(InitPhase ePhase)
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

DescMaterialFactory::DescMaterialFactory(void) :
    Inherited()
{
}

DescMaterialFactory::DescMaterialFactory(const DescMaterialFactory &source) :
    Inherited(source)
{
}

DescMaterialFactory::~DescMaterialFactory(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DescMaterialFactory::changed(ConstFieldMaskArg whichField, 
                                  UInt32            origin,
                                  BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DescMaterialFactory::dump(      UInt32    ,
                               const BitVector ) const
{
    SLOG << "Dump DescMaterialFactory NI" << std::endl;
}

/*------------------------------- Interface -------------------------------*/

ChunkMaterialTransitPtr DescMaterialFactory::getMaterial(MaterialDesc* matDesc)
{
    ShaderManager* shaderMan = getShaderManager();

    if (shaderMan)
    {
        DescMaterialUnrecPtr descMaterial = DescMaterial::createLocal();

        descMaterial->setEnvironmentDesc          (getEnvironmentDesc            ());
        descMaterial->setMaterialDesc             (matDesc                         );
        descMaterial->setFragEnvironmentBindingPnt(getFragEnvironmentBindingPnt  ());
        descMaterial->setVertMaterialBindingPnt   (getVertMaterialBindingPnt     ());
        descMaterial->setFragMaterialBindingPnt   (getFragMaterialBindingPnt     ());
        descMaterial->setTexUnitOffset            (getTexUnitOffset              ());
        descMaterial->setCapabilitiesDesc         (shaderMan->getCodeGenerator()
                                                            ->getCapabilitiesDesc());

        commitChanges();

        ShaderProgramChunk* shaderPrgChunk = shaderMan->getShaderProgramChunk(descMaterial);

        if (shaderPrgChunk)
        {
            descMaterial->addChunk(shaderPrgChunk);
        }

        return ChunkMaterialTransitPtr(descMaterial);
    }
    
    return ChunkMaterialTransitPtr(NULL);
}

void DescMaterialFactory::updateMaterial(ChunkMaterial* mat)
{
    ShaderManager* shaderMan = getShaderManager();
    
    DescMaterial* descMaterial = dynamic_cast<DescMaterial*>(mat);

    if (shaderMan && descMaterial)
    {
        descMaterial->setEnvironmentDesc       (getEnvironmentDesc         ());
        descMaterial->setVertMaterialBindingPnt(getVertMaterialBindingPnt  ());
        descMaterial->setFragMaterialBindingPnt(getFragMaterialBindingPnt  ());
        descMaterial->setTexUnitOffset         (getTexUnitOffset           ());
        descMaterial->setCapabilitiesDesc      (shaderMan->getCodeGenerator()->getCapabilitiesDesc());

        commitChanges();

        ShaderProgramChunk* shaderPrgChunk = shaderMan->getShaderProgramChunk(descMaterial);

        bool found = false;

        std::stack<StateChunkUnrecPtr> stack;

        const MFUnrecStateChunkPtr* chunks = descMaterial->getMFChunks();
        MFUnrecStateChunkPtr::const_iterator iter = chunks->begin();
        MFUnrecStateChunkPtr::const_iterator end  = chunks->end();
        for (; iter != end; ++iter)
        {
            StateChunk* chunk = *iter;
            if (!chunk)
                continue;

            if(chunk->getTypeId() == ShaderProgramChunk::getClassTypeId())
            {
                if (chunk == shaderPrgChunk)
                {
                    found = true;
                }
                else
                {
                    stack.push(chunk);
                }
            }
        }

        while (!stack.empty())
        {
            StateChunk* chunk = stack.top();
            descMaterial->subChunk(chunk);
            stack.pop();
        }

        if (shaderPrgChunk && !found)
        {
            descMaterial->addChunk(shaderPrgChunk);
        }
    }
}

void DescMaterialFactory::clearShaders()
{
    ShaderManager* shaderMan = getShaderManager();
    if (shaderMan)
    {
        shaderMan->clearShaderProgramChunks();
    }
}

OSG_END_NAMESPACE
