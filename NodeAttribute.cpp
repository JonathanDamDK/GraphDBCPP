#include "NodeAttribute.h"
#include "JsonAttribute.h"
#include "PersonAttribute.h"
#include "simdjson.h"
#include <string_view>
template <class T, class E> NodeAttribute<T, E>::NodeAttribute() {}

template <class T, class E>
void NodeAttribute<T, E>::mapJson(simdjson::dom::object obj) {
  // make absolute sure that T is a base of Attribute
  static_assert(std::is_base_of<Attribute, T>::value,
                "The base of NodeAttribute does not derive from attribute");
  // parse the value of the node
  try {
    textVal = obj["textVal"];
  } catch (simdjson::simdjson_error err) {
    std::cout << "\n Something went wrong while parsing textVal + " +
                     std::string(err.what()) + "\n";
  }
  // parse the labels
  try {
    labels = std::vector<std::string>();
    simdjson::dom::array arr = obj["labels"].get_array();
    for (auto elem : arr) {
      std::string_view rawstr = elem.get_string();
      labels.push_back(std::string(rawstr));
    }
  } catch (simdjson::simdjson_error) {
    std::cout << "Something went wrong while parsing labels";
  }
  // parse the edges
  try {
    for (auto elem : obj["edges"].get_array()) {
      Edge<E> edge;
      edge.mapJson(elem);
      edges.push_back(edge);
    }
  } catch (simdjson::simdjson_error) {
    std::cout << "Something went wrong while parsing edges \n";
  }

  try {
    attributes.mapJson(obj["attributes"]);
  } catch (simdjson::simdjson_error) {
    std::cout << "Something went wrong while parsing attributes \n";
  }
  return;
}
// This is a fancy hack to make sure compiler does not fail compilation when
// NodeAttribute<T> is instantiated
template class NodeAttribute<PersonAttribute, JsonAttribute>;
template class NodeAttribute<JsonAttribute, JsonAttribute>;
