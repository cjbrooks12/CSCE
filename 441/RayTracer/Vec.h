#pragma once

#include <cmath>
#include <cassert>
#define ImageW 600
#define ImageH 600
#define ImageD 300


class Vec {
public:
	float x, y, z;

	Vec() : x(0), y(0), z(0) { }
	Vec(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }
	Vec(float _v[3]) : x(_v[0]), y(_v[1]), z(_v[2]) { }
	~Vec() { }

	//Utility Functions
	Vec normalize() {
		float mag = sqrt(x*x + y*y + z*z);
		x = x / mag;
		y = y / mag;
		z = z / mag;

		return *this;
	}

	//vector arithmatic functions
	float dot(Vec &v) {
		return (x*v.x + y*v.y + z*v.z);
	}
	Vec cross(Vec &v){
		return Vec(y*v.z - z*v.y, -x*v.z + z*v.x, x*v.y - y*v.x);
	}
	Vec operator+(const Vec &v) {
		return Vec(x + v.x, y + v.y, z + v.z);
	}
	Vec operator-(const Vec &v) {
		return Vec(x - v.x, y - v.y, z - v.z);
	}
	Vec operator*(float c) {
		return Vec(c*x, c*y, c*z);
	}

	//overload operators to make it easier to manipulate Vec objects
	float& operator[](int i) {
		assert(i == 0 || i == 1 || i == 2);

		switch (i) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
		}
	};
	Vec& operator=(float v[3]) {
		x = v[0];
		y = v[1];
		z = v[2];

		return *this;
	}
	Vec& operator=(Vec& v) {
		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}
};

typedef Vec Point;