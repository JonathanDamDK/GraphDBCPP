#include "DBGraph.h"
#include "NodeAttribute.h"
#include <string.h>
#include <vector>
template <class T, class E> std::string DBGraph<T, E>::getGRAMstring() {

  return "NOT IMPLEMENTED";
}

template <class T, class E>
DBGraph<T, E>::DBGraph(std::vector<NodeAttribute<T, E>> nodesIn) {
  for(auto node : nodesIn){
      nodes.emplace(node.uid, node);
  }
}
template <class T, class E>
std::vector<NodeAttribute<T, E> *>
DBGraph<T, E>::getNodesWithEdgeLabel(int startIndex, std::string label) {
   std::vector<NodeAttribute<T, E> *> result;
  /*
  for (auto edge : nodes[startIndex].edges) {
    if (edge.label.compare(label) == 0) {
      result.push_back(&(nodes[0]));
    }
  }*/
  return result;
}

template class DBGraph<JsonAttribute, JsonAttribute>;
