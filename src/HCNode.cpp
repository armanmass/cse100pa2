#include "HCNode.hpp"

/** Less-than comparison, so HCNodes will work in std::priority_queue
 *  We want small counts to have high priority.
 *  And we want to break ties deterministically.
 */
bool HCNode::operator<(const HCNode& other) {
    if(other.count < this->count)
            return true;

    if(other.count == this->count) {
        if(this->symbol > other.symbol)
            return true;
    }    
    
    return false;
}
