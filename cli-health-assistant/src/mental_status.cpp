#include "mental_status.h"
#include <iostream>

void printMentalStatus(const MentalStatus& m){
    std:: cout << "Mood level: " << m.moodLevel << "/10\n";
    std::cout << "Stress Level: " << m.stressLevel << "\n";
    std::cout << "Sleep Quality: " << m.sleepQuality << "\n";
}

bool needsSupport(const MentalStatus & m){
    return m.moodLevel <= 3 || m.stressLevel == "High";
}