#include <iostream>
#include <string>
#include "patient.h"
#include "db_postgres.h"
#include "nutrition.h"
#include "fitness.h"
#include "mental_status.h"
#include "skincare.h"
#include"utils.h"

// Forward declaration for functions defined in other files
void printPatient(const Patient& patient);
void clearInput(); // Assuming this function is in utils.h/utils.cpp

void displayMenu(){
    std::cout << "Health Assistant Menu:\n";
    std::cout << "1. Add Patient\n";
    std::cout << "2. View Patient Details\n";
    std::cout << "3. Update Patient Information\n";
    std::cout << "4. Delete Patient record\n";
    std::cout << "5. List All Patients\n";
    std::cout << "6. Exit\n";
}

Nutrition inputNutrition(){
    Nutrition nutrition;
    std::cout << "Enter daily calories: ";
    std::cin >> nutrition.calories;
    std::cout << "Enter daily protein (g):";
    std::cin >> nutrition.protein;
    std::cout << "Enter daily carbs (g): ";
    std::cin >> nutrition.carbs;
    std::cout << "Enter daily fats (g): ";
    std::cin >> nutrition.fats;
    std::cout << "Enter diet type (e.g. Vegetarian, Vegan, Keto): ";
    std::cin >> nutrition.dietType;
    return nutrition;
}

Fitness inputFitness(){
    Fitness fitness;
    std::cout << "Enter steps per day: ";
    std::cin >> fitness.stepsPerDay;
    std::cout << "Enter exercise minutes per day: ";
    std::cin >> fitness.exerciseMinutesPerDay;
    std::cout << "Enter activity type (e.g Running, Cycling): ";
    std::cin >> fitness.activityType;
    std::cout << "Enter fitness goals (e.g Weight Loss, Muscle Groin, Maintenance): ";
    std::cin >> fitness.fitnessGoals;
    std::cout << "Enter workout routine (e.g Cardio, Strength Training): ";
    std::cin >> fitness.workOutRoutine;
    return fitness;
}

MentalStatus inputMentalStatus(){
    MentalStatus mentalStatus;
    std::cout << "Enter mood level (1-10): ";
    std::cin >> mentalStatus.moodLevel;
    std::cout << "Enter stress level (Low, Medium, High): ";
    std::cin >> mentalStatus.stressLevel;
    std::cout << "Enter sleep quality (Poor, Average, Good): ";
    std::cin >> mentalStatus.sleepQuality;
    return mentalStatus;
}

SkinCare inputSkinCare(){
    SkinCare skinCare;
    std::cout << "Enter skin type (e.g Oily, Dry, Combination): ";
    std::cin >> skinCare.skinType;
    std::cout << "Enter Skin concerns (e.g Acne, Aging, Sensitivity): ";
    std::cin >> skinCare.concerns;
    std::cout << "Enter skin care routine (e.g Cleansing, Moisturization): ";
    std::cin >> skinCare.routine;
    std::cout << "Enter products used (e.g Cleanser, Toner, Moisturizer): ";
    std::cin >> skinCare.productsUsed;
    std::cout << "Enter skin care goals (e.g Clear Skin, Hydration, Anti-Aging): ";
    std::cin >> skinCare.goals;
    return skinCare;
}

Patient inputPatient(){
    Patient patient;
    std::cout << "Enter patient ID:";
    std::cin >> patient.id;
    std::cout << "Enter patient name: ";
    std::cin >> patient.name;
    std::cout << "Enter patient age: ";
    std::cin >> patient.age;
    std::cout << "Enter patient height (in cm): ";
    std::cin >> patient.height;
    std::cout << "Enter mental condition (e.g Depression, Anxiety): ";
    std::cin >> patient.condition;
    std::cout << "--- Enter Nutrition Details --- \n";
    patient.nutrition = inputNutrition();
    std::cout << "--- Enter Fitness Details --- \n";
    patient.fitness = inputFitness();
    std::cout << "--- Enter Mental Status Details --- \n";
    patient.mentalStatus = inputMentalStatus();
    std::cout << "--- Enter Skin Care Details --- \n";
    patient.skinCare = inputSkinCare();
    return patient;
}

