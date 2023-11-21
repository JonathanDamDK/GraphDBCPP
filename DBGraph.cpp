#include "DBGraph.h"

std::string DBGraph::getGRAMString() {

  std::string output = "";
  for (unsigned int i = 0; i < nodes.size(); i++) {
    DBNode node = nodes[i];
    output +=  "(" + node.getValue() + "),";
  }

  for (unsigned int i = 0; i < Connections.size(); i++) {
    std::vector<std::string> currNodesEdges = Connections[i];
    for (unsigned int j = 0; j < Connections.size(); j++) {
      if (currNodesEdges[j] != "") {
        // example string is (a)-[:Likes]-> (b)
        output += "(" + nodes[i].getValue() + ")-[:" + currNodesEdges[j] +
                  "]->(" + nodes[j].getValue() + ")";
      }
    }
  }
  return output;
}
DBGraph::DBGraph(std::vector<DBNode> nodes,
                 std::vector<std::vector<std::string>> links) {
  this->nodes = nodes;
  this->Connections = links;
}
