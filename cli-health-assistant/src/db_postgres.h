#pragma once
#include <pqxx/pqxx>
#include "patient.h"
#include <vector>
#include <optional>
#include <string>

class PostgresDB {
public:
    PostgresDB(const std::string& connectinfo);
    ~PostgresDB();

    bool addPatient(const Patient&patient);
    std::optional<Patient> getPatientById(int id);
    bool updatePatient(int id, const Patient& updatePatient);
    bool deletePatient(int id);
    std::vector<Patient> listPatients();

 private:
 pqxx::connection* conn;   

};