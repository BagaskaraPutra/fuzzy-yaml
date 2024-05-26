#include "fuzzyManager.hpp"

namespace fuzzyyaml{
    FuzzyManager::FuzzyManager(const std::string& configPath)
    {
        YAML::Node config_;
        try {
            config_ = YAML::LoadFile(configPath.c_str());
        } catch(const std::exception& e) {
            std::cerr << "Failed to load " << configPath << std::endl;;
            return;
        }

        _pInputMembershipFactory = new InputMembershipFactory();
        _pOutputMembershipFactory = new OutputMembershipFactory();
        _pRuleBaseFactory = new RuleBaseFactory();
        _pDefuzzifierFactory = new DefuzzifierFactory();
        
        getInputVariablesConstructor(config_);
        getOutputVariablesConstructor(config_);
        getRuleBasesConstructor(config_);

        std::cout<<"[FuzzyManager] Finished loading config constructor: "<<configPath<<std::endl;
    }

    std::map<std::string, std::map<std::string, InputMembership *>> FuzzyManager::GetInputMemberships()
    {
        return _pInputMemberships;
    }

    std::map<std::string, std::map<std::string, OutputMembership *>> FuzzyManager::GetOutputMemberships()
    {
        return _pOutputMemberships;
    }

    bool FuzzyManager::SetCrispInput(const std::string& crispVariable, double crispInput)
    {
        for (auto& imf : _pInputMemberships.at(crispVariable)){
            imf.second->SetCrispInput(crispInput);
        }
        return true;
    }

    std::map<std::string, std::map<std::string, double>> FuzzyManager::GetFuzzifiedValues()
    {
        // fuzzification();
        return _fuzzifiedValues;
    }

    std::map<std::string, std::map<std::string, double>> FuzzyManager::GetInferenceValues()
    {
        return _inferenceValues;
    }

    std::map<std::string, double> FuzzyManager::CalcCrispOutputs()
    {
        fuzzification();
        inferenceSystem();
        defuzzification();
        return _defuzzifiedValues;
    }

    FuzzyManager::~FuzzyManager()
    {
        delete _pInputMembershipFactory;
        delete _pOutputMembershipFactory;
        delete _pRuleBaseFactory;
        delete _pDefuzzifierFactory;
        for (auto& crispVariable : _pInputMemberships){
            for (auto& membership : crispVariable.second){
                // TODO: WTF? It works when I delete the explicitly casted InputMembership* pointer to TrapezoidInputMembership*
                // https://www.quora.com/How-do-you-delete-a-subclass-pointer-where-you-use-a-parent-pointer-as-formal-parameters-in-a-function
                // delete (TrapezoidInputMembership*)membership.second;.
                // Solution: add virtual deconstructor in the Membership base class
                delete membership.second;
            }
        }
        for (auto& crispVariable : _pOutputMemberships){
            for (auto &membership : crispVariable.second){
                delete membership.second;
            }
        }
        for (auto& crispVariable : _pDefuzzifiers){
            delete crispVariable.second;
        }
        for (auto& crispVariable : _pRuleBases){
            delete crispVariable.second;
        }
    }

    bool FuzzyManager::getInputVariablesConstructor(YAML::Node &masterNode)
    {
        YAML::Node variablesNode_ = masterNode["inputVariables"];
        InputMembership *pInputMembership;
        YAML::Node membershipsNode_;
        for (YAML::const_iterator itCrisp=variablesNode_.begin(); itCrisp != variablesNode_.end(); ++itCrisp) {
            std::string crispVariable = itCrisp->first.as<std::string>();
            membershipsNode_ = itCrisp->second["memberships"];
            // std::cout << "[FuzzyManager] Input crisp variable: " << crispVariable << std::endl;
            for (YAML::const_iterator itLinguistic=membershipsNode_.begin(); itLinguistic != membershipsNode_.end(); ++itLinguistic) {
                _pInputMembershipFactory->GetInputMembership(itLinguistic, pInputMembership);
                _pInputMemberships[crispVariable].insert(std::make_pair(itLinguistic->first.as<std::string>(), pInputMembership));
                _fuzzifiedValues[crispVariable].insert(std::make_pair(itLinguistic->first.as<std::string>(), 0.0));
            }
        }
        pInputMembership = NULL;
        return true;
    }

    bool FuzzyManager::getOutputVariablesConstructor(YAML::Node &masterNode)
    {
        YAML::Node variablesNode_ = masterNode["outputVariables"];
        YAML::Node membershipsNode_; 
        OutputMembership *pOutputMembership;

        for (YAML::const_iterator itCrisp=variablesNode_.begin(); itCrisp != variablesNode_.end(); ++itCrisp) {
            std::string crispVariable = itCrisp->first.as<std::string>();
            // std::cout << "[FuzzyManager] Output crisp variable: " << crispVariable << std::endl;
            membershipsNode_ = itCrisp->second["memberships"];
            for (YAML::const_iterator itLinguistic=membershipsNode_.begin(); itLinguistic != membershipsNode_.end(); ++itLinguistic) {
                _pOutputMembershipFactory->GetOutputMembership(itLinguistic, pOutputMembership);
                _pOutputMemberships[crispVariable].insert(std::make_pair(itLinguistic->first.as<std::string>(), pOutputMembership));
                _inferenceValues[crispVariable].insert(std::make_pair(itLinguistic->first.as<std::string>(), 0.0));
            }
            std::string defuzzifierType = itCrisp->second["defuzzifier"].as<std::string>();
            getDefuzzifiersConstructor(defuzzifierType, crispVariable);
            _defuzzifiedValues[crispVariable] = 0.0;
        }
        pOutputMembership = NULL;
        return true;
    }

    bool FuzzyManager::getRuleBasesConstructor(YAML::Node &masterNode)
    {
        YAML::Node ruleBaseNode = masterNode["ruleBase"];
        return _pRuleBaseFactory->GetRuleBase(ruleBaseNode, _pRuleBases);
    }

    bool FuzzyManager::getDefuzzifiersConstructor(const std::string& defuzzifierType, const std::string& crispVariable)
    {
        Defuzzifier* pDefuzzifier;
        _pDefuzzifierFactory->GetDefuzzifier(defuzzifierType, crispVariable, _pOutputMemberships.at(crispVariable), pDefuzzifier);
        _pDefuzzifiers[crispVariable] = pDefuzzifier;
        return true;
    }

    void FuzzyManager::fuzzification()
    {
        for (auto &imf : _pInputMemberships) {
            for (auto &linguistic : imf.second) {
                // std::cout << linguistic.first << std::endl;
                _fuzzifiedValues.at(imf.first).at(linguistic.first) = linguistic.second->CalcTruthValue();
                // std::cout << "[FuzzyManager] _fuzzifiedValues crisp: " << imf.first; 
                // std::cout<< "\tlinguistic: " << linguistic.first << "\ttruth value: " << _fuzzifiedValues.at(imf.first).at(linguistic.first) << std::endl;  
            }
        }
    }

    void FuzzyManager::inferenceSystem()
    {
        std::string key;
        for (auto& crispVariable : _inferenceValues) {
            key = crispVariable.first;
            _pRuleBases.at(key)->CalcInference(_fuzzifiedValues, _inferenceValues.at(key));
        }
    }

    void FuzzyManager::defuzzification()
    {
        std::string key;
        for (auto& crispVariable : _defuzzifiedValues) {
            key = crispVariable.first;
            _defuzzifiedValues.at(key) = _pDefuzzifiers.at(key)->Defuzzify(_inferenceValues.at(key));
        }
    }
}