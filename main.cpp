#include "DBGraph.h"
#include "JsonAttribute.h"
#include "NodeAttribute.h"
#include "PersonAttribute.h"
#include "simdjson.h"
#include <iostream>
int main() {
  simdjson::dom::parser parser;
  simdjson::padded_string json =
      simdjson::padded_string::load("./DBFileFormats/graphA.json");

  std::vector<NodeAttribute<JsonAttribute, PersonAttribute>> nodeList;
  // parsing in the graph from JSON
  for (simdjson::dom::object node : parser.parse(json)) {
    NodeAttribute<JsonAttribute, PersonAttribute> currNode;
    currNode.mapJson(node);
    nodeList.push_back(currNode);
  }
  std::cout << "edge "
            << nodeList[nodeList[0].edges[0].to].edges[0].attributes.name
            << "\n";
  return 0;
}
