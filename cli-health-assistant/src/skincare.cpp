#include "skincare.h"
#include <iostream>

void printSkinCare(const SkinCare& s){
    std::cout << "Skin type: " << s.skinType << "\n";
    std::cout << "Routine:" << s.routine << "\n";
    std::cout << "Products used: " << s.productsUsed << "\n";
    std::cout << "Concerns:" << s.concerns << "\n";
}

bool isRoutineMissing(const SkinCare& s){
    return s.routine.empty();
}