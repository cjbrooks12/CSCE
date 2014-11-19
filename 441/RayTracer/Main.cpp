#include <Windows.h>
#include <gl/glut.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>

#include "Color.h"
#include "Vec.h"
#include "Scene.h"

#include "Object.h"
#include "Sphere.h"
#include "Plane.h"

using namespace std;

//frame buffer
//------------------------------------------------------------------------------
float framebuffer[ImageH][ImageW][3];
float zbuffer[ImageH][ImageW];

void clearFramebuffer() {
	for (int i = 0; i < ImageH; i++) {
		for (int j = 0; j < ImageW; j++) {
			framebuffer[i][j][0] = 0.0;
			framebuffer[i][j][1] = 0.0;
			framebuffer[i][j][2] = 0.0;
		}
	}
}

void setFramebuffer(int x, int y, Color color) {
	// changes the origin from the lower-left corner to the upper-left corner

	if (color.r <= 1.0)
	if (color.r >= 0.0) framebuffer[y][x][0] = color.r;
	else framebuffer[y][x][0] = 0.0;
	else framebuffer[y][x][0] = 1.0;

	if (color.g <= 1.0)
	if (color.g >= 0.0) framebuffer[y][x][1] = color.g;
	else framebuffer[y][x][1] = 0.0;
	else framebuffer[y][x][1] = 1.0;

	if (color.b <= 1.0)
	if (color.b >= 0.0) framebuffer[y][x][2] = color.b;
	else framebuffer[y][x][2] = 0.0;
	else framebuffer[y][x][2] = 1.0;
}

void display() {
	glDrawPixels(ImageW, ImageH, GL_RGB, GL_FLOAT, framebuffer);
	glFlush();
}

//RayTracing algorithm
//------------------------------------------------------------------------------
Point camera(0.0, 0.0, -1.0);

void render(Scene scene) {
	for (int y = 0; y < ImageH; y++) {
		for (int x = 0; x < ImageW; x++) {
			/*
			RAYTRACING ALGORITHM
			-create ray from viewer to pixel
			-shoot ray into scene
			-do magic
			-store color value into frame buffer
			*/

			//calculate ray from camera to pixel
			Point screen;
			screen.x = ((2 * x) / (float)(ImageW - 1)) - 1;
			screen.y = (1 - (2 * y) / (float)(ImageH - 1));

			Vec V;
			V.x = screen.x - camera.x;
			V.y = screen.y - camera.y;
			V.z = 0 - camera.z;
			V.normalize();

			//cast ray into scene, let magic commence
			Color color = scene.castRay(V, screen, 1);

			//store color into framebuffer
			setFramebuffer(x, y, color);
		}
	}
}

