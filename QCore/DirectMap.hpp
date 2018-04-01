#pragma once



#include "Core.hpp"



namespace qc {



template <typename K, typename V>
class DirectMap {

    static_assert(std::is_arithmetic_v<K> || std::is_enum_v<K>);

    using I = precision_ut<sizeof(K)>;

    unat m_size;
    V * m_vals;
    V m_defVal;

    public:

    DirectMap(unat size) :
        m_size(size),
        m_vals(new V[m_size]()),
        m_defVal()
    {}

    DirectMap(unat size, const V & defVal) :
        m_size(size),
        m_vals(new V[m_size]),
        m_defVal(defVal)
    {
        for (unat i(0); i < m_size; ++i) {
            m_vals[i] = m_defVal;
        }
    }

    DirectMap(std::initializer_list<std::pair<K, V>> pairs) :
        m_size(1),
        m_vals(nullptr),
        m_defVal()
    {
        for (auto & pair : pairs) {
            if (static_cast<I>(pair.first) >= m_size) {
                m_size = static_cast<I>(pair.first) + 1;
            }
        }

        m_vals = new V[m_size]();

        for (auto & pair : pairs) {
            (*this)[pair.first] = std::move(pair.second);
        }
    }

    DirectMap(std::initializer_list<std::pair<K, V>> pairs, const V & defVal) :
        m_size(1),
        m_vals(nullptr),
        m_defVal(defVal)
    {
        for (auto & pair : pairs) {
            if (static_cast<I>(pair.first) >= m_size) {
                m_size = static_cast<I>(pair.first) + 1;
            }
        }

        m_vals = new V[m_size];
        for (unat i(0); i < m_size; ++i) {
            m_vals[i] = m_defVal;
        }

        for (auto & pair : pairs) {
            (*this)[pair.first] = std::move(pair.second);
        }
    }

    DirectMap(const DirectMap<K, V> & m) :
        DirectMap(m.m_size)
    {
        m_defVal = m.m_defVal;

        for (unat i(0); i < m.m_size; ++i) {
            m_vals[i] = m.m_vals[i];
        }
    }

    DirectMap(DirectMap<K, V> && m) :
        m_size(m.m_size),
        m_vals(m.m_vals),
        m_defVal(m.m_defVal)
    {
        m.m_size = 0;
        m.m_vals = nullptr;
    }

    ~DirectMap() {
        if (m_vals) {
            delete[] m_vals;
        }
    }

    DirectMap<K, V> & operator=(const DirectMap<K, V> & m) {
        if (m_size != m.m_size) {
            delete[] m_vals;
            m_size = m.m_size;
            m_vals = new V[m_size];
        }
        m_defVal = m.m_defVal;

        for (unat i(0); i < m_size; ++i) {
            m_vals[i] = m.m_vals[i];
        }

        return *this;
    }

    DirectMap<K, V> & operator=(DirectMap<K, V> && m) {
        delete[] m_vals;
        m_size = m.m_size;
        m_vals = m.m_vals;
        m_defVal = m.m_defVal;

        m.m_size = 0;
        m.m_vals = nullptr;

        return *this;
    }

    V & operator[](const K & k) {
        I i(static_cast<I>(k));
        //if (i >= m_size) {
        //    resize(i + 1);
        //}

        return m_vals[i];
    }

    const V & operator[](const K & k) const {
        return m_vals[static_cast<I>(k)];
    }

    /*
    void resize(unat size) {
        V * newVals(new V[size]);
        for (unat i(0); i < size && i < m_size; ++i) {
            newVals[i] = std::move(m_vals[i]);
        }
        for (unat i(m_size); i < size; ++i) {
            newVals[i] = m_defVal;
        }
        delete[] m_vals;
        m_size = size;
        m_vals = newVals;
    }
    */

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