//Brian Hong
//test file for Dijkstra's Algorithm Implementiation

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "graph.h"

using namespace std;

int pathfindDriver(int argc, char **argv) {
    
  //Begin your code here. Feel free to add any helper functions or classes you need,
  //as long as we only have to call this function to run the specified assignment.

  //importing files
  string graph_filename = argv[1];
  int start_pos = stoi(argv[2]);
  ifstream input_file(graph_filename);
  string line;
  int num_of_vertices = 0;

  input_file >> num_of_vertices;
  Graph graph1(num_of_vertices);

  //reading Graph#.txt
  while(getline(input_file, line)){
    int iter = 1;
    int vertex = 0;
    int connected_vertex = 0;
    double edge_weight = 0;

    //sstream needed to get chuncks of data
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
  graph1.Dijkstra(start_pos);

  return 0;
}

int main(int argc, char **argv) {
  if (argc != 3) {
  cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
  return 0;
  }

  pathfindDriver(argc, argv);

  return 0;
}
