#pragma once
#include <string>
#include <cstdint>

enum class Gender {
  Male, Female
};

struct PatientCard {
  std::string name;
  std::string lastName;
  std::string patronymic;
  size_t birthYear;
  Gender gender;
};