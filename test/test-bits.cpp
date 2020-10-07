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

    TEST_METHOD(testCountLZero) {
        Assert::AreEqual(8, std::countl_zero(qc::u8(0)));
        Assert::AreEqual(16, std::countl_zero(qc::u16(0)));
        Assert::AreEqual(32, std::countl_zero(qc::u32(0)));
        Assert::AreEqual(64, std::countl_zero(qc::u64(0)));
        Assert::AreEqual(0, std::countl_zero(qc::u8(-1)));
        Assert::AreEqual(0, std::countl_zero(qc::u16(-1)));
        Assert::AreEqual(0, std::countl_zero(qc::u32(-1)));
        Assert::AreEqual(0, std::countl_zero(qc::u64(-1)));

        int zeroes{63};
        for (qc::u64 v{1u}; v; v <<= 1) {
            Assert::AreEqual(zeroes, std::countl_zero(v));
            --zeroes;
        }
    }

};
