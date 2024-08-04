#pragma once
#include <cmath>
#include <sstream>

class Vec2 {
public:
    float x, y;

    Vec2(float xOff = 0, float yOff = 0) : x(xOff), y(yOff) {};

    Vec2 operator+(const Vec2& other) const {
        return Vec2(x + other.x, y + other.y);
    };

    Vec2 operator-(const Vec2& other) const {
        return Vec2(x - other.x, y - other.y);
    };

    Vec2 operator*(float scalar) const {
        return Vec2(x * scalar, y * scalar);
    };

    float magnitude() const {
        return std::sqrt(x * x + y * y);
    };

    std::string toStr() const {
        std::ostringstream ss;
        ss << x << ", " << y;
        return ss.str();
    };
};

class Vec2i {
public:
    int x, y;

    Vec2i(int xOff = 0, int yOff = 0) : x(xOff), y(yOff) {};

    Vec2i operator+(const Vec2i& other) const {
        return Vec2i(x + other.x, y + other.y);
    };

    Vec2i operator-(const Vec2i& other) const {
        return Vec2i(x - other.x, y - other.y);
    };

    Vec2i operator*(int scalar) const {
        return Vec2i(x * scalar, y * scalar);
    };

    std::string toStr() const {
        std::ostringstream ss;
        ss << x << ", " << y;
        return ss.str();
    };
};

class Vec3i : public Vec2i {
public:
    int z;

    Vec3i(int xOff = 0, int yOff = 0, int zOff = 0) : Vec2i(xOff, yOff), z(zOff) {};

    Vec3i operator+(const Vec3i& other) const {
        return Vec3i(x + other.x, y + other.y, z + other.z);
    };

    Vec3i operator-(const Vec3i& other) const {
        return Vec3i(x - other.x, y - other.y, z - other.z);
    };

    Vec3i operator*(int scalar) const {
        return Vec3i(x * scalar, y * scalar, z * scalar);
    };

    std::string toStr() const {
        std::ostringstream ss;
        ss << x << ", " << y << ", " << z;
        return ss.str();
    };
};

class Vec3 : public Vec2 {
public:
    float z;

    Vec3(float xOff = 0, float yOff = 0, float zOff = 0) : Vec2(xOff, yOff), z(zOff) {};

    Vec3 operator+(const Vec3& other) const {
        return Vec3(x + other.x, y + other.y, z + other.z);
    };

    Vec3 operator-(const Vec3& other) const {
        return Vec3(x - other.x, y - other.y, z - other.z);
    };

    Vec3 operator*(float scalar) const {
        return Vec3(x * scalar, y * scalar, z * scalar);
    };

    float magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    };

    Vec3 lerp(const Vec3& target, float t) const {
        return Vec3(
            x + (target.x - x) * t,
            y + (target.y - y) * t,
            z + (target.z - z) * t
        );
    };

    std::string toStr() const {
        std::ostringstream ss;
        ss << x << ", " << y << ", " << z;
        return ss.str();
    };
};