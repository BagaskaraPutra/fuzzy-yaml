#ifndef CENTROID_HPP
#define CENTROID_HPP

#include "defuzzifier.hpp"

namespace fuzzyyaml{
    class Centroid : public Defuzzifier
    {
    public:
        Centroid(const std::string &outputVariableName, std::map<std::string, OutputMembership*>& outputMemberships);
        double Defuzzify(std::map<std::string, double> fuzzyInference) override;
    

    };
}

#endif