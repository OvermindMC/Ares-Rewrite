#pragma once

#include "../Vector/Vec.h"

class AABB {
public:
    Vec3 lower, upper;

    AABB(Vec3 lowerPoint = Vec3(), Vec3 upperPoint = Vec3()) : lower(lowerPoint), upper(upperPoint) {};

    bool intersects(const Vec3& point) const {
        return 
            (point.x >= lower.x && point.x <= upper.x) &&
            (point.y >= lower.y && point.y <= upper.y) &&
            (point.z >= lower.z && point.z <= upper.z);
    };
};