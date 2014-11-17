#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>

//RGB color Color class
//------------------------------------------------------------------------------
class Color {
public:
	float r, g, b;

	Color() {
		r = g = b = 0;
	}

	Color(float _r, float _g, float _b) {
		r = _r;
		g = _g;
		b = _b;
	}
};

//Arbitrary vector Vec Class
//------------------------------------------------------------------------------
class Vec {
public:
	float x, y, z;

	Vec() {
		x = y = z = 0;
	}

	Vec(float nX, float nY, float nZ) {
		x = nX;
		y = nY;
		z = nZ;
	}

	//Utility Functions
	Vec normalize() {
		float mag = sqrt(x*x + y*y + z*z);
		x = x / mag;
		y = y / mag;
		z = z / mag;

		return *this;
	}

	//static utility functions
	static Vec crossProduct(Vec u, Vec v){
		Vec product;
		product.x = u.y*v.z - u.z*v.y;
		product.y = -u.x*v.z + u.z*v.x;
		product.z = u.x*v.y - u.y*v.x;

		return product;
	}

	static float dotProduct(Vec u, Vec v) {
		return (u.x*v.x + u.y*v.y + u.z*v.z);
	}
};

//screen pixels. Position, depth, F(either color or normal)
//------------------------------------------------------------------------------
class Pt {
public:
	int x, y;
	float z;
	float f[3];

	Pt() {
		x = y = 0;
		z = 0.0;
		f[0] = f[1] = f[2] = 0.0;
	}

	Pt(int nX, int nY, float nZ) {
		x = nX;
		y = nY;
		z = nZ;
	}
};

//Vertex of a polygon. Window position, with normal vector
//------------------------------------------------------------------------------
class Vertex {
public:
	float x, y, z;
	Vec normal;

	Vertex() {
		x = y = z = 0;
	}

	Vertex(float nX, float nY, float nZ) {
		x = nX;
		y = nY;
		z = nZ;
	}
};

//
class Triangle {
public:
	std::vector<Vertex*> vertices;
	Vec normal;

	Triangle() { }

	void push_back(Vertex *v) { vertices.push_back(v); }

	void calculateFaceNormal() {
		//must calculate uXv, where u=(v3-v1), v=(v2-v1)
		Vec u, v;
		u.x = vertices[2]->x - vertices[0]->x;
		u.y = vertices[2]->y - vertices[0]->y;
		u.z = vertices[2]->z - vertices[0]->z;

		v.x = vertices[1]->x - vertices[0]->x;
		v.y = vertices[1]->y - vertices[0]->y;
		v.z = vertices[1]->z - vertices[0]->z;

		normal = Vec::crossProduct(u, v).normalize();
	}

	void calculateVertexNormals() {
		//push face normal to all vertices
		for (unsigned int i = 0; i < vertices.size(); i++) {
			vertices[i]->normal.x += normal.x;
			vertices[i]->normal.y += normal.y;
			vertices[i]->normal.z += normal.z;
		}
	}

	void normalizeVertexNormals() {
		for (unsigned int i = 0; i < vertices.size(); i++) {
			vertices[i]->normal.normalize();
		}
	}
};

#endif