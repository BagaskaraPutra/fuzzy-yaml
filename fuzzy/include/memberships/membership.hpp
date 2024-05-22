#ifndef MEMBERSHIP_HPP
#define MEMBERSHIP_HPP

#include <iostream>
#include <cmath>

#include "membershipType.hpp"

namespace fuzzyyaml{
    class Membership
    {
    public:
        Membership(const std::string& name, const MembershipType& mType);
        Membership(const std::string& name, const InputOrOutputType& ioType);
        Membership(const std::string& name, const MembershipType& mType, const InputOrOutputType& ioType);
        virtual ~Membership() = default;
        std::string GetName();
        MembershipType GetMembershipType();
        InputOrOutputType GetIOType();
        virtual void PrintMembershipData() = 0;
        virtual double GetYValue(double x) = 0; // useful for plotting in GUI

    protected:
        std::string _name;
        MembershipType _mType;
        InputOrOutputType _ioType;
    };
}

#endif