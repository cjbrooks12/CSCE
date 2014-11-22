#pragma once

#include <stdexcept>
#include "Object.h"
#include "Light.h"
#include "Color.h"
#include "Vec.h"

class Scene {
private:
public:
	std::vector<Object*> objects;
	std::vector<Light> lights;
	Color backgroundColor;
	Point camera;

	int INF = 100000;

	float A[3]; //ambient light intensity is constant throughout scene

	Scene() { 
		A[0] = 0.5;
		A[1] = 0.5;
		A[2] = 0.5;

		camera = Point(0, 0, -1);

		backgroundColor = Color(0, 0, 0);
	}
	~Scene() { }

	Color calculate_light(Intersection& ptOnSurface, Object& object, Point& camera, int reflection_count) {
		Vec L; //direction to light
		Vec R; //direction of reflected vector
		Vec E = (camera - ptOnSurface.intersection).normalize(); //direction to viewer
		Vec N = ptOnSurface.normal.normalize(); //normal to surface
		
		Color I_direct(0, 0, 0);

		for (unsigned int i = 0; i < lights.size(); i++) {	
			L = (lights[i].source - ptOnSurface.intersection).normalize();

			//cast ray to light source through all objects to check if this point is in shadow
			bool inShadow = false;
			for (unsigned int j = 0; j < objects.size(); j++) {
				Intersection testForShadow = objects[j]->intersect(L, 
					ptOnSurface.intersection + ptOnSurface.normal*0.0001);
				
				if (testForShadow.intersection == Point(0, 0, 0)) {
					inShadow = false;
				}
				else {
					//find vectors to the object of intersection and to the light
					Vec toObject = testForShadow.intersection - ptOnSurface.intersection;
					Vec toLight = lights[i].source - ptOnSurface.intersection;

					//find magnitude of each vector
					if (toObject.magnitude() < toLight.magnitude()) {
						inShadow = true;
						break;
					}
					else {
						continue;
					}
				}
			}

			//don't calculate light if the point is in shadow
			if (!inShadow) {
				float L_dot_N = L.dot(N);

				R = ((N*(2 * L_dot_N)) - L).normalize();
				float R_dot_E = (R.dot(E) > 0) ? R.dot(E) : 0;

				//add contributions of light source to color buffers
				float diff[3] = { 0.0, 0.0, 0.0 };
				float spec[3] = { 0.0, 0.0, 0.0 };
				for (int j = 0; j < 3; j++) {
					diff[j] = (L_dot_N > 0) ? object.KD(ptOnSurface, j) * lights[i].C[j] * L_dot_N : 0;
					spec[j] = (L_dot_N > 0) ? object.KS(ptOnSurface, j) * lights[i].C[j] * pow(R_dot_E, object.n) : 0;

					I_direct[j] += diff[j];
					I_direct[j] += spec[j];
				}
			}
		}

		//add contribution of ambient light
		float amb[3] = { 0.0, 0.0, 0.0 };
		for (int i = 0; i < 3; i++) {
			//Ambient Light: I = K_a*A
			amb[i] = object.KA(ptOnSurface, i) * A[i];

			I_direct[i] += amb[i];
			if (I_direct[i] > 1.0) I_direct[i] = 1.0;
		}

		return Color(I_direct[0], I_direct[1], I_direct[2]);
	}

	//a ray is defined by a unit vector in a direction, and a starting point
	Color castRay(Vec& v, Point& camera, int reflection_count) { 	
		//determine closet intersection to the viewer
		Intersection closest;
		closest.t = INF; //set initial intersection at infinity
		int closest_object = 0;

		for (unsigned int i = 0; i < objects.size(); i++) {
			Intersection ptOnSurface = objects[i]->intersect(v, camera);
			if (ptOnSurface.t < closest.t && !(ptOnSurface.intersection == Point(0, 0, 0))) {
				closest = ptOnSurface;
				closest_object = i;
			}
		}

		if (closest.t == INF) {
			return backgroundColor;
		}
		else {
			Color direct;
			Color reflective;
			Color refractive;

			//determine direct light on object
			direct = calculate_light(closest, *(objects[closest_object]), camera, reflection_count);

			//determine reflective light on object (if any)
			if (objects[closest_object]->isReflective && reflection_count > 1) {
				//determine the incident ray from camera, and recur on that ray
				Vec V = (camera - closest.intersection).normalize(); //direction to viewer
				Vec N = closest.normal; //normal to surface
				Vec R = ((N*(2 * V.dot(N))) - V).normalize(); //direction of reflected ray

				reflective = castRay(R, camera, reflection_count - 1);

				if (reflective == backgroundColor) reflective = Color(0, 0, 0);
			}

			

			return direct + (objects[closest_object]->G_e)*reflective;
		}
	}
};