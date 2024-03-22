//Graph.cpp
//Natalie Hoffmann

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <memory>
#include "Node.h"

class Graph{
  public:
    std::vector<std::shared_ptr<Node>> nodes;
    Graph();
    void updateValues (std::shared_ptr<Node>, std::shared_ptr<Node>, int, int);
    int minDist(std::vector<std::shared_ptr<Node>>);
    void Dijkstra (int, int, int, int);
};

#endif
