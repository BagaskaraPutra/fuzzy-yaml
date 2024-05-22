#include "inputMembership.hpp"

namespace fuzzyyaml{

InputMembership::InputMembership(const std::string& name, const MembershipType& mType)
: Membership(name, mType, INPUT_MEMBERSHIP)
{
}

void InputMembership::SetCrispInput(double crispInput)
{
    _crispInput = crispInput;
}

}