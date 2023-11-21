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
  //@TODO this value needs to be arbitrary, any struct will do, even with nested structs
  std::string value;
};
