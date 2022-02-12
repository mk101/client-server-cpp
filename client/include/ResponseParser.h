#pragma once
#include <vector>
#include <sstream>
#include "PatientCard.h"

class ResponseParser {
 public:
  // Parse response from server to PatientCard structure
  // response format is:
  //    lastName$name$patronymic$birth year$m - if gender is Male
  //    lastName$name$patronymic$birth year$f - if gender is Female
  static PatientCard parse(const std::string &response);
};