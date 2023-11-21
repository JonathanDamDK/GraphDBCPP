#pragma once

#include "DBNode.h"
#include <string>
#include <vector>
class DBGraph {
public:
  std::string getGRAMString();
  DBGraph(std::vector<DBNode>, std::vector<std::vector<std::string>>);

private:
  std::vector<DBNode> nodes;
  // 2d array of strings
  std::vector<std::vector<std::string>> Connections;
};
