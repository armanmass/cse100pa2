#include "BitInputStream.hpp"
// TODO (final)
BitInputStream::BitInputStream(istream & i) : in(i) {
    nbit = 0;
    read = in.get();
}

bool BitInputStream::readBit() {
    if(nbit == 8){
        nbit = 0;
        read = in.get();
    }

    unsigned char temp = read >> (7-nbit);
    temp &= 1;
    nbit++;

    if(temp)
        return true;
    return false;  // TODO (final)
}
