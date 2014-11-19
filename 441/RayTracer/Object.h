#pragma once

#include "Vec.h"
#include <stdexcept>
#include <algorithm>
#include "Color.h"
#include "Light.h"

/*
	An Object is the base class for more complex shapes, such as a plane, 
	a sphere, ellipsoid, torus, etc. An Object has material properties which
	determine how light is reflected off the object, and it has a notion of 
	its surface, and normals to the surface. The RayTracer does not need to know
	this internal information, it only needs a point on the surface and the 
	normal at that point to calculate the lighting equation on this Object
*/

class Intersection {
public:
	Point intersection; //easy to use point of intersection
	Vec normal; //normal at intersection point
	float t; //parameter value to determine if one intersection is closer than another
};

class Object {
public:
	//Material Properties
	float K_a[3]; //ambient coefficient
	float K_d[3]; //diffuse coefficient
	float K_s[3]; //specular coefficient
	int n;    //specular exponenet
	float G_e[3]; //reflection coefficient

	Object() {
		K_a[0] = 0.2;
		K_a[1] = 0.2;
		K_a[2] = 0.0;

		K_d[0] = 1.0;
		K_d[1] = 1.0;
		K_d[2] = 0.0;

		K_s[0] = 0.5;
		K_s[1] = 0.5;
		K_s[2] = 0.5;

		n = 5;
	}
	~Object() {}

	virtual Intersection intersect(Vec& v, Point& p) = 0;
};