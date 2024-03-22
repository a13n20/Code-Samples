//Project_3.cpp
//Natalie Hoffmann

#include <iostream>
#include <string>
#include "Node.h"
#include "Graph.h"

int main() {
  //create and take in initial values
  int node;
  int edges;
  int maxDist;
  int range;
  int start;
  int end;
  Graph locations;
  std::cin >> node >> edges >> maxDist >> range >> start >> end;
  //create and take in the information for each node and push nodes on graph
  int num;
  int station;
  for (int i=0; i<node; ++i) {
    std::cin >> num >> station;
    locations.nodes.push_back(std::shared_ptr<Node> (new Node(num, station)));
  }
  //create and take in the information for each edge and push edges on neighbors
  int fn;
  int sn;
  int distance;
  for (int i=0; i<edges; ++i) {
    std::cin >> fn >> sn >> distance;
    locations.nodes[fn]->neighbors.push_back(std::make_pair(std::shared_ptr<Node>(locations.nodes[sn]), distance));
    locations.nodes[sn]->neighbors.push_back(std::make_pair(std::shared_ptr<Node>(locations.nodes[fn]), distance));
  }
 
  locations.Dijkstra(start, range, maxDist, end);
  std::vector<std::shared_ptr<Node>> path = locations.nodes[end]->path;
  if (path.size() == 0)
    std::cout << "No suitable path from " << start << " to " << end << " exists" << std::endl;
  else {
    std::cout << "Verify Path: 1" << std::endl;
    std::cout << locations.nodes[end]->dist << ": " << start << " ";
    for (int i=1; i<path.size(); ++i) {
      if (path[i]->chargeStation == true)
        std::cout << path[i]->id << " ";
    }
    std::cout << end << " " <<  std::endl;
  }

 return 1;
}
