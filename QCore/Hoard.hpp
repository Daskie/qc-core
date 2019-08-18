#pragma once

#include <vector>

namespace qc {

template <typename T>
class Hoard {

    using shnat = precision_st<k_nat_p / 2u>;
    using uhnat = precision_ut<k_nat_p / 2u>;

    static constexpr uhnat k_defCapacity = uhnat(256);

    private:

    static std::vector<std::vector<T>> s_hoards;

    public:

    class HP {

        friend Hoard;

        private:

        uhnat m_index;
        uhnat m_hoard;

        public:

        HP() :
            m_index(~uhnat(0u)),
            m_hoard(~uhnat(0u))
        {}

        private:

        HP(uhnat index, uhnat hoard) :
            m_index(index),
            m_hoard(hoard)
        {}

        public:

        HP(const HP & hp) = default;

        HP & operator=(const HP & hp) = default;

        HP & operator+=(shnat x) { m_index += x; return *this; }
        
        HP & operator-=(shnat x) { m_index -= x; return *this; }

        HP & operator++() { ++m_index; return *this; }
        HP operator++(int) { return HP(m_index++, m_hoard); }
        
        HP & operator--() { --m_index; return *this; }
        HP operator--(int) { return HP(m_index--, m_hoard); }

        T & operator*() { return s_hoards[m_hoard][m_index]; }
        const T & operator*() const { return *this; }

        T * operator->() { return &*this; }
        const T * operator->() const { return &*this; }

        T & operator[](shnat x) { return s_hoards[m_hoard][m_index + x]; }
        const T & operator[](shnat x) const { return (*this)[x]; }

        HP operator+(shnat x) const { return HP(m_index + x, m_hoard); }

        HP operator-(shnat x) const { return HP(m_index - x, m_hoard); }

        operator bool() const { return m_hoard < s_hoards.size() && m_index < s_hoards[m_hoard].size(); }

        Hoard & hoard() { return s_hoards[m_hoard]; }
        const Hoard & hoard() const { return hoard(); }

    };

    private:

    uhnat m_index;

    public:

    Hoard(uhnat capacity = k_defCapacity) :
        m_index(uhnat(s_hoards.size()))
    {
        s_hoards.emplace_back();
        s_hoards.back().reserve(capacity);
    }

    template <typename... Args>
    HP add(Args &&... args) {
        auto & vec(s_hoards[m_index]);
        vec.emplace_back(forward<Args>(args)...);
        return HP(uhnat(vec.size()) - 1u, m_index);
    }

    HP operator[](uhnat x) { return HP(x, m_index); }

    uhnat size() const { return s_hoards[m_index].size(); }
    
};

template <typename T> std::vector<std::vector<T>> Hoard<T>::s_hoards;

//template <typename T> using HP = Hoard<T>::HP;

}
