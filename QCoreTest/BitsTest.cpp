#include "QCoreTest.hpp"

#include "QCore/Bits.hpp"




namespace {



template <typename T>
void compileFunctionsUT() {
    T v(1);

    qc::bits::rotateL(v, 0);

    qc::bits::rotateR(v, 0);

    qc::bits::interleave(v);

    qc::bits::scramble(v);
}

void compileFunctions() {
    compileFunctionsUT<unsigned char>();
    compileFunctionsUT<unsigned short>();
    compileFunctionsUT<unsigned int>();
    compileFunctionsUT<unsigned long>();
    compileFunctionsUT<unsigned long long>();

    qc::bits::spread<qc::u08, qc::u16>(-1);
    qc::bits::spread<qc::u08, qc::u32>(-1);
    qc::bits::spread<qc::u08, qc::u64>(-1);
    qc::bits::spread<qc::u16, qc::u32>(-1);
    qc::bits::spread<qc::u16, qc::u64>(-1);
    qc::bits::spread<qc::u32, qc::u64>(-1);

    qc::bits::repeat<qc::u08, qc::u16>(-1);
    qc::bits::repeat<qc::u08, qc::u32>(-1);
    qc::bits::repeat<qc::u08, qc::u64>(-1);
    qc::bits::repeat<qc::u16, qc::u32>(-1);
    qc::bits::repeat<qc::u16, qc::u64>(-1);
    qc::bits::repeat<qc::u32, qc::u64>(-1);
}



}



void testBits() {
    compileFunctions();
}