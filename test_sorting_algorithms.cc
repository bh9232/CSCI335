// Homework 4
// Testing Sorting Algorithms
// Brian Hong

/**
 * Coded VerifyOrder function that verifies that a vector is ordered
 * Coded functions that generated a random vector and a random sorted vector
 */

#include "Sort.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
using namespace std;

// Computes duration given a start time and a stop time in nano seconds.
// Keep it in.
long long ComputeDuration(chrono::high_resolution_clock::time_point start_time, 
			  chrono::high_resolution_clock::time_point end_time) {
  return chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
}

// Verifies that a vector is sorted given a comparator.
// I.e. it applies less_than() for consecutive pair of elements and returns true
// iff less_than() is true for all pairs.
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable> &input, Comparator less_than) {
  // Add code
  for(unsigned int i = 0; i < input.size(); i++){
    if(!less_than(input[i], input[i-1])){
      //do nothing
    }else{
      return false;
    }
  }
  return true;
}

// Test function that shows how you can time a piece of code.
// Just times a simple loop. Remove for final submission.

void TestTiming() {
  cout << "Test Timing" << endl;
  const auto begin_time = chrono::high_resolution_clock::now();
  // Time this piece of code.
  int sum = 0;
  for (int i = 1; i < 10000; ++i) sum ++;
  // End of piece of code to time.
  const auto end_time = chrono::high_resolution_clock::now();    
  cout << ComputeDuration(begin_time, end_time) << "ns" << endl;

}

template<typename Comparable, typename Comparator>
void TestTiming(vector<Comparable>& a, Comparator less_than){
  const auto heapStart = chrono::high_resolution_clock::now();
  // Time this piece of code.
  HeapSort(a, less_than);
  // End of piece of code to time.
  const auto heapEnd = chrono::high_resolution_clock::now();   
  cout << "HeapSort" << endl;
  cout << "Runtime: ";
  cout << ComputeDuration(heapStart, heapEnd) << "ns" << endl;
  cout << "Verified: " << VerifyOrder(a, less_than) << endl;
  cout << endl;

  const auto mergeStart = chrono::high_resolution_clock::now();
  // Time this piece of code.
  MergeSort(a, less_than);
  // End of piece of code to time.
  const auto mergeEnd = chrono::high_resolution_clock::now();   
  cout << "MergeSort" << endl;
  cout << "Runtime: ";
  cout << ComputeDuration(mergeStart, mergeEnd) << "ns" << endl;
  cout << "Verified: " << VerifyOrder(a, less_than) << endl;
  cout << endl;

  const auto quickStart = chrono::high_resolution_clock::now();
  // Time this piece of code.
  quicksort(a, less_than);
  // End of piece of code to time.
  const auto quickEnd = chrono::high_resolution_clock::now();   
  cout << "QuickSort" << endl;
  cout << "Runtime: ";
  cout << ComputeDuration(quickStart, quickEnd) << "ns" << endl;
  cout << "Verified: " << VerifyOrder(a, less_than) << endl;
  cout << endl;

  const auto med3Start = chrono::high_resolution_clock::now();
  // Time this piece of code.
  QuickSort(a, less_than);
  // End of piece of code to time.
  const auto med3End = chrono::high_resolution_clock::now();   
  cout << "Median of Three" << endl;
  cout << "Runtime: ";
  cout << ComputeDuration(med3Start, med3End) << "ns" << endl;
  cout << "Verified: " << VerifyOrder(a, less_than) << endl;
  cout << endl;

  const auto middleStart = chrono::high_resolution_clock::now();
  // Time this piece of code.
  QuickSort2(a, less_than);
  // End of piece of code to time.
  const auto middleEnd = chrono::high_resolution_clock::now();   
  cout << "Middle" << endl;
  cout << "Runtime: ";
  cout << ComputeDuration(middleStart, middleEnd) << "ns" << endl;
  cout << "Verified: " << VerifyOrder(a, less_than) << endl;
  cout << endl;

  const auto firstStart = chrono::high_resolution_clock::now();
  // Time this piece of code.
  QuickSort3(a, less_than);
  // End of piece of code to time.
  const auto firstEnd = chrono::high_resolution_clock::now();   
  cout << "First" << endl;
  cout << "Runtime: ";
  cout << ComputeDuration(firstStart, firstEnd) << "ns" << endl;
  cout << "Verified: " << VerifyOrder(a, less_than) << endl;
  cout << endl;
}

