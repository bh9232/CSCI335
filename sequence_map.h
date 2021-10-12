/*
    Brian Hong

    Header file for sequence_map.cc
*/


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SequenceMap{
    public:
    //defualt big-five
    SequenceMap() = default;
    SequenceMap(const SequenceMap &rhs) = default;
    SequenceMap& operator=(const SequenceMap &rhs) = default;
    SequenceMap(SequenceMap &&rhs) = default;
    SequenceMap& operator=(SequenceMap &&rhs) = default;
    ~SequenceMap() = default;
    //end of big five

    //additional functions

    //2 parameter constructor
    SequenceMap(const string &a_rec_seq, const string &an_enz_acro){
        recognition_sequence_ = a_rec_seq;
        enzyme_acronyms_.push_back(an_enz_acro);
    }

    //string comparison operator
    bool operator<(const SequenceMap &rhs) const{
        return recognition_sequence_ < rhs.recognition_sequence_;
    }

    //overload operator
    friend ostream& operator<<(ostream &out, const SequenceMap &another_map){        
        for(unsigned i = 0; i < another_map.enzyme_acronyms_.size(); i++){
            out << another_map.enzyme_acronyms_[i] << " ";
        }
        return out;
    }

    //merge enzyme_arcos
    void Merge(const SequenceMap &other_sequence){
        for(unsigned i = 0; i < other_sequence.enzyme_acronyms_.size(); i++){
            enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
        }
    }

    //getter methods
    string getRecSeq(){
        return recognition_sequence_;
    }

    void getEnzAcro(){
        for(unsigned i = 0; i < enzyme_acronyms_.size(); i++){
            cout << enzyme_acronyms_[i] << " ";
        }
        cout << endl;
    }

    private:
    string recognition_sequence_;
    vector<string> enzyme_acronyms_;
};