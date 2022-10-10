#pragma once

#include <vector>

#include <qc-core/core-ext.hpp>

namespace qc
{
    namespace _internal
    {
        class MemoryBubbleTrackerFriend;
    }

    template <IntegralOrPointer P>
    class MemoryBubbleTracker
    {
        friend class _internal::MemoryBubbleTrackerFriend;

        using S = decltype(std::declval<P>() - std::declval<P>());

      public:

        ///
        /// Add a bubble; may overlap with existing bubbles
        /// @param pos position of new bubble
        /// @param size size of new bubble
        ///
        void add(P pos, S size) noexcept;

        ///
        /// Remove the first bubble of the given size, or a portion of the first bubble that best fits the given size
        /// @param size size of bubble to remove
        /// @return whether there was a bubble of sufficient size, and if so, the position of the bubble removed
        ///
        std::pair<bool, P> remove(S size) noexcept;

      private:

        struct _Bubble
        {
            P pos;
            S size;
        };

        std::vector<_Bubble> _bubbles{};
    };
}

////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <IntegralOrPointer P>
    inline void MemoryBubbleTracker<P>::add(const P pos, const S size) noexcept
    {
        // Find position in ordered vector where this bubble would be inserted
        const auto it{qc::lowerBound(_bubbles.begin(), _bubbles.end(), pos, [](const _Bubble & b, const P & p) { return b.pos >= p; })};
        const size_t i{size_t(it - _bubbles.begin())};

        const bool isPre{i > 0u};
        const bool isPost{i < _bubbles.size()};
        _Bubble & postBubble{_bubbles.data()[i]};
        _Bubble & preBubble{*(&postBubble - 1)};
        const bool isPreAdjacent{isPre && preBubble.pos + preBubble.size >= pos};
        const bool isPostAdjacent{isPost && postBubble.pos <= pos + size};

        // Fill gap between two bubbles consolidating them into one
        if (isPreAdjacent && isPostAdjacent)
        {
            preBubble.size = postBubble.pos + postBubble.size - preBubble.pos;
            _bubbles.erase(it);
        }
        // Combine with pre adjacent bubble
        else if (isPreAdjacent)
        {
            qc::maxify(preBubble.size, pos + size - preBubble.pos);
        }
        // Combine with post adjacent bubble
        else if (isPostAdjacent)
        {
            postBubble.size = postBubble.pos + postBubble.size - pos;
            postBubble.pos = pos;
        }
        // No adjacent bubbles, insert new bubble
        else
        {
            _bubbles.insert(it, _Bubble{pos, size});
        }
    }

    template <IntegralOrPointer P>
    inline std::pair<bool, P> MemoryBubbleTracker<P>::remove(const S size) noexcept
    {
        if (size <= S(0))
        {
            return {};
        }

        _Bubble * bestBubble{nullptr};

        for (auto it{_bubbles.begin()}, endIt{_bubbles.end()}; it != endIt; ++it)
        {
            _Bubble & bubble{*it};

            // Check for exact fit
            if (bubble.size == size)
            {
                const P pos{bubble.pos};
                _bubbles.erase(it);
                return {true, pos};
            }

            // Keep track of best fitting bubble
            if (bubble.size > size && (!bestBubble || bubble.size < bestBubble->size))
            {
                bestBubble = &bubble;
            }
        }

        if (bestBubble)
        {
            const P pos{bestBubble->pos};
            bestBubble->pos += size;
            bestBubble->size -= size;
            return {true, pos};
        }
        else
        {
            return {};
        }
    }
}
