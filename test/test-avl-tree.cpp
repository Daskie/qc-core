#include <qc-core/avl-tree.hpp>
#include <qc-core/list.hpp>
#include <qc-core/random.hpp>

#include <string_view>

#include <gtest/gtest.h>

using namespace std::string_literals;
using namespace std::string_view_literals;
using namespace qc::types;
using namespace qc::primitives;

class qc::_internal::AvlTreeFriend
{
    template <typename T> using _Node = typename AvlTree<T>::_Node;

  public:

    template <UnsignedIntegral T>
    static std::string genString(const AvlTree<T> & tree)
    {
        const qc::List<std::string> lines{_genString<T>(tree._root)};
        u64 totalLength{!lines.empty()};
        for (const std::string & line : lines)
        {
            totalLength += line.length() + 1;
        }

        std::string string{};
        string.reserve(totalLength);
        if (!lines.empty())
        {
            string.push_back('\n');
        }
        for (const std::string & line : lines)
        {
            string += line;
            string += '\n';
        }
        return string;
    }

    template <UnsignedIntegral T>
    static bool validateOrder(const AvlTree<T> & tree)
    {
        return !tree._root || _validateOrder<T>(tree._root);
    }

    template <UnsignedIntegral T>
    static bool validateBalance(const AvlTree<T> & tree)
    {
        u64 rootHeight{0u};
        return !tree._root || _validateBalance<T>(tree._root, rootHeight);
    }

  private:

    static int _detLineAnchor(const std::string & line, const bool side)
    {
        int start{0};
        while (!std::isdigit(line[u64(start)])) ++start;
        int end{start + 1};
        while (end < int(line.size()) && std::isdigit(line[u64(end)])) ++end;
        return start + (end - start - side) / 2;
    }

    static void _shiftLinesRight(qc::List<std::string> & lines, const int n)
    {
        for (std::string & line : lines)
        {
            line.insert(0u, u64(n), ' ');
        }
    }

