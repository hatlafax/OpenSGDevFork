/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2003 by the OpenSG Forum                   *
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

OSG_BEGIN_NAMESPACE

inline
void PolygonBody::setVertices(const VecVerticesT& vertices)
{
    _vertices = vertices;
}

inline
std::size_t PolygonBody::getNumVertices() const
{
    return _vertices.size();
}

inline
const PolygonBody::VecVerticesT& PolygonBody::getVertices() const
{
    return _vertices;
}

inline
std::size_t PolygonBody::getNumPolygons() const
{
    return _polygons.size();
}

inline
const PolygonBody::VecPolygonsT& PolygonBody::getPolygons() const
{
    return _polygons;
}

inline
void PolygonBody::add(Polygon* polygon)
{
    if (polygon)
        _polygons.push_back(polygon);
}

inline
void PolygonBody::clearPolygons()
{
    VecPolygonsT::const_iterator iter = _polygons.begin();
    VecPolygonsT::const_iterator end  = _polygons.end();

    for (;iter != end; ++iter)
        delete *iter;

    _polygons.clear();
}

inline
void PolygonBody::copyPolygons(const VecPolygonsT& rhs)
{
    clearPolygons();
    addPolygons(rhs);
}

inline
void PolygonBody::addPolygons(const VecPolygonsT& rhs)
{
    VecPolygonsT::const_iterator iter = rhs.begin();
    VecPolygonsT::const_iterator end  = rhs.end();
    for (;iter != end; ++iter)
    {
        _polygons.push_back(new Polygon(**iter));
    }
}

OSG_END_NAMESPACE

