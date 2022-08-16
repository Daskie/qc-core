#include <qc-core/avl-tree.hpp>

#include <set>
#include <vector>

#include <gtest/gtest.h>

#include <qc-core/random.hpp>

using namespace std::string_literals;
using namespace qc::types;

class qc::_internal::AvlTreeFriend
{
    template <typename T> using _Node = typename AvlTree<T>::_Node;

  // TODO: Fix access specifier alignment elsewhere
  public:

    template <UnsignedIntegral T>
    static std::string genString(const AvlTree<T> & tree)
    {
        const std::vector<std::string> lines{_genString<T>(tree._root)};
        size_t totalLength{!lines.empty()};
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
        size_t rootHeight{0u};
        return !tree._root || _validateBalance<T>(tree._root, rootHeight);
    }

  private:

    static int _detLineAnchor(const std::string & line, const bool side)
    {
        int start{0};
        while (!std::isdigit(line[start])) ++start;
        int end{start + 1};
        while (end < line.size() && std::isdigit(line[end])) ++end;
        return start + (end - start - side) / 2;
    }

    static void _shiftLinesRight(std::vector<std::string> & lines, const int n)
    {
        for (std::string & line : lines)
        {
            line.insert(0u, n, ' ');
        }
    }

    template <UnsignedIntegral T>
    static std::vector<std::string> _genString(const _Node<T> * const node)
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
        std::vector<std::string> leftLines{_genString<T>(node->left)};
        std::vector<std::string> rightLines{_genString<T>(node->right)};
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
            for (int i{0}; i < leftLines.size() && i < rightLines.size(); ++i)
            {
                qc::minify(minGap, leftBlockWidth - int(leftLines[i].size()) + int(rightLines[i].find_first_not_of(' ')));
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

        std::vector<std::string> lines{};
        lines.reserve(2u + qc::max(leftLines.size(), rightLines.size()));

        //--- Add value line ---

        const int leftDashCount{qc::max(valPos - leftHeadPos - 3, 0)};
        const int rightDashCount{qc::max(rightHeadPos - (valPos + valStrLength) - 2, 0)};
        const int valLineLength{valPos + valStrLength + bool(rightDashCount) + rightDashCount};
        std::string & valLine{lines.emplace_back(valLineLength, ' ')};
        if (leftDashCount) std::fill_n(valLine.begin() + valPos - 1 - leftDashCount, leftDashCount, '_');
        std::copy(valStr.cbegin(), valStr.cend(), valLine.begin() + valPos);
        if (rightDashCount) std::fill_n(valLine.begin() + valPos + valStrLength + 1, rightDashCount, '_');

        //--- Add slash line ---

        const int slashLineLength{isRight ? rightHeadPos : leftHeadPos + 2};
        std::string & slashLine{lines.emplace_back(slashLineLength, ' ')};
        if (isLeft) slashLine[leftHeadPos + 1] = '/';
        if (isRight) slashLine.back() = '\\';

        //--- Add combined left/right lines ---

        int leftLineI{0};
        int rightLineI{0};

        // Add lines for both left and right
        for (; leftLineI < leftLines.size() && rightLineI < rightLines.size(); ++leftLineI, ++rightLineI)
        {
            lines.push_back(std::move(leftLines[leftLineI]));
            std::string & line{lines.back()};
            const std::string & rightLine{rightLines[rightLineI]};
            const size_t lineLength{rightBlockPos + rightLine.size()};
            line.reserve(lineLength);
            line.insert(line.begin(), leftBlockPos, ' ');
            line.resize(lineLength, ' ');
            const size_t rightContentOffset{rightLine.find_first_not_of(' ')};
            std::copy(rightLine.cbegin() + rightContentOffset, rightLine.cend(), line.begin() + rightBlockPos + rightContentOffset);
        }

        // Add leftover left lines
        for (; leftLineI < leftLines.size(); ++leftLineI)
        {
            lines.push_back(std::move(leftLines[leftLineI]));
            std::string & line{lines.back()};
            line.insert(line.begin(), leftBlockPos, ' ');
        }

        // Add leftover right lines
        for (; rightLineI < rightLines.size(); ++rightLineI)
        {
            lines.push_back(std::move(rightLines[rightLineI]));
            std::string & line{lines.back()};
            line.insert(line.begin(), rightBlockPos, ' ');
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
    static bool _validateBalance(const _Node<T> * const node, size_t & retHeight)
    {
        size_t leftHeight{0u};
        if (node->left && !_validateBalance<T>(node->left, leftHeight))
        {
            return false;
        }

        size_t rightHeight{0u};
        if (node->right && !_validateBalance<T>(node->right, rightHeight))
        {
            return false;
        }

        const auto [minHeight, maxHeight]{qc::minmax(leftHeight, rightHeight)};
        if (maxHeight - minHeight > 1u)
        {
            return false;
        }

        retHeight = maxHeight + 1u;
        return true;
    }
};

using _TreeFriend = qc::_internal::AvlTreeFriend;

#pragma warning(disable: 4189) // NOCOMMIT
TEST(AvlTree, standard)
{
    using Node = typename qc::AvlTree<uint>::_Node;
    qc::AvlTree<uint> tree{};
    Node * n{tree._root = new Node{.v = 111}};
    Node * n0{n->left = new Node{.v = 222222}};
    Node * n1{n->right = new Node{.v = 4}};
    Node * n00{n0->left = new Node{.v = 33}};
    Node * n10{n1->left = new Node{.v = 555}};
    Node * n000{n00->left = new Node{.v = 6}};
    Node * n100{n10->left = new Node{.v = 7}};
    Node * n0000{n000->left = new Node{.v = 8888888}};
    Node * n1000{n100->left = new Node{.v = 9}};


    std::cout << "hi: " << _TreeFriend::genString(tree) << std::endl;

    // NOCOMMIT
    tree._root = nullptr;
}

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

    for (size_t iteration{0}; iteration < 100u; ++iteration)
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
