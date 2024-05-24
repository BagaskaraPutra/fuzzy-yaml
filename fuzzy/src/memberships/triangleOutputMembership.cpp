#include "triangleOutputMembership.hpp"

namespace fuzzyyaml{

TriangleOutputMembership::TriangleOutputMembership(const std::string &name, const double &bottomLeft, const double &peak, const double &bottomRight)
: TriangleMembership(name, bottomLeft, peak, bottomRight),
    OutputMembership(name, TRIANGLE),
    Membership(name, TRIANGLE)
{
}

void TriangleOutputMembership::PrintMembershipData()
{
    std::cout << "Triangle Output Membership name: " << Membership::GetName() << std::endl;
    std::cout << "bottomLeft: " << _bottomLeft << "\tpeak: " << _peak << "\tbottomRight: " << _bottomRight << std::endl;
}

double TriangleOutputMembership::GetYValue(double x)
{
    return TriangleMembership::GetYValue(x);
}

polygon_t TriangleOutputMembership::GetPolygon()
{
    _xinf1 = MathUtils::calcX(_fuzzyInference, 0.0, 1.0, _bottomLeft, _peak);
    _xinf2 = MathUtils::calcX(_fuzzyInference, 1.0, 0.0, _peak, _bottomRight);
    bg::clear(_polygon);
    bg::append(_polygon.outer(), point_t(_bottomLeft, 0.0));
    bg::append(_polygon.outer(), point_t(_xinf1, _fuzzyInference));
    bg::append(_polygon.outer(), point_t(_xinf2, _fuzzyInference));
    bg::append(_polygon.outer(), point_t(_bottomRight,0.0));
    bg::append(_polygon.outer(), point_t(_bottomLeft, 0.0));
    // point_t centroidXY; 
    // bg::centroid(_polygon, centroidXY);
    // std::cout << "Local trapezoid name: " << _name << "\tinference: " << _fuzzyInference  << "\tarea: " << bg::area(_polygon) <<"\tcentroid: " << centroidXY.x() << std::endl;
    // for (auto& itPoint : _polygon.outer()){
    //     std::cout << "(" << itPoint.x() << "," << itPoint.y() << ") ";
    // }
    // printf("\n");
    return _polygon;
}

// double TriangleOutputMembership::GetArea()
// {
//     _base = std::fabs(_bottomRight - _bottomLeft);
//     _xinf1 = MathUtils::calcX(_fuzzyInference, 0.0, 1.0, _bottomLeft, _peak);
//     _xinf2 = MathUtils::calcX(_fuzzyInference, 1.0, 0.0, _peak, _bottomRight);
//     _roof = std::fabs(_xinf2 - _xinf1);
//     return (_base + _roof) * _fuzzyInference / 2;
// }

double TriangleOutputMembership::GetCentroidX()
{
    // GetArea();
    // double L1 = MathUtils::calcHypotenuse(_bottomLeft, 0.0, _xinf1, _fuzzyInference);
    // double L2 = MathUtils::calcHypotenuse(_xinf2, _fuzzyInference, _bottomRight, 0.0);
    // return _bottomLeft + _base/2 + (2*_roof+_base)*(L1*L1-L2*L2)/(6*(_base*_base - _roof*_roof));
    GetPolygon();
    point_t centroidXY; 
    bg::centroid(_polygon, centroidXY);
    return centroidXY.x();
}
}