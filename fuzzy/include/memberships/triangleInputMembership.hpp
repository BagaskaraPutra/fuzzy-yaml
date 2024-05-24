#ifndef TRIANGLE_INPUT_MEMBERSHIP_HPP
#define TRIANGLE_INPUT_MEMBERSHIP_HPP

#include <string>

#include "membershipType.hpp"
#include "triangleMembership.hpp"
#include "inputMembership.hpp"

namespace fuzzyyaml{
    class TriangleInputMembership : public TriangleMembership, public InputMembership
    {
    public:
        TriangleInputMembership(const std::string& name, 
                            const double& bottomLeft, 
                            const double& peak, 
                            const double& bottomRight);
        void PrintMembershipData() override;
        double GetYValue(double x) override;
        double CalcTruthValue() override;                    
        double CalcTruthValue(double crispInput) override;

    };
}

#endif