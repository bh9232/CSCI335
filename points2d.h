// --> Brian Hong
// Few comments describing the class Points2D

// Points2D class is to have points on a 2D plane 
// and have them be descrobed as sequences 

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {

// Place comments that provide a brief explanation of the class,
// and its sample usage.
template<typename Object>
class Points2D {
 public:
  // Default "big five" -- you have to alter them for your assignment.
  // That means that you will remove the "= default" statement.
  //  and you will provide an implementation.

  // Zero-parameter constructor. 
  // Set size to 0.
  Points2D(){
    size_ = 0;
    sequence_ = nullptr;
  }

  // Copy-constructor.
  Points2D(const Points2D &rhs){
    if(rhs.size_ == 0){
      sequence_ = nullptr;
      size_ = 0;
    }
    size_ = rhs.size();
    sequence_ = new std::array<Object, 2>[rhs.size_];
    for(size_t i = 0; i < rhs.size_; i++){
      sequence_[i] = rhs.sequence_[i];
    }
  }

  // Copy-assignment. If you have already written
  // the copy-constructor and the move-constructor
  // you can just use:
  // {
  // Points2D copy = rhs; 
  // std::swap(*this, copy);
  // return *this;
  // }
  Points2D& operator=(const Points2D &rhs){
    Points2D copy = rhs;
    std::swap(*this, copy);
    return *this;
  }

  // Move-constructor. 
  Points2D(Points2D &&rhs):sequence_(std::move(rhs.sequence_)), size_(std::move(rhs.size_)){
    rhs.sequence_ = nullptr;
    rhs.size_= 0;
  }

  // Move-assignment.
  // Just use std::swap() for all variables.
  Points2D& operator=(Points2D &&rhs){
    if(this != &rhs){
      std::swap(sequence_, rhs.sequence_);
      std::swap(size_, rhs.size_);
    }
    return *this;
  }

  // Destructor
  ~Points2D(){
    if(sequence_ != nullptr){
      delete[] sequence_;
    }
    sequence_ = nullptr;
  }

  // End of big-five.

  // One parameter constructor.
  Points2D(const std::array<Object, 2>& item) {
    sequence_ = new std::array<Object, 2>[1];
    sequence_[0] = item;
    size_ = 1;
  }

  // Read a chain from standard input.
  void ReadPoints2D() {
    std::cout << std::endl;
    // Part of code included (without error checking).
    std::string input_line;
    std::getline(std::cin, input_line); 
    std::stringstream input_stream(input_line);
    if (input_line.empty()) return;
    // Read size of sequence (an integer).
    int size_of_sequence;
    input_stream >> size_of_sequence;
    // Allocate space for sequence.
    // Add code here.
    size_ = size_of_sequence;
    sequence_ = new std::array<Object, 2>[size_of_sequence];

    Object token;
    for (int i = 0 ;input_stream >> token; ++i) {
      // Read coordinates.
      // Fill sequence_ here.
      sequence_[i][0] = token;
      input_stream >> token;
      sequence_[i][1] = token;
    }
  }

  size_t size() const {
    return size_;
  }

  // @location: an index to a location in the sequence.
  // @returns the point at @location.
  // const version.
  // abort() if out-of-range.
  const std::array<Object, 2>& operator[](size_t location) const { 
    if((location >= size_) || (location < 0)){
      abort();
    }else{
      return sequence_[location];
    }
  }

 //  @c1: A sequence.
 //  @c2: A second sequence.
 //  @return their sum. If the sequences are not of the same size, append the
 //    result with the remaining part of the larger sequence.
 friend Points2D operator+(const Points2D &c1, const Points2D &c2) {
   Points2D sum;
   size_t smaller_size, larger_size;

   if(c1.size() > c2.size()){
     sum.sequence_ = new std::array<Object, 2>[c1.size_];
     larger_size = c1.size();
     smaller_size = c2.size();
   }else{
     sum.sequence_ = new std::array<Object, 2>[c2.size_];
     larger_size = c2.size();
     smaller_size = c1.size();
   }
   for(size_t i = 0; i < smaller_size; ++i){
     sum.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
     sum.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
   }
   if(c1.size() > c2.size()){
     for(size_t i = smaller_size; i < larger_size; ++i){
       sum.sequence_[i][0] = c1.sequence_[i][0];
       sum.sequence_[i][1] = c1.sequence_[i][1];
     }
   }else{
     for(size_t i = smaller_size; i < larger_size; ++i){
       sum.sequence_[i][0] = c2.sequence_[i][0];
       sum.sequence_[i][1] = c2.sequence_[i][1];
     }
   }
   sum.size_ = larger_size;
   return sum;
 }

 // Overloading the << operator.
 friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points2) {
   if(some_points2.size_ == 0){
     out << "(" << ")";
   }else if(some_points2.size_ >= 1){
     for(size_t i = 0; i < some_points2.size_; ++i){
       out << "(" << some_points2.sequence_[i][0] << ", " << some_points2.sequence_[i][1] << ") ";
     }
   }
   out << "\n";
   return out;
 }
 
 private:
  // Sequence of points. 
  // array that holds 2 objects
  // *sequence_ is a pointer to memory with an array holding 2 objects
  std::array<Object, 2> *sequence_;
  // Size of sequence.
  size_t size_;

};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_POINTS2D_H_
