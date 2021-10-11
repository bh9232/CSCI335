// Brian Hong
// Main file for Part2(c) of Homework 2.
// Code will compile and run after you have completed sequence_map.h.

#include "avl_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
using namespace std;

namespace {

string getSeq(string &line){
  int pos = line.find('/');
  string seq = line.substr(0, pos);
  line = line.substr(pos+1);
  return seq;
}

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void CreateTree(const string &db_filename, TreeType &a_tree) {
  // Code for running Part2(b)  
  ifstream in_stream(db_filename);
  if(in_stream.fail()){
    cerr << "error in stream\n";
    exit(1);
  }
    
  string db_line, an_enz_acro, a_reco_seq;
  while(getline(in_stream, db_line)){
    if(db_line[db_line.size()-1] != '/'){
      continue;
    }
    
    //getting acros
    an_enz_acro = getSeq(db_line);
    
    //getting seqs
    while(db_line.length() > 2){
      a_reco_seq = getSeq(db_line);
      SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
      a_tree.insert(new_sequence_map);
    }
  }
  in_stream.close();
}


template <typename TreeType>
int numQueries(const TreeType &a_tree, const string &db_filename){
  ifstream in_file(db_filename);
  string sequence;
  int num_of_successes = 0;
  int temp = 0;
  while (getline(in_file, sequence)){
    SequenceMap map(sequence, "");
    if (a_tree.contains(map, temp)){
    num_of_successes++;
    }
  }
  in_file.close();
  return num_of_successes;
}


template <typename TreeType>
int numRecursions(const TreeType &a_tree, const string &db_filename){
  ifstream in_file(db_filename);
  string sequence;
  int counter = 0;
  while(getline(in_file, sequence)){
    SequenceMap a_map(sequence, "");
    a_tree.contains(a_map, counter);
  }
  in_file.close();
  return counter;
}

template <typename TreeType>
int numRemoves(TreeType &a_tree, const string &db_filename){
  ifstream in_file(db_filename);
  string sequence;
  int delete_count = 0, min_count = 0, temp = 0;
  bool state = true;
  
  while(getline(in_file, sequence)){
    if(state){
      state = false;
      SequenceMap a_map(sequence, "");
      if(a_tree.contains(a_map, temp)){
        a_tree.remove(a_map, delete_count, min_count);
      }
    }else{
      state = true;
    } 
  }
  in_file.close();
  return delete_count + min_count;
}

template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
  CreateTree(db_filename, a_tree);

  //2
  int num_nodes = a_tree.numNodes();
  cout<< "2: " << num_nodes << endl;
  //3a
  cout << "3a: " << a_tree.avgDepth() << endl;
  //3b
  cout << "3b: " << a_tree.avgDepth() / log2(num_nodes) << endl;

  int num_queries = numQueries(a_tree, seq_filename);
  //4a
  cout << "4a: " << num_queries << endl;
  //4b
  cout << "4b: " << (float)numRecursions(a_tree, seq_filename) / num_queries << endl;
  
  int total_removes = numRemoves(a_tree, seq_filename);
  //5a
  cout << "5a: " << num_nodes - a_tree.numNodes() << endl;
  //5b
  cout << "5b: " << (float)total_removes / (num_nodes - a_tree.numNodes()) << endl;
  //6a
  cout << "6a: " << a_tree.numNodes() << endl;
  //6b
  cout << "6b: " << a_tree.avgDepth() << endl;
  //6c
  cout << "6c: " << a_tree.avgDepth() / log2(a_tree.numNodes()) << endl;
}

}  // namespace

int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  AvlTree<SequenceMap> a_tree;
  TestTree(db_filename, seq_filename, a_tree);
  
  return 0;
}
