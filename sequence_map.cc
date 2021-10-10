/*
    Name: Brian Hong

    Provides big five and constructors for avl tree
*/

#include "sequence_map.h"

SequenceMap::SequenceMap(const std::string &a_rec_seq, const std::string &an_enz_acro){
    recognition_sequence_ = a_rec_seq;
    enzyme_acronyms_.push_back(an_enz_acro);
}

bool SequenceMap::operator<(const SequenceMap &rhs) const{
    return recognition_sequence_ < rhs.recognition_sequence_;
}

friend ostream& operator<<(ostream &out, const SequenceMap &another_map){
   if(another_map.enzyme_acronyms_.size() == 0){
       out << "Not Found";
    }else{
        for(size_t i = 0; i < another_map.enzyme_acronyms_.size(); i++){
            out << another_map.recognition_sequence_[i] << " ";
        }
    }
    out << "\n";
    return out;
}

void SequenceMap::Merge(const SequenceMap &other_sequence){
    if(recognition_sequence_ == other_sequence.recognition_sequence_){
        for(size_t i = 0, i < other_sequence.enzyme_acronyms_.size(); ++i){
            enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
        }
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