// Generates and returns random vector of size @size_of_vector.
vector<int> GenerateRandomVector(size_t size_of_vector) {
  // Use rand() to generate random integer
  // Add code
  vector<int> vector;
  for(size_t i = 0; i < size_of_vector; i++){
    vector.push_back(rand());
  }
  return vector;
}

// Generates and returns sorted vector of size @size_of_vector.
// If @smaller_to_larger is true, returns vector sorted from small to large.
// Otherwise returns vector sorted from large to small
vector<int> GenerateSortedVector(size_t size_of_vector, bool smaller_to_larger) {
  // Add code
  vector<int> vec = GenerateRandomVector(size_of_vector);

  for(size_t i = 0; i < vec.size(); i++){
    if(smaller_to_larger){
      insertionSort(vec);
    }else{
      vector<int> temp;
      insertionSort(vec);
      temp = vec;
      vec.clear();
      for(size_t i = size_of_vector; i > 0; i--){
        vec.push_back(temp[i]);
      }
      temp.clear();
    }
  }
  return vec;
}

// Wrapper function to test different sorting algorithms. See homework's PDF for details.
void testSortingWrapper(int argc, char **argv) {
  const string input_type = string(argv[1]);
  const int input_size = stoi(string(argv[2]));
  const string comparison_type = string(argv[3]);
  if (input_type != "random" && input_type != "sorted_small_to_large" && input_type != "sorted_large_to_small") {
    cout << "Invalid input type" << endl;
    return;
  }
  if (input_size <= 0) {
    cout << "Invalid size" << endl;
    return;
  }
  if (comparison_type != "less" && comparison_type != "greater") {
    cout << "Invalid comparison type" << endl;
    return;
  }

  // This block of code to be removed for your final submission.
  // TestTiming();

  // cout << "Running sorting algorithms: " << input_type << " " << input_size << " numbers " << comparison_type << endl;
  // vector<int> input_vector;
  // if(input_type == "random") {
  //   // Generate random vector @input_vector.
  //   input_vector = GenerateRandomVector(input_size);
  // }else if(input_type == "sorted_small_to_large" && comparison_type == "less"){
  //   // Generate sorted vector @input_vector.
  //   input_vector = GenerateSortedVector(input_size, true);
  //   TestTiming(input_vector, less<int>{});
  // }else if(input_type == "sorted_large_to_small" && comparison_type == "greater"){
  //   input_vector = GenerateSortedVector(input_size, false);
  //   TestTiming(input_vector, greater<int>{});
  // }else{
  //   cout << "invalid" << endl;
  // }

  // Call HeapSort / MergeSort / QuickSort  using appropriate input.
  // ...
  // if comparison type is "less" then call 
  // MergeSort(input_vector, less<int>{})
  // otherwise call
  // MergeSort(input_vector, greater<int>{})
  // ...
  // ^^SAME for HeapSort & QuickSort

  // Call quicksort with median of three as pivot / middle as pivot / first as pivot using appropriate input.
  // ...
  // if comparison type is "less" then call 
  // QuickSort(input_vector, less<int>{})
  // otherwise call
  // QuickSort(input_vector, greater<int>{})
  // ...
  // ^^SAME for QuickSort2 & QuickSort3

}

int main(int argc, char **argv) {
  // DO NOT CHANGE or ADD ANY CODE in this function.
  if (argc != 4) {
    cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
    return 0;
  }
  
  testSortingWrapper(argc, argv);

  return 0;
}
