#ifndef RULE_BASE_FACTORY_HPP
#define RULE_BASE_FACTORY_HPP

#include <string>
#include <map>
#include <yaml-cpp/yaml.h>

#include "ruleBase.hpp"

namespace fuzzyyaml{
    class RuleBaseFactory
    {
    public:
        RuleBaseFactory();
        bool GetRuleBase(YAML::Node& ruleBaseNode, std::map<std::string, RuleBase*>& pRuleBases);
    };
}

#endif