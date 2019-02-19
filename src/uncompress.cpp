#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>
#include <sstream>

#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitInputStream.hpp"

using namespace std;

void print_usage(char ** argv) {
    cout << "Usage:" << endl;
    cout << "  " << argv[0] << " INFILE OUTFILE [-b]" << endl;
    cout << "Command-line flags:" << endl;
    cout << "  -b: switch to bitwise mode" << endl;
}

/**
 * Reads infile, constructs a Huffman coding tree based on its header,
 * and produces an uncompressed version in outfile.
 * For debugging purposes, uses ASCII '0' and '1' rather than bitwise I/O.
 */
void uncompressAscii(const string & infile, const string & outfile) {
    ifstream ifs;
    ofstream ofs;
    ifs.open(infile, ios::binary);
    ofs.open(outfile, ios::binary);

    HCTree tree;
    vector<int> freqs(256, 0);
    int count;
  
    if(ifs.peek() == -1){
        ifs.close();
        ofs.close();
        return;
    }

    int first = 0;
    int next = 0;
    int total = 0;
    int num = -1;

    while(first == total){
        if(ifs.peek() == -1) break;
        if(!first){
            ifs >> first;
            total += first;
            num++;
        }else{
            ifs >> next;
        }       
        total += next;
    }

    if(first == total){
        for(int i = 0; i < first; i++)
            ofs << (unsigned char)num;
        ifs.close();
        ofs.close();
        return;
    }

    ifs.clear();
    ifs.seekg(0, ios::beg);

    for(size_t i = 0; i < freqs.size(); i++){
        ifs >> count;
        freqs[i] = count;
    }
        
    tree.build(freqs);

    std::string bitString;
    ifs >> bitString;
    std::istringstream iss(bitString);

    while(1){
        if(iss.peek() == -1) break;
        ofs << (unsigned char)tree.decode(iss);
    }

    ifs.close();
    ofs.close();
}

/**
 * Reads infile, constructs a Huffman coding tree based on its header,
 * and produces an uncompressed version in outfile.
 * Uses bitwise I/O.
 */
void uncompressBitwise(const string & infile, const string & outfile) {
    ifstream ifs;
    ofstream ofs;
    ifs.open(infile, ios::binary);
    ofs.open(outfile, ios::binary);

    HCTree tree;
    vector<int> freqs(256, 0);
    int count;
  
    if(ifs.peek() == -1){
        ifs.close();
        ofs.close();
        return;
    }

    int first = 0;
    int next = 0;
    int total = 0;
    int num = -1;

    while(first == total){
        if(ifs.peek() == -1) break;
        if(!first){
            ifs >> first;
            total += first;
            num++;
        }else{
            ifs >> next;
        }       
        total += next;
    }

    if(first == total){
        for(int i = 0; i < first; i++)
            ofs << (unsigned char)num;
        ifs.close();
        ofs.close();
        return;
    }

    ifs.clear();
    ifs.seekg(0, ios::beg);

    for(size_t i = 0; i < freqs.size(); i++){
        ifs >> count;
        freqs[i] = count;
    }
        
    tree.build(freqs);

    std::string bitString;
    ifs >> bitString;
    std::istringstream iss(bitString);

    while(1){
        if(iss.peek() == -1) break;
        ofs << (unsigned char)tree.decode(iss);
    }

    ifs.close();
    ofs.close();
    cerr << "TODO: uncompress '" << infile << "' -> '"
        << outfile << "' here (bitwise)" << endl;
}

int main(int argc, char ** argv) {
    string infile = "";
    string outfile = "";
    bool bitwise = false;
    for (int i = 1; i < argc; i++) {
        string currentArg = argv[i];
        if (currentArg == "-b") {
            bitwise = true;
        } else if (infile == "") {
            infile = currentArg;
        } else {
            outfile = currentArg;
        }
    }

    if (infile == "" || outfile == "") {
        cout << "ERROR: Must provide input and output files" << endl;
        print_usage(argv);
        return 1;
    }

    if (bitwise) {
        uncompressBitwise(infile, outfile);
    } else {
        uncompressAscii(infile, outfile);
    }

    return 0;
}
