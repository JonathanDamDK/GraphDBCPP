#pragma once

#include <_types/_uint32_t.h>
#include <stdint.h>
#include <string>

class DBNode {
public:
  DBNode(uint32_t index);
  DBNode(std::string, uint32_t index);
  uint32_t getIndex();
  std::string getValue();

private:
  uint32_t index;
  std::string value;
};