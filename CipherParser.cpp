#include "CipherParser.h"
#include <ctype.h>
#include <iostream>
void CipherParser::parse(std::string string) {
  int i = 0;
  while(i < string.size()){
    switch (string[i]) {
    case '(':
      i += 1;
      parseEntity(string, &i, ')');
      break;
    case '-':
      i += 1;
      parseRelation(string, &i);
      break;
    default:
      i += 1;
      std::cout << "main: " << string[i] << "\n";
      break;
    }
  }
}
int CipherParser::parseRelation(std::string string, int *index) {

  std::string identifier;
  std::vector<std::string> labels;
  char current = string[*index];

  while (current != '(') {
    switch (current) {
    case '[':
      *index += 1;
      parseEntity(string, index, ']');
      *index += 1; // to ignore the ] bracket
      break;
    case '-':
      if (*index + 1 >= string.size()) {
        std::cout << "reached end of input prematurely";
        return -1;
      } else if (string[*index + 1] != '>' && string[*index + 1] != ')') {
        std::cout << "syntax error expected '>' or ')' \n";
        return -1;
      }
      *index += 1;
      break;
    case '>':
      if (string[*index - 1] != '-') {
        std::cout << "> must always be after - symbol";
        return -1;
      }
      *index += 1;
      break;
    default:
      std::cout << "cant parse: " << current << "\n";
    }
    current = string[*index];
  }
  return 0;
}

int CipherParser::parseEntity(std::string string, int *index, char delimeter) {
  std::string identifier;
  std::vector<std::string> labels;
  int labelIndex = -1; // -1 will correspond to scanning the identifier first,
                       // and then label[0] label[1] etc.
  char current = string[*index];
  while (current != delimeter) {
    if (*index + 1 >= string.size()) {
      std::cout << "Syntax error missing closing ]";
      //@Todo error handling
      *index += 1;
      return -1;
    }
    switch (current) {
    case '{':
      parseAttributes(string, index);
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
  return 0;
}
int CipherParser::parseAttributes(std::string string, int *index) { return 0; }
