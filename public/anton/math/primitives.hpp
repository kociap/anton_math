#pragma once

#include <anton/math/vec3.hpp>

namespace anton::math {
    struct Ray {
        Vec3 origin;
        Vec3 direction;
    };
    
    struct Extent3 {
        Vec3 min;
        Vec3 max;
    };

    // outer_extent
    // Forms an extent that encompasses both e1 and e2, i.e. the outer extent.
    //
    // Parameters:
    // e1, e2 - extents to calculate the outer extent of.
    //
    // Returns: 
    // An extent encompassing both e1 and e2.
    //
    [[nodiscard]] inline Extent3 outer_extent(Extent3 const& e1, Extent3 const& e2) {
        return {min(e1.min, e2.min), max(e1.max, e2.max)};
    }

    struct OBB {
        Vec3 center;
        Vec3 local_x;
        Vec3 local_y;
        Vec3 local_z;
        Vec3 halfwidths;
    };
} // namespace anton::math
