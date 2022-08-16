#pragma once

#include <qc-core/geometric-pool.hpp>

namespace qc
{
    namespace _internal
    {
        class AvlTreeFriend;
    }

    template <typename T>
    class AvlTree
    {
      public: // NOCOMMIT
        struct _Node;

        template <bool constant> class _Iterator;

        friend _internal::AvlTreeFriend;

      public:

        using value_type = T;
        using difference_type = ptrdiff_t;
        using reference = T &;
        using const_reference = const T &;
        using pointer = T *;
        using const_pointer = const T *;
        using iterator = _Iterator<false>;
        using const_iterator = _Iterator<true>;

        AvlTree() noexcept = default;

        AvlTree(const AvlTree & other);
        AvlTree(AvlTree && other) noexcept;

        AvlTree & operator=(const AvlTree & other);
        AvlTree & operator=(AvlTree && other) noexcept;

        ~AvlTree() noexcept;

        void reserve(size_t capacity);

        iterator insert(const T & v) { return _insert(v); }
        iterator insert(T && v) { return _insert(std::move(v)); };

        template <typename... Args> iterator emplace(Args &&... args) { return _insert(T{std::forward<Args>(args)...}); }

        iterator erase(iterator pos) noexcept;
        iterator erase(iterator start, iterator end) noexcept;
        size_t erase(const T & v) noexcept;

        void clear() noexcept;

        bool contains(const T & v) const noexcept;

        size_t count(const T & v) const noexcept;

        iterator find(const T & v) noexcept;
        const_iterator find(const T & v) const noexcept;

        iterator lower_bound(const T & v) noexcept;
        const_iterator lower_bound(const T & v) const noexcept;

        iterator upper_bound(const T & v) noexcept;
        const_iterator upper_bound(const T & v) const noexcept;

        std::pair<iterator, iterator> equal_range(const T & v) noexcept;
        std::pair<const_iterator, const_iterator> equal_range(const T & v) const noexcept;

        size_t size() const noexcept { return _nodePool.count(); }

        size_t capacity() const noexcept { return _nodePool.capacity(); }

        iterator begin() noexcept { return const_cast<_Node *>(static_cast<const AvlTree *>(this)->begin()._node); }
        const_iterator begin() const noexcept;
        const_iterator cbegin() const noexcept { return begin(); }

        iterator end() noexcept { return nullptr; }
        const_iterator end() const noexcept { return nullptr; }
        const_iterator cend() const noexcept { return nullptr; };

      public: // NOCOMMIT

        struct _Node
        {
            T v;
            _Node * parent;
            union
            {
                _Node * children[2u];
                struct
                {
                    _Node * left;
                    _Node * right;
                    #pragma warning(suppress: 4201)
                };
            };
            int balance; // NOCOMMIT
        };

        static void _rotateLeft(_Node * & node) noexcept;
        static void _rotateRight(_Node * & node) noexcept;
        static void _rotateLeftRight(_Node * & node) noexcept;
        static void _rotateRightLeft(_Node * & node) noexcept;

        static void _balanceShrink(_Node * node, bool side) noexcept;

        _Node * _root{};
        GeometricObjectPool<_Node> _nodePool{};

        template <typename T_> iterator _insert(T_ && v);
        template <typename T_> std::pair<iterator, bool> _insert(T_ && v, _Node * & node);
    };

    template <typename T>
    template <bool constant>
    class AvlTree<T>::_Iterator
    {
        friend AvlTree;

        using T_ = std::conditional_t<constant, const T, T>;
        using _Node_ = std::conditional_t<constant, const _Node, _Node>;

      public:

        using value_type = T_;
        using difference_type = ptrdiff_t;
        using reference = T_ &;
        using pointer = T_ *;
        using iterator_category = std::bidirectional_iterator_tag;

        _Iterator() noexcept = default;

        reference operator*() const noexcept { return _node->v; }

        pointer operator->() const noexcept { return &_node->v; }

        _Iterator & operator++() noexcept;
        _Iterator operator++(int) noexcept;

        _Iterator & operator--() noexcept;
        _Iterator operator--(int) noexcept;

      private:

