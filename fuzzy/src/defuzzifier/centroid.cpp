#include "centroid.hpp"

namespace fuzzyyaml{

    Centroid::Centroid(const std::string &outputVariableName, std::map<std::string, OutputMembership *> &outputMemberships)
    : Defuzzifier(outputVariableName, outputMemberships)
    {
    }

    double Centroid::Defuzzify(double fuzzyInference)
    {
        multi_polygon_t polygonUnion;
        multi_polygon_t tmp_poly; // a temporary variable
        for (auto& omf : _pOutputMemberships){
            omf.second->SetFuzzyInference(fuzzyInference);
            bg::union_(polygonUnion, omf.second->GetPolygon(), tmp_poly);
            polygonUnion = tmp_poly;
            bg::clear(tmp_poly); 
        }
        point_t unionCentroid; 
        bg::centroid(polygonUnion, unionCentroid);
        return unionCentroid.x();
    }
}
