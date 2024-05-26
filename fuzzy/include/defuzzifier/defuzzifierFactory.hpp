#ifndef DEFUZZIFIER_FACTORY_HPP
#define DEFUZZIFIER_FACTORY_HPP

#include <string>
#include <map>
#include <yaml-cpp/yaml.h>

#include "defuzzifier.hpp"

namespace fuzzyyaml{
    class DefuzzifierFactory
    {
    public:
        DefuzzifierFactory();
        bool GetDefuzzifier(const std::string& defuzzifierType, const std::string& crispVariable, std::map<std::string, OutputMembership*>& outputMemberships, Defuzzifier*& pDefuzzifier);
    };
}

#endif