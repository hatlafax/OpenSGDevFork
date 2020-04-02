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

#ifndef _OSGPOISSONDISKGENERATOR_H_
#define _OSGPOISSONDISKGENERATOR_H_

#include <boost/random.hpp>

#include "OSGBaseTypes.h"
#include "OSGVector.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBase
    \ingroup GrpBaseBaseMathObj
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

 //
 // http://www.cs.ubc.ca/~rbridson/docs/bridson-siggraph07-poissondisk.pdf
 // https://bost.ocks.org/mike/algorithms/
 //

//
// Attention:
//      The function getDisk and getSphere taking the boolean exact=true
//      parameter might not provide the desired result and might take a
//      very long runtime. They are not supposed to be used in application
//      code but are a mean to calculate proper Poissons distribution of
//      a fixed size. These function were used for the calculation of the
//      values in the OSGPoissonDistribution.cpp file.
//

template <typename T, typename RNGType = boost::mt19937>
class PoissonDiskGenerator
{
    /*==========================  PUBLIC  =================================*/

  public:
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             PoissonDiskGenerator    ();
    explicit PoissonDiskGenerator    (UInt32 seed);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
    ~PoissonDiskGenerator   ();
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get/Set                                   */
    /*! \{                                                                 */

    void        setSizeFactor               (T value);
    T           getSizeFactor               () const;

    void        setMinDist                  (T value);
    T           getMinDist                  () const;

    void        setMaxIterations            (UInt32 value);
    UInt32      getMaxIterations            () const;

    void        setMaxIterationsOnExact     (UInt32 value);
    UInt32      getMaxIterationsOnExact     () const;

    void        setUseCircle                (bool flag);
    bool        getUseCircle                () const;

    typedef Point< T,  1 > Point1Type;
    typedef Point< T,  2 > Point2Type;
    typedef Point< T,  3 > Point3Type;
    typedef std::vector< Point1Type > PointLineStorage;
    typedef std::vector< Point2Type > PointDiskStorage;
    typedef std::vector< Point3Type > PointSphereStorage;

    const PointLineStorage&     getLine         (UInt32 size, bool exact = true, const Point1Type& center = Point1Type(T(0)));
    const PointDiskStorage&     getDisk         (UInt32 size, bool exact = true, const Point2Type& center = Point2Type(T(0),T(0)));
    const PointSphereStorage&   getSphere       (UInt32 size, bool exact = true, const Point3Type& center = Point3Type(T(0),T(0),T(0)));

    const PointLineStorage&     getLine         (const Point1Type& center = Point1Type(T(0)));
    const PointDiskStorage&     getDisk         (const Point2Type& center = Point2Type(T(0),T(0)));
    const PointSphereStorage&   getSphere       (const Point3Type& center = Point3Type(T(0),T(0),T(0)));

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operations                                */
    /*! \{                                                                 */

    void        clear();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Specific                            */
    /*! \{                                                                 */
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

    void        generate_line           (UInt32 size, const Point1Type& center);
    void        generate_disk           (UInt32 size, const Point2Type& center);
    void        generate_sphere         (UInt32 size, const Point3Type& center);

    void        generate_line           (const Point1Type& center);
    void        generate_disk           (const Point2Type& center);
    void        generate_sphere         (const Point3Type& center);

    T           getValue                ();
    UInt32      getIndex                (UInt32 maxIdx);

  private:

    struct Point1
    {
	Point1() : pnt(T(0)), valid(false) {}
        Point1(T x) : pnt(x), valid(true ) {}

	Point1Type pnt;
	bool       valid;

        bool insideLine() const;
    };
  
    struct Point2
    {
	Point2() : pnt(T(0),T(0)), valid(false) {}
        Point2(T x, T y) : pnt(x,y), valid(true) {}

	Point2Type pnt;
	bool       valid;

        bool insideRectangle() const;
        bool insideCircle   () const;
    };

    struct Point3
    {
	Point3() : pnt(T(0),T(0),T(0)), valid(false) {}
        Point3(T x, T y, T z) : pnt(x,y,z), valid(true) {}

	Point3Type pnt;
	bool       valid;

        bool insideRectangle() const;
        bool insideCircle   () const;
    };

    typedef std::vector<Point1> VecPoint1T;
    typedef std::vector<Point2> VecPoint2T;
    typedef std::vector<Point3> VecPoint3T;

    struct Grid1
    {
	Grid1(Int32 w, T cellSize);

        Vec1i   imageToGrid1        (const Point1& p);
        void    insert              (const Point1& p);
        bool    insideNeighbourhood (const Point1& p, T minDist);

	Vec1i           pnt;
	T               cellSize;
        VecPoint1T      grid;
    };
    
    struct Grid2
    {
        typedef std::vector<VecPoint2T> VecVecPoint2T;

	Grid2(Int32 w, Int32 h, T cellSize);

        Vec2i   imageToGrid2        (const Point2& p);
        void    insert              (const Point2& p);
        bool    insideNeighbourhood (const Point2& p, T minDist);

	Vec2i           pnt;
	T               cellSize;
        VecVecPoint2T   grid;
    };

    struct Grid3
    {
        typedef std::vector<VecPoint3T>       VecVecPoint3T;
        typedef std::vector<VecVecPoint3T> VecVecVecPoint3T;

	Grid3(Int32 w, Int32 h, Int32 d, T cellSize);

        Vec3i   imageToGrid3        (const Point3& p);
        void    insert              (const Point3& p);
        bool    insideNeighbourhood (const Point3& p, T minDist);

	Vec3i               pnt;
	T                   cellSize;
        VecVecVecPoint3T    grid;
    };

    Point1      generateRandomPointAround   (const Point1& p);
    Point2      generateRandomPointAround   (const Point2& p);
    Point3      generateRandomPointAround   (const Point3& p);

    void        generatePoints              (VecPoint1T& finalPoints, UInt32 size);
    void        generatePoints              (VecPoint2T& finalPoints, UInt32 size);
    void        generatePoints              (VecPoint3T& finalPoints, UInt32 size);

    void        generatePoints              (VecPoint1T& finalPoints);
    void        generatePoints              (VecPoint2T& finalPoints);
    void        generatePoints              (VecPoint3T& finalPoints);

  private:
    RNGType                 _rng;
    PointLineStorage        _line;
    PointDiskStorage        _disk;
    PointSphereStorage      _sphere;

    T                       _sizeFactor;
    T                       _minDist;
    UInt32                  _maxIterations;
    UInt32                  _maxIterationsOnExact;
    bool                    _useCircle;
    boost::uniform_real<T>  _unit_distribution;
};

OSG_END_NAMESPACE

#include "OSGPoissonDiskGenerator.inl"

#endif // _OSGPOISSONDISKGENERATOR_H_
