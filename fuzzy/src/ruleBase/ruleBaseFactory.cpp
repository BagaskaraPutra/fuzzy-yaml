#include "ruleBaseFactory.hpp"
#include "ruleTable.hpp"
// TODO: Add more rule base headers here

namespace fuzzyyaml{
    RuleBaseFactory::RuleBaseFactory()
    {
    }

    bool RuleBaseFactory::GetRuleBase(YAML::Node& ruleBaseNode, std::map<std::string, RuleBase*>& pRuleBases)
    {
        for (YAML::const_iterator itRules=ruleBaseNode.begin(); itRules != ruleBaseNode.end(); ++itRules) {
            std::string outputVariable = itRules->first.as<std::string>();
            if (itRules->second["table"]){
                pRuleBases[outputVariable] = new RuleTable(outputVariable, ruleBaseNode);
            } // else if{}
            // TODO: Add other rule base methods in else if
            // _pRuleBases.at(outputVariable)->PrintRules();
        }
        return true;
    }
}