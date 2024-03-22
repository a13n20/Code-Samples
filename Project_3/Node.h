// Node.h
// Natalie Hoffmann

#ifndef NODE_H
#define NODE_H

#include <vector>
#include <memory>

class Node{
  public:
    int id;
    int vn;
    bool chargeStation; 
    int dist;
    int rc;
    std::vector<std::shared_ptr<Node>> path;
    int finished; 
    std::vector<std::pair<std::shared_ptr<Node>, int>> neighbors;
    
    Node(int, bool);
};

#endif
