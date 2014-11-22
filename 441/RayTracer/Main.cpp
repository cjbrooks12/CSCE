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
#include "Cylinder.h"

#define ImageW 600
#define ImageH 600


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
			screen.y = ((2 * y) / (float)(ImageH - 1)) - 1;

			Vec V;
			V.x = screen.x - scene.camera.x;
			V.y = screen.y - scene.camera.y;
			V.z = 0 - scene.camera.z;
			V.normalize();

			//cast ray into scene, let magic commence
			Color color = scene.castRay(V, screen, 6);

			//store color into framebuffer
			setFramebuffer(x, y, color);
		}
	}
}

//define the four different scenes
//------------------------------------------------------------------------------
Scene scene1() {
	Scene scene;

	//This scene has 1 light sources
	Light source1;
	source1.source = Point(0, 0, 50);
	source1.C[0] = source1.C[1] = source1.C[2] = 0.25;

	Light source2;
	source2.source = Point(0, 0, 0);
	source2.C[0] = source2.C[1] = source2.C[2] = 1.0;

	//red bottom plane
	Plane *plane1 = new Plane();
	plane1->O = Point(0, -1, 0);
	plane1->N = Vec(0, 1, 0).normalize();
	plane1->isCheckered = true;

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

	plane1->isReflective = false;
	plane1->G_e = 0.5;


	//green back plane
	Plane *plane2 = new Plane();
	plane2->O = Point(0, 0, 2);
	plane2->N = Vec(0, 0, -1).normalize();
	plane2->isCheckered = true;

	plane2->K_a[0] = 0.0;
	plane2->K_a[1] = 0.1;
	plane2->K_a[2] = 0.0;

	plane2->K_d[0] = 0.0;
	plane2->K_d[1] = 0.5;
	plane2->K_d[2] = 0.0;

	plane2->K_s[0] = 1.0;
	plane2->K_s[1] = 1.0;
	plane2->K_s[2] = 1.0;

	plane2->n = 5;

	plane2->isReflective = false;
	plane2->G_e = 1.0;

	//blue left plane
	Plane *plane3 = new Plane();
	plane3->O = Point(-2, 0, 0);
	plane3->N = Vec(1, 0, 0).normalize();
	plane3->isCheckered = false;

	plane3->K_a[0] = 0.0;
	plane3->K_a[1] = 0.0;
	plane3->K_a[2] = 0.1;

	plane3->K_d[0] = 0.0;
	plane3->K_d[1] = 0.0;
	plane3->K_d[2] = 0.5;

	plane3->K_s[0] = 1.0;
	plane3->K_s[1] = 1.0;
	plane3->K_s[2] = 1.0;

	plane3->n = 5;

	plane3->isReflective = false;
	plane3->G_e = 0.5;

	//blue right plane
	Plane *plane4 = new Plane();
	plane4->O = Point(2, 0, 0);
	plane4->N = Vec(-1, 0, 0).normalize();
	plane4->isCheckered = false;

	plane4->K_a[0] = 0.0;
	plane4->K_a[1] = 0.0;
	plane4->K_a[2] = 0.1;

	plane4->K_d[0] = 0.0;
	plane4->K_d[1] = 0.0;
	plane4->K_d[2] = 0.5;

	plane4->K_s[0] = 1.0;
	plane4->K_s[1] = 1.0;
	plane4->K_s[2] = 1.0;

	plane4->n = 5;

	plane4->isReflective = false;
	plane4->G_e = 0.5;

	//red top plane
	Plane *plane5 = new Plane();
	plane5->O = Point(0, 1, 0);
	plane5->N = Vec(0, -1, 0).normalize();
	plane5->isCheckered = true;

	plane5->K_a[0] = 0.1;
	plane5->K_a[1] = 0.0;
	plane5->K_a[2] = 0.0;

	plane5->K_d[0] = 0.5;
	plane5->K_d[1] = 0.0;
	plane5->K_d[2] = 0.0;

	plane5->K_s[0] = 1.0;
	plane5->K_s[1] = 1.0;
	plane5->K_s[2] = 1.0;

	plane5->n = 5;

	plane5->isReflective = false;
	plane5->G_e = 0.5;


	//green sphere
	Sphere *sphere1 = new Sphere();
	sphere1->C = Point(-1, 0, 1);
	sphere1->r = 0.5;

	sphere1->K_a[0] = 0.0;
	sphere1->K_a[1] = 0.1;
	sphere1->K_a[2] = 0.0;

	sphere1->K_d[0] = 0.0;
	sphere1->K_d[1] = 0.75;
	sphere1->K_d[2] = 0.0;

	sphere1->K_s[0] = 1.0;
	sphere1->K_s[1] = 1.0;
	sphere1->K_s[2] = 1.0;

	sphere1->n = 1;

	//yellow sphere
	Sphere *sphere2 = new Sphere();
	sphere2->C = Point(1, 0, 1);
	sphere2->r = 0.5;

	sphere2->K_a[0] = 0.1;
	sphere2->K_a[1] = 0.0;
	sphere2->K_a[2] = 0.1;

	sphere2->K_d[0] = 0.75;
	sphere2->K_d[1] = 0.0;
	sphere2->K_d[2] = 0.75;

	sphere2->K_s[0] = 1.0;
	sphere2->K_s[1] = 1.0;
	sphere2->K_s[2] = 1.0;

	sphere2->n = 15;

	//yellow sphere
	Sphere *sphere3 = new Sphere();
	sphere3->C = Point(0, 0, 1.0);
	sphere3->r = 0.75;

	sphere3->K_a[0] = 0.1;
	sphere3->K_a[1] = 0.0;
	sphere3->K_a[2] = 0.1;

	sphere3->K_d[0] = 0.75;
	sphere3->K_d[1] = 0.25;
	sphere3->K_d[2] = 0.75;

	sphere3->K_s[0] = 1.0;
	sphere3->K_s[1] = 1.0;
	sphere3->K_s[2] = 1.0;

	sphere3->n = 8;

	//add all lights and objects to scene
	scene.lights.push_back(source1); //white light in front
	scene.lights.push_back(source2); //white light in back

	scene.objects.push_back(plane1); //red bottom plane
	scene.objects.push_back(plane3); //blue left plane
	scene.objects.push_back(plane4); //blue left plane
	scene.objects.push_back(plane5); //red top plane

	scene.objects.push_back(sphere1); //red top plane
	scene.objects.push_back(sphere2); //red top plane
	scene.objects.push_back(sphere3); //red top plane


	return scene;
}

