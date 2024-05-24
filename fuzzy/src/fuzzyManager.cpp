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
        getInputVariablesConfig(config_);
        getOutputVariablesConfig(config_);
        getRuleBasesConfig(config_);

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

    bool FuzzyManager::getInputVariablesConfig(YAML::Node &masterNode)
    {
        YAML::Node variablesNode_ = masterNode["inputVariables"];
        InputMembership *_pInputMembership;
        YAML::Node membershipsNode_;
        for (YAML::const_iterator itCrisp=variablesNode_.begin(); itCrisp != variablesNode_.end(); ++itCrisp) {
            std::string crispVariable = itCrisp->first.as<std::string>();
            membershipsNode_ = itCrisp->second["memberships"];
            // std::cout << "[FuzzyManager] Input crisp variable: " << crispVariable << std::endl;
            for (YAML::const_iterator itLinguistic=membershipsNode_.begin(); itLinguistic != membershipsNode_.end(); ++itLinguistic) {
                std::string sMembershipType = itLinguistic->second["type"].as<std::string>();
                if (sMembershipType == "trapezoid") {
                   _pInputMembership = new TrapezoidInputMembership(itLinguistic->first.as<std::string>(),
                                                                    itLinguistic->second["bottomLeft"].as<double>(),
                                                                    itLinguistic->second["upperLeft"].as<double>(),
                                                                    itLinguistic->second["upperRight"].as<double>(),
                                                                    itLinguistic->second["bottomRight"].as<double>()
                                                                    );
                } else if (sMembershipType == "triangle") {
                   _pInputMembership = new TriangleInputMembership(itLinguistic->first.as<std::string>(),
                                                                    itLinguistic->second["bottomLeft"].as<double>(),
                                                                    itLinguistic->second["peak"].as<double>(),
                                                                    itLinguistic->second["bottomRight"].as<double>()
                                                                    );
                } 
                // TODO: Add other input membership methods in else if
                // _pInputMembership->PrintMembershipData();
                _pInputMemberships[crispVariable].insert(std::make_pair(itLinguistic->first.as<std::string>(), _pInputMembership)); //.push_back(_pMembership);
                _fuzzifiedValues[crispVariable].insert(std::make_pair(itLinguistic->first.as<std::string>(), 0.0));
            }
        }
        _pInputMembership = NULL;
        return true;
    }

    bool FuzzyManager::getOutputVariablesConfig(YAML::Node &masterNode)
    {
        YAML::Node variablesNode_ = masterNode["outputVariables"];
        YAML::Node membershipsNode_; 
        OutputMembership *_pOutputMembership;

        for (YAML::const_iterator itCrisp=variablesNode_.begin(); itCrisp != variablesNode_.end(); ++itCrisp) {
            std::string crispVariable = itCrisp->first.as<std::string>();
            // std::cout << "[FuzzyManager] Output crisp variable: " << crispVariable << std::endl;
            membershipsNode_ = itCrisp->second["memberships"];
            for (YAML::const_iterator itLinguistic=membershipsNode_.begin(); itLinguistic != membershipsNode_.end(); ++itLinguistic) {
                std::string sMembershipType = itLinguistic->second["type"].as<std::string>();
                if (sMembershipType == "trapezoid") {
                   _pOutputMembership = new TrapezoidOutputMembership(itLinguistic->first.as<std::string>(),
                                                                    itLinguistic->second["bottomLeft"].as<double>(),
                                                                    itLinguistic->second["upperLeft"].as<double>(),
                                                                    itLinguistic->second["upperRight"].as<double>(),
                                                                    itLinguistic->second["bottomRight"].as<double>()
                                                                    );
                } else if (sMembershipType == "triangle") {
                   _pOutputMembership = new TriangleOutputMembership(itLinguistic->first.as<std::string>(),
                                                                    itLinguistic->second["bottomLeft"].as<double>(),
                                                                    itLinguistic->second["peak"].as<double>(),
                                                                    itLinguistic->second["bottomRight"].as<double>()
                                                                    );
                }
                // TODO: Add other output membership methods in else if
                // _pOutputMembership->PrintMembershipData();
                _pOutputMemberships[crispVariable].insert(std::make_pair(itLinguistic->first.as<std::string>(), _pOutputMembership));
                _inferenceValues[crispVariable].insert(std::make_pair(itLinguistic->first.as<std::string>(), 0.0));
            }
            std::string defuzzifierType = itCrisp->second["defuzzifier"].as<std::string>();
            getDefuzzifierConfig(defuzzifierType, crispVariable);
            _defuzzifiedValues[crispVariable] = 0.0;
        }
        _pOutputMembership = NULL;
        return true;
    }

    bool FuzzyManager::getRuleBasesConfig(YAML::Node &masterNode)
    {
        YAML::Node ruleBaseNode = masterNode["RuleBase"];
        for (YAML::const_iterator itRules=ruleBaseNode.begin(); itRules != ruleBaseNode.end(); ++itRules) {
            std::string outputVariable = itRules->first.as<std::string>();
            if (itRules->second["table"]){
                _pRuleBases[outputVariable] = new RuleTable(outputVariable, ruleBaseNode);
            }
            // TODO: Add other rule base methods in else if
            // _pRuleBases.at(outputVariable)->PrintRules();
        }
        return true;
    }

    bool FuzzyManager::getDefuzzifierConfig(const std::string& defuzzifierType, const std::string& crispVariable)
    {
        if (defuzzifierType == "centroid"){
            _pDefuzzifiers[crispVariable] = new Centroid(crispVariable, _pOutputMemberships.at(crispVariable));
        }
        // TODO: Add other defuzzifier methods in else if
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