//Brian Hong
//graph.h is need to represent a graph as a adjacency list

#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include <iostream>
#include <vector>
#include "binary_heap.h"

using namespace std;

//This file is for your graph implementation.
//Add everything you need in between the "ifndef and "endif" statements.
//Do not put anything outside those statements


class Graph{
public:
  Graph() {};

  Graph(int num_vectors){
    num_vertices = num_vectors;
    vertex_list.resize(num_vectors);

    for(auto& i : vertex_list){
      i = new Vertex;
    }

    for(int i = 0; i < num_vertices; ++i){
      vertex_list[i]->vertex_number = i+1;
    }
  }

  void addEdge(int vertex1, int vertex2, double weight){
    Vertex::Adjacency x;
    x.adjacent_number = vertex2;
    x.weight = weight;
    vertex_list[vertex1-1]->adj.push_back(x);
  }

  //to check whether two vertices are connected
  bool checkConnection(int vertex1, int vertex2){
    bool connected = false;
    size_t size = vertex_list[vertex1-1]->adj.size();
    
    int counter = 0;

    for(unsigned int i = 0; i < size; i++){
      counter = i;
      if(vertex_list[vertex1-1]->adj[i].adjacent_number == vertex2){
        connected = true;
        break;
      }
    }
    if(connected){
      cout << vertex1 << " " << vertex2 << ": connected " << vertex_list[vertex1-1]->adj[counter].weight << endl;
      return connected;
    }else{
      cout << vertex1 << " " << vertex2 << ": not_connected" << endl;
      return connected;
    }
  }

private:
  struct Vertex{
    struct Adjacency{
      int adjacent_number;
      double weight;

      //default Adjacency() constructor
      Adjacency() : adjacent_number {}, weight {} {};
      string printAdjacency(){
        return "\tadjacent_number: " + to_string(adjacent_number) + "\n\tweight: " + to_string(weight); 
      }
    };
    //end of struct Adjacency

    vector<Adjacency> adj;
    int vertex_number;
    
    //default Vertex() constructor
    Vertex() : adj {}, vertex_number {} {};

    string printVertex(){
      string result = "vertex_number " + to_string(vertex_number) + "\n";
      for (unsigned int i=0; i<adj.size(); i++){
        result += adj[i].printAdjacency() + "\n";
      }
      return result;
    }
  };

  int num_vertices;
  vector<Vertex*> vertex_list;
};



#endif
