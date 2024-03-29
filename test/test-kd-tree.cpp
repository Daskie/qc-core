#include <qc-core/kd-tree.hpp>

#include <gtest/gtest.h>

// Currently the "real" K-d tree testing happens in the testing repo

TEST(KdTree, compiles)
{
    qc::KdTree tree0{};

    const qc::fvec2 points[]{{0.0f, 1.0f}, {2.0f, 3.0f}};
    qc::KdTree tree1{points};

    qc::KdTree tree3{std::move(tree1)};

    tree1 = std::move(tree3);

    static_cast<void>(tree1.size());

    static_cast<void>(tree1.nearest({0.0f, 0.0f}));
}
