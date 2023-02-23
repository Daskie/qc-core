#pragma once

#include <iterator>

#include <qc-core/core.hpp>

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
        using reference = T &;
        using const_reference = const T &;
        using difference_type = ptrdiff_t;
        using size_type = unat;
        using iterator = _Iterator<false>;
        using const_iterator = _Iterator<true>;

        AvlTree() = default;

        AvlTree(const AvlTree &) = delete;
        AvlTree(AvlTree && other);

        AvlTree & operator=(const AvlTree &) = delete;
        AvlTree & operator=(AvlTree && other);

        ~AvlTree();

        iterator insert(const T & v) { return _insert(v); }
        iterator insert(T && v) { return _insert(std::move(v)); };

        template <typename... Args> iterator emplace(Args &&... args) { return _insert(T{std::forward<Args>(args)...}); }

        //iterator erase(iterator pos);
        //iterator erase(iterator start, iterator end);
        //unat erase(const T & v);

        void clear();

        bool contains(const T & v) const;

        unat count(const T & v) const;

        iterator find(const T & v);
        const_iterator find(const T & v) const;

        iterator lower_bound(const T & v);
        const_iterator lower_bound(const T & v) const;

        iterator upper_bound(const T & v);
        const_iterator upper_bound(const T & v) const;

        std::pair<iterator, iterator> equal_range(const T & v);
        std::pair<const_iterator, const_iterator> equal_range(const T & v) const;

        unat size() const { return _size; }

        bool empty() const { return !_size; }

        iterator begin() { return const_cast<_Node *>(static_cast<const AvlTree *>(this)->begin()._node); }
        const_iterator begin() const;
        const_iterator cbegin() const { return begin(); }

        iterator end() { return nullptr; }
        const_iterator end() const { return nullptr; }
        const_iterator cend() const { return nullptr; };

      public: // NOCOMMIT

        struct _Node
        {
            T v;
            _Node * parent;
            _Node * left;
            _Node * right;
            int balance; // NOCOMMIT
        };

        static void _rotateLeft(_Node * & node);
        static void _rotateRight(_Node * & node);
        static void _rotateLeftRight(_Node * & node);
        static void _rotateRightLeft(_Node * & node);

        //static void _balanceShrink(_Node * node, bool side);

        _Node * _root{};
        unat _size{};

        struct _InsertRet { iterator it; bool grew; };
        template <typename T_> iterator _insert(T_ && v);
        template <typename T_> _InsertRet _insert(T_ && v, _Node * & node);

        void _clear(_Node * node);
    };

    template <typename T>
    template <bool constant>
    class AvlTree<T>::_Iterator
    {
        friend class AvlTree<T>;

        using _T = std::conditional_t<constant, const T, T>;
        using _Node = std::conditional_t<constant, const _Node, _Node>;

      public:

        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = _T;
        using reference = _T &;
        using pointer = _T *;
        using difference_type = ptrdiff_t;

        _Iterator() = default;

        reference operator*() const { return _node->v; }

        pointer operator->() const { return &_node->v; }

        _Iterator & operator++();
        _Iterator operator++(int);

        _Iterator & operator--();
        _Iterator operator--(int);

      private:

        _Node * _node{};

        _Iterator(_Node * node);
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace qc
{
    template <typename T>
    AvlTree<T>::AvlTree(AvlTree && other) :
        _root{std::exchange(other._root, nullptr)},
        _size{std::exchange(other._size, 0u)}
    {}

    template <typename T>
    AvlTree<T> & AvlTree<T>::operator=(AvlTree && other)
    {
        if (&other == this)
        {
            return *this;
        }

        _root = std::exchange(other._root, nullptr);
        _size = std::exchange(other._size, 0u);

        return *this;
    }

    template <typename T>
    AvlTree<T>::~AvlTree<T>()
    {
        clear();
    }

    /*
    template <typename T>
    auto AvlTree<T>::erase(iterator pos) -> iterator
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
    auto AvlTree<T>::erase(const iterator start, const iterator end) -> iterator
    {
        // NOCOMMIT
    }

    template <typename T>
    unat AvlTree<T>::erase(const T & v)
    {
        erase(lower_bound(v), upper_bound(v));
    }
     */

    template <typename T>
    void AvlTree<T>::clear()
    {
        if (_root)
        {
            _clear(_root);
            _root = nullptr;
            _size = 0u;
        }
    }

    template <typename T>
    bool AvlTree<T>::contains(const T & v) const
    {
        return find(v)._node;
    }

    template <typename T>
    unat AvlTree<T>::count(const T & v) const
    {
        return std::distance(lower_bound(v), upper_bound(v));
    }

    template <typename T>
    auto AvlTree<T>::find(const T & v) -> iterator
    {
        return const_cast<_Node *>(static_cast<const AvlTree *>(this)->find(v)._node);
    }

    template <typename T>
    auto AvlTree<T>::find(const T & v) const -> const_iterator
    {
        const iterator it{lower_bound(v)};
        return !it._node || v < it._node->v ? nullptr : it;
    }

    template <typename T>
    auto AvlTree<T>::lower_bound(const T & v) -> iterator
    {
        return const_cast<_Node *>(static_cast<const AvlTree *>(this)->lower_bound(v)._node);
    }

    template <typename T>
    auto AvlTree<T>::lower_bound(const T & v) const -> const_iterator
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
    auto AvlTree<T>::upper_bound(const T & v) -> iterator
    {
        return const_cast<_Node *>(static_cast<const AvlTree *>(this)->upper_bound(v)._node);
    }

    template <typename T>
    auto AvlTree<T>::upper_bound(const T & v) const -> const_iterator
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
    auto AvlTree<T>::equal_range(const T & v) -> std::pair<iterator, iterator>
    {
        return {lower_bound(v), upper_bound(v)};
    }

    template <typename T>
    auto AvlTree<T>::equal_range(const T & v) const -> std::pair<const_iterator, const_iterator>
    {
        return {lower_bound(v), upper_bound(v)};
    }

    template <typename T>
    auto AvlTree<T>::begin() const -> const_iterator
    {
        _Node * node{_root};
        while (node && node->left) node = node->left;
        return node;
    }

    template <typename T>
    void AvlTree<T>::_rotateLeft(_Node * & node)
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
    void AvlTree<T>::_rotateRight(_Node * & node)
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
    void AvlTree<T>::_rotateLeftRight(_Node * & node)
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

        alpha->balance = 0;
        beta->balance = 0;
        gamma->balance = 0;
    }

    template <typename T>
    void AvlTree<T>::_rotateRightLeft(_Node * & node)
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

        alpha->balance = 0;
        beta->balance = 0;
        gamma->balance = 0;
    }

    /*
    template <typename T>
    void AvlTree<T>::_balanceShrink(_Node * const node, const bool side)
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
     */

    template <typename T>
    template <typename T_>
    auto AvlTree<T>::_insert(T_ && v) -> iterator
    {
        iterator it;

        if (_root)
        {
            it = _insert(std::forward<T_>(v), _root).it;
        }
        else
        {
            _root = new _Node{
                .v = std::forward<T_>(v),
                .parent = nullptr,
                .left = nullptr,
                .right = nullptr,
                .balance = 0u};

            it = _root;
        }

        ++_size;
        return it;
    }

    ///
    /// @pre node is not null
    ///
    template <typename T>
    template <typename T_>
    auto AvlTree<T>::_insert(T_ && v, _Node * & node) -> _InsertRet
    {
        // NOCOMMIT: Non recursive?
        if (v < node->v)
        {
            // NOCOMMIT: Consolidate
            if (node->left)
            {
                const auto [it, grew]{_insert(std::forward<T>(v), node->left)};
                if (grew)
                {
                    // Rotate if necessary
                    if (node->balance < 0)
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
                        return {it, node->balance < 0};
                    }
                }
                else
                {
                    return {it, false};
                }
            }
            else
            {
                node->left = new _Node{
                    .v = std::forward<T_>(v),
                    .parent = node,
                    .left = nullptr,
                    .right = nullptr,
                    .balance = 0};
                --node->balance;
                return {node->left, node->balance < 0};
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
                    if (node->balance > 0)
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
                        return {it, node->balance > 0};
                    }
                }
                else
                {
                    return {it, false};
                }
            }
            else
            {
                node->right = new _Node{
                    .v = std::forward<T_>(v),
                    .parent = node,
                    .left = nullptr,
                    .right = nullptr,
                    .balance = 0};
                ++node->balance;
                return {node->right, node->balance > 0};
            }
        }
    }

    template <typename T>
    void AvlTree<T>::_clear(_Node * const node)
    {
        if (node->left)
        {
            _clear(node->left);
        }

        if (node->right)
        {
            _clear(node->right);
        }

        node->v.~T();
        delete node;
    }

    template <typename T>
    template <bool constant>
    AvlTree<T>::_Iterator<constant>::_Iterator(_Node * const node) :
        _node{node}
    {}

    template <typename T>
    template <bool constant>
    auto AvlTree<T>::_Iterator<constant>::operator++() -> _Iterator &
    {
        if (_node->right)
        {
            _node = _node->right;
            while (_node->left) _node = _node->left;
        }
        else
        {
            _Node * prev;
            do {
                prev = _node;
                _node = _node->parent;
            } while (_node && prev == _node->right);
        }

        return *this;
    }

    template <typename T>
    template <bool constant>
    auto AvlTree<T>::_Iterator<constant>::operator++(int) -> _Iterator
    {
        const _Iterator temp{*this};
        ++*this;
        return temp;
    }

    template <typename T>
    template <bool constant>
    auto AvlTree<T>::_Iterator<constant>::operator--() -> _Iterator &
    {
        if (_node->left)
        {
            _node = _node->left;
            while (_node->right) _node = _node->right;
        }
        else
        {
            _Node * prev;
            do
            {
                prev = _node;
                _node = _node->parent;
            } while (_node && prev == _node->left);
        }

        return *this;
    }

    template <typename T>
    template <bool constant>
    auto AvlTree<T>::_Iterator<constant>::operator--(int) -> _Iterator
    {
        const _Iterator temp{*this};
        --*this;
        return temp;
    }
}
