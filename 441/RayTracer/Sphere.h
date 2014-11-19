#pragma once

#include <iostream>
#include "Object.h"
#include "Vec.h"

class Sphere : public Object {
public:
	Point C; //center point of sphere
	float r; //radius of sphere

	Sphere() {}
	//assume points within x[-1,1], yu[-1,1], z[0, 1]
	Sphere(Point& _C, float _r) : C(_C), r(_r) {}

	Intersection intersect(Vec& v, Point& p) {
		//equation for intersection of a vector with a sphere:
		//	((P + V*t) - c)*((P + V*t) - c) - r^2 = 0, where
		//		C is the center of the sphere
		//		r is the radius of the sphere
		//		P is the starting point of the vector
		//		V is the unit vector in the direction of the vector
		//		t is the parameter, a scalar
		//
		//final quadratic equation is 
		//	(V*V)t^2 + 2V*(P-C)t + (P-C)(P-C)-r^2 = 
		
		//ray (should be calculated using screen coordinates
		Vec V = v;
		Point P = p;

		//sphere in screen coordinates
		float R = r;

		float a = V.dot(V);
		float b = (V * 2).dot(P - C);
		float c = (P - C).dot(P - C) - r*r;

		float discriminant = (b * b) - (4*a*c); //b^2 - 4ac
		if (discriminant < 0) {
			//no intersection
			Intersection i;
			i.intersection = Point(0, 0, 0);

			return i;
		}
		else {
			//two intersections, solve quadratic equation to find closest t
			float t1 = (-b + sqrt(discriminant)) / (2.0f*a);
			float t2 = (-b - sqrt(discriminant)) / (2.0f*a);

			Intersection i;
			if (t1 >= 0 && t2 >= 0) {
				i.t = (t1 <= t2) ? t1 : t2;
			}
			else if (t1 >= 0 && t2 < 0) {
				i.t = t1;
			}
			else if (t1 < 0 && t2 > 0) {
				i.t = t2;
			}
			else {
				i.t = -1;
			}

			if (i.t > 0) {
				i.intersection = (P + (V*i.t));
				i.normal = ((P + (V*i.t)) - C).normalize();
			}
			else {
				i.intersection = Point(0, 0, 0);
			}

			return i;
		}
	}
};