    template <UnsignedIntegral T>
    static qc::List<std::string> _genString(const _Node<T> * const node)
    {
        if (!node)
        {
            return {};
        }

        if (!node->left && !node->right)
        {
            return {std::to_string(node->v)};
        }

        const std::string valStr{std::to_string(node->v)};
        const int valStrLength{int(valStr.length())};
        qc::List<std::string> leftLines{_genString<T>(node->left)};
        qc::List<std::string> rightLines{_genString<T>(node->right)};
        const bool isLeft{!leftLines.empty()};
        const bool isRight{!rightLines.empty()};
        int leftBlockWidth{0};
        for (const std::string & line : leftLines)
        {
            qc::maxify(leftBlockWidth, int(line.size()));
        }
        int leftHeadOffset{isLeft ? _detLineAnchor(leftLines.front(), false) : 0};
        int rightHeadOffset{isRight ? _detLineAnchor(rightLines.front(), true) : 0};

        //--- Calculate layout ---

        int leftBlockPos{0}; // Position of first character in left block
        int rightBlockPos{0}; // Position of first character in right block
        int leftHeadPos{leftHeadOffset}; // Position of "head" of left block
        int rightHeadPos{rightHeadOffset}; // Position of "head" of right block
        int valPos; // Position of first character of value
        if (isLeft && isRight)
        {
            int minGap{std::numeric_limits<int>::max()};
            for (int i{0}; i < int(leftLines.size()) && i < int(rightLines.size()); ++i)
            {
                qc::minify(minGap, leftBlockWidth - int(leftLines[u64(i)].size()) + int(rightLines[u64(i)].find_first_not_of(' ')));
            }
            rightBlockPos = leftBlockWidth - minGap + 3;

            leftHeadPos = leftBlockPos + leftHeadOffset;
            rightHeadPos = rightBlockPos + rightHeadOffset;
            if ((rightHeadPos - leftHeadPos - 1) % 2 != valStrLength % 2)
            {
                ++rightBlockPos;
                ++rightHeadPos;
            }

            valPos = (leftHeadPos + rightHeadPos) / 2 - (valStrLength - 1) / 2;
        }
        else if (isLeft)
        {
            valPos = leftHeadPos + 2 - (valStrLength - 1) / 2;
        }
        else
        {
            valPos = rightHeadPos - 2 - valStrLength / 2;
        }

        if (valPos < 0)
        {
            leftBlockPos -= valPos;
            rightBlockPos -= valPos;
            leftHeadPos -= valPos;
            rightHeadPos -= valPos;
            valPos = 0;
        }

        qc::List<std::string> lines{};
        lines.reserve(2u + qc::max(leftLines.size(), rightLines.size()));

        //--- Add value line ---

        const int leftDashN{qc::max(valPos - leftHeadPos - 3, 0)};
        const int rightDashN{qc::max(rightHeadPos - (valPos + valStrLength) - 2, 0)};
        const int valLineLength{valPos + valStrLength + bool(rightDashN) + rightDashN};
        std::string & valLine{lines.push(u64(valLineLength), ' ')};
        if (leftDashN) std::fill_n(valLine.begin() + valPos - 1 - leftDashN, u64(leftDashN), '_');
        std::copy(valStr.cbegin(), valStr.cend(), valLine.begin() + valPos);
        if (rightDashN) std::fill_n(valLine.begin() + valPos + valStrLength + 1, u64(rightDashN), '_');

        //--- Add slash line ---

        const int slashLineLength{isRight ? rightHeadPos : leftHeadPos + 2};
        std::string & slashLine{lines.push(u64(slashLineLength), ' ')};
        if (isLeft) slashLine[u64(leftHeadPos + 1)] = '/';
        if (isRight) slashLine.back() = '\\';

        //--- Add combined left/right lines ---

        int leftLineI{0};
        int rightLineI{0};

        // Add lines for both left and right
        for (; leftLineI < int(leftLines.size()) && rightLineI < int(rightLines.size()); ++leftLineI, ++rightLineI)
        {
            lines.push(std::move(leftLines[u64(leftLineI)]));
            std::string & line{lines.back()};
            const std::string & rightLine{rightLines[u64(rightLineI)]};
            const u64 lineLength{u64(rightBlockPos) + rightLine.size()};
            line.reserve(lineLength);
            line.insert(line.begin(), u64(leftBlockPos), ' ');
            line.resize(lineLength, ' ');
            const u64 rightContentOffset{rightLine.find_first_not_of(' ')};
            std::copy(rightLine.cbegin() + s64(rightContentOffset), rightLine.cend(), line.begin() + rightBlockPos + s64(rightContentOffset));
        }

        // Add leftover left lines
        for (; leftLineI < int(leftLines.size()); ++leftLineI)
        {
            lines.push(std::move(leftLines[u64(leftLineI)]));
            std::string & line{lines.back()};
            line.insert(line.begin(), u64(leftBlockPos), ' ');
        }

        // Add leftover right lines
        for (; rightLineI < int(rightLines.size()); ++rightLineI)
        {
            lines.push(std::move(rightLines[u64(rightLineI)]));
            std::string & line{lines.back()};
            line.insert(line.begin(), u64(rightBlockPos), ' ');
        }

        return lines;
    }

    template <UnsignedIntegral T>
    static bool _validateOrder(const _Node<T> * const node)
    {
        return
            (!node->left || (node->left->v <= node->v && _validateOrder<T>(node->left))) &&
            (!node->right || (node->right->v >= node->v && _validateOrder<T>(node->right)));
    }

    template <UnsignedIntegral T>
    static bool _validateBalance(const _Node<T> * const node, u64 & retHeight)
    {
        u64 leftHeight{0u};
        if (node->left && !_validateBalance<T>(node->left, leftHeight))
        {
            return false;
        }

        u64 rightHeight{0u};
        if (node->right && !_validateBalance<T>(node->right, rightHeight))
        {
            return false;
        }

        const u64 minHeight{qc::min(leftHeight, rightHeight)};
        const u64 maxHeight{qc::max(leftHeight, rightHeight)};
        if (maxHeight - minHeight > 1u)
        {
            return false;
        }

        retHeight = maxHeight + 1u;
        return true;
    }
};

