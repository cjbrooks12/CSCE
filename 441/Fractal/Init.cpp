#include <iostream>
#include "Init.h"
#include "FractalMain.h"
#include <GL/glut.h>

using namespace std;

/**
* Don't put anything in this file except for testing purposes
* because I will overwrite it when grading your assignment.
*/

/*
Structure of a Fractal:
	Set the transformations
	Set the initial points
	Set the number of iterations
*/

float PI = 3.1415926535;
void init() {
	sierpinski();
}

void hangman() {
	Pt ll(-0.9, -0.9);
	Pt lr(0.9, -0.9);
	Pt ul(-0.9, 0.9);
	vector<Matrix> iat;
	iat.push_back(scale(ll, 0.5));
	iat.push_back(scale(lr, 0.5));

	vector<Matrix> curl;
	curl.push_back(rotate(ll, PI / -2));
	curl.push_back(scale(ll, 0.5));
	curl.push_back(translate(Vec(0, 1.8)));

	iat.push_back(compose_all(curl));
	setIATTransformations(iat);

	vector<Pt> pts;
	pts.push_back(Pt(-0.5, -0.5));
	pts.push_back(Pt(-0.5, 0.5));
	pts.push_back(Pt(0.5, 0.5));
	pts.push_back(Pt(0.5, -0.5));
	setCondensationSet(vector<Pt>());

	setIterations(10);

	glutPostRedisplay();
}

void staircase() {
	vector<Matrix> iat;
	iat.push_back(scale(Pt(-0.9, -0.9), 0.5));
	iat.push_back(translate(Pt(0, 0)));
	iat.push_back(scale(Pt(0.9, 0.9), 0.5));
	iat.push_back(translate(Pt(0, 0)));
	setIATTransformations(iat);

	//filled triangle as condensation set
	vector<Pt> pts;
	pts.push_back(Pt(0.9, -0.9));
	pts.push_back(Pt(0, -0.9));
	pts.push_back(Pt(0, 0));
	pts.push_back(Pt(0.9, 0));
	setCondensationSet(pts);
	fillCondensationSet(false);

	setIterations(7);

	glutPostRedisplay();
}

void snowflake() {
	vector<Matrix> iat;
	vector<Pt> pts;

	for (int i = 0; i <= 5; i++){
		float theta = 2 * PI * i / 5;
		Pt point((0.35)* cosf(theta + PI / 10), (0.35)* sinf(theta + PI / 10));
		pts.push_back(point);
		iat.push_back(compose(translate(point), scale(point, 0.4)));
	}

	iat.push_back(compose(rotate(Pt(0, 0), PI / 5), scale(Pt(0, 0), 0.4)));

	setIATTransformations(iat);
	setCondensationSet(pts);
	fillCondensationSet(false);

	setIterations(6);

	glutPostRedisplay();
}

void flower() {
	vector<Matrix> iat;
	vector<Pt> pts;

	for (int i = 0; i <= 6; i++){
		float theta = 2 * PI * i / 6;
		Pt point((0.25)* cosf(theta), (0.25)* sinf(theta));
		pts.push_back(point);
		iat.push_back(compose(translate(point), scale(point, 1.0 / 3.0)));
	}

	setIATTransformations(iat);
	setCondensationSet(pts);
	fillCondensationSet(false);

	setIterations(5);

	glutPostRedisplay();
}

void sierpinski() {
	vector<Matrix> iat;
	iat.push_back(scale(Pt(-0.9, -0.7), 0.5));
	iat.push_back(scale(Pt(0.9, -0.7), 0.5));
	iat.push_back(scale(Pt(0, 0.7), 0.5));
	setIATTransformations(iat);
	
	//filled triangle as condensation set
	vector<Pt> pts;
	pts.push_back(Pt(-0.9, -0.7));
	pts.push_back(Pt(0.9, -0.7));
	pts.push_back(Pt(0.0, 0.7));
	setCondensationSet(pts);
	fillCondensationSet(true);

	setIterations(6);

	glutPostRedisplay();
}

void treetop() {
	vector<Matrix> iat;
	Matrix m1 = compose(rotate(Pt(0, 0), PI/4), scale(Pt(0, 0.75), 0.75));
	Matrix m2 = compose(rotate(Pt(0, 0), PI/-4), scale(Pt(0, 0.75), 0.75));
	iat.push_back(m1);
	iat.push_back(m2);
	setIATTransformations(iat);

	//line as condensation set
	vector<Pt> pts;
	pts.push_back(Pt(-0.5, -0.5));
	pts.push_back(Pt(0.5, -0.5));
	setCondensationSet(pts);

	setIterations(17);

	glutPostRedisplay();
}

void circlefield() {
	vector<Matrix> iat;

	iat.push_back(rotate(Pt(0, 0.27), PI / 4));
	iat.push_back(rotate(Pt(0, -0.27), PI / 4));
	iat.push_back(scale(Pt(0, 0), 0.05));

	setIATTransformations(iat);

	vector<Pt> pts;

	//empty circle as condensation set
	for (int i = 0; i <= 36; i++){
		float theta = 2 * PI * i / 36;
		pts.push_back(Pt((0.5)* cosf(theta), (0.5)* sinf(theta)));
	}
	setCondensationSet(pts);
	fillCondensationSet(false);

	setIterations(8);

	glutPostRedisplay();
}