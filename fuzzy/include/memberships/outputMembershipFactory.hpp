#ifndef OUTPUT_MEMBERSHIP_FACTORY_HPP
#define OUTPUT_MEMBERSHIP_FACTORY_HPP

#include <yaml-cpp/yaml.h>

#include "outputMembership.hpp"

namespace fuzzyyaml{
    class OutputMembershipFactory
    {
    public:
        OutputMembershipFactory();
        bool GetOutputMembership(YAML::const_iterator& itLinguistic, OutputMembership*& pOutputMembership);
    };
}

#endif