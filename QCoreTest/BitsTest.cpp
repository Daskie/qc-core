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
    compileFunctionsUT<qc::u08>();
    compileFunctionsUT<qc::u16>();
    compileFunctionsUT<qc::u32>();
    compileFunctionsUT<qc::u64>();

    qc::bits::spread<qc::u08, qc::u16>(~qc::u08(0u));
    qc::bits::spread<qc::u08, qc::u32>(~qc::u08(0u));
    qc::bits::spread<qc::u08, qc::u64>(~qc::u08(0u));
    qc::bits::spread<qc::u16, qc::u32>(~qc::u16(0u));
    qc::bits::spread<qc::u16, qc::u64>(~qc::u16(0u));
    qc::bits::spread<qc::u32, qc::u64>(~qc::u32(0u));

    qc::bits::repeat<qc::u08, qc::u16>(~qc::u08(0u));
    qc::bits::repeat<qc::u08, qc::u32>(~qc::u08(0u));
    qc::bits::repeat<qc::u08, qc::u64>(~qc::u08(0u));
    qc::bits::repeat<qc::u16, qc::u32>(~qc::u16(0u));
    qc::bits::repeat<qc::u16, qc::u64>(~qc::u16(0u));
    qc::bits::repeat<qc::u32, qc::u64>(~qc::u32(0u));
}



}



void testBits() {
    compileFunctions();
}