#include "JsonAttribute.h" 
void JsonAttribute::mapJson(simdjson::dom::object obj){
  this->jsonObj = obj;
}
