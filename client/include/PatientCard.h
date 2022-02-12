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

  [[nodiscard]] std::string toString() const {
    std::stringstream stream;
    stream << "FIO: " << name << " " << lastName
        << " " << patronymic << " Birth Year: " << birthYear
        << " Gender: " << (gender == Gender::Male ? "Male" : "Female");

    return stream.str();
  }
};