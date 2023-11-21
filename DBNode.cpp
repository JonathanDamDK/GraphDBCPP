#include "DBNode.h"
#include <string>
DBNode::DBNode(uint32_t index) { this->index = index; }
DBNode::DBNode(std::string value, uint32_t index) {
  this->value = value;
  this->index = index;
}
uint32_t DBNode::getIndex() { return index; }
std::string DBNode::getValue(){return value;}
