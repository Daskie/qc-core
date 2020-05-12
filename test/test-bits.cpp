#include <qc-core/bits.hpp>

template <typename T>
static void compileFunctionsUT() {
    T v(1);

    qc::core::bits::interleave(v);

    qc::core::bits::scramble(v);
}

static void compileFunctions() {
    compileFunctionsUT<qc::core::u08>();
    compileFunctionsUT<qc::core::u16>();
    compileFunctionsUT<qc::core::u32>();
    compileFunctionsUT<qc::core::u64>();

    qc::core::bits::spread<qc::core::u08, qc::core::u16>(~qc::core::u08(0u));
    qc::core::bits::spread<qc::core::u08, qc::core::u32>(~qc::core::u08(0u));
    qc::core::bits::spread<qc::core::u08, qc::core::u64>(~qc::core::u08(0u));
    qc::core::bits::spread<qc::core::u16, qc::core::u32>(~qc::core::u16(0u));
    qc::core::bits::spread<qc::core::u16, qc::core::u64>(~qc::core::u16(0u));
    qc::core::bits::spread<qc::core::u32, qc::core::u64>(~qc::core::u32(0u));

    qc::core::bits::repeat<qc::core::u08, qc::core::u16>(~qc::core::u08(0u));
    qc::core::bits::repeat<qc::core::u08, qc::core::u32>(~qc::core::u08(0u));
    qc::core::bits::repeat<qc::core::u08, qc::core::u64>(~qc::core::u08(0u));
    qc::core::bits::repeat<qc::core::u16, qc::core::u32>(~qc::core::u16(0u));
    qc::core::bits::repeat<qc::core::u16, qc::core::u64>(~qc::core::u16(0u));
    qc::core::bits::repeat<qc::core::u32, qc::core::u64>(~qc::core::u32(0u));
}

void testBits() {
    compileFunctions();
}
