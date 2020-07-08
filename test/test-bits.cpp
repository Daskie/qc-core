#include <CppUnitTest.h>

#include <qc-core/bits.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template <typename T>
static void compileFunctionsUT() {
    T v{1};

    qc::bits::interleave(v);

    qc::bits::scramble(v);
}

static void compileFunctions() {
    compileFunctionsUT<qc::u8>();
    compileFunctionsUT<qc::u16>();
    compileFunctionsUT<qc::u32>();
    compileFunctionsUT<qc::u64>();

    qc::bits::spread<qc::u8, qc::u16>(~qc::u8(0u));
    qc::bits::spread<qc::u8, qc::u32>(~qc::u8(0u));
    qc::bits::spread<qc::u8, qc::u64>(~qc::u8(0u));
    qc::bits::spread<qc::u16, qc::u32>(~qc::u16(0u));
    qc::bits::spread<qc::u16, qc::u64>(~qc::u16(0u));
    qc::bits::spread<qc::u32, qc::u64>(~qc::u32(0u));

    qc::bits::repeat<qc::u8, qc::u16>(~qc::u8(0u));
    qc::bits::repeat<qc::u8, qc::u32>(~qc::u8(0u));
    qc::bits::repeat<qc::u8, qc::u64>(~qc::u8(0u));
    qc::bits::repeat<qc::u16, qc::u32>(~qc::u16(0u));
    qc::bits::repeat<qc::u16, qc::u64>(~qc::u16(0u));
    qc::bits::repeat<qc::u32, qc::u64>(~qc::u32(0u));
}

TEST_CLASS(TestBits) {

    public:

    TEST_METHOD(testCompilation) {
        compileFunctions();
    }

};
