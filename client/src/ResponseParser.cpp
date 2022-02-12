#include "ResponseParser.h"

std::vector<std::string> split(const std::string &source, char delimiter) {
  std::vector<std::string> strings;
  std::istringstream f(source);
  std::string s;
  while (std::getline(f, s, delimiter)) {
    strings.push_back(s);
  }

  return strings;
}

PatientCard ResponseParser::parse(const std::string &response) {
  PatientCard patient {};
  auto strings = split(response, '$');
  patient.lastName = strings.at(0);
  patient.name = strings.at(1);
  patient.patronymic = strings.at(2);
  patient.birthYear = static_cast<size_t>(std::stoi(strings.at(3)));
  patient.gender = strings.at(4) == "m" ? Gender::Male : Gender::Female;

  return patient;
}
