#include "CipherParser.h"
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

  std::vector<NodeAttribute<JsonAttribute, JsonAttribute>> nodeList;
  // parsing in the graph from JSON
  for (simdjson::dom::object node : parser.parse(json)) {
    NodeAttribute<JsonAttribute, JsonAttribute> currNode;
    currNode.mapJson(node);
    nodeList.push_back(currNode);
  }
  DBGraph<JsonAttribute, JsonAttribute> graph =
      DBGraph<JsonAttribute, JsonAttribute>(nodeList);
  // auto result = graph.getNodesWithEdgeLabel(0, "Likes");

  CipherParser Cparser;
  Cparser.parse("(bob:Person:User)-[:Likes]->(alice:User)");
  return 0;
}
