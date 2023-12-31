#pragma once

#include "CipherEntity.h"
#pragma once
#include "DBGraph.h"
#include "JsonAttribute.h"
#include "NodeAttribute.h"
#include "simdjson.h"
#include <string>
#include <unordered_map>
#include <vector>
class CipherParser {
public:
  // the simdjson::dom::object is only alive for as long as the parser it is
  // attached to is, thus we must have a parser that is alive for the duration
  // of the CipherParser classes lifetime
  simdjson::dom::parser jsonParser;

  simdjson::dom::object getJsonFromMapFreeMap(
      std::unique_ptr<std::unordered_map<std::string,
                                         std::variant<int, float, std::string>>>
          map);
  void parse(std::string);
  void parseCipherCommand(std::string, int *);
  CipherEdge parseRelation(std::string, int *);
  void executeCreate(DBGraph<JsonAttribute, JsonAttribute> *);
  NodeAttribute<JsonAttribute, JsonAttribute>
      executeMatch(DBGraph<JsonAttribute, JsonAttribute>);
  CipherEntity parseEntity(std::string, int *, char);
  std::unique_ptr<
      std::unordered_map<std::string, std::variant<int, float, std::string>>>
  parseAttributes(std::string, int *);
  void executeQuery(DBGraph<JsonAttribute, JsonAttribute> *);
  CipherEdge *pendingEdge;
  std::vector<CipherEdge> edges;
  std::vector<CipherEntity> nodes;
  bool isPendingEdge;
  std::string previousIdentifier;
  std::string command;
};
