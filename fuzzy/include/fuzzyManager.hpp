#ifndef FUZZY_MANAGER_HPP
#define FUZZY_MANAGER_HPP

#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <yaml-cpp/yaml.h>

#include "inputMembership.hpp"
#include "outputMembership.hpp"
#include "ruleBase.hpp"
#include "defuzzifier.hpp"

#include "inputMembershipFactory.hpp"
#include "outputMembershipFactory.hpp"
#include "ruleBaseFactory.hpp"
#include "defuzzifierFactory.hpp"

namespace fuzzyyaml{

    class FuzzyManager
    {
    public:
        FuzzyManager(const std::string &configPath);
        std::map<std::string, std::map<std::string, InputMembership*>> GetInputMemberships();
        std::map<std::string, std::map<std::string, OutputMembership*>> GetOutputMemberships();
        bool SetCrispInput(const std::string &crispVariable, double crispInput);
        std::map<std::string, std::map<std::string, double>> GetFuzzifiedValues();
        std::map<std::string, std::map<std::string, double>> GetInferenceValues();
        std::map<std::string, double> CalcCrispOutputs();
        ~FuzzyManager();

    private:
        bool getInputVariablesConstructor(YAML::Node &masterNode);
        bool getOutputVariablesConstructor(YAML::Node &masterNode);
        bool getDefuzzifiersConstructor(const std::string& defuzzifierType, const std::string& crispVariable);
        bool getRuleBasesConstructor(YAML::Node &masterNode);
        
        void fuzzification();
        void inferenceSystem();
        void defuzzification();

        InputMembershipFactory* _pInputMembershipFactory;
        OutputMembershipFactory* _pOutputMembershipFactory;
        RuleBaseFactory* _pRuleBaseFactory;
        DefuzzifierFactory* _pDefuzzifierFactory;

        std::map<std::string, std::map<std::string, InputMembership*>> _pInputMemberships;
        std::map<std::string, std::map<std::string, OutputMembership*>> _pOutputMemberships;
        std::map<std::string, Defuzzifier*> _pDefuzzifiers;
        std::map<std::string, std::map<std::string, double>> _fuzzifiedValues;
        std::map<std::string, RuleBase*> _pRuleBases;
        std::map<std::string, std::map<std::string, double>> _inferenceValues;
        std::map<std::string, double> _defuzzifiedValues;
    };
}

#endif