#include <algorithm>
#include <vector>
#include <gl/glut.h>
#include "Triangle.h"
#include "ScanConvert.h"
#include "Vec.h"

using namespace std;

//Member functions of Triangle
//------------------------------------------------------------------------------
void Triangle::calculateFaceNormal() {
	//must calculate uXv, where u=(v3-v1), v=(v2-v1)
	Vec u, v;
	u.x = vertices[2]->x - vertices[0]->x;
	u.y = vertices[2]->y - vertices[0]->y;
	u.z = vertices[2]->z - vertices[0]->z;

	v.x = vertices[1]->x - vertices[0]->x;
	v.y = vertices[1]->y - vertices[0]->y;
	v.z = vertices[1]->z - vertices[0]->z;

	normal = Vec::crossProduct(u, v).normalize();
}

void Triangle::calculateVertexNormals() {
	//push face normal to all vertices
	for (unsigned int i = 0; i < vertices.size(); i++) {
		vertices[i]->normal.x += normal.x;
		vertices[i]->normal.y += normal.y;
		vertices[i]->normal.z += normal.z;
	}
}

void Triangle::normalizeVertexNormals() {
	for (unsigned int i = 0; i < vertices.size(); i++) {
		vertices[i]->normal.normalize();
	}
}

//void Triangle::drawWireframe() {
//	glColor3f(1.0, 0.0, 0.0);
//
//	vector<Pt> points = convertToScreenPoints(vertices);
//
//	glBegin(GL_LINE_LOOP);
//	for (unsigned int i = 0; i < points.size(); i++) {
//		glVertex3f(points[i].x, points[i].y, 1.0);
//	}
//	glEnd();
//	glFlush();
//}