#include "CardParser.h"

PatientCard CardParser::parseFile(const std::string &path) {
  PatientCard patient = {};
  std::ifstream file(path);
  char buffer;

  file >> patient.lastName;
  file >> patient.name;
  file >> patient.patronymic;
  file >> patient.birthYear;
  file >> buffer;
  patient.gender = tolower(buffer) == 'm'
      ? Gender::Male : Gender::Female;

  return patient;
}
std::string CardParser::convertToString(const PatientCard &patient) {
  auto fmt = boost::format("%s$%s$%s$%u$%c")
      % patient.lastName
      % patient.name
      % patient.patronymic
      % patient.birthYear
      % (patient.gender == Gender::Male ? 'm' : 'f');

  return boost::str(fmt);
}
