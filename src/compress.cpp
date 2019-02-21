#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitOutputStream.hpp"

using namespace std;

void print_usage(char ** argv) {
    cout << "Usage:" << endl;
    cout << "  " << argv[0] << " INFILE OUTFILE [-b]" << endl;
    cout << "Command-line flags:" << endl;
    cout << "  -b: switch to bitwise mode" << endl;
}

/**
 * Reads infile, constructs a Huffman coding tree based on its contents,
 * and produces a compressed version in outfile.
 * For debugging purposes, uses ASCII '0' and '1' rather than bitwise I/O.
 */
void compressAscii(const string & infile, const string & outfile) {
    ifstream ifs;
    ofstream ofs;
    ifs.open(infile, ios::binary);
    ofs.open(outfile, ios::binary);
    ifs >> std::noskipws;
    
    HCTree tree;
    vector<int> freqs(256, 0);
    byte c;

    if(ifs.peek() == -1){
        for(size_t i = 0; i < freqs.size(); i++)
            ofs << 0 << endl;
        ifs.close();
        ofs.close();
        return;
    }

    while(ifs.peek() != -1){
        ifs >> c;
        freqs[(int)c]++;
    }

    tree.build(freqs);
    //tree.printTree();
    for(size_t i = 0; i < freqs.size(); i++)
        ofs << freqs[i] << endl;

    ifs.clear();
    ifs.seekg(0, ios::beg);

    while(ifs.peek() != -1){
        ifs >> c;
        tree.encode(c, ofs);
    }

    cerr << "TODO: compress '" << infile << "' -> '"
        << outfile << "' here (ASCII)" << endl;
    
    ifs.close();
    ofs.close();
}

/**
 * Reads infile, constructs a Huffman coding tree based on its contents,
 * and produces a compressed version in outfile.
 * Uses bitwise I/O.
 */
void compressBitwise(const string & infile, const string & outfile) {
    ifstream ifs;
    ofstream ofs;
    ifs.open(infile, ios::binary);
    ofs.open(outfile, ios::binary);
    ifs >> std::noskipws;
    BitOutputStream bos(ofs);
    
    HCTree tree;
    vector<int> freqs(256, 0);
    byte c;

    if(ifs.peek() == -1){
        for(size_t i = 0; i < 1024; i++)
            ofs << (unsigned char)0;
        ifs.close();
        ofs.close();
        return;
    }

    while(ifs.peek() != -1){
        ifs >> c;
        freqs[(int)c]++;
    }

    tree.build(freqs);
    //tree.printTree();
    for(size_t i = 0; i < freqs.size(); i++){
        int convert = freqs[i];
        for(int j = 0; j < 4; j++){
            unsigned char temp = (unsigned char)(convert >> (8*j));
            ofs << temp;
        }
    }

    ifs.clear();
    ifs.seekg(0, ios::beg);

    while(ifs.peek() != -1){
        ifs >> c;
        tree.encode(c, bos);
    }
    bos.flush();

    cerr << "TODO: compress '" << infile << "' -> '"
        << outfile << "' here (bitwise)" << endl;
    
    ifs.close();
    ofs.close();
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
        compressBitwise(infile, outfile);
    } else {
        compressAscii(infile, outfile);
    }

    return 0;
}
