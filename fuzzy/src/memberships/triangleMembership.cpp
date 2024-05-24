#include "triangleMembership.hpp"

namespace fuzzyyaml{
    TriangleMembership::TriangleMembership(const std::string &name,
                                            const double &bottomLeft,
                                            const double &peak,
                                            const double &bottomRight)
                                            : 
                                            Membership(name, TRIANGLE)
    {
        _name = name;
        _bottomLeft  = bottomLeft;
        _peak        = peak; 
        _bottomRight = bottomRight;
    }

    void TriangleMembership::PrintMembershipData()
    {
        std::cout << "Triangle Membership name: " << _name << std::endl;
        std::cout << "bottomLeft: " << _bottomLeft << "\tpeak: " << _peak << "\tbottomRight: " << _bottomRight << std::endl;
    }

    double TriangleMembership::GetYValue(double x)
    {
        if (_bottomLeft <= x && x < _peak){
            return MathUtils::calcY(x, _bottomLeft, _peak, 0.0, 1.0);
        } else if (_peak <= x && x <= _bottomRight){
            return MathUtils::calcY(x, _peak, _bottomRight, 1.0, 0.0);
        } else{
            return 0.0;
        }
    }
}