#ifndef LIGHT_H
#define LIGHT_H

#include "Vec.h"
#include <iostream>
#include <algorithm>

using namespace std;

class Light {
public:
	Vec L; //Direction of light
	Vec E; //direction to viewer
	Vec N; //direction of normal
	Vec R; //direction of reflected specular vector

	//Ambient Light: I = K_a*A
	float A[3]; //coefficient of ambient light
	float K_a[3]; //ambient reflection coefficient

	//Diffuse Light: I = C*K_d*(L*N) ***ASSUMES NORMALIZED VECTORS
	float C[3]; //intensity of point light source
	float K_d[3]; //diffuse reflection coefficient

	//Specular Light: I = C*K_s*(R*E)^n ***ASSUMES NORMALIZED VECTORS
	float K_s[3]; //specular reflection coefficient
	int n; //specular exponent


	Color calculate() {
		
	}
};

#endif