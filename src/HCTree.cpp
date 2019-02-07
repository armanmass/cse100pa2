#include <stack>
#include <queue>

#include "HCTree.hpp"

/**
 * Destructor for HCTree
 */
HCTree::~HCTree() {
    for(size_t i = 0; i < leaves.size(); i++) {
        if(leaves[i]) {
            delete leaves[i];
            leaves[i] = (HCNode*)0;
        }
    }
}

/** Use the Huffman algorithm to build a Huffman coding tree.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the tree,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs) {

    std::priority_queue<HCNode*> pq;

    for(size_t i = 0; i < freqs.size(); i++){
            if(freqs[i] > 0) {
                HCNode *n1 = new HCNode(freqs[i], (byte)i, 0, 0, 0);
                leaves[i] = n1;
                pq.push(n1);
            }
        }

        HCNode* p1;
        HCNode* p2;

        while(pq.size() > 1) {

            p1 = pq.pop();
            p2 = pq.pop();


            HCNode* merge = new HCNode(p1->count + p2->count, 
                                       p1->symbol, p1, p2, 0);
                                       
            p1->p = merge;
            p2->p = merge;

            pq.push(merge);
        }
}

/** Write to the given ostream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, ostream& out) const {
    HCNode* climb = leaves[(int)symbol];
        while(climb){
            if(climb->p->c0 == climb){
                out << 0;
            }else{
                out << 1;
            }
            climb = climb->p;
        }
}

/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the istream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
byte HCTree::decode(istream& in) const {
    HCNode* temp = root;
        int bit;

        while(1){
            in >> bit;

            if(in.eof())
                break;

            if(in){
                temp = temp->c1;
            }else{
                temp = temp->c0;
            }

            if(!temp->c1)
                return temp->symbol;
        }

        return 0;
}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const {
    // TODO (final)
}

/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
byte HCTree::decode(BitInputStream& in) const {
    return 0;  // TODO (final)
}

/**
 * Print the contents of a tree
 */
void HCTree::printTree() const {
    cout << "=== PRINT TREE BEGIN ===" << endl;
    printTreeHelper(root);
    cout << "=== PRINT TREE END =====" << endl;
}

/**
 * Recursive helper function for printTree
 */
void HCTree::printTreeHelper(HCNode * node, string indent) const {
    if (node == nullptr) {
        cout << indent << "nullptr" << endl;
        return;
    }

    cout << indent << *node << endl;
    if (node->c0 != nullptr || node->c1 != nullptr) {
        printTreeHelper(node->c0, indent + "  ");
        printTreeHelper(node->c1, indent + "  ");
    }
}
