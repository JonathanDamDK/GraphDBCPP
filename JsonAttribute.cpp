#include "JsonAttribute.h"
void JsonAttribute::mapJson(simdjson::dom::object obj) { this->jsonObj = obj; }
std::string JsonAttribute::getJsonString() {
  std::string str = simdjson::to_string(jsonObj);
  std::cout <<"object: " <<jsonObj<< "\n";
  return str;
}
