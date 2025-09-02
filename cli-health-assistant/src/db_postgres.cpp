#include "db_postgres.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

PostgresDB::PostgresDB(const std::string& connectinfo){
    conn = new pqxx::connection(connectinfo);
}

PostgresDB::~PostgresDB(){
    delete conn;
}

// Serialization helpers
json nutritionToJson(const Nutrition& n){
    return json{{"calories", n.calories}, {"protein", n.protein}, {"carbs", n.carbs}, {"fats", n.fats}, {"dietType", n.dietType}};
}

json fitnessToJson(const Fitness& f){
    return json{{"stepsPerDay", f.stepsPerDay}, {"exerciseMinutesPerDay", f.exerciseMinutesPerDay}, {"activityType", f.activityType}, {"fitnessGoals", f.fitnessGoals}, {"workOutRoutine", f.workOutRoutine}};
}

json mentalStatusToJson(const MentalStatus& m){
    return json{{"moodLevel", m.moodLevel}, {"stressLevel", m.stressLevel}, {"sleepQuality", m.sleepQuality}};
}

json skinCareToJson(const SkinCare& s){
    return json{{"skinType", s.skinType}, {"routine", s.routine}, {"productsUsed", s.productsUsed}, {"concerns", s.concerns}, {"goals", s.goals}};
}

// Deserialization helpers
Nutrition jsonToNutrition(const json & j ){
    Nutrition n;
    n.calories = j.value("calories", 0.0);
    n.protein = j.value("protein", 0.0);
    n.carbs = j.value("carbs", 0.0);
    n.fats = j.value("fats", 0.0);
    n.dietType = j.value("dietType", "");
    return n;
}

Fitness jsonToFitness(const json & j){
    Fitness f;
    f.stepsPerDay = j.value("stepsPerDay", 0);
    f.exerciseMinutesPerDay = j.value("exerciseMinutesPerDay", 0.0);
    f.activityType = j.value("activityType", "");
    f.fitnessGoals = j.value("fitnessGoals", "");
    f.workOutRoutine = j.value("workOutRoutine", "");
    return f;
}

MentalStatus jsonToMentalStatus(const json & j){
    MentalStatus m;
    m.moodLevel = j.value("moodLevel", 5);
    m.stressLevel = j.value("stressLevel", "");
    m.sleepQuality = j.value("sleepQuality", "");
    return m;
}

SkinCare jsonToSkinCare(const json & j){
    SkinCare s;
    s.skinType = j.value("skinType", "");
    s.routine = j.value("routine", "");
    s.productsUsed = j.value("productsUsed", "");
    s.concerns = j.value("concerns", "");
    s.goals = j.value("goals", "");
    return s;
}

bool PostgresDB::addPatient(const Patient& patient) {
    pqxx::work txn(*conn);
    txn.exec_params(
        "INSERT INTO patients (name, age, height, condition, nutrition, fitness, mental_status, skincare) VALUES ($1, $2, $3, $4, $5, $6, $7, $8)",
        patient.name, patient.age, patient.height, patient.condition,
        nutritionToJson(patient.nutrition).dump(),
        fitnessToJson(patient.fitness).dump(),
        mentalStatusToJson(patient.mentalStatus).dump(),
        skinCareToJson(patient.skinCare).dump()
    );
    txn.commit();
    return true;
}

std::optional<Patient> PostgresDB::getPatientById(int id){
    pqxx::work txn(*conn);
    auto res = txn.exec_params("SELECT id, name, age, height, condition, nutrition, fitness, mental_status, skincare FROM patients WHERE id=$1", id);
    if (res.empty()) return std::nullopt;
    Patient patient;
    patient.id = res[0][0].as<int>();
    patient.name = res[0][1].as<std::string>();
    patient.age = res[0][2].as<int>();
    patient.height = res[0][3].as<double>();
    patient.condition = res[0][4].as<std::string>();
    patient.nutrition = jsonToNutrition(json::parse(res[0][5].as<std::string>()));
    patient.fitness = jsonToFitness(json::parse(res[0][6].as<std::string>()));
    patient.mentalStatus = jsonToMentalStatus(json::parse(res[0][7].as<std::string>()));
    patient.skinCare = jsonToSkinCare(json::parse(res[0][8].as<std::string>()));
    return patient;
}

bool PostgresDB::updatePatient(int id, const Patient& updatePatient){
    pqxx::work txn(*conn);
    txn.exec_params(
        "UPDATE patients SET name=$1, age=$2, height=$3, condition=$4, nutrition=$5, fitness=$6, mental_status=$7, skincare=$8 WHERE id=$9",
        updatePatient.name, updatePatient.age, updatePatient.height, updatePatient.condition,
        nutritionToJson(updatePatient.nutrition).dump(),
        fitnessToJson(updatePatient.fitness).dump(),
        mentalStatusToJson(updatePatient.mentalStatus).dump(),
        skinCareToJson(updatePatient.skinCare).dump(),
        id
    );
    txn.commit();
    return true;
}

bool PostgresDB::deletePatient(int id){
    pqxx::work txn(*conn);
    txn.exec_params("DELETE FROM patients WHERE id=$1", id);
    txn.commit();
    return true;
}

std::vector<Patient> PostgresDB::listPatients(){
    pqxx::work txn(*conn);
    auto res = txn.exec("SELECT id, name, age, height, condition, nutrition, fitness, mental_status, skincare FROM patients");
    std::vector<Patient> patients;
    for (const auto& row : res){
        Patient patient;
        patient.id = row[0].as<int>();
        patient.name = row[1].as<std::string>();
        patient.age = row[2].as<int>();
        patient.height = row[3].as<double>();
        patient.condition = row[4].as<std::string>();
        patient.nutrition = jsonToNutrition(json::parse(row[5].as<std::string>()));
        patient.fitness = jsonToFitness(json::parse(row[6].as<std::string>()));
        patient.mentalStatus = jsonToMentalStatus(json::parse(row[7].as<std::string>()));
        patient.skinCare = jsonToSkinCare(json::parse(row[8].as<std::string>()));
        patients.push_back(patient);
    }
    return patients;
}