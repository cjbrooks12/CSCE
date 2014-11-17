#include <Windows.h>
#include <gl/glut.h>
#include <vector>
#include <algorithm>
#include "Parser.h"
#include "ScanConvert.h"

using namespace std;

//frame and z buffers, drawing image to screen
//------------------------------------------------------------------------------
float framebuffer[ImageH][ImageW][3];
float zbuffer[ImageH][ImageW];

void clearFramebuffer() {
	for(int i = 0; i < ImageH; i++) {
		for(int j = 0; j < ImageW; j++) {
			framebuffer[i][j][0] = 0.0;
			framebuffer[i][j][1] = 0.0;
			framebuffer[i][j][2] = 0.0;
		}
	}
}

void clearZbuffer() {
	for(int i = 0; i < ImageH; i++) {
		for(int j = 0; j < ImageW; j++) {
			zbuffer[i][j] = 1000.0;
		}
	}
}

void setFramebuffer(int x, int y, Color color) {
	// changes the origin from the lower-left corner to the upper-left corner
	y = ImageH - 1 - y;

	if(color.r <= 1.0)
	if(color.r >= 0.0) framebuffer[y][x][0] = color.r;
	else framebuffer[y][x][0] = 0.0;
	else framebuffer[y][x][0] = 1.0;
	
	if(color.g <= 1.0)
	if(color.g >= 0.0) framebuffer[y][x][1] = color.g;
	else framebuffer[y][x][1] = 0.0;
	else framebuffer[y][x][1] = 1.0;
	
	if(color.b <= 1.0)
	if(color.b >= 0.0) framebuffer[y][x][2] = color.b;
	else framebuffer[y][x][2] = 0.0;
	else framebuffer[y][x][2] = 1.0;
}

void setZbuffer(int x, int y, float Z) {
	zbuffer[y][x] = Z;
}

float getZbuffer(int x, int y) {
	return zbuffer[y][x];
}

void drawit() {
	glDrawPixels(ImageW, ImageH, GL_RGB, GL_FLOAT, framebuffer);
	glFlush();
}

vector<Pt> convertToScreenPoints(vector<Vertex*> vertices) {
	vector<Pt> points;

	for (unsigned int i = 0; i < vertices.size(); i++) {
		Vertex *v = vertices[i];
		Pt p;

		p.x = ((ImageW - 1) / 2)*(1 + v->x);
		p.y = ((ImageH - 1) / 2)*(1 - v->y);
		p.z = v->z;

		p.f[0] = v->normal.x;
		p.f[1] = v->normal.y;
		p.f[2] = v->normal.z;

		points.push_back(p);
	}

	return points;
}

void display() {
	drawit();
}