Scene scene2() {
	Scene scene;
	scene.backgroundColor = Color(0.4, 0.8, 0.9);

	//This scene has 4 light sources
	Light source1;
	source1.source = Point(2.5, -0.35, 2);
	source1.C[0] = source1.C[1] = source1.C[2] = 0.75;

	Light source2;
	source2.source = Point(-2.5, -0.35, 2.0);
	source2.C[0] = source2.C[1] = source2.C[2] = 0.75;

	Light source3;
	source3.source = Point(1.5, 1, 0.0);
	source3.C[0] = source3.C[1] = source3.C[2] = 0.5;

	Light source4;
	source4.source = Point(-1.5, 1, 0.0);
	source4.C[0] = source4.C[1] = source4.C[2] = 0.5;

	Light source5;
	source5.source = Point(0, 6, 25);
	source5.C[0] = 0.0;
	source5.C[1] = 0.0;
	source5.C[2] = 0.5;

	//yellow sphere
	Sphere *sphere1 = new Sphere();
	sphere1->C = Point(-0.75, -0.35, 1);
	sphere1->r = 0.5;

	sphere1->K_a[0] = 0.1;
	sphere1->K_a[1] = 0.1;
	sphere1->K_a[2] = 0.0;

	sphere1->K_d[0] = 0.75;
	sphere1->K_d[1] = 0.75;
	sphere1->K_d[2] = 0.0;

	sphere1->K_s[0] = 1.0;
	sphere1->K_s[1] = 1.0;
	sphere1->K_s[2] = 1.0;

	sphere1->n = 50;

	sphere1->isReflective = true;
	sphere1->G_e = 0.25;

	//cyan sphere
	Sphere *sphere2 = new Sphere();
	sphere2->C = Point(0.75, -0.35, 1);
	sphere2->r = 0.5;

	sphere2->K_a[0] = 0.0;
	sphere2->K_a[1] = 0.1;
	sphere2->K_a[2] = 0.1;

	sphere2->K_d[0] = 0.0;
	sphere2->K_d[1] = 0.15;
	sphere2->K_d[2] = 0.15;

	sphere2->K_s[0] = 1.0;
	sphere2->K_s[1] = 1.0;
	sphere2->K_s[2] = 1.0;

	sphere2->n = 50;

	sphere2->isReflective = true;
	sphere2->G_e = 1.0;

	//large green sphere
	Sphere *sphere3 = new Sphere();
	sphere3->C = Point(0, 1.0, 2.0);
	sphere3->r = 1.0;

	sphere3->K_a[0] = 0.1;
	sphere3->K_a[1] = 0.1;
	sphere3->K_a[2] = 0.1;

	sphere3->K_d[0] = 0.31;
	sphere3->K_d[1] = 0.54;
	sphere3->K_d[2] = 0.31;

	sphere3->K_s[0] = 1.0;
	sphere3->K_s[1] = 1.0;
	sphere3->K_s[2] = 1.0;

	sphere3->n = 5;

	sphere3->isReflective = false;


	//red plane
	Plane *plane1 = new Plane();
	plane1->O = Point(0, -1, 0);
	plane1->N = Vec(0, 1, -0.25).normalize();
	plane1->isCheckered = false;

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

	plane1->isReflective = false;
	plane1->G_e = 1.0;

	//large green sphere
	Cylinder *cylinder1 = new Cylinder();
	cylinder1->C = Point(2, 0, 2.5);
	cylinder1->A = Vec(0, 1, 0);
	cylinder1->r = 0.5;

	cylinder1->K_a[0] = 0.1;
	cylinder1->K_a[1] = 0.1;
	cylinder1->K_a[2] = 0.1;

	cylinder1->K_d[0] = 1.0;
	cylinder1->K_d[1] = 1.0;
	cylinder1->K_d[2] = 1.0;

	cylinder1->K_s[0] = 1.0;
	cylinder1->K_s[1] = 1.0;
	cylinder1->K_s[2] = 1.0;

	cylinder1->n = 5;

	cylinder1->isReflective = false;

	//large green sphere
	Cylinder *cylinder2 = new Cylinder();
	cylinder2->C = Point(-2, 0, 2.5);
	cylinder2->A = Vec(0, 1, 0);
	cylinder2->r = 0.5;

	cylinder2->K_a[0] = 0.1;
	cylinder2->K_a[1] = 0.1;
	cylinder2->K_a[2] = 0.1;

	cylinder2->K_d[0] = 1.0;
	cylinder2->K_d[1] = 1.0;
	cylinder2->K_d[2] = 1.0;

	cylinder2->K_s[0] = 1.0;
	cylinder2->K_s[1] = 1.0;
	cylinder2->K_s[2] = 1.0;

	cylinder2->n = 5;

	cylinder2->isReflective = false;


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
	scene.objects.push_back(cylinder1); //cylinder
	scene.objects.push_back(cylinder2); //cylinder

	return scene;
}

