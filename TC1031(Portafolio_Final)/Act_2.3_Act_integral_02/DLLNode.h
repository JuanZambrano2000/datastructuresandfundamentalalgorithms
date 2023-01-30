#ifndef _DLLNODE_H_
#define _DLLNODE_H_

#include "Registro.h"
class DLLNode {
public:
  Registro data;
  DLLNode *next;
  DLLNode *prev;
  DLLNode();
  DLLNode(Registro value);
};

DLLNode::DLLNode() : data{}, next{nullptr}, prev{nullptr} {}


DLLNode::DLLNode(Registro value) : data{value}, next{nullptr}, prev{nullptr} {}

#endif // _DLLNODE_H_
