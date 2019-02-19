#include "BitOutputStream.hpp"

// TODO (final)
BitOutputStream::BitOutputStream(ostream & o) : out(o) {
    nbit = 0;
    write = 0;
}

void BitOutputStream::writeBit(bool bit) {
    write <<= 1;
    write |= bit;
    nbit++;

    if(nbit == 8)
        BitOutputStream::flush();
}

void BitOutputStream::flush() {
    if(!nbit)
        return;
    if(nbit < 8){
        write <<= (8-nbit);
        out.put(write);
    }else{  
        out.put(write);
    }
    nbit = 0;
    write = 0;
}