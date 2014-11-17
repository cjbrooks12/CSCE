#pragma once

#include <cassert>

class Color {
public:
	float r, g, b;

	Color() : r(0), g(0), b(0) { }
	Color(float _r, float _g, float _b) : r(_r), g(_g), b(_b) { }
	Color(float _c[3]) : r(_c[0]), g(_c[1]), b(_c[2]) { }
	Color(Color& _c) : r(_c.r), g(_c.g), b(_c.b) { }
	~Color() { }

	float& operator[](int i) {
		assert(i == 0 || i == 1 || i == 2);

		switch (i) {
		case 0: return r;
		case 1: return g;
		case 2: return b;
		}
	};
	Color& operator=(float c[3]) {
		r = c[0];
		g = c[1];
		b = c[2];

		return *this;
	}
	Color& operator=(Color& c) {
		r = c.r;
		g = c.g;
		b = c.b;

		return *this;
	}
};