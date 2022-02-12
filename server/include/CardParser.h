#pragma once
#include <fstream>

#include <boost/format.hpp>
#include "PatientCard.h"

// Class help to convert patient data.
// Class can parse file to PatientCard structure or
// convert PatientCard to special string.
class CardParser {
 public:
  // Parse file to structure.
  // File has the following structure:
  //    lastName
  //    name
  //    patronymic
  //    birth year
  //    gender as char (m,f)
  static PatientCard parseFile(const std::string &path);
  // Convert patientCard structure to special string.
  // String format has the following structure:
  //    lastName$name$patronymic$birth year$m - if gender is Male
  //    lastName$name$patronymic$birth year$f - if gender is Female
  static std::string convertToString(const PatientCard &patient);
};