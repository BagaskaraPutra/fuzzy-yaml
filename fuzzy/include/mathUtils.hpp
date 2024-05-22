#ifndef MATH_UTILS_HPP
#define MATH_UTILS_HPP

#include <cmath>

namespace fuzzyyaml{
    class MathUtils{
    public:
        static double calcX(double y, double y1, double y2, double x1, double x2);
        static double calcY(double x, double x1, double x2, double y1, double y2);
        static double calcGradient(double x1, double y1, double x2, double y2);
        static double calcHypotenuse(double x1, double y1, double x2, double y2);
    };
}

#endif