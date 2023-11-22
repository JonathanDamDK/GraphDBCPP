#pragma once

#include "Attributes.h"
class PersonAttribute : public Attribute {
  public: 
    void mapJson(simdjson::dom::object);
    int salary;
    std::string name; 
};
