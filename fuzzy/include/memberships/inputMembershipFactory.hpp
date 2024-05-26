#ifndef INPUT_MEMBERSHIP_FACTORY_HPP
#define INPUT_MEMBERSHIP_FACTORY_HPP

#include <yaml-cpp/yaml.h>

#include "inputMembership.hpp"

namespace fuzzyyaml{
    class InputMembershipFactory
    {
    public:
        InputMembershipFactory();
        bool GetInputMembership(YAML::const_iterator& itLinguistic, InputMembership*& pInputMembership);
    };
}

#endif