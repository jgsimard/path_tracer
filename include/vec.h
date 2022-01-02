//
// Created by jeang on 2022-01-01.
//

#pragma once

#include <linalg.h> // use this instead of eigen because very slow build times
using namespace linalg::aliases;

using Vec3 = float3;
using Point3 = float3;
using Color = float3;

inline Vec3 unit_vector(const Vec3& v){
    return v / length(v);
}

