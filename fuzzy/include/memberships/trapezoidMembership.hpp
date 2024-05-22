#ifndef TRAPEZOID_MEMBERSHIP_HPP
#define TRAPEZOID_MEMBERSHIP_HPP

#include <iostream>

#include "membership.hpp"
#include "mathUtils.hpp"

namespace fuzzyyaml{
    class TrapezoidMembership : virtual public Membership
    {
    public:
        TrapezoidMembership(const std::string& name, 
                            const double& bottomLeft, 
                            const double& upperLeft, 
                            const double& upperRight, 
                            const double& bottomRight);
        void PrintMembershipData() override;
        double GetYValue(double x) override;

        // bool SetName(const std::string& name);
        // double GetBottomLeft();
        // double GetUpperLeft();
        // double GetUpperRight();
        // double GetBottomRight();

    protected:
        double _input;
        double _bottomLeft;
        double _upperLeft;
        double _upperRight;
        double _bottomRight;
    };
}

#endif