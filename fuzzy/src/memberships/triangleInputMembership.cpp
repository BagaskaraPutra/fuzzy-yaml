#include "triangleInputMembership.hpp"

namespace fuzzyyaml{

TriangleInputMembership::TriangleInputMembership(const std::string &name, const double &bottomLeft, const double &peak, const double &bottomRight)
: TriangleMembership(name, bottomLeft, peak, bottomRight),
    InputMembership(name, TRIANGLE),
    Membership(name, TRIANGLE)
{
}

void TriangleInputMembership::PrintMembershipData()
{
    std::cout << "Triangle Input Membership name: " << Membership::GetName() << std::endl;
    std::cout << "bottomLeft: " << _bottomLeft << "\tpeak: " << _peak << "\tbottomRight: " << _bottomRight << std::endl;
}

double TriangleInputMembership::GetYValue(double x)
{
    return TriangleMembership::GetYValue(x);
}

double TriangleInputMembership::CalcTruthValue()
{
    _fuzzyTruthValue = TriangleMembership::GetYValue(_crispInput);
    // std::cout << "[TriangleInputMembership] _name: " << _name << "\tcrispInput: " << _crispInput << "\ttruth value: " << _fuzzyTruthValue << std::endl;
    return _fuzzyTruthValue;
}

double TriangleInputMembership::CalcTruthValue(double crispInput)
{
    _crispInput = crispInput;
    _fuzzyTruthValue = TriangleMembership::GetYValue(_crispInput);
    return _fuzzyTruthValue;
}

}