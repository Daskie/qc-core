#pragma once

#include <QJsonRead.hpp>
#include <QJsonWrite.hpp>

#include "Vector.hpp"

template <typename T, int t_n>
void qjson_encode(qjson::Writer & writer, const qc::vec<T, t_n> & v) {
    writer.array(true);
    if constexpr (t_n >= 1) writer.val(v.x);
    if constexpr (t_n >= 2) writer.val(v.y);
    if constexpr (t_n >= 3) writer.val(v.z);
    if constexpr (t_n >= 4) writer.val(v.w);
    writer.end();
}

template <typename T, int t_n>
void qjson_encode(qjson::Writer & writer, const qc::span<T, t_n> & v) {
    writer.array(true).val(v.min).val(v.max).end();
}

template <typename T, int t_n>
struct qjson_decode<qc::vec<T, t_n>> {
    qc::vec<T, t_n> operator()(const qjson::Value & v) {
        const qjson::Array & arr(v.asArray());
        if constexpr (t_n == 2) return {arr.at(0)->as<T>(), arr.at(1)->as<T>()};
        if constexpr (t_n == 3) return {arr.at(0)->as<T>(), arr.at(1)->as<T>(), arr.at(2)->as<T>()};
        if constexpr (t_n == 4) return {arr.at(0)->as<T>(), arr.at(1)->as<T>(), arr.at(2)->as<T>(), arr.at(3)->as<T>()};
    }
};

template <typename T, int t_n>
struct qjson_decode<qc::span<T, t_n>> {
    qc::span<T, t_n> operator()(const qjson::Value & v) {
        const qjson::Array & arr(v.asArray());
        return {arr.at(0)->as<qc::span_value_t<T, t_n>>(), arr.at(1)->as<qc::span_value_t<T, t_n>>()};
    }
};
