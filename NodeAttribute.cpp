#include "NodeAttribute.h"
#include "PersonAttribute.h"
#include "simdjson.h"
#include <string_view>

template <class T> NodeAttribute<T>::NodeAttribute() {}

template <class T> void NodeAttribute<T>::mapJson(simdjson::dom::object obj) {
  // make absolute sure that T is a base of Attribute
  static_assert(std::is_base_of<Attribute, T>::value,
                "The base of NodeAttribute does not derive from attribute");
  try {
    textVal = obj["textVal"];
  } catch (simdjson::simdjson_error err) {
    std::cout << "\n Something went wrong while parsing textVal + " +
                     std::string(err.what()) + "\n";
  }
  try {
    labels = std::vector<std::string>();
    simdjson::dom::array arr = obj["labels"].get_array();
    for (auto elem : arr) {
      std::string_view rawstr = elem.get_string();

      std::cout << std::string(rawstr) + "\n";
      labels.push_back(std::string(rawstr));
    }
  } catch (simdjson::simdjson_error) {
    std::cout << "Something went wrong while parsing labels";
  }
  try {
    further_attribute.mapJson(obj["attributes"]);
  } catch (simdjson::simdjson_error) {
    std::cout << "Something went wrong while parsing attributes \n";
  }
  return;
}

template class NodeAttribute<PersonAttribute>;
