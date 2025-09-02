#include "fitness.h"
#include <iostream>

void printFitness(const Fitness& f){
std::cout << "Steps per day: " << f.stepsPerDay << "\n";
std::cout << "Exercise minutes per day: " << f.exerciseMinutesPerDay << "\n";
std::cout << "Activity type:" << f.activityType << "\n";
std::cout << "Fitness goals: " << f.fitnessGoals << "\n";
std::cout << "Workout routine: " << f.workOutRoutine << "\n";
}

bool achieveDailyGoal(const Fitness& f){
return f.stepsPerDay >= 10000 || f.exerciseMinutesPerDay >= 30;
} 

// This function is missing and is causing the "undefined reference" error
bool isFitnessGoal(const Fitness& f) {
    // You need to define the logic for this function.
    // A simple example could be checking if the user is meeting some arbitrary goal.
    return f.stepsPerDay >= 5000 && f.exerciseMinutesPerDay >= 20;
}