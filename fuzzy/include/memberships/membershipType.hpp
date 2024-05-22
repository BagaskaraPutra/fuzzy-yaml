#ifndef MEMBERSHIP_TYPE_HPP
#define MEMBERSHIP_TYPE_HPP

namespace fuzzyyaml{
    enum MembershipType{
        TRAPEZOID,
        TRIANGLE,
        SINGLETON,
        GAUSSIAN
    };

    enum InputOrOutputType{
        INPUT_MEMBERSHIP,
        OUTPUT_MEMBERSHIP
    };
}

#endif