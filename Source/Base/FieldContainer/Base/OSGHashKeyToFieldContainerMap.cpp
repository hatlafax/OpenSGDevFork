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

#include "OSGHashKeyToFieldContainerMap.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGHashKeyToFieldContainerMapBase.cpp file.
// To modify it, please change the .fcd file (OSGHashKeyToFieldContainerMap.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void HashKeyToFieldContainerMap::initMethod(InitPhase ePhase)
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

HashKeyToFieldContainerMap::HashKeyToFieldContainerMap(void) :
    Inherited()
{
}

HashKeyToFieldContainerMap::HashKeyToFieldContainerMap(const HashKeyToFieldContainerMap &source) :
    Inherited(source)
{
}

HashKeyToFieldContainerMap::~HashKeyToFieldContainerMap(void)
{
}

/*----------------------------- class specific ----------------------------*/

void HashKeyToFieldContainerMap::changed(ConstFieldMaskArg whichField, 
                                         UInt32            origin,
                                         BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void HashKeyToFieldContainerMap::dump(      UInt32    ,
                                      const BitVector ) const
{
    SLOG << "Dump HashKeyToFieldContainerMap NI" << std::endl;
}

bool HashKeyToFieldContainerMap::insert(HashKeyType key, FieldContainer* value)
{
    MFUnrecHashKeyValuePtr::iterator iter = std::lower_bound(_mfValues.begin(), _mfValues.end(), key, value_compare());

    if (iter == _mfValues.end() || key < (*iter)->getKey())
    {
        HashKeyValueUnrecPtr value_type = HashKeyValue::createLocal();

        value_type->setKey  (key);
        value_type->setValue(value);

        editMField(ValuesFieldMask, _mfValues);
        _mfValues.insert(iter, value_type);

        return true;
    }
    return false;
}

MFUnrecHashKeyValuePtr::const_iterator HashKeyToFieldContainerMap::find_(HashKeyType key) const
{
    MFUnrecHashKeyValuePtr::const_iterator iter = std::lower_bound(_mfValues.begin(), _mfValues.end(), key, value_compare());
    if (iter != _mfValues.end() && key < (*iter)->getKey())
    {
        iter = _mfValues.end();
    }
    return iter;
}

void HashKeyToFieldContainerMap::recycle()
{
    UInt32 sz = _mfValues.size32();

    MFUnrecHashKeyValuePtr mfValues;

    for (UInt32 idx = 0; idx < sz; ++idx)
    {
        FieldContainer* fc = at(idx);

        RefCountStore ref_cnt = fc->getRefCount();

        if (ref_cnt > 1)
        {
            mfValues.push_back(_mfValues[idx]);
        }
    }

    editMField(ValuesFieldMask, _mfValues);
    _mfValues.clear();

    sz = mfValues.size32();

    for (UInt32 idx = 0; idx < sz; ++idx)
    {
        _mfValues.push_back(mfValues[idx]);
    }
}

OSG_END_NAMESPACE
