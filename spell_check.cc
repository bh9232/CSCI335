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

  while(file >> line){
    dictionary_hash.Insert(line);
  }

  return dictionary_hash;
}

// For each word in the document_file, it checks the 3 cases for a word being
// misspelled and prints out possible corrections
void SpellChecker(const HashTableDouble<string>& dictionary, const string &document_file) {
  fstream document(document_file);
  string line;
  string temp = "";
  string alphabet = "abcdefghijklmnopqrstuvwxyz";
  vector<string> potential_spellings;
  vector<string> error_type;

  while(document >> line){
    for(size_t i = 0; i < line.size(); i++){
      temp = tolower(line[i]);
      if(temp[i] == ',' || temp[i] == '.'){
        temp.erase(i, 1);
      }
    }
    line = temp;
    temp.clear();

    try{
      dictionary.Get(line);
      cout << line << " is CORRECT" << endl;
    }catch(const exception &e){
      cout << line << " is INCORRECT" << endl;
      temp = line;

      //all possible misspellings

      //Case A - missing letter
      for(size_t i = 0; i < 26; i++){
        for(size_t j = 0; j < line.size(); j++){
          temp.insert(j, string(1, alphabet[i]));
          potential_spellings.push_back(temp);
          error_type.push_back("A");
          temp = line;
        }
      }

      //Case B - extra letter
      for(size_t i = 0; i < line.size(); i++){
        temp.erase(i, 1);
        potential_spellings.push_back(temp);
        error_type.push_back("B");
        temp = line;
      }

      //Case C - swapping letters
      for(size_t i = 0; i < line.size(); i++){
        swap(temp[i], temp[i+1]);
        potential_spellings.push_back(temp);
        error_type.push_back("C");
        temp = line;
      }

      for(size_t i = 0; i < potential_spellings.size(); i++){
        try{
          dictionary.Get(potential_spellings[i]);
          cout << "*** " << line << " -> " << potential_spellings[i] << " *** case " << error_type[i] << endl;
        }catch(const exception &e){}
      }
    }
    potential_spellings.clear();
    error_type.clear();
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