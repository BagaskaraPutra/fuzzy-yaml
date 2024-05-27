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
    fuzzyyaml::FuzzyManager anklePitch;

    anklePitch.LoadConfig(filePath);
    anklePitch.SetCrispInput("Angle", 21);
    anklePitch.SetCrispInput("AngularVelocity", 3.67);
    std::map<std::string, double> gain = anklePitch.CalcCrispOutputs();
    printf("\n");
    std::cout << "Kp: " << gain.at("Kp") << std::endl;
    std::cout << "Kd: " << gain.at("Kd") << std::endl;
    
    anklePitch.LoadConfig("../config/anklePitchExample2.yaml");
    anklePitch.SetCrispInput("Angle", 21);
    anklePitch.SetCrispInput("AngularVelocity", 3.67);
    gain = anklePitch.CalcCrispOutputs();
    printf("\n");
    std::cout << "Kp: " << gain.at("Kp") << std::endl;
    std::cout << "Kd: " << gain.at("Kd") << std::endl;

    return 0;
}