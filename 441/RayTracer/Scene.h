#pragma once

#include <stdexcept>
#include "Object.h"
#include "Light.h"
#include "Color.h"
#include "Vec.h"

class Scene {
private:
public:
	Object *objects;
	Light lightSources;

	Scene() { }
	~Scene() { }

	//a ray is defined by a unit vector in a direction, and a starting point
	Color castRay(Vec& v, Point& p) { 
		Intersection i = objects->intersect(v, p);
		//std::cout << i.t << "\n";
		Color color;
		if (i.t < 0) {
			color = Color(0.4, 0.8, 0.9);
		}
		else {
			color = objects->calculate_light(i, lightSources);
		}

		return color;
	}
};