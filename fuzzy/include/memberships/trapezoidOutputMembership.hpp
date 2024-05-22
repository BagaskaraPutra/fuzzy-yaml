#ifndef TRAPEZOID_OUTPUT_MEMBERSHIP_HPP
#define TRAPEZOID_OUTPUT_MEMBERSHIP_HPP

#include <string>

#include "membershipType.hpp"
#include "trapezoidMembership.hpp"
#include "outputMembership.hpp"

namespace fuzzyyaml{
    class TrapezoidOutputMembership : public TrapezoidMembership, public OutputMembership
    {
    public:
        TrapezoidOutputMembership(const std::string& name, 
                            const double& bottomLeft, 
                            const double& upperLeft, 
                            const double& upperRight, 
                            const double& bottomRight);
        
        void PrintMembershipData() override;
        double GetYValue(double x) override;
        
        polygon_t GetPolygon() override;
        double GetCentroidX() override;
    
    protected:
        double _xinf1;
        double _xinf2;
        // double _base;
        // double _roof;
    };
}

#endif