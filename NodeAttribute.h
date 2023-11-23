#pragma once
#include "Attributes.h"
#include <type_traits>

template <class T> class NodeAttribute : public Attribute {

public:
  NodeAttribute();
  std::string textVal;
  std::vector<std::string> labels;
  T attributes;
  static_assert(std::is_base_of<Attribute, T>::value,"The base of NodeAttribute does not derive from attribute");
  void mapJson(simdjson::dom::object) override;
};
  
