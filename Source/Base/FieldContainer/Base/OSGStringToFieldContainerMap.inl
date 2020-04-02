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
bool StringToFieldContainerMap::empty() const
{
    return _mfValues.empty();
}

inline
FieldContainer* StringToFieldContainerMap::at(UInt32 idx) const
{
    OSG_ASSERT(idx < size());
    return _mfValues[idx]->getValue();
}

inline
const std::string& StringToFieldContainerMap::key(UInt32 idx) const
{
    OSG_ASSERT(idx < size());
    return _mfValues[idx]->getKey();
}

inline
void StringToFieldContainerMap::clear()
{
    editMField(ValuesFieldMask, _mfValues);
    _mfValues.clear();
}

inline
UInt32 StringToFieldContainerMap::size() const
{
    return _mfValues.size32();
}

inline
FieldContainer* StringToFieldContainerMap::find(const std::string& key) const
{
    MFUnrecKeyValuePtr::const_iterator iter = find_(key);
    if (iter != _mfValues.end())
    {
        return (*iter)->getValue();
    }
    return NULL;
}

inline
bool StringToFieldContainerMap::erase(const std::string& key)
{
    MFUnrecKeyValuePtr::const_iterator iter = find_(key);
    if (iter != _mfValues.end())
    {
        _mfValues.erase(iter-_mfValues.begin());
        return true;
    }
    return false;
}

OSG_END_NAMESPACE
