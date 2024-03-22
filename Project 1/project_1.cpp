//Project 1
//CSCI 311
//Author: Natalie Hoffmann

#include<iostream>
#include<vector>
#include<time.h>
#include<math.h>
#include<chrono>
#include<string>
#include<fstream>
using namespace std;

//temporary print function
void print(vector<int> v) {
  for(int i=0; i<v.size(); ++i)
    cout << v[i] << " ";
  cout << endl;
}

//Generates a vector with random ints from a given range
vector<int> randomVector(int size, int low, int high) {
  vector<int> v(size, 0);
  for (int i=0; i<size; ++i) {
    v[i] = rand() % (high-low+1) + low;
  }
  return v;
}

//Generates a vector for best case for sorting functions except quicksort
vector<int> sortedVector(int size) {
  vector<int> v;
  for (int i=0; i<size; ++i)
    v.push_back(i);
  return v;
}

//Generates a vector for worst case for sorting functions except quicksort
vector<int> reverseSortedVector(int size) {
  vector<int> v;
  for (int i=size; i>0; --i)
    v.push_back(i);
  return v;
}

//Calculates sample standard deviation of a vector
double sampleSD(const vector<double> v) {
  double mean = 0;
  for (int i=0; i<v.size(); ++i) {
    mean += v[i];
  }
  mean = mean/v.size();
  double sd=0;
  for (int i=0; i<v.size(); ++i) {
    sd += (v[i]-mean)*(v[i]-mean);
  }
  sd = sd/(v.size()-1);
  return sqrt(sd);
}

//Returns minimum in a vector
double minimumHelper(const vector<double> v, int start) {
  if (v.size()==start)
    return v[start];
  return min(v[start], minimumHelper(v, start+1));
}

double minimum(const vector<double> v) {
  return minimumHelper(v, 0);
}

//Returns maximum in a vector
double maximumHelper(const vector<double> v, int start) {
  if (v.size() == start)
    return v[start];
  return max(v[start], maximumHelper(v, start+1));
}

double maximum(const vector<double> v) {
  return maximumHelper(v, 0);
}

//IsSorted function
bool isSorted(vector<int> &v) {
  bool result = true; //begin with assumption of true
  for (int i=1; i<v.size(); ++i) {
    if (v[i-1] > v[i]) { //check if current element is less than previous element
      result = false; //return false if above is true
      break; //break for loop if above is true
    }
  }
  return result;
}

//Bubble sort function
vector<int> bubbleSort(vector<int> &v) {
  bool swapped = true; //include swapped bool for better runtime of best case scenario
  while (swapped) {
    swapped = false;
    for (int i=1; i<v.size(); ++i) {
      if (v[i-1] > v[i]) { //check if current element is less than previous element
        int temp = v[i-1];
        v[i-1] = v[i];
        v[i] = temp;
        swapped = true; //if above is true, then continue while loop
      }
    }
  }
  return v;
}

//Insertion sort function
vector<int> insertionSort(vector<int> &v) {
  int i = 1;
  while (i<v.size()) { //repeat loop for length of v
    int j = i;
    while (j>0 && v[j] < v[j-1]) { //repeat loop if j isn't 0 and the current element is less than the previous element
      int temp = v[j-1];
      v[j-1] = v[j];
      v[j] = temp;
      j = j-1; //decrement j until j reaches 0
    }
    i = i+1; //increment i so the sorted elements aren't gone through again
  }
  return v;
}

//Selection sort function
vector<int> selectionSort(vector<int> &v) {
  for (int i=0; i<v.size()-1; ++i) { //repeat loop for one less than length of v
    int uMin = i; //set uMin to first index and then move up one index for each loop iteration
    for (int j=i+1; j<v.size(); ++j) { 
      if (v[j] < v[uMin])  //check if current element is less than element at uMin
        uMin = j; //set uMin to index of smallest element if above is true  
    }
    //swap elements
    int temp = v[i];
    v[i] = v[uMin];
    v[uMin] = temp;  
  }
  return v;
}

//Quicksort function with piv into that changes depending on best or worst case (2 for best, 1 for everyhting else)
vector<int> quicksort(vector<int> &v, int piv) {
  if (v.size() <= 1) 
    return v; //check if sorted once recursion has occured for all vector elements 
  int pivot = v[(v.size()-1)/piv]; //set pivot to last element or middle element
  vector<int> A;
  vector<int> B;
  for (int e=1; e<v.size(); ++e) { //repeat loop for length of v
    if (v[e] <= pivot)
      A.push_back(v[e]); //put current element in smaller vector if smaller than pivot
    else
      B.push_back(v[e]); // put current element in larger vector if larger than pivot
  } 
  //recursively quicksort each separate vector
  vector<int> ASort = quicksort(A, piv);
  vector<int> BSort = quicksort(B, piv);
  //combine all vectors and pivot into one vector
  ASort.push_back(pivot);
  ASort.insert(ASort.end(), BSort.begin(), BSort.end()); 
  return ASort;
}

