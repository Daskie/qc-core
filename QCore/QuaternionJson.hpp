#pragma once

#include "MatrixJson.hpp"
#include "Quaternion.hpp"

template <typename T>
void qjson_encode(qjson::Writer & writer, const qc::quat<T> & v) {
    writer.array(true).val(v.a).val(v.w).end();
}
