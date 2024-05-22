#include "trapezoidInputMembership.hpp"

namespace fuzzyyaml{

TrapezoidInputMembership::TrapezoidInputMembership(const std::string &name, const double &bottomLeft, const double &upperLeft, const double &upperRight, const double &bottomRight)
: TrapezoidMembership(name, bottomLeft, upperLeft, upperRight, bottomRight),
    InputMembership(name, TRAPEZOID),
    Membership(name, TRAPEZOID)
{
}

void TrapezoidInputMembership::PrintMembershipData()
{
    std::cout << "Trapezoid Input Membership name: " << Membership::GetName() << std::endl;
    std::cout << "bottomLeft: " << _bottomLeft << "\tupperLeft: " << _upperLeft << "\tupperRight: " << _upperRight << "\tbottomRight: " << _bottomRight << std::endl;
}

double TrapezoidInputMembership::GetYValue(double x)
{
    return TrapezoidMembership::GetYValue(x);
}

double TrapezoidInputMembership::CalcTruthValue()
{
    _fuzzyTruthValue = TrapezoidMembership::GetYValue(_crispInput);
    // std::cout << "[TrapezoidInputMembership] _name: " << _name << "\tcrispInput: " << _crispInput << "\ttruth value: " << _fuzzyTruthValue << std::endl;
    return _fuzzyTruthValue;
}

double TrapezoidInputMembership::CalcTruthValue(double crispInput)
{
    _crispInput = crispInput;
    _fuzzyTruthValue = TrapezoidMembership::GetYValue(_crispInput);
    return _fuzzyTruthValue;
}

}