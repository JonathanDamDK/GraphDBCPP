#pragma once
#include "Attributes.h"
#include "Edge.h"
#include <type_traits>
template <class T, class E> class NodeAttribute : public Attribute {

public:
  NodeAttribute();
  std::string textVal;
  std::string uid;
  std::vector<std::string> labels;
  std::vector<Edge<E>> edges;
  T attributes;
  static_assert(std::is_base_of<Attribute, T>::value,
                "The base of NodeAttribute does not derive from attribute");
  void mapJson(simdjson::dom::object) override;
  std::string getJsonString() override;
  void setHasAttributesTrue(){
      hasAttributes = true;
  }
private:
  bool hasAttributes = false;
};
