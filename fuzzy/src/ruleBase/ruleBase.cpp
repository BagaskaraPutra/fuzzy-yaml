#include "ruleBase.hpp"

namespace fuzzyyaml{

RuleBase::RuleBase(const std::string& outputVariableName)
{
    _outputVariableName = outputVariableName;
}

void RuleBase::SetOperator(const std::string &operatorStr)
{
    _operatorString = operatorStr;
}

}