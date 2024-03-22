//Heap.h
//Natalie Hoffmann

#ifndef HEAP_H
#define HEAP_H

#include <string>
#include <vector>
#include "Plane.h"

class Heap {
  public:
    Heap(); //constructor
    bool empty(); //check if empty
    int getSize(); //return size
    bool comparePlanes(Plane a, Plane b); //compare values of two planes 0-a, 1-b
    void push(Plane p); //adds object plane to heap
    void heapsort(std::vector<Plane> p); //sort vector
    void constructMinHeap(std::vector<Plane> p); //create max heap based on priority
    void minHeapify(std::vector<Plane> &p, int i); //sort values
    Plane pop(); //removes plane object from heap
    Plane peek(); //looks at next object in heap without removing it
    void print();
  private:
    std::vector<Plane> planes;
    int size; //number of elements in heap
};

#endif
