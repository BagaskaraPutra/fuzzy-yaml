#include <iostream>

#include "fuzzyManager.hpp"

int main(int argc, char *argv[]) 
{
    std::string filePath;
    if (argc <= 1){
        filePath = "../config/anklePitch.yaml";
    } else {
        filePath = argv[1];
    }
    fuzzyyaml::FuzzyManager anklePitch(filePath);

    anklePitch.SetCrispInput("Angle", 7.9);
    anklePitch.SetCrispInput("AngularVelocity", -0.635);
    
    std::map<std::string, double> gain = anklePitch.CalcCrispOutputs();
    
    printf("\n");
    std::cout << "Kp: " << gain.at("Kp") << std::endl;
    std::cout << "Kd: " << gain.at("Kd") << std::endl;
    
    return 0;
}