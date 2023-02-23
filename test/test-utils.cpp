#include <qc-core/utils.hpp>

#include <gtest/gtest.h>

namespace
{
    using namespace qc::types;

    std::filesystem::path dirFile{"utils-test-dir"};

    void ensureDirExists()
    {
        std::filesystem::create_directory(dirFile);
    }
}

TEST(Utils, writeReadBinary)
{
    const qc::List<u8> srcData{7u, 3u, 1u};
    ASSERT_TRUE(qc::utils::writeFile("utils-test.tmp", srcData.data(), srcData.size()));

    const qc::Result<qc::List<u8>> result{qc::utils::readFile("utils-test.tmp")};
    ASSERT_TRUE(result);
    ASSERT_EQ(*result, srcData);
}

TEST(Utils, readWriteText)
{
    const std::string srcStr{"crazy..."};
    ASSERT_TRUE(qc::utils::writeTextFile("utils-test.tmp", srcStr));

    const qc::Result<std::string> result{qc::utils::readTextFile("utils-test.tmp")};
    ASSERT_TRUE(result);
    ASSERT_EQ(*result, srcStr);
}

TEST(Utils, readFail)
{
    ensureDirExists();

    ASSERT_FALSE(qc::utils::readFile("this-file-doesnt-exist"));
    ASSERT_FALSE(qc::utils::readTextFile("this-file-doesnt-exist"));
    ASSERT_FALSE(qc::utils::readFile(dirFile));
    ASSERT_FALSE(qc::utils::readTextFile(dirFile));
}

TEST(Result, writeFail)
{
    ensureDirExists();

    std::string str{"blah blah blah"};

    ASSERT_FALSE(qc::utils::writeFile(dirFile, str.c_str(), str.size()));
    ASSERT_FALSE(qc::utils::writeTextFile(dirFile, str));
}
