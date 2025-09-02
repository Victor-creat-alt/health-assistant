#pragma once
#include <string>
#include "nutrition.h"
#include "fitness.h"
#include "mental_status.h"
#include "skincare.h"

struct Patient {
    int id;
    std::string name;
    int age;
    double height;
    std::string condition;
    Nutrition nutrition;
    Fitness fitness;
    MentalStatus mentalStatus;
    SkinCare skinCare;


};