Scene scene3() {
	Scene scene;
	scene.camera = Point(-0.25, 0.5, -5);

	Light source1;
	source1.source = Point(0, 1.5, 1);
	source1.C[0] = 1.0;
	source1.C[1] = 1.0;
	source1.C[2] = 1.0;

	Light source2;
	source2.source = Point(0, -0.99, 2);
	source2.C[0] = 1.0;
	source2.C[1] = 1.0;
	source2.C[2] = 1.0;
	
	//large green sphere
	Sphere *sphere1 = new Sphere();
	sphere1->C = Point(-1.0, 0.05, 2.5);
	sphere1->r = 1.0;

	sphere1->K_a[0] = 0.1;
	sphere1->K_a[1] = 0.1;
	sphere1->K_a[2] = 0.1;

	sphere1->K_d[0] = 0.31;
	sphere1->K_d[1] = 0.54;
	sphere1->K_d[2] = 0.31;

	sphere1->K_s[0] = 0.62;
	sphere1->K_s[1] = 1.0;
	sphere1->K_s[2] = 0.62;

	sphere1->n = 5;

	sphere1->isReflective = true;
	sphere1->G_e = 0.75;

	//large green sphere
	Sphere *sphere2 = new Sphere();
	sphere2->C = Point(0, 0, 0.25);
	sphere2->r = 0.25;

	sphere2->K_a[0] = 0.1;
	sphere2->K_a[1] = 0.1;
	sphere2->K_a[2] = 0.1;

	sphere2->K_d[0] = 0.31;
	sphere2->K_d[1] = 0.54;
	sphere2->K_d[2] = 0.31;

	sphere2->K_s[0] = 0.62;
	sphere2->K_s[1] = 1.0;
	sphere2->K_s[2] = 0.62;

	sphere2->n = 5;

	sphere2->isReflective = true;
	sphere2->G_e = 0.75;


	//medium green sphere
	Sphere *sphere3 = new Sphere();
	sphere3->C = Point(0, 0.5, 1.5);
	sphere3->r = 0.5;

	sphere3->K_a[0] = 0.1;
	sphere3->K_a[1] = 0.1;
	sphere3->K_a[2] = 0.1;

	sphere3->K_d[0] = 0.31;
	sphere3->K_d[1] = 0.54;
	sphere3->K_d[2] = 0.31;

	sphere3->K_s[0] = 0.62;
	sphere3->K_s[1] = 1.0;
	sphere3->K_s[2] = 0.62;

	sphere3->n = 5;

	sphere3->isReflective = true;
	sphere3->G_e = 0.75;

	//medium green sphere
	Sphere *sphere4 = new Sphere();
	sphere4->C = Point(0.25, -0.25, 0.35);
	sphere4->r = 0.15;

	sphere4->K_a[0] = 0.1;
	sphere4->K_a[1] = 0.1;
	sphere4->K_a[2] = 0.1;

	sphere4->K_d[0] = 0.31;
	sphere4->K_d[1] = 0.54;
	sphere4->K_d[2] = 0.31;

	sphere4->K_s[0] = 0.62;
	sphere4->K_s[1] = 1.0;
	sphere4->K_s[2] = 0.62;

	sphere4->n = 5;

	sphere4->isReflective = true;
	sphere4->G_e = 0.75;


	//red plane
	Plane *plane1 = new Plane();
	plane1->O = Point(0, -1, -0.5);
	plane1->N = Vec(0, 1, 0).normalize();
	plane1->isCheckered = true;

	plane1->K_a[0] = 0.1;
	plane1->K_a[1] = 0.0;
	plane1->K_a[2] = 0.0;

	plane1->K_d[0] = 1.0;
	plane1->K_d[1] = 0.0;
	plane1->K_d[2] = 0.0;

	plane1->K_s[0] = 1.0;
	plane1->K_s[1] = 1.0;
	plane1->K_s[2] = 1.0;

	plane1->n = 5;

	plane1->isReflective = false;
	plane1->G_e = 1.0;


	//add all lights and objects to scene
	scene.lights.push_back(source1); //white light above sphere
	scene.lights.push_back(source2); //white light above sphere

	scene.objects.push_back(sphere1); //large green sphere
	scene.objects.push_back(sphere2); //small green sphere
	scene.objects.push_back(sphere3); //medium green sphere
	scene.objects.push_back(sphere4); //very small green sphere
	scene.objects.push_back(plane1); //red plane

	return scene;
}