        _Node_ * _node{};

        _Iterator(_Node_ * node) noexcept;
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    AvlTree<T>::AvlTree(const AvlTree & other)
    {
        // NOCOMMIT
    }

    template <typename T>
    AvlTree<T>::AvlTree(AvlTree && other) noexcept :
        _root{std::exchange(other._root, nullptr)},
        _nodePool{std::move(other._nodePool)}
    {}

    template <typename T>
    AvlTree<T> & AvlTree<T>::operator=(const AvlTree & other)
    {
        // NOCOMMIT
    }

    template <typename T>
    AvlTree<T> & AvlTree<T>::operator=(AvlTree && other) noexcept
    {
        _root = std::exchange(other._root, nullptr);
        _nodePool = std::move(other._nodePool);
    }

    template <typename T>
    AvlTree<T>::~AvlTree<T>() noexcept
    {
        clear();
    }

    template <typename T>
    void AvlTree<T>::reserve(const size_t capacity)
    {
        _nodePool.reserve(capacity);
    }

    template <typename T>
    auto AvlTree<T>::erase(iterator pos) noexcept -> iterator
    {
        _Node * const eraseNode{pos._node};
        const iterator nextIt{++pos};
        _Node * & parentChildPtr{eraseNode->parent ? (eraseNode == eraseNode->parent->left ? eraseNode->parent->left : eraseNode->parent->right) : _root};

        if (!eraseNode->left && !eraseNode->right)
        {
            parentChildPtr = nullptr;
        }
        else
        {
            const bool side{eraseNode->balance >= 0};
            const bool antiSide{!side};

            _Node * swapNode{eraseNode->children[side]};
            while (swapNode->children[antiSide]) swapNode = swapNode->children[antiSide];
            _Node * balanceNode{swapNode};

            if (swapNode != eraseNode->children[side])
            {
                _Node * const swapParent{swapNode->parent};

                swapParent->children[antiSide] = swapNode->children[side];
                if (swapParent->children[antiSide]) swapParent->children[antiSide]->parent = swapParent;

                swapNode->children[side] = eraseNode->children[side];
                swapNode->children[side]->parent = swapNode;

                balanceNode = swapParent;
            }

            swapNode->children[antiSide] = eraseNode->children[antiSide];
            if (swapNode->children[antiSide]) swapNode->children[antiSide]->parent = swapNode;

            swapNode->parent = eraseNode->parent;
            parentChildPtr = swapNode;

            swapNode->balance = eraseNode->balance;
            _balanceShrink(balanceNode, side);
        }

        _nodePool.delete_(eraseNode);
        return nextIt;
    }

    template <typename T>
    auto AvlTree<T>::erase(const iterator start, const iterator end) noexcept -> iterator
    {
        // NOCOMMIT
    }

    template <typename T>
    size_t AvlTree<T>::erase(const T & v) noexcept
    {
        erase(lower_bound(v), upper_bound(v));
    }

    template <typename T>
    void AvlTree<T>::clear() noexcept
    {
        for (auto it{begin()}; it._node; ++it)
        {
            _nodePool.delete_(it._node);
        }

        _root = nullptr;
    }

    template <typename T>
    bool AvlTree<T>::contains(const T & v) const noexcept
    {
        return find(v)._node;
    }

    template <typename T>
    size_t AvlTree<T>::count(const T & v) const noexcept
    {
        return std::distance(lower_bound(v), upper_bound(v));
    }

    template <typename T>
    auto AvlTree<T>::find(const T & v) noexcept -> iterator
    {
        return const_cast<_Node *>(static_cast<const AvlTree *>(this)->find(v)._node);
    }

    template <typename T>
    auto AvlTree<T>::find(const T & v) const noexcept -> const_iterator
    {
        const iterator it{lower_bound(v)};
        return !it._node || v < it._node->v ? nullptr : it;
    }

    template <typename T>
    auto AvlTree<T>::lower_bound(const T & v) noexcept -> iterator
    {
        return const_cast<_Node *>(static_cast<const AvlTree *>(this)->lower_bound(v)._node);
    }

