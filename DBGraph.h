#pragma once

#include "NodeAttribute.h"
#include <_wctype.h>
#include <string>
#include <vector>
#include "unordered_map"
template <class T, class E>

class DBGraph {
public:
  static_assert(std::is_base_of<Attribute, T>::value,
                "The base of DBGraph does not derive from attribute");
  static_assert(std::is_base_of<Attribute, E>::value,
                "The base of DBGraph does not derive from attribute");
  std::unordered_map<std::string, NodeAttribute<T, E>> nodes;
  DBGraph<T,E>( std::vector<NodeAttribute<T, E>>);
  std::string getGRAMstring();
  std::vector<NodeAttribute<T, E>*> getNodesWithEdgeLabel(int startIndex,
                                                         std::string label);
};
