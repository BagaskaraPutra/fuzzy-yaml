#include "outputMembership.hpp"

namespace fuzzyyaml{

    OutputMembership::OutputMembership(const std::string& name, const MembershipType& mType)
    : Membership(name, mType, OUTPUT_MEMBERSHIP)
    {
    }

    void OutputMembership::SetFuzzyInference(double fuzzyInference)
    {
        _fuzzyInference = fuzzyInference;
    }
}