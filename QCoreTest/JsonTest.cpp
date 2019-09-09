#include "QCoreTest.hpp"

#include <QCore/QuaternionJson.hpp>

template <typename T, int t_n>
void testVecTN() {
    std::string json(qjson::Writer().key("v").val(qc::vec<T, t_n>()).finish());
    qjson::read(json).at("v")->as<qc::vec<T, t_n>>();
}

template <typename T>
void testVecT() {
    testVecTN<T, 2>();
    testVecTN<T, 3>();
    testVecTN<T, 4>();
}

template <typename T, int t_n>
void testSpanTN() {
    std::string json(qjson::Writer().key("v").val(qc::span<T, t_n>()).finish());
    qjson::read(json).at("v")->as<qc::span<T, t_n>>();
}

template <typename T>
void testSpanT() {
    testSpanTN<T, 1>();
    testSpanTN<T, 2>();
    testSpanTN<T, 3>();
    testSpanTN<T, 4>();
}

template <typename T, int t_n>
void testMatTN() {
    std::string json(qjson::Writer().key("v").val(qc::mat<T, t_n>()).finish());
    qjson::read(json).at("v")->as<qc::mat<T, t_n>>();
}

template <typename T>
void testMatT() {
    testMatTN<T, 2>();
    testMatTN<T, 3>();
    testMatTN<T, 4>();
}

template <typename T>
void testQuatT() {
    std::string json(qjson::Writer().key("v").val(qc::quat<T>()).finish());
    qjson::read(json).at("v")->as<qc::quat<T>>();
}

void testJson() {
    testVecT<qc::f32>();
    testVecT<qc::f64>();
    testVecT<qc::s08>();
    testVecT<qc::s16>();
    testVecT<qc::s32>();
    testVecT<qc::s64>();
    testVecT<qc::u08>();
    testVecT<qc::u16>();
    testVecT<qc::u32>();
    testVecT<qc::u64>();
    testVecT<bool>();

    testSpanT<qc::f32>();
    testSpanT<qc::f64>();
    testSpanT<qc::s08>();
    testSpanT<qc::s16>();
    testSpanT<qc::s32>();
    testSpanT<qc::s64>();
    testSpanT<qc::u08>();
    testSpanT<qc::u16>();
    testSpanT<qc::u32>();
    testSpanT<qc::u64>();
    
    testMatT<qc::f32>();
    testMatT<qc::f64>();
    
    testQuatT<qc::f32>();
    testQuatT<qc::f64>();
}
