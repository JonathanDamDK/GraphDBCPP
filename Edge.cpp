#include "Edge.h"
#include "PersonAttribute.h"
#include <string_view>
template <class T> void Edge<T>::mapJson(simdjson::dom::object obj) {
  // try to parse in the "to" property from an edge
  try {
    to = std::string(std::string_view(obj["to"].get_string()));
  } catch (simdjson::simdjson_error err) {
    std::cout << "\n Something went wrong while parsing 'to' " +
                     std::string(err.what()) + "\n";
  }
  // parsing the label
  try {
    label = std::string(std::string_view(obj["label"].get_string()));
  } catch (simdjson::simdjson_error err) {
    std::cout << "\n Something went wrong while parsing label edge: " +
                     std::string(err.what()) + "\n";
  }
  // parsing the Attributes
  try {
    attributes.mapJson(obj["attributes"]);
  } catch (simdjson::simdjson_error err) {
    std::cout << "\n Something went wrong while parsing edge attributes: " +
                     std::string(err.what()) + "\n";
  }
  return;
}

template class Edge<PersonAttribute>;
template class Edge<JsonAttribute>;
