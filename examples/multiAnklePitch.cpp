#include <iostream>
#include <sys/time.h>

#include "fuzzyManager.hpp"

std::map<std::string, double> testAnklePitch(fuzzyyaml::FuzzyManager& manager, double angle, double angularVelocity){
    struct timeval begin, end;
    gettimeofday(&begin, 0);

    manager.SetCrispInput("Angle", angle);
    manager.SetCrispInput("AngularVelocity", angularVelocity);
    std::map<std::string, double> gain = manager.CalcCrispOutputs();
    
    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;

    printf("\n");
    std::cout << "[test] Angle: " << angle << "\tAngularVelocity: " << angularVelocity << "\tKp: " << gain.at("Kp") << "\tKd: " << gain.at("Kd") << std::endl;
    printf("Measured execution time: %.6f seconds.\n", elapsed);
    
    return gain;
}

int main(int argc, char *argv[]) 
{
    std::string filePath;
    if (argc <= 1){
        filePath = "../config/anklePitch.yaml";
    } else {
        filePath = argv[1];
    }
    fuzzyyaml::FuzzyManager anklePitch(filePath);

    testAnklePitch(anklePitch, 7.9, -0.635);
    testAnklePitch(anklePitch, 7.9, -4.67);
    testAnklePitch(anklePitch, -46.2, 3.02);
    testAnklePitch(anklePitch, -14.6, 0.56);
    testAnklePitch(anklePitch, 5.51, 0);
    testAnklePitch(anklePitch, 5.51, -4.26);
    testAnklePitch(anklePitch, 15.2, -4.26);
    testAnklePitch(anklePitch, 21, 3.67);
    testAnklePitch(anklePitch, -15.3, 3.67);
    testAnklePitch(anklePitch, -3.2, -4.12);
    
    return 0;
}