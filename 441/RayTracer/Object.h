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
	float t;
	Vec v;
	Vec normal;
};

class Object {
	//Material Properties
	/*float K_a[3];// = { 0.1, 0.0, 0.0 }; //ambient coefficient
	float K_d[3];// = { 0.7, 0.0, 0.0 }; //diffuse coefficient
	float K_s[3];// = { 0.5, 0.5, 0.5 }; //specular coefficient
	int n = 5;    //specular exponenet
	float G_e[3]; //reflection coefficient*/

public:
	Object() {}
	~Object() {}

	virtual Intersection intersect(Vec& v, Point& p) = 0;

	Color calculate_light(Intersection& i, Light& l) {
		Vec L = Vec(1, 1, -1).normalize();
		Vec E = Vec(0, 0, -1).normalize();
		Vec N = i.normal;
		Vec R;

		//Ambient Light: I = K_a*A
		float A[3] = { 0.5, 0.5, 0.5 };
		float K_a[3] = { 0.1, 0.0, 0.0 };
		float amb[3];

		//Diffuse Light: I = C*K_d*(L*N) 
		float C[3] = { 1.0, 1.0, 1.0 };
		float K_d[3] = { 0.7, 0.0, 0.0 }; 
		float diff[3];

		//Specular Light: I = C*K_s*(R*E)^n
		float K_s[3] = { 0.5, 0.5, 0.5 };
		int n = 5;
		float spec[3];

		float L_dot_N = L.dot(N);

		R.x = (2 * L_dot_N * N.x) - L.x;
		R.y = (2 * L_dot_N * N.y) - L.y;
		R.z = (2 * L_dot_N * N.z) - L.z;
		R = R.normalize();
		float R_dot_E = (R.dot(E) > 0) ? R.dot(E) : 0;

		float I[3];
		for (int i = 0; i < 3; i++) {
			amb[i] = K_a[i] * A[i];
			diff[i] = (L_dot_N > 0) ? K_d[i] * C[i] * L_dot_N : 0;
			spec[i] = (L_dot_N > 0) ? K_d[i] * C[i] * pow(R_dot_E, n) : 0;

			I[i] = amb[i] + diff[i] + spec[i];
		}

		return Color(I[0], I[1], I[2]);
	}
};