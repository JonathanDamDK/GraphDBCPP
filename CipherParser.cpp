#include "CipherParser.h"
#include "CipherEntity.h"
#include "DBGraph.h"
#include "Edge.h"
#include "JsonAttribute.h"
#include "NodeAttribute.h"
#include "simdjson.h"
#include <ctype.h>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>

simdjson::dom::object CipherParser::getJsonFromMapFreeMap(
    std::unique_ptr<
        std::unordered_map<std::string, std::variant<int, float, std::string>>>
        map) {
  simdjson::dom::object result;
  // super slow bad solution below
  std::string JSON;

  JSON.append("{");
  int count = 0;
  for (auto &elem : *map) {
    JSON.append("\"");
    JSON.append(elem.first);
    JSON.append("\"");
    JSON.append(":");
    try {
      int res = std::get<int>(elem.second);
      JSON.append(std::to_string(res));
    } catch (std::bad_variant_access) {
      try {
        float res = std::get<float>(elem.second);
        JSON.append(std::to_string(res));

      } catch (std::bad_variant_access) {
        std::string res = std::get<std::string>(elem.second);
        JSON.append(res);
      }
    }
    count++;
    if (count < map->size()) {
      JSON.append(",");
    }
  }
  JSON.append("}");
  // use class attached json parser instance to avoid nasty memory errors. As
  // soon as the parser is deleted so is all its dom::objects, might be fixable.
  result = jsonParser.parse(JSON);
  return result;
}
std::string parseAttributeIdentifier(std::string string, int *index);
std::variant<int, float, std::string> parseAttributeValue(std::string string,
                                                          int *index);

void CipherParser::parse(std::string string) {
  int i = 0;
  while (i < string.size()) {
    switch (string[i]) {
    case '(': {
      i += 1; // consume '('
      auto entity = parseEntity(string, &i, ')');
      auto debug = string[i];
      if (isPendingEdge) {
        pendingEdge->to = entity.identifier;
        edges.push_back(std::move(*pendingEdge));
        isPendingEdge = false;
      }
      previousIdentifier = entity.identifier;
      nodes.push_back(std::move(entity));
      break;
    }
    case '-': {
      i += 1; // Consume '-'
      auto relation = parseRelation(string, &i);
      relation.from = previousIdentifier;
      isPendingEdge = true;
      pendingEdge = new CipherEdge;
      pendingEdge->identifier = relation.identifier;
      pendingEdge->label = relation.label;
      pendingEdge->attributes = std::move(relation.attributes);
      pendingEdge->from = previousIdentifier;
      break;
    }
    default:
      i += 1;
      break;
    }
  }
}
CipherEdge CipherParser::parseRelation(std::string string, int *index) {

  CipherEdge result;
  CipherEntity entity;
  char current = string[*index];
  std::unordered_map<std::string, std::variant<int, float, std::string>>
      attributes;
  while (current != '(') {
    switch (current) {
    case '[':
      *index += 1;
      entity = parseEntity(string, index, ']');
      break;
    case '-':
      if (*index + 1 >= string.size()) {
        std::cout << "reached end of input prematurely";
        return result;
      } else if (string[*index + 1] != '>' && string[*index + 1] != '(') {
        std::cout << "syntax error expected '>' or ')' \n";
        return result; //@TODO throw errors in the future
      }
      *index += 1;
      break;
    case '>':
      if (string[*index - 1] != '-') {
        std::cout << "> must always be after - symbol";
        return result;
      }
      *index += 1;
      break;
    default:
      std::cout << "cant parse: " << current << "\n";
      *index += 1;
      break;
    }
    current = string[*index];
  }
  result.label = entity.labels[0];
  result.identifier = entity.identifier;
  result.attributes = std::move(entity.attributes);
  result.hasAttributes = entity.hasAttributes;
  return result;
}

CipherEntity CipherParser::parseEntity(std::string string, int *index,
                                       char delimeter) {
  CipherEntity result;
  std::string identifier;
  std::vector<std::string> labels;
  std::unique_ptr<
      std::unordered_map<std::string, std::variant<int, float, std::string>>>
      attributes;
  int labelIndex = -1; // -1 will correspond to scanning the identifier first,
                       // and then label[0] label[1] etc.
  char current = string[*index];
  while (current != delimeter) {
    if (*index + 1 >= string.size()) {
      std::cout << "Syntax error missing closing ]";
      //@Todo error handling
      *index += 1;
      return result;
    }
    switch (current) {
    case '{':
      *index += 1;
      attributes = parseAttributes(string, index);
      result.hasAttributes = true;

      break;
    case ':':
      labelIndex += 1;
      labels.push_back("");
      break;
    default:
      if (isalpha(current) == 1) {
        if (labelIndex == -1) {
          identifier.push_back(current);
        } else {
          labels[labelIndex].push_back(current);
        }
      } else {
        std::cout << "currently no support for none alphebetical identifiers:  "
                  << current << "\n";
      }
    }
    *index = *index + 1;
    current = string[*index];
  }

  result.labels = labels;
  result.attributes = std::move(attributes);
  result.identifier = identifier;
  // consume the close operator, this if statement SHOULD always be true but it
  // is a safeguard for now, can possibly be removed.
  if (current == delimeter) {
    *index += 1;
  }
  return result;
}
std::unique_ptr<
    std::unordered_map<std::string, std::variant<int, float, std::string>>>
