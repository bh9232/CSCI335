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
    SequenceMap(const std::string &a_rec_seq, const std::string &an_enz_acro);
    bool operator<(const SequenceMap &rhs) const;
    friend ostream& operator<<(ostream &out, const SequenceMap &another_map);
    void Merge(const SequenceMap &other_sequence);
    bool isEmpty() const;
    std::string getSequence() const;
    std::vector<std::string> getAcronym() const; 
    
    private:
    std::string recognition_sequence_;
    std::vector<std::string> enzyme_acronyms_;
};