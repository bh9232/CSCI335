//Brian Hong
//test file for creating ajacency list

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "graph.h"

using namespace std;

int graphTestDriver(int argc, char **argv) {
  
  //Begin your code here. Feel free to add any helper functions or classes you need,
  //as long as we only have to call this function to run the specified assignment.

  //importing files
  string graph_filename = argv[1];
  string adjacency_queryfilename = argv[2];
  ifstream input_file(graph_filename);
  string line;
  int num_of_vertices = 0;

  input_file >> num_of_vertices;
  Graph graph1(num_of_vertices);

  //reading Graph#.txt
  while(getline(input_file, line)){
    int vertex = 0;
    int connected_vertex = 0;
    double edge_weight = 0;

    //sstream needed to get chuncks of data
    stringstream object_stream(line);
    object_stream >> vertex;
    
    while(object_stream){ 

      object_stream >> connected_vertex;
      object_stream >> edge_weight;
      
      if(object_stream){
        graph1.addEdge(vertex, connected_vertex, edge_weight);
      }
    }
  }

  //reading AdjacenyQuery files
  int vertex1 = 0;
  int vertex2 = 0;
  ifstream adj_file(adjacency_queryfilename);

  while(getline(adj_file, line)){
    stringstream object_stream(line);
    object_stream >> vertex1;
    object_stream >> vertex2;
    graph1.checkConnection(vertex1,vertex2);
  }

  return 0;
}

int main(int argc, char **argv) {
  if (argc != 3) {
  cout << "Usage: " << argv[0] << " <GRAPH_File>" << "<ADJACENCY_QUERYFILE>" << endl;
  return 0;
  }

  graphTestDriver(argc, argv);

  return 0;
}
