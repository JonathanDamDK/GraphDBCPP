#pragma once
#include <string>
#include <unordered_map>
struct CipherEntity {
  std::string identifier;
  std::vector<std::string> labels;
  std::unique_ptr<std::unordered_map<std::string, std::variant<int, float, std::string>>>
      attributes;
}; 

struct CipherEdge {
  std::string from;
  std::string to;
  std::string label;
  std::string identifier;
  std::unique_ptr<std::unordered_map<std::string, std::variant<int, float, std::string>>>
      attributes;
};
