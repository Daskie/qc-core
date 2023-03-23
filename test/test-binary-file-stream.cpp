#include <qc-core/binary-file-stream.hpp>

#include <gtest/gtest.h>

#include <qc-core/matrix.hpp>
#include <qc-core/random.hpp>

using namespace qc::types;
using namespace qc::primitives;

const std::filesystem::path file{"qc-binary-file-stream-test.bin"};

TEST(BinaryFStream, general)
{
    {
        qc::BinaryOFStream ofs{file};
        ASSERT_TRUE(ofs);
        ofs << u8{1u} << u16{2u} << u32{3u} << u64{4u};
        ofs << dmat4{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};
        ASSERT_TRUE(ofs.close());
    }
    {
        qc::BinaryIFStream ifs{file};
        ASSERT_TRUE(ifs);
        {
            u8 v1{}; u16 v2{}; u32 v3{}; u64 v4{};
            ifs >> v1 >> v2 >> v3 >> v4;
            ASSERT_EQ(v1, 1u);
            ASSERT_EQ(v2, 2u);
            ASSERT_EQ(v3, 3u);
            ASSERT_EQ(v4, 4u);
        }
        {
            dmat4 v;
            ifs >> v;
            ASSERT_EQ(v, (dmat4{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0}));
        }
        ASSERT_TRUE(ifs.close());
    }
}

template <u64 n>
void testLarge()
{
    {
        qc::Random random{};

        qc::BinaryOFStream ofs{file};
        ASSERT_TRUE(ofs);
        for (u64 i{0u}; i < n; ++i)
        {
            ofs << random.next<u8>();
        }
        ASSERT_TRUE(ofs.close());

        random.reset();

        qc::BinaryIFStream ifs{file};
        ASSERT_TRUE(ifs);
        for (u64 i{0u}; i < n; ++i)
        {
            u8 v;
            ifs >> v;
            ASSERT_EQ(v, random.next<u8>());
        }
        ASSERT_TRUE(ifs.close());
    }

    {
        struct Large { u8 vals[n]; };

        qc::Random random{};

        qc::BinaryOFStream ofs{file};
        Large * large1{new Large};
        for (u64 i{0u}; i < n; ++i)
        {
            large1->vals[i] = random.next<u8>();
        }
        ASSERT_TRUE(ofs);
        ASSERT_TRUE(ofs << *large1);
        ASSERT_TRUE(ofs.close());

        random.reset();

        qc::BinaryIFStream ifs{file};
        Large * large2{new Large};
        ASSERT_TRUE(ifs);
        ASSERT_TRUE(ifs >> *large2);
        ASSERT_TRUE(ifs.close());
        for (u64 i{0u}; i < n; ++i)
        {
            ASSERT_EQ(large2->vals[i], random.next<u8>());
        }

        delete large1;
        delete large2;
    }
}

TEST(BinaryFStream, exactlyBufferSize)
{
    testLarge<qc::_BinaryStreamCommon::bufferSize>();
}

TEST(BinaryFStream, largerThanBufferSize)
{
    testLarge<qc::_BinaryStreamCommon::bufferSize / 2u * 5u>();
}

TEST(BinaryFStream, close)
{
    {
        qc::BinaryOFStream ofs{file};
        ASSERT_TRUE(ofs);
        ASSERT_TRUE(ofs.close());
        ASSERT_TRUE(ofs.close());
        ASSERT_TRUE(ofs);
    }
    {
        qc::BinaryIFStream ifs{file};
        ASSERT_TRUE(ifs);
        ASSERT_TRUE(ifs.close());
        ASSERT_TRUE(ifs.close());
        ASSERT_TRUE(ifs);
    }
    {
        qc::BinaryOFStream ofs{file};
        ASSERT_TRUE(ofs);
        ofs << 777;
        ASSERT_TRUE(ofs);
        ASSERT_TRUE(ofs.close());
        ASSERT_TRUE(ofs.close());
        ASSERT_TRUE(ofs);
    }
    {
        qc::BinaryIFStream ifs{file};
        ASSERT_TRUE(ifs);
        s32 v;
        ifs >> v;
        ASSERT_EQ(v, 777);
        ASSERT_TRUE(ifs);
        ASSERT_TRUE(ifs.close());
        ASSERT_TRUE(ifs.close());
        ASSERT_TRUE(ifs);
    }
}

TEST(BinaryFStream, multipleStreamsSameFile)
{
    qc::BinaryOFStream ofs1{file};
    ASSERT_TRUE(ofs1);
    qc::BinaryOFStream ofs2{file};
    ASSERT_EQ(bool(ofs2), qc::platform != qc::Platform::windows);
    ASSERT_EQ(ofs2.close(), qc::platform != qc::Platform::windows);

    ASSERT_TRUE(ofs1 << 123);
    ASSERT_TRUE(ofs1.close());

    qc::BinaryIFStream ifs1{file};
    ASSERT_TRUE(ifs1);
    qc::BinaryIFStream ifs2{file};
    ASSERT_TRUE(ifs2);

    s32 v1, v2;
    ASSERT_TRUE(ifs1 >> v1);
    ASSERT_EQ(v1, 123);
    ASSERT_TRUE(ifs2 >> v2);
    ASSERT_EQ(v2, 123);

    ASSERT_TRUE(ifs1.close());
    ASSERT_TRUE(ifs2.close());
}
