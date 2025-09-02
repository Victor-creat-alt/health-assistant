#include "patient.h"
#include <iostream>
#include "nutrition.h"
#include "fitness.h"
#include "mental_status.h"
#include "skincare.h"

// Forward declarations are not needed here if the headers already provide them.
// It's good practice to rely on the headers for function prototypes.
// We'll keep them for clarity, but they might be redundant depending on your .h files.

// Forward declaration for isBalancedDiet from nutrition.h
bool isBalancedDiet(const Nutrition& nutrition);

// Forward declaration for isFitnessGoal from fitness.h
bool isFitnessGoal(const Fitness& fitness);

// Forward declaration for needsSupport from mental_status.h
bool needsSupport(const MentalStatus& mentalStatus);

// Forward declaration for isRoutineMissing from skincare.h
bool isRoutineMissing(const SkinCare& skinCare);

// The full definitions of the helper print functions should be in their respective .cpp files
// (e.g., printNutrition in nutrition.cpp, printFitness in fitness.cpp, etc.)
// For now, we'll assume they are defined elsewhere.
void printNutrition(const Nutrition& nutrition);
void printFitness(const Fitness& fitness);
void printMentalStatus(const MentalStatus& mentalStatus);
void printSkinCare(const SkinCare& skinCare);


//compares two patients by ID
bool comparePatientById(const Patient& a, int id){
    return a.id == id;
}

//checks if the patient has achieved a balanced diet and fitness
void printPatientSummary(const Patient& patient){
    std::cout << "Patient: " << patient.name << "(ID: "<< patient.id <<")\n";
    std::cout << "Balanced Diet: " << (isBalancedDiet(patient.nutrition) ? "Yes" : "No") << "\n";
    std::cout << "Fitness Goal Achieved: " << (isFitnessGoal(patient.fitness) ? "Yes" : "No") << "\n";
    std::cout << "Needs Mental Support: " << (needsSupport(patient.mentalStatus) ? "Yes" : "No") << "\n";
    std::cout << "Skin Care Routine: " << (isRoutineMissing(patient.skinCare) ? "Yes" : "No" ) << "\n";
    
}