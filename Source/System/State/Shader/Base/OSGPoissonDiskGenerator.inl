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

template <typename T, typename RNGType>
PoissonDiskGenerator<T, RNGType>::PoissonDiskGenerator()
: _rng()
, _line()
, _disk()
, _sphere()
, _sizeFactor(T(1.0))
, _minDist(-T(1.0))
, _maxIterations(30)
, _maxIterationsOnExact(200)
, _useCircle(true)
, _unit_distribution(T(0.0),  T(1.0))
{
}

template <typename T, typename RNGType>
PoissonDiskGenerator<T, RNGType>::PoissonDiskGenerator(UInt32 seed)
: _rng(seed)
, _line()
, _disk()
, _sphere()
, _sizeFactor(T(1.0))
, _minDist(-T(1.0))
, _maxIterations(30)
, _maxIterationsOnExact(200)
, _useCircle(true)
, _unit_distribution(T(0.0), T(1.0))
{
}

template <typename T, typename RNGType>
PoissonDiskGenerator<T, RNGType>::~PoissonDiskGenerator()
{
}


template <typename T, typename RNGType>
inline void PoissonDiskGenerator<T, RNGType>::setSizeFactor(T value)
{
    _sizeFactor = value;
}

template <typename T, typename RNGType>
inline T PoissonDiskGenerator<T, RNGType>::getSizeFactor() const
{
    return _sizeFactor;
}

template <typename T, typename RNGType>
inline void PoissonDiskGenerator<T, RNGType>::setMinDist(T value)
{
    _minDist = value;
}

template <typename T, typename RNGType>
inline T PoissonDiskGenerator<T, RNGType>::getMinDist() const
{
    return _minDist;
}

template <typename T, typename RNGType>
inline void PoissonDiskGenerator<T, RNGType>::setMaxIterations(UInt32 value)
{
    _maxIterations = value;
}

template <typename T, typename RNGType>
inline UInt32 PoissonDiskGenerator<T, RNGType>::getMaxIterations() const
{
    return _maxIterations;
}

template <typename T, typename RNGType>
inline void PoissonDiskGenerator<T, RNGType>::setMaxIterationsOnExact(UInt32 value)
{
    _maxIterationsOnExact = value;
}

template <typename T, typename RNGType>
inline UInt32 PoissonDiskGenerator<T, RNGType>::getMaxIterationsOnExact() const
{
    return _maxIterationsOnExact;
}

template <typename T, typename RNGType>
inline void PoissonDiskGenerator<T, RNGType>::setUseCircle(bool flag)
{
    _useCircle = flag;
}

template <typename T, typename RNGType>
inline bool PoissonDiskGenerator<T, RNGType>::getUseCircle() const
{
    return _useCircle;
}

template <typename T, typename RNGType>
inline void PoissonDiskGenerator<T, RNGType>::clear()
{
    _line.clear();
    _disk.clear();
    _sphere.clear();
}

template <typename T, typename RNGType>
const typename PoissonDiskGenerator<T, RNGType>::PointLineStorage& PoissonDiskGenerator<T, RNGType>::getLine(UInt32 size, bool exact, const Point1Type& center)
{
    if (_line.size() != size)
    {
        if (exact)
        {
            UInt32 cnt = 0;

            do 
            {
                cnt++;
                generate_line(size, center);

                if (_line.size() != size)
                {
                    T minDist = getMinDist();

                         if (_line.size() < size - size/30)
                         minDist -= minDist / T(10.0);
                    else if (_line.size() > size + size/30)
                        minDist += minDist / T(10.0);
                    else if (_line.size() < size - size/10)
                        minDist -= minDist / T(2.0);
                    else if (_line.size() > size + size/10)
                        minDist += minDist / T(2.0);

                    setMinDist(minDist);
                }

            } while (_line.size() != size && cnt < _maxIterationsOnExact);

            if (cnt >= _maxIterationsOnExact)
            {
                _line.clear();
            }
        }
        else
        {
            generate_line(size, center);
        }
    }

    return _line;
}

