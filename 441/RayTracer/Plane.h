#pragma once

#include <iostream>
#include <cmath>
#include "Object.h"
#include "Vec.h"

class Plane : public Object {
public:
	Point O; 
	Vec N; 
	bool isCheckered;

	Plane() {}

	//override 
	float KA(Intersection pt, int i) { 
		if (isCheckered) {
			float width = fmod(pt.intersection.x, 1.0);
			float depth = fmod(sqrt(pt.intersection.y*pt.intersection.y +
				pt.intersection.z*pt.intersection.z), 1.0);

			//1st quadrants
			if (width >= 0 && depth >= 0) {
				if ((fabs(width) < 0.5) && (fabs(depth) < 0.5)) {
					return K_a[i];
				}
				else if ((fabs(width) >= 0.5) && (fabs(depth) >= 0.5)) {
					return K_a[i];
				}
				else {
					return 0;
				}
			}
			//2nd quadrant
			else {
				if ((fabs(width) < 0.5) && (fabs(depth) < 0.5)) {
					return 0;
				}
				else if ((fabs(width) >= 0.5) && (fabs(depth) >= 0.5)) {
					return 0;
				}
				else {
					return K_a[i];
				}
			}
		}
		else {
			return K_a[i];
		}
	}

	float KD(Intersection pt, int i) {
		if (isCheckered) {
			float width = fmod(pt.intersection.x, 1.0);
			float depth = fmod(sqrt(pt.intersection.y*pt.intersection.y +
				pt.intersection.z*pt.intersection.z), 1.0);

			//1st quadrants
			if (width >= 0 && depth >= 0) {
				if ((fabs(width) < 0.5) && (fabs(depth) < 0.5)) {
					return K_d[i];
				}
				else if ((fabs(width) >= 0.5) && (fabs(depth) >= 0.5)) {
					return K_d[i];
				}
				else {
					return 0;
				}
			}
			//2nd quadrant
			else {
				if ((fabs(width) < 0.5) && (fabs(depth) < 0.5)) {
					return 0;
				}
				else if ((fabs(width) >= 0.5) && (fabs(depth) >= 0.5)) {
					return 0;
				}
				else {
					return K_d[i];
				}
			}
		}
		else {
			return K_d[i];
		}
	}

	float KS(Intersection pt, int i) {
		if (isCheckered) {
			float width = fmod(pt.intersection.x, 1.0);
			float depth = fmod(sqrt(pt.intersection.y*pt.intersection.y +
				pt.intersection.z*pt.intersection.z), 1.0);

			//1st quadrants
			if (width >= 0 && depth >= 0) {
				if ((fabs(width) < 0.5) && (fabs(depth) < 0.5)) {
					return K_s[i];
				}
				else if ((fabs(width) >= 0.5) && (fabs(depth) >= 0.5)) {
					return K_s[i];
				}
				else {
					return 0;
				}
			}
			//2nd quadrant
			else {
				if ((fabs(width) < 0.5) && (fabs(depth) < 0.5)) {
					return 0;
				}
				else if ((fabs(width) >= 0.5) && (fabs(depth) >= 0.5)) {
					return 0;
				}
				else {
					return K_s[i];
				}
			}
		}
		else {
			return K_s[i];
		}
	}

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
			i.t = -1;
			return i;
		}

		float t = (N.dot(O - P)) / (N.dot(V));
			
		//ray does not have a positive intersection
		if (t < 0) {
			Intersection i;
			i.intersection = Point(0, 0, 0);
			i.t = -1;
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