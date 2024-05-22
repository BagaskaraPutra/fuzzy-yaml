#include "ruleTable.hpp"

namespace fuzzyyaml{

    RuleTable::RuleTable(const std::string &outputVariableName, YAML::Node &ruleBaseNode)
    : RuleBase(outputVariableName)
    {
        SetRuleBase(ruleBaseNode);
    }

    bool RuleTable::SetRuleBase(YAML::Node &ruleBaseNode)
    {
        YAML::Node rules = ruleBaseNode[_outputVariableName];
        _rowVariable = rules["row_variable"].as<std::string>();
        _rowValues = rules["row_values"].as<std::vector<std::string>>();
        _columnVariable = rules["column_variable"].as<std::string>();
        _columnValues = rules["column_values"].as<std::vector<std::string>>();
        _operatorString = rules["operator"].as<std::string>();
        _ruleTable = rules["table"].as<std::vector<std::vector<std::string>>>();
        return true;
    }

    void RuleTable::PrintRules()
    {
        std::cout << "[RuleTable] outputVariable: " << _outputVariableName << std::endl;
        for (auto &itRuleVector : _ruleTable){
            for (auto &itRule : itRuleVector){
                std::cout << itRule << " ";
            }
            printf("\n");
        }
    }

    double RuleTable::CalcInference(std::map<std::string, std::map<std::string, double>>& fuzzifiedValues)
    {
        _fuzzyInference = 0.0;
        if (_operatorString == "AND" || _operatorString == "and"){
            for (auto& row_el : _rowValues){
                for(auto & col_el : _columnValues){
                    _fuzzyInference = std::fmax(_fuzzyInference, std::fmin(
                        fuzzifiedValues.at(_rowVariable).at(row_el),
                        fuzzifiedValues.at(_columnVariable).at(col_el)
                    ));
                    // std::cout << "row_el: " << row_el << "\tcol_el: " << col_el << std::endl;
                    // std::cout << "fuzzRow: " << fuzzifiedValues.at(_rowVariable).at(row_el);
                    // std::cout << "\tfuzzCol: " << fuzzifiedValues.at(_columnVariable).at(col_el) << std::endl;
                }
            }
        }
        return _fuzzyInference;
    }
}