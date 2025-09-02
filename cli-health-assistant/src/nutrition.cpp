#include "nutrition.h"
#include <iostream>

void printNutrition(const Nutrition& n){
    std::cout << "Calories: " << n.calories << "\n";
    std::cout << "Protein: " << n.protein << "g\n";
    std::cout << "Carbs: " << n.carbs << "g\n";
    std::cout << "Fats: " << n.fats << "g\n";
    std::cout << "Diet Type:" <<n.dietType << "\n";
}

bool isBalancedDiet(const Nutrition& n){
    return n.protein > 0 && n.carbs > 0 && n.fats > 0;
}