#include "mathUtils.hpp"

namespace fuzzyyaml{
    double MathUtils::calcX(double y, double y1, double y2, double x1, double x2)
    {
        // 2D Line Equation

        //   x - x1          y - y1
        // ---------   =   ---------
        //  x2 - x1         y2 - y1    
        //                (Y_section)

        //       y - y1 
        // x = --------- ( x2 - x1 ) + x1
        //      y2 - y1 

        double Y_section = (y - y1) / (y2 - y1);

        return ((x2 - x1) * Y_section) + x1;
    }

    double MathUtils::calcY(double x, double x1, double x2, double y1, double y2)
    {
        // 2D Line Equation

        //   x - x1          y - y1
        // ---------   =   ---------
        //  x2 - x1         y2 - y1    
        // (X_section)

        //       x - x1 
        // y = --------- ( y2 - y1 ) + y1
        //      x2 - x1 

        double X_section = (x - x1) / (x2 - x1);

        return ((y2 - y1) * X_section) + y1;
    }

    double MathUtils::calcHypotenuse(double x1, double y1, double x2, double y2)
    {
        // c = sqrt((x2 - x1)^2 + (y2 - y1)^2)

        double x = x2-x1;
        double y = y2-y1;

        return sqrt(pow(x,2)+pow(y,2));
    }

    double MathUtils::calcGradient(double x1, double y1, double x2, double y2)
    {
        //      y2 - y1
        // m = ---------
        //      x2 - x1
        return (y2-y1)/(x2-x1);
    }
}