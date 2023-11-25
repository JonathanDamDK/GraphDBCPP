#pragma once

#include "Attributes.h"
class PersonAttribute : public Attribute {
public:
  void mapJson(simdjson::dom::object) override;
  int salary;
  std::string name;
  std::string getJsonString() override;
};
