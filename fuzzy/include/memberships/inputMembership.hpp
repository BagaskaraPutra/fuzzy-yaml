#ifndef INPUT_MEMBERSHIP_HPP
#define INPUT_MEMBERSHIP_HPP

#include <string>

#include "membershipType.hpp"
#include "membership.hpp"

namespace fuzzyyaml{
    class InputMembership : virtual public Membership
    {
    public:
        InputMembership(const std::string& name, const MembershipType& mType);
        void SetCrispInput(double crispInput);
        virtual double CalcTruthValue() = 0;
        virtual double CalcTruthValue(double crispInput) = 0;

    protected:
        double _crispInput;
        double _fuzzyTruthValue;
    };
}

#endif