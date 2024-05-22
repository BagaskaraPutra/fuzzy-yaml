#include "trapezoidMembership.hpp"

namespace fuzzyyaml{
    TrapezoidMembership::TrapezoidMembership(const std::string &name,
                                            const double &bottomLeft,
                                            const double &upperLeft,
                                            const double &upperRight,
                                            const double &bottomRight)
                                            : 
                                            Membership(name, TRAPEZOID)
    {
        _name = name;
        _bottomLeft  = bottomLeft;
        _upperLeft   = upperLeft;
        _upperRight  = upperRight;
        _bottomRight = bottomRight;
    }

    void TrapezoidMembership::PrintMembershipData()
    {
        std::cout << "Trapezoid Membership name: " << _name << std::endl;
        std::cout << "bottomLeft: " << _bottomLeft << "\tupperLeft: " << _upperLeft << "\tupperRight: " << _upperRight << "\tbottomRight: " << _bottomRight << std::endl;
    }

    double TrapezoidMembership::GetYValue(double x)
    {
        if (_bottomLeft <= x && x < _upperLeft){
            return MathUtils::calcY(x, _bottomLeft, _upperLeft, 0.0, 1.0);
        } else if (_upperLeft <= x && x < _upperRight){
            return 1.0;
        } else if (_upperRight < x && x <= _bottomRight){
            return MathUtils::calcY(x, _upperRight, _bottomRight, 1.0, 0.0);
        } else{
            return 0.0;
        }
    }
}