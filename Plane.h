//Plane.h
//Natalie Hoffmann

#ifndef PLANE_H
#define PLANE_H

#include <string>

class Plane{
  public:
    Plane(int t, int i, std::string s, int p); //constructor with input values
    int getTime(); //get time value
    int getId(); //get id value
    bool getStatus(); //get status value
    int getPriority(); //get priority value
    void print();
  private:
    int time; //time plane enters simulation
    int id; //plane id
    bool status; //0-departing/1-arriving
    int priority; //priority in heap
};

#endif
