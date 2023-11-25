#include "PersonAttribute.h"

std::string PersonAttribute::getJsonString(){
  return "{\"personAttribute\" : \"not implemented\"}";
}

void PersonAttribute::mapJson(simdjson::dom::object obj) {
  try {
    salary = int(obj["salary"].get_int64());
  } catch (simdjson::simdjson_error err) {
    std::cout << "\n error occured while loading salary: "
              << std::string(err.what()) << "\n";
  }
  try {
    name = std::string(std::string_view(obj["name"].get_string()));
  } catch (simdjson::simdjson_error err) {
    std::cout << "\n error occured while loading name: "
              << std::string(err.what()) << "\n";
  }
}
