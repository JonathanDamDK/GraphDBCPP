#pragma once
#include "Attributes.h"
#include "simdjson.h"
#include <type_traits>
class JsonAttribute : public Attribute {

public:
  simdjson::dom::object jsonObj;
  void mapJson(simdjson::dom::object) override;
  std::string getJsonString() override;
};
