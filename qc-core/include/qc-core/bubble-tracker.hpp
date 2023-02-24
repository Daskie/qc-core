#pragma once

#include <qc-core/core-ext.hpp>
#include <qc-core/list.hpp>

namespace qc
{
    template <IntegralOrPointer P>
    class BubbleTracker
    {
        using S = std::conditional_t<Integral<P>, P, s64>;

      public:

        struct Bubble
        {
            P pos;
            S size;
        };

        ///
        /// Add a bubble; may overlap with existing bubbles
        /// @param pos position of new bubble
        /// @param size size of new bubble
        ///
        void add(P pos, S size);
        void add(const Bubble & bubble);

        ///
        /// Remove the first bubble of the given size, or a portion of the first bubble that best fits the given size
        /// @param size size of bubble to remove
        /// @return whether there was a bubble of sufficient size, and if so, the position of the bubble removed
        ///
        std::pair<bool, P> remove(S size);

        ///
        /// Get the size of trailing free memory
        /// @param memoryEnd one past the last memory position
        /// @return free tail size
        ///
        S tail(P memoryEnd) const;

        ///
        /// Clear all bubbles
        ///
        void clear();

        const List<Bubble> & bubbles() const { return _bubbles; }

      private:

        List<Bubble> _bubbles{};
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <IntegralOrPointer P>
    inline void BubbleTracker<P>::add(const P pos, const S size)
    {
        if (size <= S(0))
        {
            return;
        }

        // Find position in ordered list where this bubble would be inserted
        const auto it{qc::lowerBound(_bubbles.begin(), _bubbles.end(), pos, [](const Bubble & b, const P & p) { return b.pos >= p; })};
        const u64 i{u64(it - _bubbles.begin())};

        const bool isPre{i > 0u};
        const bool isPost{i < _bubbles.size()};
        Bubble & postBubble{_bubbles.data()[i]};
        Bubble & preBubble{*(&postBubble - 1)};
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
            _bubbles.insert(it, Bubble{pos, size});
        }
    }

    template <IntegralOrPointer P>
    inline std::pair<bool, P> BubbleTracker<P>::remove(const S size)
    {
        if (size <= S(0))
        {
            return {};
        }

        Bubble * bestBubble{nullptr};

        for (auto it{_bubbles.begin()}, endIt{_bubbles.end()}; it != endIt; ++it)
        {
            Bubble & bubble{*it};

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

    template <IntegralOrPointer P>
    inline auto BubbleTracker<P>::tail(const P memoryEnd) const -> S
    {
        if (_bubbles.empty())
        {
            return 0u;
        }
        else
        {
            const Bubble & lastBubble{_bubbles.back()};
            return lastBubble.pos < memoryEnd && lastBubble.pos + lastBubble.size >= memoryEnd ? memoryEnd - lastBubble.pos : S(0);
        }
    }

    template <IntegralOrPointer P>
    inline void BubbleTracker<P>::clear()
    {
        _bubbles.clear();
    }
}
