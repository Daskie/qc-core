#pragma once

#include <cassert>

#include <algorithm>
#include <span>

#include <qc-core/list.hpp>
#include <qc-core/vector.hpp>

namespace qc
{
    class KdTree
    {
        friend class _KdTreeTester;

      public:

        KdTree() = default;
        explicit KdTree(std::span<const fvec2> points);

        KdTree(const KdTree &) = delete;
        KdTree(KdTree &&) = default;

        KdTree & operator=(const KdTree &) = delete;
        KdTree & operator=(KdTree &&) = default;

        ~KdTree() = default;

        fvec2 nearest(fvec2 point) const;

        unat size() const { return _nodes.size(); }

      private:

        struct _Node
        {
            fvec2 point{};
            u32 lowerOffset{};
            u32 upperOffset{};
        };

        List<_Node> _nodes{};

        template <int axis> void _constructRecursive(const fvec2 * points, std::span<u32> orderedA, std::span<u32> orderedB, std::span<u32> scratch, _Node * node);

        template <int axis> void _nearestRecursive(fvec2 point, const _Node * node, fvec2 & nearestPoint, float & minDist2) const;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    inline KdTree::KdTree(const std::span<const fvec2> points) :
        _nodes(points.size())
    {
        assert(points.size() <= 1'000'000'000);

        if (points.empty())
        {
            return;
        }

        // Fill two arrays with increasing indices [0, 1, 2, ... , N]
        List<u32> orderedX(points.size());
        for (u32 i{0u}; i < orderedX.size(); ++i) orderedX[i] = i;
        List<u32> orderedY(orderedX.begin(), orderedX.end());

        // Sort by axes
        // We sort along the secondary axis as well to improve spatial coherency
        const auto sortX{[&points](const u32 i0, const u32 i1) { const fvec2 & p0{points[i0]}, & p1{points[i1]}; return p0.x < p1.x || p0.x == p1.x && p0.y < p1.y; }};
        const auto sortY{[&points](const u32 i0, const u32 i1) { const fvec2 & p0{points[i0]}, & p1{points[i1]}; return p0.y < p1.y || p0.y == p1.y && p0.x < p1.x; }};
        // Stable sort necessary to preserve order of equal elements
        std::stable_sort(orderedX.begin(), orderedX.end(), sortX);
        std::stable_sort(orderedY.begin(), orderedY.end(), sortY);

        // Reserve scratch
        List<u32> scratch(_nodes.size() / 2u);

        // Recursively construct tree
        _constructRecursive<0>(points.data(), orderedX, orderedY, scratch, &_nodes.front());
    }

    inline fvec2 KdTree::nearest(const fvec2 point) const
    {
        assert(!_nodes.empty());

        fvec2 nearestPoint{};
        float minDist2{std::numeric_limits<float>::infinity()};

        _nearestRecursive<0>(point, _nodes.data(), nearestPoint, minDist2);

        return nearestPoint;
    }

    template <int alpha>
    inline void KdTree::_constructRecursive(const fvec2 * const points, const std::span<u32> orderedA, const std::span<u32> orderedB, const std::span<u32> scratch, _Node * const node)
    {
        static constexpr int beta{1 - alpha};

        // Terminal case
        if (orderedA.size() <= 3u)
        {
            if (orderedA.size() == 1u)
            {
                node->point = points[orderedA.front()];
            }
            else
            {
                node->point = points[orderedA[1]];
                node->lowerOffset = 1u;
                node[1].point = points[orderedA[0]];

                if (orderedA.size() == 3u)
                {
                    node->upperOffset = 2u;
                    node[2].point = points[orderedA[2]];
                }
            }

            return;
        }

        // Select median point along alpha axis
        const unat lowerACount{orderedA.size() / 2u};
        const u32 medianPointI{orderedA[lowerACount]};
        const fvec2 medianPoint{points[medianPointI]};

        const std::span<u32> lowerOrderedA{orderedA.subspan(0u, lowerACount)};
        const std::span<u32> upperOrderedA{orderedA.subspan(lowerACount + 1u)};

        node->point = medianPoint;
        node->lowerOffset = 1u;
        node->upperOffset = node->lowerOffset + u32(lowerOrderedA.size());

        // Split ordered beta span into two ordered subspans
        unat lowerBCount{0u};
        unat upperBCount{0u};
        for (const u32 pointI: orderedB)
        {
            const fvec2 point{points[pointI]};

            if (point.at<alpha>() < medianPoint.at<alpha>())
            {
                orderedB[lowerBCount] = pointI;
                ++lowerBCount;
            }
            else if (point.at<alpha>() > medianPoint.at<alpha>())
            {
                scratch[upperBCount] = pointI;
                ++upperBCount;
            }
            else
            {
                if (point.at<beta>() < medianPoint.at<beta>())
                {
                    orderedB[lowerBCount] = pointI;
                    ++lowerBCount;
                }
                else if (point.at<beta>() > medianPoint.at<beta>())
                {
                    scratch[upperBCount] = pointI;
                    ++upperBCount;
                }
                else
                {
                    if (pointI < medianPointI)
                    {
                        orderedB[lowerBCount] = pointI;
                        ++lowerBCount;
                    }
                    else if (pointI > medianPointI)
                    {
                        scratch[upperBCount] = pointI;
                        ++upperBCount;
                    }
                }
            }
        }

        // Define the ordered beta subspans
        const std::span<u32> lowerOrderedB{orderedB.subspan(0u, lowerBCount)};
        const std::span<u32> upperOrderedB{orderedB.subspan(lowerBCount + 1u)};

        // Sanity check
        assert(lowerOrderedA.size() == lowerOrderedB.size());
        assert(upperOrderedA.size() == upperOrderedB.size());

        // Copy upper subspan from scratch back into main span
        std::copy_n(scratch.begin(), upperBCount, upperOrderedB.begin());

        // Recurse along the other axis
        _constructRecursive<beta>(points, lowerOrderedB, lowerOrderedA, scratch, node + node->lowerOffset);
        _constructRecursive<beta>(points, upperOrderedB, upperOrderedA, scratch, node + node->upperOffset);
    }

    template <int axis>
    inline void KdTree::_nearestRecursive(const fvec2 point, const _Node * const node, fvec2 & nearestPoint, float & minDist2) const
    {
        const fvec2 delta{point - node->point};
        const fvec2 dists2{delta.x * delta.x, delta.y * delta.y};
        const float dist2{dists2.x + dists2.y};

        if (dist2 < minDist2)
        {
            nearestPoint = node->point;
            minDist2 = dist2;
        }

        u32 primaryChildNodeOffset{};
        u32 secondaryChildNodeOffset{};

        if (node->lowerOffset && point.at<axis>() <= node->point.at<axis>())
        {
            primaryChildNodeOffset = node->lowerOffset;
            secondaryChildNodeOffset = node->upperOffset;
        }
        else if (node->upperOffset)
        {
            primaryChildNodeOffset = node->upperOffset;
            secondaryChildNodeOffset = node->lowerOffset;
        }

        // Search down the primary branch
        if (primaryChildNodeOffset)
        {
            _nearestRecursive<1 - axis>(point, node + primaryChildNodeOffset, nearestPoint, minDist2);

            // The boundary is within our current best range, so we must search down the secondary branch for a closer point
            if (secondaryChildNodeOffset && dists2.at<axis>() <= minDist2)
            {
                _nearestRecursive<1 - axis>(point, node + secondaryChildNodeOffset, nearestPoint, minDist2);
            }
        }
    }
}
