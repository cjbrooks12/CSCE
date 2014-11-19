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

	int INF = 100000;

	float A[3]; //ambient light intensity is constant throughout scene

	Scene() { 
		A[0] = 0.5;
		A[1] = 0.5;
		A[2] = 0.5;
	}
	~Scene() { }

	Color calculate_light(Intersection& ptOnSurface, Object& object, Point& camera, int reflection_count) {
		Vec L; //direction to light
		Vec R; //direction of reflected vector
		Vec E = (camera - ptOnSurface.intersection).normalize(); //direction to viewer
		Vec N = ptOnSurface.normal; //normal to surface
		
		Color I_direct(0, 0, 0);
		Color I_reflected(0, 0, 0);
		Color I_refracted(0, 0, 0);

		for (unsigned int i = 0; i < lights.size(); i++) {	
			L = (lights[i].source - ptOnSurface.intersection).normalize();

			//cast ray to light source through all objects to check if this point is in shadow
			bool inShadow = false;
			for (unsigned int j = 0; j < objects.size(); j++) {
				Intersection testForShadow = objects[j]->intersect(L, ptOnSurface.intersection + L*0.0001);
				
				if (testForShadow.intersection == Point(0, 0, 0)) {
					continue;
				}
				else {
					inShadow = true;
					break;
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
					diff[j] = (L_dot_N > 0) ? object.K_d[j] * lights[i].C[j] * L_dot_N : 0;
					spec[j] = (L_dot_N > 0) ? object.K_s[j] * lights[i].C[j] * pow(R_dot_E, object.n) : 0;

					I_direct[j] += diff[j];
					I_direct[j] += spec[j];
				}
			}
		}

		if (object.isReflective && reflection_count > 1) {
			Vec viewer = (camera - ptOnSurface.intersection).normalize();
			Vec incident = ((N*(2 * viewer.dot(N))) - viewer).normalize();

			I_reflected = castRay(incident, ptOnSurface.intersection, reflection_count--);
			I_reflected[0] = I_reflected[0] * object.G_e[0];
			I_reflected[1] = I_reflected[1] * object.G_e[1];
			I_reflected[2] = I_reflected[2] * object.G_e[2];
		}

		//add contribution of ambient light
		float amb[3] = { 0.0, 0.0, 0.0 };
		for (int i = 0; i < 3; i++) {
			//Ambient Light: I = K_a*A
			amb[i] = object.K_a[i] * A[i];

			I_direct[i] += amb[i];
			if (I_direct[i] > 1.0) I_direct[i] = 1.0;
		}


		Color finalColor(
			I_direct[0] + I_reflected[0] + I_refracted[0],
			I_direct[1] + I_reflected[1] + I_refracted[1],
			I_direct[2] + I_reflected[2] + I_refracted[2]);

		return finalColor;

	}

	//a ray is defined by a unit vector in a direction, and a starting point
	Color castRay(Vec& v, Point& camera, int reflection_count) { 
		Color color;
		
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
			color = Color(0.4, 0.8, 0.9);
		}
		else {
			color = calculate_light(closest, *(objects[closest_object]), camera, reflection_count);
		}

		return color;
	}
};