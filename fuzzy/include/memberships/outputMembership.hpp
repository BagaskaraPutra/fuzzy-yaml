#ifndef OUTPUT_MEMBERSHIP_HPP
#define OUTPUT_MEMBERSHIP_HPP

#include <string>

#include "membershipType.hpp"
#include "membership.hpp"
#include "polygon.hpp"

namespace fuzzyyaml{
    class OutputMembership : virtual public Membership, virtual public IPolygon
    {
    public:
        OutputMembership(const std::string& name, const MembershipType& mType);
        void SetFuzzyInference(double fuzzyInference);

    protected:
        double _fuzzyInference;
    };
}

#endif