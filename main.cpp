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
  std::cout << "edge to: " << graph.nodes.find("superid")->second.textVal;
  CipherParser Cparser;
  Cparser.parse("(bob:User{age: 50})-[:Wrote{timeSpent : "
                "'abasdasdasd'}]->(book:Book{edition:2})");
  int debug = 0;
  Cparser.executeQuery(&graph);

  std::cout << "edge to: "
            << graph.nodes.find("book")->second.textVal;
  return 0;
}
