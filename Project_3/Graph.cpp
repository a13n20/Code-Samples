//Graph.cpp
//Natalie Hoffmann

#include <iostream>
#include "Graph.h"
#include <queue>
#include <limits.h>

Graph::Graph(){
  nodes = {};
}

void Graph::updateValues(std::shared_ptr<Node> curr, std::shared_ptr<Node> neighbor, int distance, int max) {
  neighbor->dist = curr->dist + distance;
  neighbor->path = curr->path;
  neighbor->path.push_back(curr);
  neighbor->vn += 1;
  if (neighbor->chargeStation == true)
    neighbor->rc = max; 
  else
    neighbor->rc = curr->rc - distance;
}

int Graph::minDist(std::vector<std::shared_ptr<Node>> check) {
  int shortest = 0;
  for (int i=0; i<check.size(); ++i) {
    if (check[i]->dist < check[shortest]->dist)
      shortest = i;
  }
  return shortest;
}

void Graph::Dijkstra (int s, int charge, int max, int e) {
  int index = 0;
  for (int i=0; i<nodes.size(); ++i) {
    nodes[i]->dist = INT_MAX;
    nodes[i]->rc = 0;
    nodes[i]->vn = 0;
    nodes[i]->path.clear();
    if (nodes[i]->id == s) {
      index = i;
      nodes[i]->dist = 0;
      if (nodes[i]->chargeStation == true)
        nodes[i]->rc = max;
      else
        nodes[i]->rc = charge;
      nodes[i]->vn = 1;
    }
  }
  std::vector<std::shared_ptr<Node>> Q;
  Q.push_back(nodes[index]);
  while (Q.size() > 0) {
    int ind = minDist(Q);
    std::shared_ptr<Node> curr = Q[0 + ind];
    Q.erase(Q.begin()+ind);
    for (int i=0; i < curr->neighbors.size(); ++i) {
      if (curr->neighbors[i].first->dist > curr->dist + curr->neighbors[i].second && curr->neighbors[i].second <= curr->rc) {
        Q.push_back(curr->neighbors[i].first);  
        updateValues(curr, curr->neighbors[i].first, curr->neighbors[i].second, max);
      }
      else if (curr->neighbors[i].first->id != e && curr->neighbors[i].first->vn > 0 && (curr->neighbors[i].first->rc < curr->rc - curr->neighbors[i].second && curr->neighbors[i].second <= curr->rc)) {
        Q.push_back(curr->neighbors[i].first);
        updateValues(curr, curr->neighbors[i].first, curr->neighbors[i].second, max);
      }
    }
  }
}

