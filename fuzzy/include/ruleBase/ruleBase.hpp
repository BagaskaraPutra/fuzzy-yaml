#ifndef RULE_BASE_HPP
#define RULE_BASE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <yaml-cpp/yaml.h>

namespace fuzzyyaml{
    class RuleBase
    {
    public:
        RuleBase(const std::string& outputVariableName);
        void SetOperator(const std::string& operatorStr);
        virtual bool SetRuleBase(YAML::Node& ruleBaseNode) = 0;
        virtual void PrintRules() = 0; 
        virtual void CalcInference(std::map<std::string, std::map<std::string, double>>& fuzzifiedValues,
                                    std::map<std::string, double>& inferenceValues) = 0;
    protected:
        std::string _outputVariableName;
        std::string _operatorString;
    };
}

#endif