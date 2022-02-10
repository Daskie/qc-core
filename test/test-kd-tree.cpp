#include <gtest/gtest.h>

#include <qc-core/kd-tree.hpp>

// Currently the "real" K-d tree testing happens in the testing repo

TEST(kdTree, compiles)
{
    qc::KdTree tree0{};

    const qc::fvec2 points[]{{0.0f, 1.0f}, {2.0f, 3.0f}};
    qc::KdTree tree1{points};

    qc::KdTree tree2{tree0};
    qc::KdTree tree3{std::move(tree0)};

    tree2 = tree3;
    tree3 = std::move(tree2);

    tree1.size();

    tree1.nearest({0.0f, 0.0f});
}
