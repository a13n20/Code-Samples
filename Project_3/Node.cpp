//Node.cpp
//Natalie Hoffmann 

#include "Node.h"
#include <limits.h>

Node::Node(int i, bool c){
  id = i;
  vn = 0;
  chargeStation = c;
  dist = INT_MAX;
  rc = 0;
  path.clear();
  neighbors = {};
}
