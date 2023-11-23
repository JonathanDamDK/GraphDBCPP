#pragma once

#include "NodeAttribute.h"
#include <_wctype.h>
#include <string>
#include <vector>
template <class T, class E>

class DBGraph {
public:
  static_assert(std::is_base_of<Attribute, T>::value,
                "The base of DBGraph does not derive from attribute");
  static_assert(std::is_base_of<Attribute, E>::value,
                "The base of DBGraph does not derive from attribute");
  std::vector<NodeAttribute<T, E>> nodes;
  std::string getGRAMstring();
};
