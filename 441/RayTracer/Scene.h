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
	std::vector<Light> lightSources;

	int INF = 100000;

	float A[3]; //ambient light intensity is constant throughout scene

	Scene() { 
		A[0] = 0.5;
		A[1] = 0.5;
		A[2] = 0.5;
	}
	~Scene() { }

	Color calculate_light(Intersection& i, Object& object, std::vector<Light>& light, Point& camera) {
		Vec E = (camera - i.intersection).normalize();
		Vec N = i.normal;
		
		float amb[3] = { 0.0, 0.0, 0.0 };
		float diff[3] = { 0.0, 0.0, 0.0 };
		float spec[3] = { 0.0, 0.0, 0.0 };
		float I[3] = { 0.0, 0.0, 0.0 };

		for (unsigned int k = 0; k < light.size(); k++) {
			//L is vector to light source
			Vec L = (light[k].source - i.intersection).normalize();
			
			//determine closet intersection to the viewer
			bool inShadow = false;

			for (unsigned int kk = 0; kk < objects.size(); kk++) {
				Intersection testForShadow = objects[kk]->intersect(L, i.intersection + L*0.0001);
				
				//ray to light source does not hit this object, check to see if it hits others
				if (testForShadow.intersection == Point(0, 0, 0)) {
					continue;
				}

				//ray to light source has hit some object, omit this light's contribution
				else {
					inShadow = true;
				}
			}

			if (!inShadow) {
				Vec R;
				float L_dot_N = L.dot(N);

				R.x = (2 * L_dot_N * N.x) - L.x;
				R.y = (2 * L_dot_N * N.y) - L.y;
				R.z = (2 * L_dot_N * N.z) - L.z;
				R = R.normalize();
				float R_dot_E = (R.dot(E) > 0) ? R.dot(E) : 0;

				//add contributions of light source to color buffers
				for (int i = 0; i < 3; i++) {
					//Diffuse Light: I = C*K_d*(L*N) 
					diff[i] = (L_dot_N > 0) ? object.K_d[i] * light[k].C[i] * L_dot_N : 0;

					//Specular Light: I = C*K_s*(R*E)^n
					spec[i] = (L_dot_N > 0) ? object.K_d[i] * light[k].C[i] * pow(R_dot_E, object.n) : 0;

					I[i] += diff[i] + spec[i];
				}
			}
		}

		//add contribution of ambient light
		for (int i = 0; i < 3; i++) {
			//Ambient Light: I = K_a*A
			amb[i] = object.K_a[i] * A[i];

			I[i] += amb[i];
			if (I[i] > 1.0) I[i] = 1.0;
		}

		return Color(I[0], I[1], I[2]);
	}

	//a ray is defined by a unit vector in a direction, and a starting point
	Color castRay(Vec& v, Point& camera) { 
		Color color;
		
		//determine closet intersection to the viewer
		Intersection closest;
		closest.t = INF; //set initial intersection at infinity
		int closest_object = 0;

		for (unsigned int k = 0; k < objects.size(); k++) {
			Intersection i = objects[k]->intersect(v, camera);
			if (i.t < closest.t && !(i.intersection == Point(0, 0, 0))) {
				closest = i;
				closest_object = k;
			}
		}

		if (closest.t == INF) {
			color = Color(0.4, 0.8, 0.9);
		}
		else {
			color = calculate_light(closest, *(objects[closest_object]), lightSources, camera);
		}

		return color;
	}
};