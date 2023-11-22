#pragma once
#include "simdjson.h"

class Attribute {
public:
  /// This function will be used when converting a json object to a json object to an actual class
  virtual void mapJson(simdjson::dom::object) = 0;
};
