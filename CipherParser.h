#pragma once

#include "CipherEntity.h"
#include <string>
#include <unordered_map>
#include <vector>

class CipherParser {
public:
  void parse(std::string);
  CipherEdge parseRelation(std::string, int *);
  CipherEntity parseEntity(std::string, int *, char);
  std::unique_ptr<std::unordered_map<std::string, std::variant<int, float, std::string>>>
  parseAttributes(std::string, int *);
  CipherEdge *pendingEdge;
  std::vector<CipherEdge> edges;
  std::vector<CipherEntity> nodes;
  bool isPendingEdge;
  std::string previousIdentifier;
};
