// UPDATED: Tests for final part of PA2

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

using namespace std;

TEST_CASE("Bitwise output -> input") {
    // Write a sequence of bits
    ostringstream oss;
    BitOutputStream bos(oss);
    const vector<bool> message {1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1};
    for (unsigned int i = 0; i < message.size(); i++) {
        bos.writeBit(message[i]);
    }
    bos.flush();
    string transmitted = oss.str();
    cout << transmitted << endl;
    CHECK(transmitted.size() == 2);

    // Read a sequence of bits
    istringstream iss(transmitted);
    BitInputStream bis(iss);
    vector<bool> results;
    for (unsigned int i = 0; i < message.size(); i++) {
        results.push_back(bis.readBit());
    }
    CHECK(results == message);
}

TEST_CASE("Multi-byte message: encode followed by decode") {
    HCTree tree;
    vector<int> freqs(256, 0);
    freqs[120] = 1000;
    freqs[121] = 500;
    freqs[200] = 250;
    tree.build(freqs);

    //tree.printTree();

    ostringstream oss;
    BitOutputStream bos(oss);

    SECTION("encode -> decode (encoded message length <= 8 bits)") {
        const vector<byte> message {120, 120, 121, 200, 200};

        // Compress via encode + flush
        for (byte b : message) {
            tree.encode(b, bos);
        }
        bos.flush();
        string compressed_str = oss.str();
        REQUIRE(compressed_str.size() == 1);

        // Uncompress via decode
        istringstream iss(compressed_str);
        BitInputStream bis(iss);
        vector<byte> results;
        for (unsigned int i = 0; i < message.size(); i++) {
            results.push_back(tree.decode(bis));
        }

        REQUIRE(results == message);
    }

    SECTION("encode -> decode (encoded message length > 8 bits)") {
        const vector<byte> message {120, 120, 121, 200, 200, 120, 121, 200, 200, 200};

        // Compress via encode + flush
        for (byte b : message) {
            tree.encode(b, bos);
        }
        bos.flush();
        string compressed_str = oss.str();
        REQUIRE(compressed_str.size() == 3);

        // Uncompress via decode
        istringstream iss(compressed_str);
        BitInputStream bis(iss);
        vector<byte> results;
        for (unsigned int i = 0; i < message.size(); i++) {
            results.push_back(tree.decode(bis));
        }

        REQUIRE(results == message);
    }
}
