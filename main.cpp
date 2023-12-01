#include "CipherParser.h"
#include "DBGraph.h"
#include "JsonAttribute.h"
#include "NodeAttribute.h"
#include "PersonAttribute.h"
#include "simdjson.h"
#include <iostream>

int main() {
  simdjson::dom::parser parser;
  /* simdjson::padded_string json =
      simdjson::padded_string::load("./DBFileFormats/graphA.json"); */
  simdjson::padded_string json;
  try {
    json = simdjson::padded_string::load("./DBFileFormats/dbgraph.json");
  } catch (simdjson::simdjson_error &e) {
    std::cout << "catch";
    json = simdjson::padded_string(std::string_view("[]"));
  }
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
  ;

  std::string input = "";

  // if the query should be written at runtime
 /* while (input.compare("quit") != 0) {

    //std::cout << "Please write query: " << std::endl;
    //std::getline(std::cin, input);
    //Cparser.parse(input);
    Cparser.executeQuery(&graph);
  }*/
  // example query for debug
  input = "Match(a:User{name : 'Jonathan'})";
  Cparser.parse(input);
  Cparser.executeQuery(&graph);

  return 0;
}
