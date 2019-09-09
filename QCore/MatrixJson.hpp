#pragma once

#include "VectorJson.hpp"
#include "Matrix.hpp"

template <typename T, int t_n>
void qjson_encode(qjson::Writer & writer, const qc::mat<T, t_n> & v) {
    writer.array();
    if constexpr (t_n >= 1) writer.val(v.c1);
    if constexpr (t_n >= 2) writer.val(v.c2);
    if constexpr (t_n >= 3) writer.val(v.c3);
    if constexpr (t_n >= 4) writer.val(v.c4);
    writer.end();
}

template <typename T, int t_n>
struct qjson_decode<qc::mat<T, t_n>> {
    qc::mat<T, t_n> operator()(const qjson::Value & v) {
        const qjson::Array & arr(v.asArray());
        if constexpr (t_n == 2) return {arr.at(0)->as<qc::vec2<T>>(), arr.at(1)->as<qc::vec2<T>>()};
        if constexpr (t_n == 3) return {arr.at(0)->as<qc::vec3<T>>(), arr.at(1)->as<qc::vec3<T>>(), arr.at(2)->as<qc::vec3<T>>()};
        if constexpr (t_n == 4) return {arr.at(0)->as<qc::vec4<T>>(), arr.at(1)->as<qc::vec4<T>>(), arr.at(2)->as<qc::vec4<T>>(), arr.at(3)->as<qc::vec4<T>>()};
    }
};