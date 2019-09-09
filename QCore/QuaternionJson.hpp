#pragma once

#include "MatrixJson.hpp"
#include "Quaternion.hpp"

template <typename T>
void qjson_encode(qjson::Writer & writer, const qc::quat<T> & v) {
    writer.array(true).val(v.a).val(v.w).end();
}

template <typename T>
struct qjson_decode<qc::quat<T>> {
    qc::quat<T> operator()(const qjson::Value & v) {
        const qjson::Array & arr(v.asArray());
        return {arr.at(0)->as<qc::vec3<T>>(), arr.at(1)->as<T>()};
    }
};
