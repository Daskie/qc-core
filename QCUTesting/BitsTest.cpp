#include "QCUTest.hpp"

#include "QCU/Bits.hpp"




namespace {



template <typename T>
void compileFunctionsUT() {
    T v(1);

    qcu::bits::rotateL(v, 0);

    qcu::bits::rotateR(v, 0);

    qcu::bits::interleave(v);

    qcu::bits::scramble(v);
}

void compileFunctions() {
    compileFunctionsUT<unsigned char>();
    compileFunctionsUT<unsigned short>();
    compileFunctionsUT<unsigned int>();
    compileFunctionsUT<unsigned long>();
    compileFunctionsUT<unsigned long long>();

    qcu::bits::spread<qcu::u08, qcu::u16>(-1);
    qcu::bits::spread<qcu::u08, qcu::u32>(-1);
    qcu::bits::spread<qcu::u08, qcu::u64>(-1);
    qcu::bits::spread<qcu::u16, qcu::u32>(-1);
    qcu::bits::spread<qcu::u16, qcu::u64>(-1);
    qcu::bits::spread<qcu::u32, qcu::u64>(-1);

    qcu::bits::repeat<qcu::u08, qcu::u16>(-1);
    qcu::bits::repeat<qcu::u08, qcu::u32>(-1);
    qcu::bits::repeat<qcu::u08, qcu::u64>(-1);
    qcu::bits::repeat<qcu::u16, qcu::u32>(-1);
    qcu::bits::repeat<qcu::u16, qcu::u64>(-1);
    qcu::bits::repeat<qcu::u32, qcu::u64>(-1);
}



}



void testBits() {
    compileFunctions();
}