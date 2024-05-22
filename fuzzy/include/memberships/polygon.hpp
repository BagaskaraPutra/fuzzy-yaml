#pragma once

#include <vector>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>

namespace fuzzyyaml{
    namespace bg = boost::geometry;
    typedef bg::model::d2::point_xy<double> point_t;
    typedef bg::model::polygon<point_t> polygon_t;
    typedef bg::model::multi_polygon<polygon_t> multi_polygon_t;
    
    class IPolygon{
    public:
        virtual polygon_t GetPolygon() = 0;
        // virtual double GetArea() = 0;
        virtual double GetCentroidX() = 0;
    protected:
        polygon_t _polygon;
        // double _area;
        double _centroidX;
    };
}