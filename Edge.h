#pragma once
#include "Attributes.h"
#include <type_traits>
#include "JsonAttribute.h"
template <class T> class Edge : public Attribute {

public:
  std::string to;
  std::string label;
  T attributes;
  static_assert(std::is_base_of<Attribute, T>::value,"The base of Edge does not derive from attribute");
  void mapJson(simdjson::dom::object) override;
};


