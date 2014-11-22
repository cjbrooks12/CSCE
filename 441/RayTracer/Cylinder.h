#pragma once

#include <iostream>
#include "Object.h"
#include "Vec.h"

class Cylinder : public Object {
public:
	Point C; //center point of cylinder
	float r; //radius of cylinder
	Vec A; //unit axis of cylinder

	Cylinder() {}
	//assume points within x[-1,1], yu[-1,1], z[0, 1]
	Cylinder(Point& _C, float _r) : C(_C), r(_r) {}

	float KA(Intersection pt, int i) { return K_a[i]; }
	float KD(Intersection pt, int i) { return K_d[i]; }
	float KS(Intersection pt, int i) { return K_s[i]; }

	Intersection intersect(Vec& v, Point& p) {
		//ray (should be calculated using screen coordinates
		Vec V = v;
		Point P = p;

		Vec Cpar = A*(C.dot(A)/(A.dot(A))); //deformed center of cylinder
		Vec Cperp = C - Cpar;

		Vec Ppar = A*(P.dot(A) / (A.dot(A))); //deformed center of cylinder
		Vec Pperp = P - Ppar;

		Vec Vpar = A*(V.dot(A) / (A.dot(A))); //deformed center of cylinder
		Vec Vperp = V - Vpar;

		float a = Vperp.dot(Vperp);
		float b = (Vperp * 2).dot(Pperp - Cperp);
		float c = (Pperp - Cperp).dot(Pperp - Cperp) - r*r;

		float discriminant = (b * b) - (4 * a*c); //b^2 - 4ac
		if (discriminant < 0) {
			//no intersection
			Intersection i;
			i.intersection = Point(0, 0, 0);
			i.t = -1;
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
				i.t = -1;
			}

			return i;
		}
	}
};