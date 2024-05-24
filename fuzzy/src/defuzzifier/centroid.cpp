#include "centroid.hpp"

namespace fuzzyyaml{

    Centroid::Centroid(const std::string &outputVariableName, std::map<std::string, OutputMembership *> &outputMemberships)
    : Defuzzifier(outputVariableName, outputMemberships)
    {
    }

    double Centroid::Defuzzify(std::map<std::string, double> fuzzyInference)
    {
        multi_polygon_t polygonUnion;
        multi_polygon_t tmp_poly; // a temporary variable
        for (auto& omf : _pOutputMemberships){
            // std::cout << _outputVariableName << " omf.first: " << omf.first << "\tfuzzyInference.at(omf.first): " << fuzzyInference.at(omf.first) << std::endl;
            omf.second->SetFuzzyInference(fuzzyInference.at(omf.first));
            // TODO: GetPolygon() is called twice, maybe call it once?
            if (bg::is_valid(omf.second->GetPolygon())){
                bg::union_(polygonUnion, omf.second->GetPolygon(), tmp_poly);
                polygonUnion = tmp_poly;
                bg::clear(tmp_poly);
            } 
        }
        point_t unionCentroid; 
        bg::centroid(polygonUnion, unionCentroid);
        return unionCentroid.x();
    }
}
