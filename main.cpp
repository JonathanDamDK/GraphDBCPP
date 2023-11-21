#include <iostream>

#include "DBGraph.h"
#include "DBNode.h"
int main() {
  std::vector<DBNode> nodes;
  nodes.push_back(DBNode(std::string("a"), 0));
  nodes.push_back(DBNode(std::string("b"), 1));
  nodes.push_back(DBNode(std::string("c"), 2));
  nodes.push_back(DBNode(std::string("d"),3));
  std::vector<std::vector<std::string>> edges;
  std::vector<std::string> edgesA;
  edgesA.push_back(std::string(""));      // A
  edgesA.push_back(std::string("hates")); // B
  edgesA.push_back(std::string(""));      // C
  edgesA.push_back(std::string(""));      //D
  edges.push_back(edgesA);

  // b edges
  std::vector<std::string> edgesB;
  edgesB.push_back(std::string(""));      // A
  edgesB.push_back(std::string(""));      // B
  edgesB.push_back(std::string("likes")); // C
  edgesB.push_back(std::string(""));      // D
  edges.push_back(edgesB);
  // c edges
  std::vector<std::string> edgesC;
  edgesC.push_back(std::string("likes")); // A
  edgesC.push_back(std::string(""));      // B
  edgesC.push_back(std::string(""));      // C
  edgesC.push_back(std::string("likes"));      // D
  edges.push_back(edgesC);


  std::vector<std::string> edgesD;
  edgesD.push_back(std::string("likes")); // A
  edgesD.push_back(std::string(""));      // B
  edgesD.push_back(std::string("hates"));      // C
  edgesD.push_back(std::string(""));      // D
  edges.push_back(edgesC);
  DBGraph graph = DBGraph(nodes, edges);

  std::cout << graph.getGRAMString()
            << "\n";
}
