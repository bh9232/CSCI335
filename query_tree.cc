// Brian Hong
// Main file for Part2(a) of Homework 2.
// Code will compile and run after you have completed sequence_map.h.

#include "avl_tree.h"
#include "bst_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
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


  string db_line, an_enz_acro, a_reco_seq;
  for(unsigned i = 0; i < 10; i++){ //skipping first 10 lines of rebase210.txt
    getline(in_stream, db_line);
  }
  
  while(getline(in_stream, db_line)){
    if(db_line.empty()){
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
  
  vector<string> user_input;
  int counter = 0;
  while(counter < 3){
    cin >> a_reco_seq;
    user_input.push_back(a_reco_seq);
    counter++;
  }

  for (int i = 0; i < counter; i++){
    a_tree.printEnzyme(user_input[i]);
  }
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
