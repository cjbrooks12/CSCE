#pragma once

#include <iostream>
#include "Object.h"
#include "Vec.h"

class Plane : public Object {
public:
	Point O; 
	Vec N; 

	Plane() {}
	//assume points within x[-1,1], yu[-1,1], z[0, 1]
	Plane(Point& _O, Vec _N) : O(_O), N(_N) {}

	Intersection intersect(Vec& v, Point& p) {
		//equation for intersection of a vector with a sphere:
		//	N*(P + V*t) - O) = 0, where
		//		N is the normal to the plane
		//		O is some point in the plane
		//		P is the starting point of the ray
		//		V is the unit vector in the direction of the ray
		//		t is the ray parameter, a scalar
		//
		//final equation to solve
		//t=N*(O-P)/N*V

		//ray should be calculated using screen coordinates
		Vec V = v;
		Point P = p;

		//ray is parallel to plane
		if (N.dot(V) == 0) {
			Intersection i;
			i.intersection = Point(0, 0, 0);
			return i;
		}

		float t = (N.dot(O - P)) / (N.dot(V));
			
		//ray does not have a positive intersection
		if (t < 0) {
			Intersection i;
			i.intersection = Point(0, 0, 0);
			return i;
		}
		else {
			Intersection i;
			i.intersection = P + V*t;
			i.normal = N.normalize();
			i.t = t;
			return i;
		}
	}
};