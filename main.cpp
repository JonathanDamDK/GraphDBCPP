#include <iostream>

#include "DBGraph.h"
#include "DBNode.h"
int main() {
  std::vector<DBNode> nodes;
  nodes.push_back(DBNode(std::string("a"), 0));
  nodes.push_back(DBNode(std::string("b"), 1));
  nodes.push_back(DBNode(std::string("c"), 2));
  nodes.push_back(DBNode(std::string("d"), 3));
  std::vector<relation> edges;
  edges.push_back(relation{0, 1, std::string("likes")});
  edges.push_back(relation{1, 2, std::string("hates")});
  edges.push_back(relation{2, 3, std::string("ignores")});
  edges.push_back(relation{3, 1, std::string("adores")});
  edges.push_back(relation{3, 0, std::string("likes")});
  DBGraph graph = DBGraph(nodes, edges);
  std::cout << graph.getGRAMString() << "\n";
}