    template <typename T>
    auto AvlTree<T>::lower_bound(const T & v) const noexcept -> const_iterator
    {
        _Node * node{_root};
        _Node * lowerBound{};

        while (node)
        {
            if (node->v < v)
            {
                node = node->right;
            }
            else
            {
                lowerBound = node;
                node = node->left;
            }
        }

        return lowerBound;
    }

    template <typename T>
    auto AvlTree<T>::upper_bound(const T & v) noexcept -> iterator
    {
        return const_cast<_Node *>(static_cast<const AvlTree *>(this)->upper_bound(v)._node);
    }

    template <typename T>
    auto AvlTree<T>::upper_bound(const T & v) const noexcept -> const_iterator
    {
        _Node * node{_root};
        _Node * upperBound{};

        while (node)
        {
            if (v < node->v)
            {
                upperBound = node;
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }

        return upperBound;
    }

    template <typename T>
    auto AvlTree<T>::equal_range(const T & v) noexcept -> std::pair<iterator, iterator>
    {
        return {lower_bound(v), upper_bound(v)};
    }

    template <typename T>
    auto AvlTree<T>::equal_range(const T & v) const noexcept -> std::pair<const_iterator, const_iterator>
    {
        return {lower_bound(v), upper_bound(v)};
    }

    template <typename T>
    auto AvlTree<T>::begin() const noexcept -> const_iterator
    {
        _Node * node{_root};
        while (node && node->left) node = node->left;
        return node;
    }

    template <typename T>
    void AvlTree<T>::_rotateLeft(_Node * & node) noexcept
    {
        _Node * const alpha{node};
        _Node * const beta{alpha->right};

        alpha->right = beta->left;
        beta->left = alpha;

        beta->parent = alpha->parent;
        alpha->parent = beta;

        node = beta;

        alpha->balance = 0;
        beta->balance = 0;
    }

    template <typename T>
    void AvlTree<T>::_rotateRight(_Node * & node) noexcept
    {
        _Node * const alpha{node};
        _Node * const beta{alpha->left};

        alpha->left = beta->right;
        beta->right = alpha;

        beta->parent = alpha->parent;
        alpha->parent = beta;

        node = beta;

        alpha->balance = 0;
        beta->balance = 0;
    }

    template <typename T>
    void AvlTree<T>::_rotateLeftRight(_Node * & node) noexcept
    {
        _Node * const alpha{node};
        _Node * const beta{alpha->left};
        _Node * const gamma{beta->right};

        alpha->left = gamma->right;
        beta->right = gamma->left;
        gamma->left = beta;
        gamma->right = alpha;

        gamma->parent = alpha->parent;
        beta->parent = gamma;
        alpha->parent = gamma;

        node = gamma;

        alpha->balance = gamma->balance > 0 ? 0 : 1; // NOCOMMIT: (1 - gamma->balance) / 2
        beta->balance = gamma->balance < 0 ? 0 : -1; // NOCOMMIT: (-1 - gamma->balance) / 2
        gamma->balance = 0;
    }

    template <typename T>
    void AvlTree<T>::_rotateRightLeft(_Node * & node) noexcept
    {
        _Node * const alpha{node};
        _Node * const beta{alpha->right};
        _Node * const gamma{beta->left};

        alpha->right = gamma->left;
        beta->left = gamma->right;
        gamma->right = beta;
        gamma->left = alpha;

        gamma->parent = alpha->parent;
        beta->parent = gamma;
        alpha->parent = gamma;

        node = gamma;

        alpha->balance = gamma->balance < 0 ? 0 : -1; // NOCOMMIT: (-1 - gamma->balance) / 2
        beta->balance = gamma->balance > 0 ? 0 : 1; // NOCOMMIT: (1 - gamma->balance) / 2
        gamma->balance = 0;
    }

    template <typename T>
    void AvlTree<T>::_balanceShrink(_Node * const node, const bool side) noexcept
    {
        if (side)
        {
            if (node->balance == -1)
            {
                if (node->left->balance > 0)
                {
                    _rotateLeftRight(node);
                }
                else
                {
                    _rotateRight(node);
                }
            }
            else if (node->balance == 1)
            {
                node->balance = 0;
            }
            else
            {
                node->balance = -1;
                return;
            }
        }
        else
        {
            if (node->balance == 1)
            {
                if (node->right->balance < 0)
                {
                    _rotateRightLeft(node);
                }
                else
                {
                    _rotateLeft(node);
                }
            }
            else if (node->balance == -1)
            {
                node->balance = 0;
            }
            else
            {
                node->balance = 1;
                return;
            }
        }

        if (node->parent)
        {
            _balanceShrink(node->parent, node == node->parent->right);
        }
    }

    template <typename T>
    template <typename T_>
    auto AvlTree<T>::_insert(T_ && v) -> iterator
    {
        if (!_root)
        {
            return _root = _nodePool.new_(std::forward<T_>(v));
        }
        else
        {
            return _insert(std::forward<T_>(v), _root);
        }
    }

    ///
    /// @pre node is not null
    ///
    template <typename T>
    template <typename T_>
    auto AvlTree<T>::_insert(T_ && v, _Node * & node) -> std::pair<iterator, bool>
    {
        if (v < node->v)
        {
            // NOCOMMIT: Consolidate
            if (node->left)
            {
                const auto [it, grew]{_insert(std::forward<T>(v), node->left)};
                if (grew)
                {
                    // Rotate if necessary
                    if (node->balance == -1)
                    {
                        if (node->left->balance < 0)
                        {
                            _rotateRight(node);
                        }
                        else
                        {
                            _rotateLeftRight(node);
                        }
                        return {it, false};
                    }
                    else
                    {
                        --node->balance;
                        return {it, node->balance == -1};
                    }
                }
                else
                {
                    return {it, false};
                }
            }
            else
            {
                node->left = _nodePool.new_(std::forward<T_>(v), node);
                --node->balance;
                return {node->left, !node->right};
            }
        }
        else
        {
            if (node->right)
            {
                const auto [it, grew]{_insert(std::forward<T>(v), node->right)};
                if (grew)
                {
                    // Rotate if necessary
                    if (node->balance == 1)
                    {
                        if (node->right->balance > 0)
                        {
                            _rotateLeft(node);
                        }
                        else
                        {
                            _rotateRightLeft(node);
                        }
                        return {it, false};
                    }
                    else
                    {
                        ++node->balance;
                        return {it, node->balance == 1};
                    }
                }
                else
                {
                    return {it, false};
                }
            }
            else
            {
                node->right = _nodePool.new_(std::forward<T_>(v), node);
                ++node->balance;
                return {node->right, !node->left};
            }
        }
    }

    template <typename T>
    template <bool constant>
    AvlTree<T>::_Iterator<constant>::_Iterator(_Node_ * const node) noexcept :
        _node{node}
    {}

    template <typename T>
    template <bool constant>
    auto AvlTree<T>::_Iterator<constant>::operator++() noexcept -> _Iterator &
    {
        if (_node->right)
        {
            _node = _node->right;
            while (_node->left) _node = _node->left;
        }
        else
        {
            _Node_ * prev{_node};
            _node = _node->parent;
            while (_node && prev == _node->right)
            {
                prev = _node;
                _node = _node->parent;
            }
        }

        return *this;
    }

    template <typename T>
    template <bool constant>
    auto AvlTree<T>::_Iterator<constant>::operator++(int) noexcept -> _Iterator
    {
        _Iterator temp{*this};
        ++*this;
        return temp;
    }

    template <typename T>
    template <bool constant>
    auto AvlTree<T>::_Iterator<constant>::operator--() noexcept -> _Iterator &
    {
        if (_node->left)
        {
            _node = _node->left;
            while (_node->right) _node = _node->right;
        }
        else
        {
            _Node_ * prev{_node};
            _node = _node->parent;
            while (_node && prev == _node->left)
            {
                prev = _node;
                _node = _node->parent;
            }
        }

        return *this;
    }

    template <typename T>
    template <bool constant>
    auto AvlTree<T>::_Iterator<constant>::operator--(int) noexcept -> _Iterator
    {
        _Iterator temp{*this};
        --*this;
        return temp;
    }
}
