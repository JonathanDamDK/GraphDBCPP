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
  ;

  std::string input;
  /*
  // if the query should be written at runtime
  //
  std::cout << "Please write query: " << std::endl;
  std::getline(std::cin, input);
  */

  // example query for debug
  input = "(bob:User{age: 50})-[:Wrote{timeSpent : "
          "'abasdasdasd'}]->(book:Book{edition:2})";

  Cparser.parse(input);
  Cparser.executeQuery(&graph);
  std::string testResult;
  testResult.append("{\n\"nodes\" [");
  bool needsComma = false;
  for (auto &node : graph.nodes) {
    if (needsComma == false) {
      testResult.append(node.second.getJsonString());
      needsComma = true;
    } else {
      testResult.append("," + node.second.getJsonString());
    }
  }
  testResult.append("]\n }");
  std::cout << testResult;
return 0;
}
