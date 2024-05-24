#ifndef DEFUZZIFIER_HPP
#define DEFUZZIFIER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>

#include "outputMembership.hpp"

namespace fuzzyyaml
{
    class Defuzzifier
    {
    public:
        Defuzzifier(const std::string &outputVariableName, std::map<std::string, OutputMembership*>& outputMemberships);
        void SetOutputMemberships(std::map<std::string, OutputMembership*>& outputMemberships);
        virtual double Defuzzify(std::map<std::string, double> fuzzyInference) = 0;

    protected:
        std::string _outputVariableName;
        std::map<std::string, OutputMembership *> _pOutputMemberships;
        double _fuzzyInference;
        double _crispOutput;
    };
}

#endif