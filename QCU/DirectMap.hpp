#pragma once



#include "Core.hpp"



namespace qcu {



template <typename K, typename V>
class DirectMap {

    static_assert(std::is_arithmetic_v<K> || std::is_enum_v<K>);

    using UI = precision_ut<sizeof(K)>;

    unat m_size;
    V * m_vals;

    public:

    DirectMap(unat size) :
        m_size(size),
        m_vals(new V[m_size]())
    {}

    DirectMap(std::initializer_list<std::pair<K, V>> pairs) :
        m_size(pairs.size()),
        m_vals(new V[m_size]())
    {
        for (auto & pair : pairs) {
            (*this)[pair.first] = std::move(pair.second);
        }
    }

    DirectMap(const DirectMap<K, V> & m) :
        DirectMap(m.m_size)
    {
        for (unat i(0); i < m.m_size; ++i) {
            m_vals[i] = m.m_vals[i];
        }
    }

    DirectMap(DirectMap<K, V> && m) :
        m_size(m.m_size),
        m_vals(m.m_vals)
    {
        m.m_size = 0;
        m.m_vals = nullptr;
    }

    ~DirectMap() {
        delete[] m_vals;
    }

    DirectMap<K, V> & operator=(const DirectMap<K, V> & m) {
        if (m_size != m.m_size) {
            delete[] m_vals;
            m_size = m.m_size;
            m_vals = new V[m_size];
        }

        for (unat i(0); i < m_size; ++i) {
            m_vals[i] = m.m_vals[i];
        }

        return *this;
    }

    DirectMap<K, V> & operator=(DirectMap<K, V> && m) {
        delete[] m_vals;
        m_size = m.m_size;
        m_vals = m.m_vals;
        m.m_size = 0;
        m.m_vals = nullptr;

        return *this;
    }

    V & operator[](const K & k) {
        return m_vals[static_cast<UI>(k)];
    }

    const V & operator[](const K & k) const {
        return m_vals[static_cast<UI>(k)];
    }

    unat size() const {
        return m_size;
    }

    V * get() {
        return m_vals;
    }

    const V * get() const {
        return m_vals;
    }

};



}