int main(){
    std::string connectinfo = "host=localhost dbname=health_assistant user=health password=2005 port=5432";
    PostgresDB db(connectinfo);

    int choice;
    while (true){
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        clearInput();

        if (choice == 6) {
            std::cout << "Exiting the program.\n";
            break;
        }

        if (choice == 1) {
            Patient patient = inputPatient();
            db.addPatient(patient);
            std::cout << "Patient added successfully. \n";
        } else if(choice == 2){
            int id;
            std::cout << "Enter Patient ID to view details:";
            std::cin >> id;
            clearInput();
            auto patientOpt = db.getPatientById(id);
            if(patientOpt){
                printPatient(*patientOpt);
            } else {
                std::cout<< "Patient not found.\n";
            }
        } else if (choice == 3) {
            int id;
            std::cout << "Enter Patient ID to update: ";
            std::cin >> id;
            clearInput();
            auto patient = db.getPatientById(id);
            if(patient) {
                std::cout << "Enter new details for the patient:\n";
                Patient updatedPatient = inputPatient();
                updatedPatient.id = id;
                if(db.updatePatient(id, updatedPatient)){
                    std::cout << "Patient updated successfully.\n";
                }
            } else {
                std::cout << "Patient not found.\n";
            }
        } else if(choice == 4) {
            int id;
            std::cout << "Enter Patient ID to delete:";
            std::cin >> id;
            clearInput();
            if(db.deletePatient(id)){
                std::cout << "Patient deleted successfully.\n";
                } else {
                std::cout << "Patient not found.\n";
                }
        } else if (choice == 5){
            auto patients = db.listPatients();
            if(patients.empty()){
                std::cout << "No patients found. \n";
            } else {
                for (const auto&patient : patients){
                    printPatient(patient);
                    std::cout << "------------------------\n";
                }
            }
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}

// Definition for printPatient
void printPatient(const Patient& patient) {
    std::cout << "Patient ID: " << patient.id << "\n";
    std::cout << "Name: " << patient.name << "\n";
    std::cout << "Age: " << patient.age << "\n";
    std::cout << "Height: " << patient.height << " cm\n";
    std::cout << "Condition: " << patient.condition << "\n";
    std::cout << "--- Nutrition ---\n";
    std::cout << "Calories: " << patient.nutrition.calories << "\n";
    std::cout << "Protein: " << patient.nutrition.protein << " g\n";
    std::cout << "Carbs: " << patient.nutrition.carbs << " g\n";
    std::cout << "Fats: " << patient.nutrition.fats << " g\n";
    std::cout << "Diet Type: " << patient.nutrition.dietType << "\n";
    std::cout << "--- Fitness ---\n";
    std::cout << "Steps/Day: " << patient.fitness.stepsPerDay << "\n";
    std::cout << "Exercise Minutes/Day: " << patient.fitness.exerciseMinutesPerDay << "\n";
    std::cout << "Activity Type: " << patient.fitness.activityType << "\n";
    std::cout << "Fitness Goals: " << patient.fitness.fitnessGoals << "\n";
    std::cout << "Workout Routine: " << patient.fitness.workOutRoutine << "\n";
    std::cout << "--- Mental Status ---\n";
    std::cout << "Mood Level: " << patient.mentalStatus.moodLevel << "\n";
    std::cout << "Stress Level: " << patient.mentalStatus.stressLevel << "\n";
    std::cout << "Sleep Quality: " << patient.mentalStatus.sleepQuality << "\n";
    std::cout << "--- Skin Care ---\n";
    std::cout << "Skin Type: " << patient.skinCare.skinType << "\n";
    std::cout << "Concerns: " << patient.skinCare.concerns << "\n";
    std::cout << "Routine: " << patient.skinCare.routine << "\n";
    std::cout << "Products Used: " << patient.skinCare.productsUsed << "\n";
    std::cout << "Goals: " << patient.skinCare.goals << "\n";
}