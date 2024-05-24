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

    void RuleTable::CalcInference(std::map<std::string, std::map<std::string, double>> &fuzzifiedValues, 
                                    std::map<std::string, double> &inferenceValues)
    {
        for (auto& inferenceValue : inferenceValues){
            inferenceValue.second = 0.0;
        }
        // std::cout << "\n[RuleTable] outputVariable: " << _outputVariableName << std::endl;
        if (_operatorString == "AND" || _operatorString == "and"){
            for (size_t i=0; i < _rowValues.size(); ++i){
                for(size_t j=0; j < _columnValues.size(); ++j){
                    inferenceValues.at(_ruleTable.at(i).at(j)) = std::fmax(
                        inferenceValues.at(_ruleTable.at(i).at(j)) , 
                        std::fmin(
                            fuzzifiedValues.at(_rowVariable).at(_rowValues.at(i)),
                            fuzzifiedValues.at(_columnVariable).at(_columnValues.at(j))
                        ));
                    // std::cout << "row[" << i << "]: " << _rowValues.at(i) << "\tcol[" << j << "]: " << _columnValues.at(j) << std::endl;
                    // std::cout << "fuzzRow: " << fuzzifiedValues.at(_rowVariable).at(_rowValues.at(i));
                    // std::cout << "\tfuzzCol: " << fuzzifiedValues.at(_columnVariable).at(_columnValues.at(j)) << std::endl;
                    // std::cout << _ruleTable.at(i).at(j) << "\tinferenceValues: " << inferenceValues.at(_ruleTable.at(i).at(j)) << std::endl;
                }
            }
        } 
    }
}