template <typename T, typename RNGType>
const typename PoissonDiskGenerator<T, RNGType>::PointDiskStorage& PoissonDiskGenerator<T, RNGType>::getDisk(UInt32 size, bool exact, const Point2Type& center)
{
    if (_disk.size() != size)
    {
        if (exact)
        {
            UInt32 cnt = 0;

            do 
            {
                cnt++;
                generate_disk(size, center);

                if (_disk.size() != size)
                {
                    T minDist = getMinDist();

                         if (_disk.size() < size - size/30)
                         minDist -= minDist / T(10.0);
                    else if (_disk.size() > size + size/30)
                        minDist += minDist / T(10.0);
                    else if (_disk.size() < size - size/10)
                        minDist -= minDist / T(2.0);
                    else if (_disk.size() > size + size/10)
                        minDist += minDist / T(2.0);

                    setMinDist(minDist);
                }

            } while (_disk.size() != size && cnt < _maxIterationsOnExact);

            if (cnt >= _maxIterationsOnExact)
            {
                _disk.clear();
            }
        }
        else
        {
            generate_disk(size, center);
        }
    }

    return _disk;
}

template <typename T, typename RNGType>
const typename PoissonDiskGenerator<T, RNGType>::PointSphereStorage& PoissonDiskGenerator<T, RNGType>::getSphere(UInt32 size, bool exact, const Point3Type& center)
{
    if (_sphere.size() != size)
    {
        if (exact)
        {
            UInt32 cnt = 0;

            do 
            {
                cnt++;
                generate_sphere(size, center);

                if (_sphere.size() != size)
                {
                    T minDist = getMinDist();

                         if (_sphere.size() < size - size/30)
                         minDist -= minDist / T(10.0);
                    else if (_sphere.size() > size + size/30)
                        minDist += minDist / T(10.0);
                    else if (_sphere.size() < size - size/10)
                        minDist -= minDist / T(2.0);
                    else if (_sphere.size() > size + size/10)
                        minDist += minDist / T(2.0);

                    setMinDist(minDist);
                }

            } while (_sphere.size() != size && cnt < _maxIterationsOnExact);

            if (cnt >= _maxIterationsOnExact)
            {
                _sphere.clear();
            }
        }
        else
        {
            generate_sphere(size, center);
        }
    }

    return _sphere;
}

template <typename T, typename RNGType>
inline const typename PoissonDiskGenerator<T, RNGType>::PointLineStorage& PoissonDiskGenerator<T, RNGType>::getLine(const Point1Type& center)
{
    generate_line(center);
    return _line;
}

template <typename T, typename RNGType>
inline const typename PoissonDiskGenerator<T, RNGType>::PointDiskStorage& PoissonDiskGenerator<T, RNGType>::getDisk(const Point2Type& center)
{
    generate_disk(center);
    return _disk;
}

template <typename T, typename RNGType>
inline const typename PoissonDiskGenerator<T, RNGType>::PointSphereStorage& PoissonDiskGenerator<T, RNGType>::getSphere(const Point3Type& center)
{
    generate_sphere(center);
    return _sphere;
}

template <typename T, typename RNGType>
inline void PoissonDiskGenerator<T, RNGType>::generate_line(UInt32 size, const Point1Type& center)
{
    VecPoint1T points;
    generatePoints(points, size);

    std::size_t sz = points.size();

    _line.resize(sz);

    for (std::size_t i = 0; i < sz; ++i)
    {
        _line[i] = center + _sizeFactor * (points[i].pnt - Point1Type(T(0.5)));
    }
}

template <typename T, typename RNGType>
inline void PoissonDiskGenerator<T, RNGType>::generate_disk(UInt32 size, const Point2Type& center)
{
    VecPoint2T points;
    generatePoints(points, size);

    std::size_t sz = points.size();

    _disk.resize(sz);

    for (std::size_t i = 0; i < sz; ++i)
    {
        _disk[i] = center + _sizeFactor * (points[i].pnt - Point2Type(T(0.5),T(0.5)));
    }
}