int main() {

  //*******Create function output*******\\

  srand(time(NULL));
  int bs=0, is=0, ss=0, qs=0;
  vector<double> btime;
  vector<double> itime;
  vector<double> stime;
  vector<double> qtime;

  for (int i=0; i<10; ++i) {
    //create vectors
    vector<int> v = randomVector(100, 0, 100);
    vector<int> bv = v;
    vector<int> iv = v;
    vector<int> sv = v;
    vector<int> qv = v;

    //define time varaibles
    chrono::high_resolution_clock::time_point bstart;
    chrono::high_resolution_clock::time_point bend;
    chrono::high_resolution_clock::time_point istart;
    chrono::high_resolution_clock::time_point iend;
    chrono::high_resolution_clock::time_point sstart;
    chrono::high_resolution_clock::time_point send;
    chrono::high_resolution_clock::time_point qstart;
    chrono::high_resolution_clock::time_point qend;

    //bubble sort
    bstart = chrono::high_resolution_clock::now();
    bubbleSort(bv);
    bend = chrono::high_resolution_clock::now();
    if (isSorted(bv))
      bs++;

    //insertion sort
    istart = chrono::high_resolution_clock::now();
    insertionSort(iv);
    iend = chrono::high_resolution_clock::now();
    if (isSorted(iv))
      is++;

    //selection sort
    sstart = chrono::high_resolution_clock::now();
    selectionSort(sv);
    send = chrono::high_resolution_clock::now();
    if (isSorted(sv))
      ss++;

    //quicksort
    qstart = chrono::high_resolution_clock::now();
    qv = quicksort(qv, 1);
    qend = chrono::high_resolution_clock::now(); 
    if (isSorted(qv))
      qs++;


    double belapsed = chrono::duration_cast<chrono::duration<double>>(bend-bstart).count();
    btime.push_back(belapsed);
    double ielapsed = chrono::duration_cast<chrono::duration<double>>(iend-istart).count();
    itime.push_back(ielapsed);
    double selapsed = chrono::duration_cast<chrono::duration<double>>(send-sstart).count();
    stime.push_back(selapsed);
    double qelapsed = chrono::duration_cast<chrono::duration<double>>(qend-qstart).count();
    qtime.push_back(qelapsed);
  }

  //produce output for sorts
  for (int i=0; i<4; ++i) {
    cout << "************************" << endl;
    switch (i) {
      case 0:
        cout << "Bubble sort ";
        break;
      case 1:
        cout << "Insertion sort ";
        break;
      case 2:
        cout << "Selection sort ";
        break;
      case 3:
        cout << "Quicksort ";
        break;
    }
    cout << "on 10 vectors of length 100" << endl;
    switch (i) {
      case 0:
        if (bs==10)
          cout << "Sorting successful" << endl;
        else
          cout << "Sorting unsuccessful" << endl;
        break;
      case 1:    
        if (is==10)
          cout << "Sorting successful" << endl;
        else
          cout << "Sorting unsuccessful" << endl;
        break;
      case 2:
        if (ss==10)
          cout << "Sorting successful" << endl;
        else
          cout << "Sorting unsuccessful" << endl;
        break;
      case 3:
        if (qs==10)
          cout << "Sorting successful" << endl;
        else
          cout << "Sorting unsuccessful" << endl;
        break;
    }
    switch (i) {
      case 0:
        cout << "Minimum: " << minimum(btime) << " sec; Standard deviation: " << sampleSD(btime) << " sec; Maximum: " << maximum(btime) << " sec" << endl;       
        break;
      case 1:
        cout << "Minimum: " << minimum(itime) << " sec; Standard deviation: " << sampleSD(itime) << " sec; Maximum: " << maximum(itime) << " sec" << endl;   
        break;
      case 2:
        cout << "Minimum: " << minimum(stime) << " sec; Standard deviation: " << sampleSD(stime) << " sec; Maximum: " << maximum(stime) << endl;
        break;
      case 3:
        cout << "Minimum: " << minimum(qtime) << " sec; Standard deviation: " << sampleSD(qtime) << " sec; Maximum: " << maximum(qtime) << endl;
        break;
    }
    cout << "************************" << endl;
  }

  //*******Create data to put in csv file*******\\

  //create csv file
  ofstream bestFile("best_case_times.csv");
  ofstream averageFile("average_case_times.csv");
  ofstream worstFile("worst_case_times.csv");

  for (int s=0; s<5; ++s) {
    //Determine size for each iteration
    int size=0;
    switch (s) {
      case 0:
        size = 10;
        break;
      case 1:
        size = 100;
        break;
      case 2:
        size = 1000;
        break;
      case 3:
        size = 5000;
        break;
      case 4:
        size = 10000;
        break;
    }
    for (int i=0; i<50; ++i) {
      //create runtime variables
      chrono::high_resolution_clock::time_point bstart;
      chrono::high_resolution_clock::time_point bend;
      chrono::high_resolution_clock::time_point istart;
      chrono::high_resolution_clock::time_point iend;
      chrono::high_resolution_clock::time_point sstart;
      chrono::high_resolution_clock::time_point send;
      chrono::high_resolution_clock::time_point qstart;
      chrono::high_resolution_clock::time_point qend;

      //best case
      //create vectors
      vector<int> bbv = sortedVector(size);
      vector<int> biv = sortedVector(size);
      vector<int> bsv = sortedVector(size);
      vector<int> bqv = sortedVector(size);

      //collect data
      bstart = chrono::high_resolution_clock::now();
      bubbleSort(bbv);
      bend = chrono::high_resolution_clock::now();  
      double bbelapsed = chrono::duration_cast<chrono::duration<double>>(bend-bstart).count();
      bestFile << "bubble," << size << "," << bbelapsed << endl;

      istart = chrono::high_resolution_clock::now();
      insertionSort(biv);
      iend = chrono::high_resolution_clock::now();
      double bielapsed = chrono::duration_cast<chrono::duration<double>>(iend-istart).count(); 
      bestFile << "insertion," << size << "," << bielapsed << endl;

      sstart = chrono::high_resolution_clock::now();
      selectionSort(bsv);
      send = chrono::high_resolution_clock::now();
      double bselapsed = chrono::duration_cast<chrono::duration<double>>(send-sstart).count(); 
      bestFile << "selection," << size << "," << bselapsed << endl;

      qstart = chrono::high_resolution_clock::now();
      bqv = quicksort(bqv, 2);
      qend = chrono::high_resolution_clock::now();
      double bqelapsed = chrono::duration_cast<chrono::duration<double>>(qend-qstart).count(); 
      bestFile << "quick," << size << "," << bqelapsed << endl;
     
      //average case
      //create vectors
      vector<int> rv = randomVector(size, 0, size);
      vector<int> abv = rv;
      vector<int> aiv = rv;
      vector<int> asv = rv;
      vector<int> aqv = rv;

      //collect data
      bstart = chrono::high_resolution_clock::now();
      bubbleSort(abv);
      bend = chrono::high_resolution_clock::now();  
      double abelapsed = chrono::duration_cast<chrono::duration<double>>(bend-bstart).count();
      averageFile << "bubble," << size << "," << abelapsed << endl;

      istart = chrono::high_resolution_clock::now();
      insertionSort(aiv);
      iend = chrono::high_resolution_clock::now();
      double aielapsed = chrono::duration_cast<chrono::duration<double>>(iend-istart).count(); 
      averageFile << "insertion," << size << "," << aielapsed << endl;

      sstart = chrono::high_resolution_clock::now();
      selectionSort(asv);
      send = chrono::high_resolution_clock::now();
      double aselapsed = chrono::duration_cast<chrono::duration<double>>(send-sstart).count(); 
      averageFile << "selection," << size << "," << aselapsed << endl;

      qstart = chrono::high_resolution_clock::now();
      aqv = quicksort(aqv, 1);
      qend = chrono::high_resolution_clock::now();
      double aqelapsed = chrono::duration_cast<chrono::duration<double>>(qend-qstart).count(); 
      averageFile << "quick," << size << "," << aqelapsed << endl;

      //worst case
      //create vectors
      vector<int> wbv = reverseSortedVector(size);
      vector<int> wiv = reverseSortedVector(size);
      vector<int> wsv = reverseSortedVector(size);
      vector<int> wqv = reverseSortedVector(size);

      //collect data
      bstart = chrono::high_resolution_clock::now();
      bubbleSort(wbv);
      bend = chrono::high_resolution_clock::now();  
      double wbelapsed = chrono::duration_cast<chrono::duration<double>>(bend-bstart).count();
      worstFile << "bubble," << size << "," << wbelapsed << endl;

      istart = chrono::high_resolution_clock::now();
      insertionSort(wiv);
      iend = chrono::high_resolution_clock::now();
      double wielapsed = chrono::duration_cast<chrono::duration<double>>(iend-istart).count(); 
      worstFile << "insertion," << size << "," << wielapsed << endl;

      sstart = chrono::high_resolution_clock::now();
      selectionSort(wsv);
      send = chrono::high_resolution_clock::now();
      double wselapsed = chrono::duration_cast<chrono::duration<double>>(send-sstart).count(); 
      worstFile << "selection," << size << "," << wselapsed << endl;

      qstart = chrono::high_resolution_clock::now();
      wqv = quicksort(wqv, 1);
      qend = chrono::high_resolution_clock::now();
      double wqelapsed = chrono::duration_cast<chrono::duration<double>>(qend-qstart).count(); 
      worstFile << "quick," << size << "," << wqelapsed << endl;
      
    }
  }
  //close files
  bestFile.close();
  averageFile.close();
  worstFile.close();

  return 0;
}
