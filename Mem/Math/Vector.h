#pragma once

template<typename T>
class Vec2 {
public:
	T _x, _y;
public:
	Vec2(T x = T{}, T y = T{}) : _x(x), _y(y) {};
public:
	void operator *= (Vec2<T> v) {
		*this = Vec2<T>(this->_x * v._x, this->_y * v._y);
	};
	void operator += (Vec2<T> v) {
		*this = Vec2<T>(this->_x + v._x, this->_y + v._y);
	};
	void operator -= (Vec2<T> v) {
		*this = Vec2<T>(this->_x - v._x, this->_y - v._y);
	};
	void operator /= (Vec2<T> v) {
		*this = Vec2<T>(this->_x / v._x, this->_y / v._y);
	};
};

template<typename T>
class Vec3 : public Vec2<T> {
public:
	T _z;
public:
	Vec3(T x = T{}, T y = T{}, T z = T{}) : _z(z), Vec2<T>(x, y) {};
public:
	bool operator == (Vec3<T> comp) {
		return this->_x == comp._x && this->_y == comp._y && this->_z == comp._z;
	};
	bool operator != (Vec3<T> comp) {
		return !(this == comp);
	};
public:
	void operator *= (Vec3<T> v) {
		*this = Vec3<T>(this->_x * v._x, this->_y * v._y, this->_z * v._z);
	};
	void operator += (Vec3<T> v) {
		*this = Vec3<T>(this->_x + v._x, this->_y + v._y, this->_z + v._z);
	};
	void operator -= (Vec3<T> v) {
		*this = Vec3<T>(this->_x - v._x, this->_y - v._y, this->_z - v._z);
	};
	void operator /= (Vec3<T> v) {
		*this = Vec3<T>(this->_x / v._x, this->_y / v._y, this->_z / v._z);
	};
public:
	auto dist(Vec3<T> _v) -> double {
		auto dX = this->_x - _v._x;
		auto dY = this->_y - _v._y;
		auto dZ = this->_z - _v._z;

		return sqrt(dX * dX + dY * dY + dZ * dZ);
	};
};

template<typename T>
class Vec4 : public Vec3<T> {
public:
	T _w;
public:
	Vec4(T x = T{}, T y = T{}, T z = T{}, T w = T{}) : _w(w), Vec3<T>(x, y, z) {};
public:
	template<typename T>
	auto intersects(Vec2<T> point) -> bool {
		return (
			point._x >= this->_x &&
            point._x <= this->_z &&
            point._y >= this->_y &&
            point._y <= this->_w
		);
	};
};

template<typename T>
class AABB {
public:
	Vec3<T> lower = Vec3<T>(T{}, T{}, T{});
	Vec3<T> upper = Vec3<T>(T{}, T{}, T{});
public:
	AABB(Vec3<T> lower = Vec3<T>(T{}, T{}, T{}), Vec3<T> upper = Vec3<T>(T{}, T{}, T{})) {};
};