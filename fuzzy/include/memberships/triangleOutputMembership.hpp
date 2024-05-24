#ifndef TRIANGLE_OUTPUT_MEMBERSHIP_HPP
#define TRIANGLE_OUTPUT_MEMBERSHIP_HPP

#include <string>

#include "membershipType.hpp"
#include "triangleMembership.hpp"
#include "outputMembership.hpp"

namespace fuzzyyaml{
    class TriangleOutputMembership : public TriangleMembership, public OutputMembership
    {
    public:
        TriangleOutputMembership(const std::string& name, 
                            const double& bottomLeft, 
                            const double& peak, 
                            const double& bottomRight);
        
        void PrintMembershipData() override;
        double GetYValue(double x) override;
        
        polygon_t GetPolygon() override;
        double GetCentroidX() override;
    
    protected:
        double _xinf1;
        double _xinf2;
    };
}

#endif