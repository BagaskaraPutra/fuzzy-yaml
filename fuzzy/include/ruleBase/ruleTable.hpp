#ifndef RULE_TABLE_HPP
#define RULE_TABLE_HPP

#include <yaml-cpp/yaml.h>

#include "ruleBase.hpp"

namespace fuzzyyaml{
    class RuleTable : public RuleBase
    {
    public:
        RuleTable(const std::string& outputVariableName, YAML::Node& ruleBaseNode);
        bool SetRuleBase(YAML::Node& ruleBaseNode); 
        void PrintRules() override;
        double CalcInference(std::map<std::string, std::map<std::string, double>>& fuzzifiedValues) override;
    protected:
        std::string _rowVariable, _columnVariable;
        std::vector<std::string> _rowValues, _columnValues;
        std::vector<std::vector<std::string>> _ruleTable;
    };
}

#endif