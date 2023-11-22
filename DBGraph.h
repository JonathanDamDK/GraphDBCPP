#pragma once

#include "DBNode.h"
#include <_wctype.h>
#include <string>
#include <vector>

struct relation {
  uint32_t node1;
  uint32_t node2;

  std::string value;
};


class DBGraph {
public:
  //@TODO write parser of to help with GRAM.
  std::string getGRAMString();
  DBGraph(std::vector<DBNode>, std::vector<std::vector<std::string>>);
  DBGraph(std::vector<DBNode>, std::vector<relation>);

private:
  std::vector<DBNode> nodes;
  // 2d array of strings
  std::vector<std::vector<std::string>> Connections;
};
