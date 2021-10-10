/*
    Name: Brian Hong

    Header file for sequence_map.cc
*/

#include <iostream>
#include <string>
#include <vector>
#include <avl_tree.h>
#include <bst_tree.h>

class SequenceMap{
    public:
        
    //defualt big-five
    SequenceMap() = default;
    SequenceMap(const SequenceMap &rhs) = default;
    SequenceMap& operator=(const SequenceMap &rhs) = default;
    SequenceMap(SequenceMap &&rhs) = default;
    SequenceMap& operator=(SequenceMap &&rhs) = default;
    ~SequenceMap() = default;
    //additional functions
    SequenceMap(const std::string &a_rec_seq, const std::string &an_enz_acro){
        recognition_sequence_ = a_rec_seq;
        enzyme_acronyms_.push_back(an_enz_acro);
    }

    bool operator<(const SequenceMap &rhs) const{
        return recognition_sequence_ < rhs.recognition_sequence_;
    }

    friend ostream& operator<<(ostream &out, const SequenceMap &another_map){
        out << another_map.recognition_sequence_ << "\n";
        if(another_map.enzyme_acronyms_.size() == 0){
            cout << "Not Found";
        }else{
            for(size_t i = 0; i < another_map.enzyme_acronyms_.size(); i++){
                cout << another_map.enzyme_acronyms_[i] << " ";
            }
        }
        return out;
    }

    void Merge(const SequenceMap &other_sequence){
        for(size_t i = 0; i < other_sequence.enzyme_acronyms_.size(); ++i){
            enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
        }
    }

    bool isEmpty() const{
        return recognition_sequence_.empty();
    }

    std::string getSequence() const{
        return recognition_sequence_;
    }

    std::vector<std::string> getAcronym() const{
        return enzyme_acronyms_;
    }

    private:
    std::string recognition_sequence_;
    std::vector<std::string> enzyme_acronyms_;
};