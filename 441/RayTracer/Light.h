#pragma once

class Light {
public:
	Point source;

	float C[3];

	Light() {
		source = Point(1, -1, 1);

		C[0] = 1.0;
		C[1] = 1.0;
		C[2] = 1.0;
	}

	~Light() {}
};