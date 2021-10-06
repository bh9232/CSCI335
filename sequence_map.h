#include <iostream>
#include <string>
#include <vector>

class SequenceMap{
public:
    //constructor
    SequenceMap(const std::string &rec_seq, const std::string &enz_acro);
    //defualt big-five
    SequenceMap(const SequenceMap &rhs) = default;
    SequenceMap &operator=(const SequenceMap &rhs) = default;
    SequenceMap(SequenceMap &&rhs) = default;
    SequenceMap &operator=(SequenceMap &&rhs) = default;
    ~SequenceMap() = default;
    
private:
    std::string recognition_sequence_;
    std::vector<std::string> enzyme_acronyms_;
}