Scene scene4() {
	Scene scene;
	scene.camera = Point(0, 0, -1);

	Light source1;
	source1.source = Point(2, 2, 1);
	source1.C[0] = source1.C[1] = source1.C[2] = 1.0;

	Light source2;
	source2.source = Point(-2, 2, 1);
	source2.C[0] = source2.C[1] = source2.C[2] = 1.0;

	Light source3;
	source3.source = Point(2, 2, 4);
	source3.C[0] = source3.C[1] = source3.C[2] = 1.0;

	Light source4;
	source4.source = Point(-2, 2, 4);
	source4.C[0] = source4.C[1] = source4.C[2] = 1.0;

	//red plane
	Plane *plane1 = new Plane();
	plane1->O = Point(0, -1, 0);
	plane1->N = Vec(0, 1, 0).normalize();
	plane1->isCheckered = true;

	plane1->K_a[0] = 0.1;
	plane1->K_a[1] = 0.1;
	plane1->K_a[2] = 0.1;

	plane1->K_d[0] = 0.5;
	plane1->K_d[1] = 0.5;
	plane1->K_d[2] = 0.5;

	plane1->K_s[0] = 1.0;
	plane1->K_s[1] = 1.0;
	plane1->K_s[2] = 1.0;

	plane1->n = 5;

	plane1->isReflective = false;
	plane1->G_e = 1.0;

	for (int i = -10; i != 10; i++) {
		for (int j = 1; j < 10; j++) {
			//for (int k = 0; k < 6; k++) {
				float k = 0.5;
				Sphere *sphere1 = new Sphere();
				sphere1->C = Point(i, k-1, j);
				sphere1->r = 0.25;

				sphere1->K_a[0] = 0.1*i;
				sphere1->K_a[1] = 0.1*j;
				sphere1->K_a[2] = 0.1*k;

				sphere1->K_d[0] = 0.1*i;
				sphere1->K_d[1] = 0.1*j;
				sphere1->K_d[2] = 0.1*k;

				sphere1->K_s[0] = 0.1*i;
				sphere1->K_s[1] = 0.1*j;
				sphere1->K_s[2] = 0.1*k;

				sphere1->n = 5;

				sphere1->isReflective = true;
				sphere1->G_e = 1.0;
				scene.objects.push_back(sphere1);
			//}
		}
	}


	scene.lights.push_back(source1);
	scene.lights.push_back(source2);
	scene.lights.push_back(source3);
	scene.lights.push_back(source4);
	scene.objects.push_back(plane1);
	
	return scene;
}


//Program interface
//------------------------------------------------------------------------------
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		cout << "drawing Scene 1, please wait...";
		clearFramebuffer();
		render(scene1());
		display();
		cout << "done\n";
		break;
	case '2':
		cout << "drawing Scene 2, please wait...";
		clearFramebuffer();
		render(scene2());
		display();
		cout << "done\n";
		break;
	case '3':
		cout << "drawing Scene 3, please wait...";
		clearFramebuffer();
		render(scene3());
		display();
		cout << "done\n";
		break;
	case '4':
		cout << "drawing Scene 4, please wait...";
		clearFramebuffer();
		render(scene4());
		display();
		cout << "done\n";
		break;
	}
}

void init() {

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ImageW, ImageH);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Casey Brooks - Homework 5");
	glOrtho(0, ImageW, ImageH, 0, -1, 1);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	init();

	glutMainLoop();
	return 0;
}
