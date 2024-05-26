#include "outputMembershipFactory.hpp"
#include "trapezoidOutputMembership.hpp"
#include "triangleOutputMembership.hpp"
// TODO: Add more output membership header files here

namespace fuzzyyaml{
    OutputMembershipFactory::OutputMembershipFactory()
    {
    }

    bool OutputMembershipFactory::GetOutputMembership(YAML::const_iterator &itLinguistic, OutputMembership*& pOutputMembership)
    {
        std::string sMembershipType = itLinguistic->second["type"].as<std::string>();
        // try{
            if (sMembershipType == "trapezoid") {
                pOutputMembership = new TrapezoidOutputMembership(itLinguistic->first.as<std::string>(),
                                                                    itLinguistic->second["bottomLeft"].as<double>(),
                                                                    itLinguistic->second["upperLeft"].as<double>(),
                                                                    itLinguistic->second["upperRight"].as<double>(),
                                                                    itLinguistic->second["bottomRight"].as<double>()
                                                                    );
            } else if (sMembershipType == "triangle") {
                pOutputMembership = new TriangleOutputMembership(itLinguistic->first.as<std::string>(),
                                                                    itLinguistic->second["bottomLeft"].as<double>(),
                                                                    itLinguistic->second["peak"].as<double>(),
                                                                    itLinguistic->second["bottomRight"].as<double>()
                                                                    );
            }
            // TODO: Add other output membership methods in else if
            // pOutputMembership->PrintMembershipData();
            return true;
        // } catch (std::exception e) {
        //     return false;
        // }
    }
}