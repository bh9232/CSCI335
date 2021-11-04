// Brian Hong
// spell_check.cc: A simple spell checker.

#include <fstream>
#include <iostream>
#include <string>

// You can change to quadratic probing if you
// haven't implemented double hashing.
#include "double_hashing.h"
using namespace std;

// You can add more functions here.

// Creates and fills double hashing hash table with all words from
// dictionary_file
HashTableDouble<string> MakeDictionary(const string &dictionary_file) {
  HashTableDouble<string> dictionary_hash;
  // Fill dictionary_hash.
  fstream dictionary(dictionary_file);
  string line;

  while(dictionary >> line){
    dictionary_hash.Insert(line);
  }

  return dictionary_hash;
}

// For each word in the document_file, it checks the 3 cases for a word being
// misspelled and prints out possible corrections
void SpellChecker(HashTableDouble<string> &dictionary, const string &document_file) {
  ifstream document(document_file);
  string line;
  string temp = "";
  string alphabet = "abcdefghijklmnopqrstuvwxyz";

  while(document >> line){
    for(size_t i = 0; i < line.size(); i++){
      temp += tolower(line[i]);
      if(temp[i] == ',' || temp[i] == '.'){
        temp.erase(i);
      }
    }
    line = temp;
    temp.clear();

    if(dictionary.Contains(line)){
      cout << line << " is CORRECT" << endl;
    }else{
      cout << line << " is INCORRECT" << endl;

      //all possible misspellings
      //Case A - missing letter
      for(size_t i = 0; i < 26; i++){
        for(size_t j = 0; j <= line.size(); j++){
          string temp2(line);
          temp2.insert(j, string(1, alphabet[i]));
          if(dictionary.Contains(temp2)){
          cout << "*** " << line << " -> " << temp2 << " *** case A" << endl;
          }
          
        }
      }

      //Case B - extra letter
      for(size_t i = 0; i < line.size(); i++){
        string temp2(line);
        temp2.erase(i, 1);
        if(dictionary.Contains(temp2)){
          cout << "*** " << line << " -> " << temp2 << " *** case B" << endl;
        }
        
      }

      //Case C - swapping letters
      for(size_t i = 0; i < line.size()-1; i++){
        string temp2(line);
        swap(temp2[i], temp2[i+1]);
        if(dictionary.Contains(temp2)){
          cout << "*** " << line << " -> " << temp2 << " *** case C" << endl;
        }
        
      }
    }
  }
}

// @argument_count: same as argc in main
// @argument_list: save as argv in main.
// Implements
int testSpellingWrapper(int argument_count, char** argument_list) {
    const string document_filename(argument_list[1]);
    const string dictionary_filename(argument_list[2]);

    // Call functions implementing the assignment requirements.
    HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename);
    SpellChecker(dictionary, document_filename);

    return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char** argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
         << endl;
    return 0;
  }
  
  testSpellingWrapper(argc, argv);
  
  return 0;
}