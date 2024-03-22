//Plane.cpp
//Natalie Hoffmann

#include <iostream>
#include "Plane.h"

Plane::Plane(int t, int i, std::string s, int p) {
  //set all elements to input values
  time = t;
  id = i;
  if (s == "departing")
    status = 0;
  else 
    status = 1;
  priority = p;
}

int Plane::getTime() {
  return time; //return time value
}

int Plane::getId() {
  return id; //return id value
}

bool Plane::getStatus() {
  return status; //return either 0-arriving or 1-departing
}

int Plane::getPriority() {
  return priority; //return priority value
}

void Plane::print() {
  std::cout << time << " " <<  id;
  if (status == 1)
    std::cout << " arriving ";
  else 
    std::cout << " departing ";
  std::cout << priority << std::endl;
}
