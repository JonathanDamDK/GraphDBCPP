#include "DBGraph.h"

std::string DBGraph::getGRAMString() {

  std::string output = "";
  for (unsigned int i = 0; i < nodes.size(); i++) {
    DBNode node = nodes[i];
    output += "(" + node.getValue() + "),";
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

DBGraph::DBGraph(std::vector<DBNode> nodes, std::vector<relation> relations) {
  this->nodes = nodes;
  // construct connections table
  std::vector<std::vector<std::string>> edges;
  for(int i = 0; i < nodes.size(); i++) {
    std::vector<std::string> nodeEdges;
    for (int j = 0; j < nodes.size(); j++) {
      nodeEdges.push_back(std::string(""));
    }
    edges.push_back(nodeEdges);
  }
  for (int i = 0; i < relations.size(); i++) {
    relation currentRelation = relations[i];
    edges[currentRelation.node1][currentRelation.node2] += currentRelation.value;
  }
  this->Connections = edges;
}

DBGraph::DBGraph(std::vector<DBNode> nodes,
                 std::vector<std::vector<std::string>> links) {
  this->nodes = nodes;
  this->Connections = links;
}
