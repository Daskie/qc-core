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
