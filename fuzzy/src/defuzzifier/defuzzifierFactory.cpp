#include "defuzzifierFactory.hpp"
#include "centroid.hpp"
// TODO: Add more defuzzifier header files here

namespace fuzzyyaml{
    DefuzzifierFactory::DefuzzifierFactory()
    {
    }
    bool DefuzzifierFactory::GetDefuzzifier(const std::string &defuzzifierType, const std::string &crispVariable, std::map<std::string, OutputMembership *> &outputMemberships, Defuzzifier*& pDefuzzifier)
    {
        if (defuzzifierType == "centroid"){
            pDefuzzifier = new Centroid(crispVariable, outputMemberships);
        } // else if{}
        // TODO: Add other defuzzifier methods in else if
        return false;
    }
}