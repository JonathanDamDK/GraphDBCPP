#pragma once

#include <string>

class CipherParser {
public:
  void parse(std::string);
  int parseRelation(std::string, int *);
  int parseEntity(std::string, int *, char);
  int parseAttributes(std::string, int *);
};
