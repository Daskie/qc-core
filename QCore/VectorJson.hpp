#pragma once

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
