#ifndef TRAPEZOID_INPUT_MEMBERSHIP_HPP
#define TRAPEZOID_INPUT_MEMBERSHIP_HPP

#include <string>

#include "membershipType.hpp"
#include "trapezoidMembership.hpp"
#include "inputMembership.hpp"

namespace fuzzyyaml{
    class TrapezoidInputMembership : public TrapezoidMembership, public InputMembership
    {
    public:
        TrapezoidInputMembership(const std::string& name, 
                            const double& bottomLeft, 
                            const double& upperLeft, 
                            const double& upperRight, 
                            const double& bottomRight);
        void PrintMembershipData() override;
        double GetYValue(double x) override;
        double CalcTruthValue() override;                    
        double CalcTruthValue(double crispInput) override;

    };
}

#endif