// Brian Hong
// Main file for Part2(a) of Homework 2.
// Code will compile and run after you have completed sequence_map.h.

#include "avl_tree.h"
#include "bst_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

namespace {


// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
  // Code for running Part2(a)
  // Parse input file @db_filename and feel tree @a_tree
  // Then prompt the user for exactly three strings (do a loop) and
  // provide the results of find() as described in the assignment.

  ifstream in_stream(db_filename);
  if(in_stream.fail()){
    cerr << "error in stream\n";
    exit(1);
  }

  string db_line, skip_lines;
  for(int i = 0; i < 10; i++){ //skipping first 10 lines of rebase210.txt
    getline(in_stream, skip_lines);
  }

  vector<string> enzyme_acro;
  while(getline(in_stream, db_line, '/')){
    string an_enz_acro = db_line.substr(0,db_line.find("/"));
    string a_reco_seq;
    while(getline(cin, a_reco_seq)){
      SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
      cout << new_sequence_map;
      a_tree.insert(new_sequence_map);
    }
  }

  in_stream.close();
  
}

}  // namespace

int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    BinarySearchTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else if (param_tree == "AVL") {
    AvlTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
