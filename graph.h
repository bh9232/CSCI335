//Brian Hong
//graph.h is need to represent a graph as a adjacency list

#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include <iostream>
#include <limits>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "binary_heap.h"

using namespace std;

//This file is for your graph implementation.
//Add everything you need in between the "ifndef and "endif" statements.
//Do not put anything outside those statements


class Graph{
public:
  Graph() {};

  //constructor
  Graph(int num_vectors){
    num_vertices_ = num_vectors;
    vertex_list_.resize(num_vectors);

    for(auto& i : vertex_list_){
      i = new Vertex;
    }

    for(int i = 0; i < num_vertices_; ++i){
      vertex_list_[i]->vertex_number_ = i+1;
    }
  }

  ~Graph() {};

  //adding adjacent vertices
  void addEdge(int vertex1, int vertex2, double weight){
    Vertex::Adjacency x;
    x.adjacent_number_ = vertex2;
    x.weight_ = weight;
    vertex_list_[vertex1-1]->adj_.push_back(x);
  }

  //to check whether two vertices are connected
  bool checkConnection(int vertex1, int vertex2){
    bool connected = false;
    size_t size = vertex_list_[vertex1-1]->adj_.size();
    
    int counter = 0;

    for(unsigned int i = 0; i < size; i++){
      counter = i;
      if(vertex_list_[vertex1-1]->adj_[i].adjacent_number_ == vertex2){
        connected = true;
        break;
      }
    }
    if(connected){
      cout << vertex1 << " " << vertex2 << ": connected " << vertex_list_[vertex1-1]->adj_[counter].weight_ << endl;
      return connected;
    }else{
      cout << vertex1 << " " << vertex2 << ": not_connected" << endl;
      return connected;
    }
  }

  //Dijkstra method of graphing
  void Dijkstra(int pos){
    BinaryHeap<Vertex*> priority_queue;
    priority_queue.insert(vertex_list_[pos-1]);
    vertex_list_[pos-1]->distance_ = 0;

    while(!priority_queue.isEmpty()){
      Vertex* v = priority_queue.findMin();
      priority_queue.deleteMin();
      v->known_ = true;

      for(unsigned int i = 0; i < v->adj_.size(); i++){
        int v_num = v->adj_[i].adjacent_number_-1;
        Vertex* w = vertex_list_[v_num];

        if(w->known_ == false){
          if(v->distance_ + v->adj_[i].weight_ < w->distance_){
            w->distance_ = v->distance_ + v->adj_[i].weight_;
            w->path_ = v;
          }
          priority_queue.insert(w);
        }
      }
    }
    printPath(pos);
  }

  //print the pathing(interation: vertex numbers/path cost: distance/not_possible)
  void printPath(int pos){
		vector<int> path;//vector of vertex numbers in the path in from current -> start/previous
		for(int i = 0; i < vertex_list_.size(); i++){
			cout << i+1 << ": ";
			Vertex* v = vertex_list_[i];
      if(v->path_ != nullptr){
        double cost = v->distance_;
        while(v != nullptr){
          if(v->vertex_number_ == 0){
            v->vertex_number_ = i+1;
          }
          path.push_back(v->vertex_number_);
          v = v->path_;
        }
        
        reverse(path.begin(),path.end());//path start/previous -> current
        for(int i= 0; i<path.size();i++){
          cout << path[i] << " ";
        }
        path.clear();

        cout << "cost: " << fixed << setprecision(1) << cost << endl;
      }else if(i+1 == pos){
        cout << i+1 << " cost: 0.0" << endl;
      }else{
        cout << "not_possible" << endl;
      }
		}
	}

private:
  struct Vertex{
    struct Adjacency{
      int adjacent_number_;
      double weight_;

      //default Adjacency() constructor
      Adjacency() : adjacent_number_ {}, weight_ {} {};

      //debugging method
      string printAdjacency(){
        return "\tadjacent_number: " + to_string(adjacent_number_) + "\n\tweight: " + to_string(weight_); 
      }
      //end of debugging method
    };
    //end of struct Adjacency

    vector<Adjacency> adj_;
    int vertex_number_;
    bool known_;
    double distance_;
    Vertex* path_;

    //default Vertex() constructor
    Vertex() : adj_ {}, vertex_number_ {}, known_ {}, distance_ {numeric_limits<double>::max()}, path_{nullptr} {};

    //debugging methods
    string printVertexNumber(){
      return to_string(vertex_number_);
    }

    string printVertex(){
      string result = "vertex_number " + to_string(vertex_number_) + "\n";
      for (unsigned int i=0; i<adj_.size(); i++){
        result += adj_[i].printAdjacency() + "\n";
      }
      if (known_ ) {
        result += "\tknown true\n";
      } else {
        result += "\tknown false\n";
      }
      result += "\tdistance: " + to_string(distance_);
      result += "\n";
      if (path_ != nullptr){
        result += "\tpath is " + path_->printVertexNumber();
      } else {
        result += "\tpath is nonexistance";
      }
      return result;
    }
    //end of debugging methods
  };//end of Vertex struct

  int num_vertices_;
  vector<Vertex*> vertex_list_;
};



#endif
