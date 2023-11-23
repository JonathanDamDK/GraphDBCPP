#include "CipherParser.h"
#include "CipherEntity.h"
#include "simdjson.h"
#include <ctype.h>
#include <exception>
#include <iostream>
#include <string>
#include <unordered_map>
#include <variant>

std::string parseAttributeIdentifier(std::string string, int *index);
std::variant<int, float, std::string> parseAttributeValue(std::string string,
                                                          int *index);

void CipherParser::parse(std::string string) {
  int i = 0;
  while (i < string.size()) {
    switch (string[i]) {
    case '(': {
      i += 1;
      auto entity = parseEntity(string, &i, ')');
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
      i += 1;
      auto relation = parseRelation(string, &i);
      relation.from = previousIdentifier;
      isPendingEdge = true;
      pendingEdge = new CipherEdge;
      pendingEdge->identifier = relation.identifier;
      pendingEdge->label = relation.label[0];
      pendingEdge->attributes = std::move(relation.attributes);
      pendingEdge->from  = previousIdentifier;
      break;
    }
    default:
      i += 1;
      std::cout << "main: " << string[i] << "\n";
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
      *index += 1; // to ignore the ] bracket
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
    }
    current = string[*index];
  }
  result.label = entity.labels[0];
  result.identifier = entity.identifier;
  result.attributes = std::move(entity.attributes);
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

  // debug
  std::cout << "identifier: " << identifier << "\n";
  std::cout << "labels : [";
  for (auto label : labels) {
    std::cout << label << ",";
  }
  std::cout << "]\n";
  result.labels = labels;
  result.attributes = std::move(attributes);
  result.identifier = identifier;
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
  while (current == ' ' || current == ':') {
    *index += 1;
    current = string[*index];
  }
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
    result = rawValue;
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