//Scan convert
//------------------------------------------------------------------------------
void scanConvert(Triangle triangle) {
	//convert window vertices (float) to screen pixels (int)
	vector<Pt> points = convertToScreenPoints(triangle.vertices);
	Color color;

	//how to determine color for triangle
	if (shader == FLAT) {
		color = calculateLight(triangle.normal);
	}
	else {
		for (unsigned int i = 0; i < points.size(); i++) {
			if (shader == GOURAUD) {
				color = calculateLight(triangle.vertices[i]->normal);
				points[i].f[0] = color.r;
				points[i].f[1] = color.g;
				points[i].f[2] = color.b;
			}
			else if (shader == PHONG) {
				points[i].f[0] = triangle.vertices[i]->normal.x;
				points[i].f[1] = triangle.vertices[i]->normal.y;
				points[i].f[2] = triangle.vertices[i]->normal.z;
			}
		}
	}

	//Build active edge table
	vector<vector<Edge> > activeEdgeTable;
	vector<Edge> activeEdgeList;

	// add rows equal to height of image to active edge table
	for (unsigned int i = 0; i < ImageH; i++) {
		vector<Edge> row;

		activeEdgeTable.push_back(row);
	}

	for (unsigned int i = 0; i < points.size(); i++) {
		Edge e;
		int next = (i + 1) % points.size();

		// ignore horizontal lines
		if (points[i].y == points[next].y) continue;

		e.maxY = max(points[i].y, points[next].y);

		//only calculate F values for gouraud and phong shading
		if (shader == GOURAUD || shader == PHONG) {
			e.fIncr[0] = (points[i].f[0] - points[next].f[0]) / (float)(points[i].y - points[next].y);
			e.fIncr[1] = (points[i].f[1] - points[next].f[1]) / (float)(points[i].y - points[next].y);
			e.fIncr[2] = (points[i].f[2] - points[next].f[2]) / (float)(points[i].y - points[next].y);

			if (points[i].y == e.maxY) {
				e.currentF[0] = points[next].f[0];
				e.currentF[1] = points[next].f[1];
				e.currentF[2] = points[next].f[2];
			}
			else {
				e.currentF[0] = points[i].f[0];
				e.currentF[1] = points[i].f[1];
				e.currentF[2] = points[i].f[2];
			}
		}

		//Calculate X, and Z values for all shaders
		e.xIncr = (points[i].x - points[next].x) / (float)(points[i].y - points[next].y);
		e.zIncr = (points[i].z - points[next].z) / (float)(points[i].y - points[next].y);

		if (points[i].y == e.maxY) {
			e.currentX = points[next].x;
			e.currentZ = points[next].z;

			activeEdgeTable[points[next].y].push_back(e);
		}
		else {
			e.currentX = points[i].x;
			e.currentZ = points[i].z;

			activeEdgeTable[points[i].y].push_back(e);
		}
	}

	for (int y = 0; y < ImageH; y++) {
		// add edges into active Edge List
		for (unsigned int i = 0; i < activeEdgeTable[y].size(); i++) {
			activeEdgeList.push_back(activeEdgeTable[y][i]);
		}

		// delete edges from active Edge List
		for (unsigned int i = 0; i < activeEdgeList.size(); i++) {
			if (activeEdgeList[i].maxY <= y) {
				activeEdgeList.erase(activeEdgeList.begin() + i);
				i--;
			}
		}

		// sort according to x value... a little expensive since not always necessary
		sort(activeEdgeList.begin(), activeEdgeList.end());

		// draw scan line
		for (unsigned int i = 0; i < activeEdgeList.size(); i += 2) {
			Edge start = activeEdgeList[i];
			Edge end = activeEdgeList[i + 1];

			float line_length = end.currentX - start.currentX;
			int nearestX = (int)ceil(start.currentX);

			float dZ = (end.currentZ - start.currentZ) / line_length;
			float Z = start.currentZ + dZ * (nearestX - start.currentX);
			float dF[3];
			float F[3];

			//only interpolate data in gouraud and phong shading
			if (shader == GOURAUD || shader == PHONG) {
				//calculate by how much each pixel color needs to change horizontally for this line
				dF[0] = (end.currentF[0] - start.currentF[0]) / line_length;
				dF[1] = (end.currentF[1] - start.currentF[1]) / line_length;
				dF[2] = (end.currentF[2] - start.currentF[2]) / line_length;

				//account for distance to nearest pixel
				F[0] = start.currentF[0] + dF[0] * (nearestX - start.currentX);
				F[1] = start.currentF[1] + dF[1] * (nearestX - start.currentX);
				F[2] = start.currentF[2] + dF[2] * (nearestX - start.currentX);
			}


			for (int x = nearestX; x < end.currentX; x++) {
				//draw pixel with the color interpolated to that point
				if (Z < getZbuffer(x, y)) {
					//if shader is flat, color has already been calculated

					//if shader is gouraud, interpolate color
					if (shader == GOURAUD) {
						color = Color(F[0], F[1], F[2]);
						F[0] += dF[0];
						F[1] += dF[1];
						F[2] += dF[2];
					}
					//if shader is phong, calculate actual color
					else if (shader == PHONG) {
						color = calculateLight(Vec(F[0], F[1], F[2]).normalize());
						F[0] += dF[0];
						F[1] += dF[1];
						F[2] += dF[2];
					}

					setFramebuffer(x, y, color);
					setZbuffer(x, y, Z);
					Z += dZ;
				}
			}
		}

		// update edges in active edge list
		for (unsigned i = 0; i < activeEdgeList.size(); i++) {
			activeEdgeList[i].currentX += activeEdgeList[i].xIncr;
			activeEdgeList[i].currentZ += activeEdgeList[i].zIncr;

			if (shader == GOURAUD || shader == PHONG) {
				activeEdgeList[i].currentF[0] += activeEdgeList[i].fIncr[0];
				activeEdgeList[i].currentF[1] += activeEdgeList[i].fIncr[1];
				activeEdgeList[i].currentF[2] += activeEdgeList[i].fIncr[2];
			}
		}
	}
}

