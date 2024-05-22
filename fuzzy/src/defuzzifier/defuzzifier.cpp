#include "defuzzifier.hpp"

namespace fuzzyyaml{

    Defuzzifier::Defuzzifier(const std::string &outputVariableName, std::map<std::string, OutputMembership*>& outputMemberships)
    {
        _outputVariableName = outputVariableName;
        _pOutputMemberships = outputMemberships;
    }

    void Defuzzifier::SetOutputMemberships(std::map<std::string, OutputMembership*>& outputMemberships)
    {
        _pOutputMemberships = outputMemberships;
    }
}