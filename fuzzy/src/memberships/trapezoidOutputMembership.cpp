#include "trapezoidOutputMembership.hpp"

namespace fuzzyyaml{

TrapezoidOutputMembership::TrapezoidOutputMembership(const std::string &name, const double &bottomLeft, const double &upperLeft, const double &upperRight, const double &bottomRight)
: TrapezoidMembership(name, bottomLeft, upperLeft, upperRight, bottomRight),
    OutputMembership(name, TRAPEZOID),
    Membership(name, TRAPEZOID)
{
}

void TrapezoidOutputMembership::PrintMembershipData()
{
    std::cout << "Trapezoid Output Membership name: " << Membership::GetName() << std::endl;
    std::cout << "bottomLeft: " << _bottomLeft << "\tupperLeft: " << _upperLeft << "\tupperRight: " << _upperRight << "\tbottomRight: " << _bottomRight << std::endl;
}

double TrapezoidOutputMembership::GetYValue(double x)
{
    return TrapezoidMembership::GetYValue(x);
}

polygon_t TrapezoidOutputMembership::GetPolygon()
{
    _xinf1 = MathUtils::calcX(_fuzzyInference, 0.0, 1.0, _bottomLeft, _upperLeft); //(_upperLeft - _bottomLeft)*_fuzzyInference + _bottomLeft;
    _xinf2 = MathUtils::calcX(_fuzzyInference, 1.0, 0.0, _upperRight, _bottomRight);
    bg::append(_polygon.outer(), point_t(_bottomLeft, 0.0));
    bg::append(_polygon.outer(), point_t(_xinf1,  _fuzzyInference));
    bg::append(_polygon.outer(), point_t(_xinf2, _fuzzyInference));
    bg::append(_polygon.outer(), point_t(_bottomRight,0.0));
    bg::append(_polygon.outer(), point_t(_bottomLeft, 0.0));
    point_t centroidXY; 
    bg::centroid(_polygon, centroidXY);
    // std::cout << "Local trapezoid name: " << _name << "\tinference: " << _fuzzyInference  << "\tarea: " << bg::area(_polygon) <<"\tcentroid: " << centroidXY.x() << std::endl;
    return _polygon;
}

// double TrapezoidOutputMembership::GetArea()
// {
//     _base = std::fabs(_bottomRight - _bottomLeft);
//     // double _roof = (1-_fuzzyInference) * _base;
//     _xinf1 = MathUtils::calcX(_fuzzyInference, 0.0, 1.0, _bottomLeft, _upperLeft); //(_upperLeft - _bottomLeft)*_fuzzyInference + _bottomLeft;
//     _xinf2 = MathUtils::calcX(_fuzzyInference, 1.0, 0.0, _upperRight, _bottomRight);
//     _roof = std::fabs(_xinf2 - _xinf1);
//     return (_base + _roof) * _fuzzyInference / 2;
// }

double TrapezoidOutputMembership::GetCentroidX()
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