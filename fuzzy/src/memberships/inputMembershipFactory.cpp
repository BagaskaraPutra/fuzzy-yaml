#include "inputMembershipFactory.hpp"
#include "trapezoidInputMembership.hpp"
#include "triangleInputMembership.hpp"
// TODO: Add more input membership header files here

namespace fuzzyyaml{
    InputMembershipFactory::InputMembershipFactory()
    {
    }

    bool InputMembershipFactory::GetInputMembership(YAML::const_iterator &itLinguistic, InputMembership*& pInputMembership)
    {
        std::string sMembershipType = itLinguistic->second["type"].as<std::string>();
        // try{
            if (sMembershipType == "trapezoid") {
                pInputMembership = new TrapezoidInputMembership(itLinguistic->first.as<std::string>(),
                                                                    itLinguistic->second["bottomLeft"].as<double>(),
                                                                    itLinguistic->second["upperLeft"].as<double>(),
                                                                    itLinguistic->second["upperRight"].as<double>(),
                                                                    itLinguistic->second["bottomRight"].as<double>()
                                                                    );
            } else if (sMembershipType == "triangle") {
                pInputMembership = new TriangleInputMembership(itLinguistic->first.as<std::string>(),
                                                                    itLinguistic->second["bottomLeft"].as<double>(),
                                                                    itLinguistic->second["peak"].as<double>(),
                                                                    itLinguistic->second["bottomRight"].as<double>()
                                                                    );
            }
            // TODO: Add other input membership methods in else if
            // pInputMembership->PrintMembershipData();
            return true;
        // } catch (std::exception e) {
        //     return false;
        // }
    }
}