template <typename T, typename RNGType>
inline void PoissonDiskGenerator<T, RNGType>::generate_sphere(UInt32 size, const Point3Type& center)
{
    VecPoint3T points;
    generatePoints(points, size);

    std::size_t sz = points.size();

    _sphere.resize(sz);

    for (std::size_t i = 0; i < sz; ++i)
    {
        _sphere[i] = center + _sizeFactor * (points[i].pnt - Point3Type(T(0.5),T(0.5),T(0.5)));
    }
}

template <typename T, typename RNGType>
inline void PoissonDiskGenerator<T, RNGType>::generate_line(const Point1Type& center)
{
    VecPoint1T points;
    generatePoints(points);

    std::size_t sz = points.size();

    _line.resize(sz);

    for (std::size_t i = 0; i < sz; ++i)
    {
        _line[i] = center + _sizeFactor * (points[i].pnt - Point1Type(T(0.5)));
    }
}

template <typename T, typename RNGType>
inline void PoissonDiskGenerator<T, RNGType>::generate_disk(const Point2Type& center)
{
    VecPoint2T points;
    generatePoints(points);

    std::size_t sz = points.size();

    _disk.resize(sz);

    for (std::size_t i = 0; i < sz; ++i)
    {
        _disk[i] = center + _sizeFactor * (points[i].pnt - Point2Type(T(0.5),T(0.5)));
    }
}

template <typename T, typename RNGType>
inline void PoissonDiskGenerator<T, RNGType>::generate_sphere(const Point3Type& center)
{
    VecPoint3T points;
    generatePoints(points);

    std::size_t sz = points.size();

    _sphere.resize(sz);

    for (std::size_t i = 0; i < sz; ++i)
    {
        _sphere[i] = center + _sizeFactor * (points[i].pnt - Point3Type(T(0.5),T(0.5),T(0.5)));
    }
}

template <typename T, typename RNGType>
inline T PoissonDiskGenerator<T, RNGType>::getValue()
{
    return _unit_distribution(_rng);
}

template <typename T, typename RNGType>
inline UInt32 PoissonDiskGenerator<T, RNGType>::getIndex(UInt32 maxIdx)
{
    boost::uniform_int<UInt32> index_dist(0, maxIdx);
    return index_dist(_rng);
}

template <typename T, typename RNGType>
bool PoissonDiskGenerator<T, RNGType>::Point1::insideLine() const
{
    return pnt.x() >= T(0) && pnt.x() <= T(1);
}

template <typename T, typename RNGType>
bool PoissonDiskGenerator<T, RNGType>::Point2::insideRectangle() const
{
    return pnt.x() >= T(0) && pnt.y() >= T(0)
        && pnt.x() <= T(1) && pnt.y() <= T(1);
}

template <typename T, typename RNGType>
bool PoissonDiskGenerator<T, RNGType>::Point2::insideCircle() const
{
    Vector< T,  2 > v = pnt - Point2Type(T(0.5),T(0.5));
    return v.squareLength() <= T(0.25);
}

template <typename T, typename RNGType>
bool PoissonDiskGenerator<T, RNGType>::Point3::insideRectangle() const
{
    return pnt.x() >= T(0) && pnt.y() >= T(0) && pnt.z() >= T(0)
        && pnt.x() <= T(1) && pnt.y() <= T(1) && pnt.z() <= T(1);
}

template <typename T, typename RNGType>
bool PoissonDiskGenerator<T, RNGType>::Point3::insideCircle() const
{
    Vector< T,  3 > v = pnt - Point3Type(T(0.5),T(0.5),T(0.5));
    return v.squareLength() <= T(0.25);
}

template <typename T, typename RNGType>
PoissonDiskGenerator<T, RNGType>::Grid1::Grid1(Int32 w, T cellSize)
: pnt(w)
, cellSize(cellSize)
, grid()
{
    grid.resize(w);
}

template <typename T, typename RNGType>
inline Vec1i PoissonDiskGenerator<T, RNGType>::Grid1::imageToGrid1(const Point1& p)
{
    return Vec1i( Int32( p.pnt.x() / cellSize ) );
}

template <typename T, typename RNGType>
inline void PoissonDiskGenerator<T, RNGType>::Grid1::insert(const Point1& p)
{
    Vec1i g = imageToGrid1(p);
    grid[g.x()] = p;
}

