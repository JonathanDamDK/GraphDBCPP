#pragma once
#include "Attributes.h"
#include <type_traits>
#include "simdjson.h"
class JsonAttribute : public Attribute {

public:
  std::string textVal;
  std::vector<std::string> labels;
  simdjson::dom::object jsonObj;
  void mapJson(simdjson::dom::object) override;
};

