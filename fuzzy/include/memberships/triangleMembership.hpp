#ifndef TRIANGLE_MEMBERSHIP_HPP
#define TRIANGLE_MEMBERSHIP_HPP

#include <iostream>

#include "membership.hpp"
#include "mathUtils.hpp"

namespace fuzzyyaml{
    class TriangleMembership : virtual public Membership
    {
    public:
        TriangleMembership(const std::string& name, 
                            const double& bottomLeft, 
                            const double& peak, 
                            const double& bottomRight);
        void PrintMembershipData() override;
        double GetYValue(double x) override;

    protected:
        double _input;
        double _bottomLeft;
        double _peak;
        double _bottomRight;
    };
}

#endif