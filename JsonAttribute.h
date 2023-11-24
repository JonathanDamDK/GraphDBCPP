#pragma once
#include "Attributes.h"
#include <type_traits>
#include "simdjson.h"
class JsonAttribute : public Attribute {

public:
  simdjson::dom::object jsonObj;
  void mapJson(simdjson::dom::object) override;
};