void drawShape() {
	//calculate and normalize vectors on all faces and vertices
	for (unsigned int i = 0; i < faces.size(); i++) {
		faces[i].calculateFaceNormal();
		faces[i].calculateVertexNormals();
	}
	for (unsigned int i = 0; i < faces.size(); i++) {
		faces[i].normalizeVertexNormals();
	}
	for (unsigned int i = 0; i < faces.size(); i++) {
		//backface culling
		if (faces[i].normal.z < 0) {
			scanConvert(faces[i]);
		}
	}
}

//Lighting equations
//------------------------------------------------------------------------------
Color calculateLight(Vec _N) {
	Vec L = Vec(1, 1, -1).normalize(); 
	Vec E = Vec(0, 0, -1).normalize(); 
	Vec N = _N; 
	Vec R; 

	//Ambient Light: I = K_a*A
	float A[3]   = { 0.5, 0.5, 0.5 }; 
	float K_a[3] = { 0.1, 0.0, 0.0 };
	float amb[3];

	//Diffuse Light: I = C*K_d*(L*N) 
	float C[3]   = { 1.0, 1.0, 1.0 }; 
	float K_d[3] = { 0.7, 0.0, 0.0 };
	float diff[3];

	//Specular Light: I = C*K_s*(R*E)^n 
	float K_s[3] = { 0.5, 0.5, 0.5 }; 
	int n = 5;
	float spec[3];

	float L_dot_N = Vec::dotProduct(L, N);

	R.x = (2 * L_dot_N * N.x) - L.x;
	R.y = (2 * L_dot_N * N.y) - L.y;
	R.z = (2 * L_dot_N * N.z) - L.z;
	R = R.normalize();
	float R_dot_E = max(0.0, Vec::dotProduct(R, E));

	float I[3];
	for (int i = 0; i < 3; i++) {
		amb[i] = K_a[i] * A[i];
		diff[i] = (L_dot_N > 0) ? K_d[i] * C[i] * L_dot_N : 0;
		spec[i] = (L_dot_N > 0) ? K_d[i] * C[i] * pow(R_dot_E, n) : 0;;

		I[i] = amb[i] + diff[i] + spec[i];
	}

	return Color(I[0], I[1], I[2]);
}

//Program interface
//------------------------------------------------------------------------------
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		cout << "drawing: FLAT \n";
		clearFramebuffer();
		clearZbuffer();
		shader = FLAT;
		drawShape();
		drawit();
		break;
	case '2':
		cout << "drawing: GOURAUD \n";
		clearFramebuffer();
		clearZbuffer();
		shader = GOURAUD;
		drawShape();
		drawit();
		break;
	case '3':
		cout << "drawing: PHONG \n";
		clearFramebuffer();
		clearZbuffer();
		shader = PHONG;
		drawShape();
		drawit();
		break;
	case '4':
		//draw wireframe of object
		cout << "drawing: WIREFRAME \n";
		clearFramebuffer();
		clearZbuffer();

		glColor3f(1.0, 0.0, 0.0);

		for (unsigned int i = 0; i < faces.size(); i++) {
			vector<Pt> points = convertToScreenPoints(faces[i].vertices);

			if (faces[i].normal.z < 0) {
				glBegin(GL_LINE_LOOP);
				for (unsigned int i = 0; i < points.size(); i++) {
					glVertex3f(points[i].x, points[i].y, 1.0);
				}
				glEnd();
			}
		}
		glFlush();

		break;
	case 'q':
		cout << "parsing new file: cube.obj \n";
		faces = Parser::parseFile("cube.obj");
		break;
	case 'w':
		cout << "parsing new file: cube2.obj \n";
		faces = Parser::parseFile("cube2.obj");
		break;
	case 'e':
		cout << "parsing new file: sphere.obj \n";
		faces = Parser::parseFile("sphere.obj");
		break;
	case 'r':
		cout << "parsing new file: cow.obj \n";
		faces = Parser::parseFile("cow.obj");
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ImageW, ImageH);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Casey Brooks - Homework 4");
	glOrtho(0, ImageW, ImageH, 0, -1, 1);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	//initialize program by parsing a file and gouraud shading it
	if (argc > 1) {
		cout << "displaying argc: " << argv[1] << "\n";
		faces = Parser::parseFile(argv[1]);
	}
	else {
		cout << "displaying default: cube2.obj\n";
		faces = Parser::parseFile("cube2.obj");
	}
	clearFramebuffer();
	clearZbuffer();
	shader = GOURAUD;
	drawShape();
	drawit();

	glutMainLoop();
	return 0;
}