template <typename T, typename RNGType>
bool PoissonDiskGenerator<T, RNGType>::Grid1::insideNeighbourhood(const Point1& p, T minDist)
{
    Vec1i g = imageToGrid1(p);

    const Int32 d = 5;

    for (Int32 i = g.x()-d; i < g.x()+d; ++i)
    {
        if (i >= 0 && i < pnt.x())
        {
            const Point1& q = grid[i];
            if (q.valid && q.pnt.dist(p.pnt) < minDist)
            {
                return true;
            }
        }
    }
    return false;
}

template <typename T, typename RNGType>
PoissonDiskGenerator<T, RNGType>::Grid2::Grid2(Int32 w, Int32 h, T cellSize)
: pnt(w,h)
, cellSize(cellSize)
, grid()
{
    grid.resize(h);
    VecVecPoint2T::iterator iter = grid.begin();
    VecVecPoint2T::iterator end  = grid.end();

    for (; iter != end; ++iter)
    {
        iter->resize(w);
    }
}

template <typename T, typename RNGType>
inline Vec2i PoissonDiskGenerator<T, RNGType>::Grid2::imageToGrid2(const Point2& p)
{
    return Vec2i( Int32( p.pnt.x() / cellSize ), Int32( p.pnt.y() / cellSize ) );
}

template <typename T, typename RNGType>
inline void PoissonDiskGenerator<T, RNGType>::Grid2::insert(const Point2& p)
{
    Vec2i g = imageToGrid2(p);
    grid[g.x()][g.y()] = p;
}

