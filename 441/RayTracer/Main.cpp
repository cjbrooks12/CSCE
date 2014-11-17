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
Point camera(0, 0.5, -100.0);

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
			screen.x = (x / (ImageW / 2.0f)) - 1;
			screen.y = (y / (ImageH / 2.0f)) + 1;

			Vec V;
			V.x = screen.x - camera.x;
			V.y = screen.y - camera.y;
			V.z = 0 - camera.z;
			V.normalize();

			//cast ray into scene, let magic commence
			Color color = scene.castRay(V, camera);

			//store color into framebuffer
			setFramebuffer(x, y, color);
		}
	}
}

//define the four different scenes
//------------------------------------------------------------------------------
Scene scene1() {
	Scene scene;
	Sphere *sphere = new Sphere();
	sphere->C = Point(0, 2, 0.5);
	sphere->r = 0.5;
	scene.objects = sphere;

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
