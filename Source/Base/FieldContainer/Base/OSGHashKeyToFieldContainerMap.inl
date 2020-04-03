/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
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

OSG_BEGIN_NAMESPACE

inline
bool HashKeyToFieldContainerMap::empty() const
{
    return _mfValues.empty();
}

inline
FieldContainer* HashKeyToFieldContainerMap::at(UInt32 idx) const
{
    OSG_ASSERT(idx < size());
    return _mfValues[idx]->getValue();
}

inline
HashKeyToFieldContainerMap::HashKeyType HashKeyToFieldContainerMap::key(UInt32 idx) const
{
    OSG_ASSERT(idx < size());
    return _mfValues[idx]->getKey();
}

inline
void HashKeyToFieldContainerMap::clear()
{
    editMField(ValuesFieldMask, _mfValues);
    _mfValues.clear();
}

inline
UInt32 HashKeyToFieldContainerMap::size() const
{
    return _mfValues.size32();
}

inline
FieldContainer* HashKeyToFieldContainerMap::find(HashKeyType key) const
{
    MFUnrecHashKeyValuePtr::const_iterator iter = find_(key);
    if (iter != _mfValues.end())
    {
        return (*iter)->getValue();
    }
    return NULL;
}

inline
bool HashKeyToFieldContainerMap::erase(HashKeyType key)
{
    MFUnrecHashKeyValuePtr::const_iterator iter = find_(key);
    if (iter != _mfValues.end())
    {
        _mfValues.erase(iter-_mfValues.begin());
        return true;
    }
    return false;
}

OSG_END_NAMESPACE