namespace
{
    using _TreeFriend = qc::_internal::AvlTreeFriend;

    template <UnsignedIntegral T> bool _treeMatches(const qc::AvlTree<T> & tree, const std::string_view expectedStr)
    {
        const std::string treeStr{_TreeFriend::genString(tree)};
        if (treeStr != expectedStr)
        {
            std::cout << "Tree mismatch!\nExpected:" << expectedStr << "Got:" << treeStr << std::endl;
            return false;
        }
        else
        {
            return true;
        }
    }
}

TEST(AvlTree, rotateRight)
{
    qc::AvlTree<u32> tree{};
    ASSERT_EQ(tree.size(), 0u);

    tree.insert(10u);
    ASSERT_EQ(tree.size(), 1u);
    std::string_view expected{R"(
10
)"sv};
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(9u);
    ASSERT_EQ(tree.size(), 2u);
    expected = R"(
  10
 /
9
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(8u);
    ASSERT_EQ(tree.size(), 3u);
    expected = R"(
  9
 / \
8   10
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(7u);
    ASSERT_EQ(tree.size(), 4u);
    expected = R"(
    9
   / \
  8   10
 /
7
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(6u);
    ASSERT_EQ(tree.size(), 5u);
    expected = R"(
    9
   / \
  7   10
 / \
6   8
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(5u);
    ASSERT_EQ(tree.size(), 6u);
    expected = R"(
    7
   / \
  6   9
 /   / \
5   8   10
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(4u);
    ASSERT_EQ(tree.size(), 7u);
    expected = R"(
    _ 7 _
   /     \
  5       9
 / \     / \
4   6   8   10
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));
}

TEST(AvlTree, rotateLeft)
{
    qc::AvlTree<u32> tree{};
    ASSERT_EQ(tree.size(), 0u);

    tree.insert(10u);
    ASSERT_EQ(tree.size(), 1u);
    std::string_view expected{R"(
10
)"sv};
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(11u);
    ASSERT_EQ(tree.size(), 2u);
    expected = R"(
10
  \
   11
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(12u);
    ASSERT_EQ(tree.size(), 3u);
    expected = R"(
   11
  /  \
10    12
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(13u);
    ASSERT_EQ(tree.size(), 4u);
    expected = R"(
   11
  /  \
10    12
        \
         13
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(14u);
    ASSERT_EQ(tree.size(), 5u);
    expected = R"(
   11
  /  \
10    13
     /  \
   12    14
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(15u);
    ASSERT_EQ(tree.size(), 6u);
    expected = R"(
      13
     /  \
   11    14
  /  \     \
10    12    15
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(16u);
    ASSERT_EQ(tree.size(), 7u);
    expected = R"(
      __ 13 __
     /        \
   11          15
  /  \        /  \
10    12    14    16
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));
}

TEST(AvlTree, rotateLeftRight)
{
    qc::AvlTree<u32> tree{};
    ASSERT_EQ(tree.size(), 0u);

    tree.insert(10u);
    ASSERT_EQ(tree.size(), 1u);
    std::string_view expected{R"(
10
)"sv};
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(2u);
    ASSERT_EQ(tree.size(), 2u);
    expected = R"(
  10
 /
2
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(9u);
    ASSERT_EQ(tree.size(), 3u);
    expected = R"(
  9
 / \
2   10
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(8u);
    ASSERT_EQ(tree.size(), 4u);
    expected = R"(
  9
 / \
2   10
 \
  8
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(5u);
    ASSERT_EQ(tree.size(), 5u);
    expected = R"(
    9
   / \
  5   10
 / \
2   8
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(6u);
    ASSERT_EQ(tree.size(), 6u);
    expected = R"(
    8
   / \
  5   9
 / \   \
2   6   10
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(3u);
    ASSERT_EQ(tree.size(), 7u);
    expected = R"(
    8
   / \
  5   9
 / \   \
2   6   10
 \
  3
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(1u);
    ASSERT_EQ(tree.size(), 8u);
    expected = R"(
      8
     / \
    5   9
   / \   \
  2   6   10
 / \
1   3
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(4u);
    ASSERT_EQ(tree.size(), 9u);
    expected = R"(
      8
     / \
    3   9
   / \   \
  2   5   10
 /   / \
1   4   6
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(7u);
    ASSERT_EQ(tree.size(), 10u);
    expected = R"(
      _ 5 _
     /     \
    3       8
   / \     / \
  2   4   6   9
 /         \   \
1           7   10
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));
}

