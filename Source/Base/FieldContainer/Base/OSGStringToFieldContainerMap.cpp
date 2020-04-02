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

#include "OSGStringToFieldContainerMap.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGStringToFieldContainerMapBase.cpp file.
// To modify it, please change the .fcd file (OSGStringToFieldContainerMap.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void StringToFieldContainerMap::initMethod(InitPhase ePhase)
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

StringToFieldContainerMap::StringToFieldContainerMap(void) :
    Inherited()
{
}

StringToFieldContainerMap::StringToFieldContainerMap(const StringToFieldContainerMap &source) :
    Inherited(source)
{
}

StringToFieldContainerMap::~StringToFieldContainerMap(void)
{
}

/*----------------------------- class specific ----------------------------*/

void StringToFieldContainerMap::changed(ConstFieldMaskArg whichField, 
                                        UInt32            origin,
                                        BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void StringToFieldContainerMap::dump(      UInt32    ,
                                     const BitVector ) const
{
    SLOG << "Dump StringToFieldContainerMap NI" << std::endl;
}

bool StringToFieldContainerMap::insert(const std::string& key, FieldContainer* value)
{
    MFUnrecKeyValuePtr::iterator iter = std::lower_bound(_mfValues.begin(), _mfValues.end(), key, value_compare());

    if (iter == _mfValues.end() || key < (*iter)->getKey())
    {
        KeyValueUnrecPtr value_type = KeyValue::createLocal();

        value_type->setKey  (key);
        value_type->setValue(value);

        editMField(ValuesFieldMask, _mfValues);
        _mfValues.insert(iter, value_type);

        return true;
    }
    return false;
}

MFUnrecKeyValuePtr::const_iterator StringToFieldContainerMap::find_(const std::string& key) const
{
    MFUnrecKeyValuePtr::const_iterator iter = std::lower_bound(_mfValues.begin(), _mfValues.end(), key, value_compare());
    if (iter != _mfValues.end() && key < (*iter)->getKey())
    {
        iter = _mfValues.end();
    }
    return iter;
}

OSG_END_NAMESPACE