template <typename T, typename RNGType>
bool PoissonDiskGenerator<T, RNGType>::Grid2::insideNeighbourhood(const Point2& p, T minDist)
{
    Vec2i g = imageToGrid2(p);

    const Int32 d = 5;

    for (Int32 i = g.x()-d; i < g.x()+d; ++i)
    {
        for (Int32 j = g.y()-d; j < g.y()+d; ++j)
        {
            if (i >= 0 && i < pnt.x() && j >= 0 && j < pnt.y())
            {
                const Point2& q = grid[i][j];
                if (q.valid && q.pnt.dist(p.pnt) < minDist)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

template <typename T, typename RNGType>
PoissonDiskGenerator<T, RNGType>::Grid3::Grid3(Int32 w, Int32 h, Int32 d, T cellSize)
: pnt(w,h,d)
, cellSize(cellSize)
, grid()
{
    grid.resize(d);

    VecVecVecPoint3T::iterator iter1 = grid.begin();
    VecVecVecPoint3T::iterator end1  = grid.end();

    for (; iter1 != end1; ++iter1)
    {
        iter1->resize(h);

        VecVecPoint3T::iterator iter2 = iter1->begin();
        VecVecPoint3T::iterator end2  = iter1->end();

        for (; iter2 != end2; ++iter2)
        {
            iter2->resize(w);
        }
    }
}

template <typename T, typename RNGType>
inline Vec3i PoissonDiskGenerator<T, RNGType>::Grid3::imageToGrid3(const Point3& p)
{
    return Vec3i( Int32( p.pnt.x() / cellSize ), Int32( p.pnt.y() / cellSize ), Int32( p.pnt.z() / cellSize ) );
}

template <typename T, typename RNGType>
inline void PoissonDiskGenerator<T, RNGType>::Grid3::insert(const Point3& p)
{
    Vec3i g = imageToGrid3(p);
    grid[g.x()][g.y()][g.z()] = p;
}

template <typename T, typename RNGType>
bool PoissonDiskGenerator<T, RNGType>::Grid3::insideNeighbourhood(const Point3& p, T minDist)
{
    Vec3i g = imageToGrid3(p);

    const Int32 d = 5;

    for (Int32 i = g.x()-d; i < g.x()+d; ++i)
    {
        for (Int32 j = g.y()-d; j < g.y()+d; ++j)
        {
            for (Int32 k = g.z()-d; k < g.z()+d; ++k)
            {
                if (i >= 0 && i < pnt.x() && j >= 0 && j < pnt.y() && k >= 0 && k < pnt.z())
                {
                    const Point3& q = grid[i][j][k];
                    if (q.valid && q.pnt.dist(p.pnt) < minDist)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

template <typename T, typename RNGType>
inline typename PoissonDiskGenerator<T, RNGType>::Point1 PoissonDiskGenerator<T, RNGType>::generateRandomPointAround(const Point1& p)
{
    T r1 = getValue();
    T r2 = getValue();

    // radius should be between MinDist and 2 * MinDist
    T radius = _minDist * ( r1 + T(1.0));
    T sign   = r2 < T(0.5) ? T(-1.0) : T(1.0);

    // the new point is generated around the point (x)
    T x = p.pnt.x() + radius * sign;

    return Point1(x);
}

template <typename T, typename RNGType>
inline typename PoissonDiskGenerator<T, RNGType>::Point2 PoissonDiskGenerator<T, RNGType>::generateRandomPointAround(const Point2& p)
{
    T r1 = getValue();
    T r2 = getValue();

    // radius should be between MinDist and 2 * MinDist
    T radius = _minDist * ( r1 + T(1.0));

    // random angle
    T phi = T(6.28318530717958647692528676655900576) * r2;

    // the new point is generated around the point (x, y)
    T x = p.pnt.x() + radius * osgCos(phi);
    T y = p.pnt.y() + radius * osgSin(phi);

    return Point2(x,y);
}

template <typename T, typename RNGType>
inline typename PoissonDiskGenerator<T, RNGType>::Point3 PoissonDiskGenerator<T, RNGType>::generateRandomPointAround(const Point3& p)
{
    T r1 = getValue();
    T r2 = getValue();
    T r3 = getValue();

    // radius should be between MinDist and 2 * MinDist
    T radius = _minDist * ( r1 + T(1.0));

    // random angle
    T phi   = T(6.28318530717958647692528676655900576) * r2;
    T theta = T(3.14159265358979323846264338327950288) * r3;

    // the new point is generated around the point (x,y,z)
    T x = p.pnt.x() + radius * osgSin(theta) * osgCos(phi);
    T y = p.pnt.y() + radius * osgSin(theta) * osgSin(phi);
    T z = p.pnt.z() + radius * osgCos(theta);

    return Point3(x,y,z);
}

template <typename T, typename RNGType>
void PoissonDiskGenerator<T, RNGType>::generatePoints(VecPoint1T& finalStore, UInt32 size)
{
    if (_minDist < T(0.0))
    {
        _minDist = osgSqrt(T(size)) / (T(1.25)*T(size));
    }

    generatePoints(finalStore);
}

template <typename T, typename RNGType>
void PoissonDiskGenerator<T, RNGType>::generatePoints(VecPoint1T& finalStore)
{
    finalStore.clear();

    if (_minDist <= T(0))
        return;

    T cellSize = _minDist / osgSqrt(T(2.0));

    Int32 gridW = static_cast<Int32>(osgCeil( T(1.0) / cellSize));
 
    Grid1 grid(gridW, cellSize);

    Point1 p0;
    do
    {
        p0 = Point1(getValue());
    } while ( !p0.insideLine() );

    VecPoint1T activeStore;

    activeStore.push_back(p0);
    finalStore .push_back(p0);
    grid       .insert   (p0);

    // generate new points for each point in the queue
    while (!activeStore.empty())
    {
        // get random element from the activeStore
        UInt32 idx = getIndex(UInt32(activeStore.size()-1));

        const Point1& p = activeStore[idx];

        bool found_candidate = false;

        for (UInt32 i = 0; i < _maxIterations; ++i)
        {
            Point1 q;
            do 
            {
                q = generateRandomPointAround(p);
            } while ( !q.insideLine() );

            if (!grid.insideNeighbourhood(q, _minDist))
            {
                found_candidate = true;

                activeStore.push_back(q);
                finalStore .push_back(q);
                grid       .insert(q);

                break;
            }
        }

        if (!found_candidate)
        {
            activeStore.erase(activeStore.begin() + idx);
        }
    }
}

template <typename T, typename RNGType>
void PoissonDiskGenerator<T, RNGType>::generatePoints(VecPoint2T& finalStore, UInt32 size)
{
    if (_minDist < T(0.0))
    {
        _minDist = osgSqrt(T(size)) / (T(1.25)*T(size));
    }

    generatePoints(finalStore);
}

template <typename T, typename RNGType>
void PoissonDiskGenerator<T, RNGType>::generatePoints(VecPoint2T& finalStore)
{
    finalStore.clear();

    if (_minDist <= T(0))
        return;

    T cellSize = _minDist / osgSqrt(T(2.0));

    Int32 gridW = static_cast<Int32>(osgCeil( T(1.0) / cellSize));
    Int32 gridH = static_cast<Int32>(osgCeil( T(1.0) / cellSize));

    Grid2 grid(gridW, gridH, cellSize);

    Point2 p0;
    do
    {
        p0 = Point2(getValue(), getValue());	     
    } while (!(_useCircle ? p0.insideCircle()
                          : p0.insideRectangle()));

    VecPoint2T activeStore;

    activeStore.push_back(p0);
    finalStore .push_back(p0);
    grid       .insert   (p0);

    // generate new points for each point in the queue
    while (!activeStore.empty())
    {
        // get random element from the activeStore
        UInt32 idx = getIndex(UInt32(activeStore.size()-1));

        const Point2& p = activeStore[idx];

        bool found_candidate = false;

        for (UInt32 i = 0; i < _maxIterations; ++i)
        {
            Point2 q;
            do 
            {
                q = generateRandomPointAround(p);
            } while ( !(_useCircle ? q.insideCircle() : q.insideRectangle()) );

            if (!grid.insideNeighbourhood(q, _minDist))
            {
                found_candidate = true;

                activeStore.push_back(q);
                finalStore .push_back(q);
                grid       .insert(q);

                break;
            }
        }

        if (!found_candidate)
        {
            activeStore.erase(activeStore.begin() + idx);
        }
    }
}

template <typename T, typename RNGType>
void PoissonDiskGenerator<T, RNGType>::generatePoints(VecPoint3T& finalStore, UInt32 size)
{
    if (_minDist < T(0.0))
    {
        _minDist = osgSqrt(T(size)) / T(size);
    }

    generatePoints(finalStore);
}

template <typename T, typename RNGType>
void PoissonDiskGenerator<T, RNGType>::generatePoints(VecPoint3T& finalStore)
{
    finalStore.clear();

    if (_minDist <= T(0))
        return;

    T cellSize = _minDist / osgSqrt(T(3.0));

    Int32 gridW = static_cast<Int32>(osgCeil( T(1.0) / cellSize));
    Int32 gridH = static_cast<Int32>(osgCeil( T(1.0) / cellSize));
    Int32 gridD = static_cast<Int32>(osgCeil( T(1.0) / cellSize));

    Grid3 grid(gridW, gridH, gridD, cellSize);

    Point3 p0;
    do
    {
        p0 = Point3(getValue(), getValue(), getValue());
    } while (!(_useCircle ? p0.insideCircle()
                          : p0.insideRectangle()));

    VecPoint3T activeStore;

    activeStore.push_back(p0);
    finalStore .push_back(p0);
    grid       .insert   (p0);

    // generate new points for each point in the queue
    while (!activeStore.empty())
    {
        // get random element from the activeStore
        UInt32 idx = getIndex(UInt32(activeStore.size()-1));

        const Point3& p = activeStore[idx];

        bool found_candidate = false;

        for (UInt32 i = 0; i < _maxIterations; ++i)
        {
            Point3 q;
            do 
            {
                q = generateRandomPointAround(p);
            } while ( !(_useCircle ? q.insideCircle() : q.insideRectangle()) );

            if (!grid.insideNeighbourhood(q, _minDist))
            {
                found_candidate = true;

                activeStore.push_back(q);
                finalStore .push_back(q);
                grid       .insert(q);

                break;
            }
        }

        if (!found_candidate)
        {
            activeStore.erase(activeStore.begin() + idx);
        }
    }
}

OSG_END_NAMESPACE

