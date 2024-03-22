//AirportDriver.cpp
//Natalie Hoffmann

#include <iostream>
#include "Heap.h"
#include "Plane.h"

using namespace std;

//make both heaps global for the sorting function and main function
unique_ptr<Heap> RunwayA(new Heap());
unique_ptr<Heap> RunwayB(new Heap());

//sorts planes in respective heaps based on status
void sort(vector<Plane> list) {
  for (int i=0; i<list.size(); ++i) {
    if (list[i].getStatus() == 0)
      RunwayA->push(list[i]);
    else
      RunwayB->push(list[i]);
  }  
}

//prints the list of planes entering the simulation
void printList(vector<Plane> list) {
  for (int i=0; i<list.size(); ++i) { 
    cout << "\t\t";
    list[i].print();
  }
}

int main() {
  //declare variables
  int numPlanes = 0;
  int time = 0;
  int id = 0;
  string status = "";
  int priority = 0;
  vector<Plane> list;
  //cin number of planes in simulation and add them all to a vector based on the number
  cin >> numPlanes;
  for (int i=0; i<numPlanes; ++i) {
    cin >> time >> id >> status >> priority;
    Plane p(time, id, status, priority);
    list.push_back(p);
  } 
  //create vector for planes entering simulation based on the time step
  vector<Plane> entering;
  int ts = 0; //Time Step
  //executes as long as there are still planes in either vector or heap
  while (!list.empty() || !entering.empty() || !RunwayA->empty() || !RunwayB->empty()) {
    //only add planes from list to entering if time matches ts
    for (int i=0; i<list.size(); list.erase(list.begin())) {
      if (list[i].getTime() == ts)
        entering.push_back(list[i]); 
      else
        break;
    }
    //only executes if there are planes entering the simulation or are in the heaps
    if (!entering.empty() || !RunwayA->empty() || !RunwayB->empty()) {
      cout << "Time step " << ts << endl;
      cout << "\tEntering simulation" << endl; 
      printList(entering);
      sort(entering);
      entering.clear(); 
      if (!RunwayA->empty() && !RunwayB->empty()) {
        cout << "\tRunway A" << endl;
        cout << "\t\t"; 
        RunwayA->pop().print();
        cout << "\tRunway B" << endl;
        cout << "\t\t";
        RunwayB->pop().print();
      }
      else if (RunwayA->empty() && !RunwayB->empty()) {
        //ensure Runway B priority for the RunwayB heap
        Plane p = RunwayB->pop();
        cout << "\tRunway A" << endl;
        if (!RunwayB->empty()) {
          cout << "\t\t";
          RunwayB->pop().print();
        }
        cout << "\tRunway B" << endl;
        cout << "\t\t";
        p.print();
      }
      else if (!RunwayA->empty() && RunwayB->empty()) {
        cout << "\tRunway A" << endl;
        cout << "\t\t"; 
        RunwayA->pop().print();
        cout << "\tRunway B" << endl;
        if (!RunwayA->empty()) {
          cout << "\t\t";
          RunwayA->pop().print();
        }
      }
    }
    ts++;
  }
  return 0;
}
