#ifndef SCAN_CONVERT_H
#define SCAN_CONVERT_H

#include <vector>
#include "Triangle.h"

#define ImageW 600
#define ImageH 600
#define ImageD 600

class Edge {
public:
	float maxY;
	float currentX;
	float xIncr;
	float currentF[3];
	float fIncr[3];
	float currentZ;
	float zIncr;

	bool operator < (const Edge &e) {
		if (currentX == e.currentX) {
			return xIncr < e.xIncr;
		}
		else {
			return currentX < e.currentX;
		}
	}
};

// Clears framebuffer to black
void clearFramebuffer();
void clearZbuffer();

void setFramebuffer(int x, int y, Color color);
void setZbuffer(int x, int y, float Z);
float getZbuffer(int x, int y);

//Converts from window coordinates to screen pixel coordinates
std::vector<Pt> convertToScreenPoints(std::vector<Vertex*> vertices);

//shading triangles
enum SHADER { FLAT, GOURAUD, PHONG, WIREFRAME };
std::string file;
std::vector<Triangle> faces;
SHADER shader;
void scanConvert(Triangle triangle);
void drawShape();
Color calculateLight(Vec _N);

#endif