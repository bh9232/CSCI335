//Brian Hong
//test file for graph.h

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

  string graph_filename = argv[1];
  string adjacency_queryfilename = argv[2];
  ifstream input_file(graph_filename);
  string line;
  int num_of_vertices = 0;

  input_file >> num_of_vertices;
  Graph graph1(num_of_vertices);

  while(getline(input_file, line)){
    int iter = 1;
    int vertex = 0;
    int connected_vertex = 0;
    double edge_weight = 0;

    stringstream object_stream(line);
    
    
    while(object_stream){ 
      if(iter == 1){
        object_stream >> vertex;
      }
      object_stream >> connected_vertex;
      object_stream >> edge_weight;
      
      if(object_stream){
        graph1.addEdge(vertex, connected_vertex, edge_weight);
      }
      iter++;
    }
  }
  // took this out of the loop
  int vertex1 = 0;
  int vertex2 = 0;
  ifstream adj_file(adjacency_queryfilename);

  // int counter_for_adj_file = 0;
  //while(!(adj_file.eof())){
  while(getline(adj_file, line)){
    stringstream object_stream(line);
  
    object_stream >> vertex1;
    cout << "\tvertex1 is " << vertex1 << endl;
    object_stream >> vertex2;
    cout << "\tvertex2 is " << vertex2 << endl;
    graph1.checkConnection(vertex1,vertex2);
    // counter_for_adj_file++;
  }
  // cout << "it read the adj file " << counter_for_adj_file << " times";

  return 0;
}

/* originial
while(!(adj_file.eof())){
  adj_file >> vertex1;
  adj_file >> vertex2;
  graph1.checkConnection(vertex1, vertex2);
}
*/

int main(int argc, char **argv) {
  if (argc != 3) {
  cout << "Usage: " << argv[0] << " <GRAPH_File>" << "<ADJACENCY_QUERYFILE>" << endl;
  return 0;
  }

  graphTestDriver(argc, argv);

  return 0;
}
