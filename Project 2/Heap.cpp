//Heap.cpp
//Natalie Hoffmann

#include <iostream>
#include <algorithm>
#include "Heap.h"

Heap::Heap() { 
}

bool Heap::empty() {
  if (size == 0)
    return true;
  else
    return false;
}

int Heap::getSize() {
  return size;
}

//compares values of two planes based on priority first, then time of arrival, then the plane id
bool Heap::comparePlanes(Plane a, Plane b) {
  if (a.getPriority() == b.getPriority()) {
    if (a.getTime() == b.getTime()) {
      if (a.getId() < b.getId())
        return 0;
      else
        return 1;
    }
    else if (a.getTime() < b.getTime())
      return 0;
    else
      return 1; 
  }
  else if (a.getPriority() < b.getPriority())
    return 0;
  else
    return 1; 
}

void Heap::push(Plane p) { 
  //add plane to heap
  planes.push_back(p);
  size++;
  int i = size-1;
  //heapify upward
  if (size > 1) {
    while (i>0 && comparePlanes(planes[i], planes[floor((i-1)/2)]) == 0) {
      std::swap(planes[i], planes[floor((i-1)/2)]);
      i = floor((i-1)/2);
    }
  }
}

void Heap::heapsort(std::vector<Plane> p) {
  constructMinHeap(p);
}

//mobilize heapify
void Heap::constructMinHeap(std::vector<Plane> p) {
  for (int i=floor((p.size()-2)/2); i>-1; --i)
    minHeapify(p, i);
}

//ensures for true heap by comparing children as well as parent
void Heap::minHeapify(std::vector<Plane> &p, int i) {
  int l = 2*i+1; //left child
  int r = 2*i+2; //right child
  int m = i; //copy index
  if (l < size && comparePlanes(p[l], p[i]) == 0)
    m = l;
  if (r < size && comparePlanes(p[r], p[m]) == 0)
    m = r;
  if (m != i) {
    std::swap(p[i], p[m]);
    minHeapify(p, m);
  }
}

Plane Heap::pop() {
  Plane value = peek();
  //only heapify if theres more than 1 value
  if (size > 1) {
    planes[0] = planes[size-1];
    planes.pop_back();
    size--;
    int i = size-1;
    minHeapify(planes, 0);
  }
  //just pop value if only 1
  else {
    planes.pop_back();
    size--;
  } 
  return value;
}

Plane Heap::peek() {
  return planes[0];
}

void Heap::print() {
  for (int i=0; i<size; ++i)
    planes[i].print();
}
