#pragma once

#include <anton/math/vector3.hpp>

namespace anton::math {
    struct Ray {
        Vector3 origin;
        Vector3 direction;
    };
    
    struct OBB {
        Vector3 center;
        Vector3 local_x;
        Vector3 local_y;
        Vector3 local_z;
        Vector3 halfwidths;
    };
} // namespace anton::math