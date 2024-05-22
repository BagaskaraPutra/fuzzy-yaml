#include "membership.hpp"

namespace fuzzyyaml{
    Membership::Membership(const std::string &name, const MembershipType &mType)
    {
        _name = name;
        _mType = mType;
    }

    Membership::Membership(const std::string &name, const InputOrOutputType &ioType)
    {
        _name = name;
        _ioType = ioType;
    }

    Membership::Membership(const std::string& name, const MembershipType& mType, const InputOrOutputType& ioType)
    {
        _name = name;
        _mType = mType;
        _ioType = ioType;
    }

    std::string Membership::GetName()
    {
        return _name;
    }

    MembershipType Membership::GetMembershipType()
    {
        return _mType;
    }

    InputOrOutputType Membership::GetIOType()
    {
        return _ioType;
    }
}