TEST(AvlTree, rotateRightLeft)
{
    qc::AvlTree<u32> tree{};
    ASSERT_EQ(tree.size(), 0u);

    tree.insert(10u);
    ASSERT_EQ(tree.size(), 1u);
    std::string_view expected{R"(
10
)"sv};
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(18u);
    ASSERT_EQ(tree.size(), 2u);
    expected = R"(
10
  \
   18
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(11u);
    ASSERT_EQ(tree.size(), 3u);
    expected = R"(
   11
  /  \
10    18
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(12u);
    ASSERT_EQ(tree.size(), 4u);
    expected = R"(
   11
  /  \
10    18
     /
   12
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(15u);
    ASSERT_EQ(tree.size(), 5u);
    expected = R"(
   11
  /  \
10    15
     /  \
   12    18
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(14u);
    ASSERT_EQ(tree.size(), 6u);
    expected = R"(
      12
     /  \
   11    15
  /     /  \
10    14    18
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(17u);
    ASSERT_EQ(tree.size(), 7u);
    expected = R"(
      12
     /  \
   11    15
  /     /  \
10    14    18
           /
         17
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(19u);
    ASSERT_EQ(tree.size(), 8u);
    expected = R"(
      12
     /  \
   11    15
  /     /  \
10    14    18
           /  \
         17    19
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(16u);
    ASSERT_EQ(tree.size(), 9u);
    expected = R"(
      12
     /  \
   11    17
  /     /  \
10    15    18
     /  \     \
   14    16    19
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));

    tree.insert(13u);
    ASSERT_EQ(tree.size(), 10u);
    expected = R"(
         __ 15 __
        /        \
      12          17
     /  \        /  \
   11    14    16    18
  /     /              \
10    13                19
)"sv;
    ASSERT_TRUE(_treeMatches(tree, expected));
}

/*
TEST(AvlTree, stress)
{
    qc::AvlTree<u32> qcTree{};
    std::multiset<u32> stdTree{};
    qc::Random random{};

    const auto expand{[&]()
    {
        const u32 v{random.next<u32>() % 1024u};
        stdTree.insert(v);
        qcTree.insert(v);
    }};

    const auto contract{[&]()
    {
        if (stdTree.empty())
        {
            return;
        }

        u32 v{random.next<u32>() % 1024u};
        auto stdIt{stdTree.lower_bound(v)};
        if (stdIt == stdTree.end())
        {
            --stdIt;
            v = *stdIt;
        }

        const auto qcIt{qcTree.find(v)};
        ASSERT_NE(qcTree.end(), qcIt);

        stdTree.erase(stdIt);
        qcTree.erase(qcIt);
    }};

    for (u64 iteration{0}; iteration < 100u; ++iteration)
    {
        // Expand to 1024 elements
        while (stdTree.size() < 1024u)
        {
            // Grows by 0.25 elements on average
            if (random.next() % 8u < 3u)
            {
                contract();
            }
            else
            {
                expand();
            }

            ASSERT_EQ(stdTree.size(), qcTree.size());

            ASSERT_TRUE(_TreeFriend::validateOrder(qcTree));
            ASSERT_TRUE(_TreeFriend::validateBalance(qcTree));
        }

        // Contract to 0 elements
        while (!stdTree.empty())
        {
            // Shrinks by 0.25 elements on average
            if (random.next() % 8u < 5u)
            {
                contract();
            }
            else
            {
                expand();
            }

            ASSERT_EQ(stdTree.size(), qcTree.size());

            ASSERT_TRUE(_TreeFriend::validateOrder(qcTree));
            ASSERT_TRUE(_TreeFriend::validateBalance(qcTree));
        }
    }
}
 */
