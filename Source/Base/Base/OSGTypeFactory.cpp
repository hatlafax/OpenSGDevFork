/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2003 by the OpenSG Forum                    *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#define OSG_COMPILE_TYPEFACTORY

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include <iostream>

#include "OSGTypeFactory.h"

#include "OSGFactoryController.h"
#include "OSGLog.h"
#include "OSGTypeBase.h"

#include "OSGSingletonHolder.ins"

#include <algorithm>
#include <functional>

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

OSG_SINGLETON_INST(TypeFactoryBase, addPostFactoryExitFunction)

template class SingletonHolder<TypeFactoryBase>;

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

void TypeFactoryBase::writeTypeDot(FILE     *pOut,
                                   TypeBase *pTypeBase)
{
    fprintf(pOut, "    OpenSG%s [shape=record,label=\"%s - %s\"]\n", 
            pTypeBase->getCName(),
            pTypeBase->getCName(),
            pTypeBase->isInitialized() ? "Init" : "UnInit");

    if(pTypeBase->getCParentName() != NULL)
    {
        fprintf(pOut, 
                "    OpenSG%s -> OpenSG%s\n", 
                pTypeBase->getCParentName(), 
                pTypeBase->getCName());
    }
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

TypeFactoryBase::TypeFactoryBase(void) :
     Inherited    ("TypeFactory"),
    _vTypeNameMaps(             ),
    _vTypeStore   (             )
{
    _vTypeStore.reserve  (512 );
    _vTypeStore.push_back(NULL);

    _vTypeNameMaps.push_back(new TypeNameMap);

    FactoryController::the()->registerTypeFactory(this);
}

TypeFactoryBase::TypeFactoryBase(const Char8 *szName) :
     Inherited    (szName),
    _vTypeNameMaps(      ),
    _vTypeStore   (      )
{
    _vTypeStore.reserve  (512 );
    _vTypeStore.push_back(NULL);

    _vTypeNameMaps.push_back(new TypeNameMap);

    FactoryController::the()->registerTypeFactory(this);
}

TypeFactoryBase::~TypeFactoryBase(void)
{
}

bool TypeFactoryBase::initialize(void)
{
    TypeStoreIt typeIt  = _vTypeStore.begin();
    TypeStoreIt typeEnd = _vTypeStore.end  ();

    while(typeIt != typeEnd)
    {
        if((*typeIt) != NULL)
            (*typeIt)->initialize();

        ++typeIt;
    }

    return true;
}

bool TypeFactoryBase::initializeFactoryPost(void)
{
    return true;
}

bool TypeFactoryBase::terminate(void)
{
    for(UInt32 i = 0; i < _vTypeNameMaps.size(); ++i)
    {
        delete _vTypeNameMaps[i];
    }

    _vTypeNameMaps.clear();

    return true;
}

bool TypeFactoryBase::onLoadInitialize(void)
{
    return true;
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

UInt32 TypeFactoryBase::registerType(TypeBase *pType)
{
    UInt32 returnValue = 0;

    if(pType == NULL)
    {
        SWARNING << "no data store given" << endLog;

        return returnValue;
    }

    if(pType->getName().empty() == true) 
    {
        SWARNING << "DataElementType without name" << endLog;

        return returnValue;
    }

    UInt32 uiTypeId = findTypeId(pType->getCName    (), 
                                 pType->getNameSpace());

    if(uiTypeId != 0)
    {
        if(pType != findType(uiTypeId))
        {
            SWARNING << "ERROR: Can't add a second "
                     << "type with the name " << pType->getCName() 
                     << "(" << pType << ")"
                     << " in namespace " << pType->getNameSpace()
                     << endLog;
        }
        else
        {
            SWARNING << "Do not run ctr twice "
                     << "type with the name " << pType->getCName() 
                     << "(" << pType << ")"
                     << endLog;

//            findType(uiTypeId)->dump();

            returnValue = uiTypeId;
        }

        return returnValue;
    }

    returnValue = UInt32(_vTypeStore.size());

    _vTypeStore.push_back(pType);

    while(_vTypeNameMaps.size() <= pType->getNameSpace())
    {
        _vTypeNameMaps.push_back(new TypeNameMap);

        PINFO << "Added namespace : " << _vTypeNameMaps.size() << endLog;
    }

    (*(_vTypeNameMaps[pType->getNameSpace()]))
        [pType->getName()] = returnValue;


    FDEBUG(("Registered type %s | %d (%p)\n", pType->getCName(), returnValue,
                                              static_cast<void *>(pType))); 

    return returnValue;
}

UInt32 TypeFactoryBase::findTypeId(const Char8 *szName,
                                   const UInt32 uiNameSpace)
{
    TypeNameMapConstIt typeIt;
    UInt32             uiTypeId = 0;

    if(szName == NULL)
        return uiTypeId;

    if(_vTypeNameMaps.size() <= uiNameSpace)
        return uiTypeId;

    TypeNameMap *pMap = _vTypeNameMaps[uiNameSpace];

    typeIt   = pMap->find(std::string(szName));

    uiTypeId = (typeIt == pMap->end()) ? 0 : (*typeIt).second;

    return uiTypeId;
}

TypeBase *TypeFactoryBase::findType(UInt32 uiTypeId)
{
    if(uiTypeId < _vTypeStore.size())
    {
        return _vTypeStore[uiTypeId];
    }
    else
    {
        return NULL;
    }
}

TypeBase *TypeFactoryBase::findType(const Char8    *szName,
                                    const UInt32    uiNameSpace)
{
    UInt32 uiTypeId = findTypeId(szName, uiNameSpace);

    return findType(uiTypeId);
}

UInt32 TypeFactoryBase::getNumTypes(void)
{
    return UInt32(_vTypeStore.size());
}

void TypeFactoryBase::writeTypeGraph(FILE *pOut)
{
    if(pOut == NULL)
        return;

    fprintf(pOut, "digraph OSGTypeGraph\n{\n");

    fprintf(pOut, "    rankdir=LR;\n");
    fprintf(pOut, "    size=\"120,200\";\n");
    fprintf(pOut, "    page=\"8.2677,11.69\";\n");
    fprintf(pOut, "    radio=auto;\n");

    for(UInt32 i = 1; i < _vTypeStore.size(); i++)
    {
        writeTypeDot(pOut, _vTypeStore[i]);
    }

    fprintf(pOut, "}\n");
}

void TypeFactoryBase::writeTypeGraph(const Char8 *szFilename)
{
    if(szFilename == NULL)
        return;

    FILE *pOut = fopen(szFilename, "w");

    if(pOut == NULL)
        return;

    writeTypeGraph(pOut);

    if(pOut != NULL)
        fclose(pOut);
}

OSG_END_NAMESPACE