//define the four different scenes
//------------------------------------------------------------------------------
Scene scene1() {
	Scene scene;

	//This scene has 2 light sources
	Light source1;
	source1.source = Point(2.0, 0, 2.0);
	source1.C[0] = source1.C[1] = source1.C[2] = 1.0;

	Light source2;
	source2.source = Point(-2.0, 0, 2.0);
	source2.C[0] = source2.C[1] = source2.C[2] = 1.0;

	Light source3;
	source3.source = Point(1.5, -0.45, 0);
	source3.C[0] = source3.C[1] = source3.C[2] = 0.5;

	Light source4;
	source4.source = Point(-1.5, -0.45, 0);
	source4.C[0] = source4.C[1] = source4.C[2] = 0.5;

	Light source5;
	source5.source = Point(0, -5.75, 25);
	source5.C[0] = 0.0;
	source5.C[1] = 0.0;
	source5.C[2] = 0.5;

	//yellow sphere
	Sphere *sphere1 = new Sphere();
	sphere1->C = Point(-1.0, 0.35, 1);
	sphere1->r = 0.5;

	sphere1->K_a[0] = 0.1;
	sphere1->K_a[1] = 0.1;
	sphere1->K_a[2] = 0.0;

	sphere1->K_d[0] = 0.75;
	sphere1->K_d[1] = 0.75;
	sphere1->K_d[2] = 0.0;

	sphere1->K_s[0] = 0.25;
	sphere1->K_s[1] = 0.25;
	sphere1->K_s[2] = 0.25;

	sphere1->n = 1;

	//cyan sphere
	Sphere *sphere2 = new Sphere();
	sphere2->C = Point(1.0, 0.35, 1);
	sphere2->r = 0.5;

	sphere2->K_a[0] = 0.0;
	sphere2->K_a[1] = 0.1;
	sphere2->K_a[2] = 0.1;

	sphere2->K_d[0] = 0.0;
	sphere2->K_d[1] = 1.0;
	sphere2->K_d[2] = 1.0;

	sphere2->K_s[0] = 1.0;
	sphere2->K_s[1] = 1.0;
	sphere2->K_s[2] = 1.0;

	sphere2->n = 50;

	sphere2->isReflective = true;
	sphere2->G_e[0] = 0.1;
	sphere2->G_e[0] = 0.1;
	sphere2->G_e[0] = 0.1;

	//large green sphere
	Sphere *sphere3 = new Sphere();
	sphere3->C = Point(0, 0.0, 2.0);
	sphere3->r = 1.0;

	sphere3->K_a[0] = 0.1;
	sphere3->K_a[1] = 0.1;
	sphere3->K_a[2] = 0.1;

	sphere3->K_d[0] = 0.31;
	sphere3->K_d[1] = 0.54;
	sphere3->K_d[2] = 0.31;

	sphere3->K_s[0] = 0.62;
	sphere3->K_s[1] = 1.0;
	sphere3->K_s[2] = 0.61;

	sphere3->n = 3;

	sphere3->isReflective = true;
	sphere3->G_e[0] = 0.5;
	sphere3->G_e[0] = 0.5;
	sphere3->G_e[0] = 0.5;

	//red plane
	Plane *plane1 = new Plane();
	plane1->O = Point(0, 0.65, 0);
	plane1->N = Vec(0, -1, -0.25).normalize();

	plane1->K_a[0] = 0.1;
	plane1->K_a[1] = 0.0;
	plane1->K_a[2] = 0.0;

	plane1->K_d[0] = 0.5;
	plane1->K_d[1] = 0.0;
	plane1->K_d[2] = 0.0;

	plane1->K_s[0] = 1.0;
	plane1->K_s[1] = 1.0;
	plane1->K_s[2] = 1.0;

	plane1->n = 5;

	//add all lights and objects to scene
	scene.lights.push_back(source1); //white light to right
	scene.lights.push_back(source2); //white light to left
	scene.lights.push_back(source3); //white light in center
	scene.lights.push_back(source4); //blue light in back
	scene.lights.push_back(source5); //blue light in back

	scene.objects.push_back(sphere1); //yellow sphere
	scene.objects.push_back(sphere2); //cyan sphere
	scene.objects.push_back(sphere3); //large green sphere
	scene.objects.push_back(plane1); //red plane

	return scene;
}

//Scene scene2() {
//	Scene scene;
//	return scene;
//}
//
//Scene scene3() {
//	Scene scene;
//	return scene;
//}
//
//Scene scene4() {
//	Scene scene;
//	return scene;
//}

//Program interface
//------------------------------------------------------------------------------
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		cout << "drawing Scene 1, please wait... \n";
		clearFramebuffer();
		render(scene1());
		display();
		break;
	//case '2':
	//	cout << "drawing Scene 2, please wait... \n";
	//	clearFramebuffer();
	//	render(scene2());
	//	display();
	//	break;
	//case '3':
	//	cout << "drawing Scene 3, please wait... \n";
	//	clearFramebuffer();
	//	render(scene3());
	//	display();
	//	break;
	//case '4':
	//	cout << "drawing Scene 4, please wait... \n";
	//	clearFramebuffer();
	//	render(scene4());
	//	display();
	//	break;
	}
}

void init() {

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ImageW, ImageH);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Casey Brooks - Homework 5");
	glOrtho(0, ImageW, ImageH, 0, -1, 1);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	init();

	glutMainLoop();
	return 0;
}
