#pragma once



#include <memory>

#include "QHash/Map.hpp"

#include "Core.hpp"



namespace qcu {



template <typename T>
class Depot {

    private:

    static qhm::Map<const T *, std::unique_ptr<T>> s_store;

    Depot();

    public:

    static T * add(T * v) {
        s_store.emplace(v, std::unique_ptr<T>(v));
        return v;
    }

    static bool has(const T * v) {
        return s_store.count(v) > 0;
    }

    static std::unique_ptr<T> remove(T * v) {
        auto it(s_store.find(v));
        if (it == s_store.end()) {
            return nullptr;
        }
        std::unique_ptr<T> e(std::move(*it));
        s_store.erase(it);
        return e;
    }

};

template <typename T>
qhm::Map<const T *, std::unique_ptr<T>> Depot<T>::s_store;



}
