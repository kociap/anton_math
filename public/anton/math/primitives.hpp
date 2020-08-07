#pragma once

#include <anton/math/vec3.hpp>

namespace anton::math {
    struct Ray {
        Vec3 origin;
        Vec3 direction;
    };
    
    struct OBB {
        Vec3 center;
        Vec3 local_x;
        Vec3 local_y;
        Vec3 local_z;
        Vec3 halfwidths;
    };
} // namespace anton::math