CipherParser::parseAttributes(std::string string, int *index) {
  char current = string[*index];
  if (current == '{') {
    *index += 1;
    current = string[*index];
  }
  std::string jsonString;

  // instantiate map pointer on the heap
  auto map = std::make_unique<
      std::unordered_map<std::string, std::variant<int, float, std::string>>>();
  while (current != '}') {
    if (current == '\n' || current == ',') {
      *index += 1;
    }
    std::string identifier = parseAttributeIdentifier(string, index);
    if (string[*index] == ':') {
      *index += 1; // consume ':'
    }
    auto value = parseAttributeValue(string, index);

    map->insert_or_assign(identifier, value);
    current = string[*index];
  }
  return map;
}
std::variant<int, float, std::string> parseAttributeValue(std::string string,
                                                          int *index) {

  std::string rawValue;
  std::variant<int, float, std::string> result;
  bool isFloat = false;
  char current = string[*index];
  if (current == ':') {
    std::cout << "syntax error multiple ':' in attribute definition";
    return result;
  }
  while (current == ' ') { // ignore whitespace
    *index += 1;
    current = string[*index];
  }
  // parse strings
  if (current == '\'') {
    *index += 1; // consume '
    current = string[*index];
    while (current != '\'') {
      if (current == '}' || *index + 1 >= string.size()) {
        std::cout << "Syntax error string is not closed";
      }
      rawValue.push_back(current);
      *index += 1;
      current = string[*index];
    }
    // consume  ' character
    *index += 1;
    // return string
    result = rawValue;
    return result;
  }

  // parse non strings
  while (current != ',' && current != '}') {
    rawValue.push_back(current);
    *index += 1;
    current = string[*index];
    if (current == '.') {
      isFloat = true;
    }
  }
  try {
    if (isFloat) {
      float value = std::stof(rawValue);
      result = value;
    } else {
      int value = std::stoi(rawValue);
      result = value;
    }

  } catch (std::exception) {
    std::cout << "error parsing number"
              << "\n";
  }

  return result;
}

std::string parseAttributeIdentifier(std::string string, int *index) {
  std::string result;
  char current = string[*index];
  while (current != ':') {
    if (*index >= string.length()) {
      std::cout << "Missing : after variable declaration in attribute"
                << "\n";
    }
    if (current != ' ') {

      result.push_back(current);
    }
    *index = *index + 1;
    current = string[*index];
  }
  return result;
}
void CipherParser::executeQuery(DBGraph<JsonAttribute, JsonAttribute> *graph) {
  executeCreate(graph);
}

void CipherParser::executeCreate(DBGraph<JsonAttribute, JsonAttribute> *graph) {
  // convert it to NodeAttribute instead
  for (CipherEntity &node : nodes) {
    auto resultNode = NodeAttribute<JsonAttribute, JsonAttribute>();
    if (node.hasAttributes == true) {
      resultNode.setHasAttributesTrue();
    }
    resultNode.uid = node.identifier;
    resultNode.labels = std::move(node.labels);
    resultNode.textVal = node.identifier;
    resultNode.attributes = JsonAttribute();
    simdjson::dom::object result =
        getJsonFromMapFreeMap(std::move(node.attributes));
    resultNode.attributes.mapJson(result);
    graph->nodes.emplace(node.identifier, std::move(resultNode));
  }
  // pretty bad
  for (auto &edge : edges) {
    auto node = &(graph->nodes.find(edge.from)->second);
    Edge<JsonAttribute> resultEdge;
    resultEdge.to = edge.to;
    resultEdge.label = edge.label;
    node->edges.push_back(resultEdge);
  }

  bool needsComma = false;
  std::string jsonString;
  jsonString.push_back('[');
  for (auto &node : graph->nodes) {
    if (needsComma == false) {
      jsonString.append(node.second.getJsonString());
      needsComma = true;
    } else {
      jsonString.append("," + node.second.getJsonString());
    }
  }
  jsonString.append("\n]");
  std::remove("./DBFileFormats/dbgraph.json");
  if (!std::ifstream{"file1.txt"}) // uses operator! of temporary stream object
  {
    std::perror("Error opening deleted file");
  }
  std::ofstream fileStream = std::ofstream("./DBFileFormats/dbgraph.json");
  bool ok = static_cast<bool>(fileStream); // create file
  if (!ok) {
    std::perror("Error creating file");
  }
  else{
    fileStream << jsonString;
    fileStream.close();
  }
}
