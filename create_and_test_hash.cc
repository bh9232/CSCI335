// Brian Hong
#include <fstream>
#include <iostream>
#include <string>

// Uncomment when you implemented linear probing & double hashing
#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"

using namespace std;


// You can add more functions here

// @hash_table: a hash table (can be linear, quadratic, or double)
// @words_filename: a filename of input words to construct the hash table
// @query_filename: a filename of input words to test the hash table
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
    hash_table.MakeEmpty();
    //..Insert your own code
    fstream words(words_filename);
    fstream query(query_filename);
    string line;

    while(words >> line){
        hash_table.Insert(line);
    }    

    //output stuff
    cout << "number_of_elements: " << hash_table.TotalElements() << endl;
    cout << "size_of_table: " << hash_table.Size() << endl;
    cout << "load_factor: " << hash_table.TotalElements() / (float)hash_table.Size() << endl;
    cout << "average_collisions: " << hash_table.TotalCollisions() / (float)hash_table.TotalElements() << endl;
    cout << "total_collisions: " << hash_table.TotalCollisions() << endl;
    cout << endl;

    while(query >> line){
        try{
            int collisions = hash_table.Get(line);
            cout << line << " Found " << collisions << endl;
        }catch(const exception &e){
            cout << line << " Not_Found " << hash_table.collisions_ << endl;
        }
    }
}

// @argument_count: argc as provided in main
// @argument_list: argv as provided in imain
// Calls the specific testing function for hash table (linear, quadratic, or double).
int testHashingWrapper(int argument_count, char **argument_list) {
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 10;

    if (argument_count == 5) {
	const string rvalue(argument_list[4]);
	R = stoi(rvalue);
    }

    if (param_flag == "linear") {
      // Uncomment below when you have implemented linear probing.
      HashTableLinear<string> linear_probing_table;
      TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
    } else if (param_flag == "quadratic") {
        HashTable<string> quadratic_probing_table;
        TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
    } else if (param_flag == "double") {
	cout << "r_value: " << R << endl;
    // Uncomment below when you have implemented double hashing.
	HashTableDouble<string> double_probing_table;
    double_probing_table.SetR(R);
	TestFunctionForHashTable(double_probing_table, words_filename, query_filename);
    } else {
	cout << "Unknown tree type " << param_flag
	     << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash. DO NOT CHANGE IT.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv) {
    if (argc != 4 and argc != 5) {
	cout << "Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag>" << endl;
	cout << "or Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
	return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}
