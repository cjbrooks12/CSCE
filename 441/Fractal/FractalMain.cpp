#include "FractalMain.h"
#include "Init.h"
#include <Windows.h>
#include <GL/glut.h>


//utility functions
//------------------------------------------------------------------------------
Pt transform(Matrix m, Pt v) {
	/*
	
	[a b c][x]    [ax + by + cz]
	[d e f][y] == [dx + ey + fz]
	[g h i][z]    [gx + hy + iz]
	
	*/

	float a = m.data[0][0];	float b = m.data[0][1];	float c = m.data[0][2];
	float d = m.data[1][0];	float e = m.data[1][1];	float f = m.data[1][2];
	float g = m.data[2][0];	float h = m.data[2][1];	float i = m.data[2][2];

	float x = v.x;
	float y = v.y;
	float z = 1;

	Pt result;
	result.x = (a*x + b*y + c*z);
	result.y = (d*x + e*y + f*z);

	return result;
}

Matrix inverse(Matrix m) {
	// computes the inverse of a matrix m
	double det = m.data[0][0] * (m.data[1][1] * m.data[2][2] - m.data[2][1] * m.data[1][2]) -
		m.data[0][1] * (m.data[1][0] * m.data[2][2] - m.data[1][2] * m.data[2][0]) +
		m.data[0][2] * (m.data[1][0] * m.data[2][1] - m.data[1][1] * m.data[2][0]);

	double invdet = 1 / det;

	Matrix minv; // inverse of matrix m
	minv.data[0][0] = (m.data[1][1] * m.data[2][2] - m.data[2][1] * m.data[1][2]) * invdet;
	minv.data[0][1] = (m.data[0][2] * m.data[2][1] - m.data[0][1] * m.data[2][2]) * invdet;
	minv.data[0][2] = (m.data[0][1] * m.data[1][2] - m.data[0][2] * m.data[1][1]) * invdet;

	minv.data[1][0] = (m.data[1][2] * m.data[2][0] - m.data[1][0] * m.data[2][2]) * invdet;
	minv.data[1][1] = (m.data[0][0] * m.data[2][2] - m.data[0][2] * m.data[2][0]) * invdet;
	minv.data[1][2] = (m.data[1][0] * m.data[0][2] - m.data[0][0] * m.data[1][2]) * invdet;

	minv.data[2][0] = (m.data[1][0] * m.data[2][1] - m.data[2][0] * m.data[1][1]) * invdet;
	minv.data[2][1] = (m.data[2][0] * m.data[0][1] - m.data[0][0] * m.data[2][1]) * invdet;
	minv.data[2][2] = (m.data[0][0] * m.data[1][1] - m.data[1][0] * m.data[0][1]) * invdet;

	return minv;
}

//transformations
//------------------------------------------------------------------------------
Matrix translate(Vec v) {
	Matrix rvalue;

	rvalue.data[0][0] = 1;	rvalue.data[0][1] = 0;	rvalue.data[0][2] = v.x;
	rvalue.data[1][0] = 0;	rvalue.data[1][1] = 1;	rvalue.data[1][2] = v.y;
	rvalue.data[2][0] = 0;	rvalue.data[2][1] = 0;	rvalue.data[2][2] = 1;

	return rvalue;
}

Matrix rotate(Pt p, float theta) {
	Matrix rvalue;

	rvalue.data[0][0] = cos(theta);
	rvalue.data[0][1] = -sin(theta);
	rvalue.data[0][2] = p.x + p.y*sin(theta) - p.x*cos(theta);

	rvalue.data[1][0] = sin(theta);
	rvalue.data[1][1] = cos(theta);
	rvalue.data[1][2] = p.y + p.y*cos(theta) - p.x*sin(theta);

	rvalue.data[2][0] = 0;
	rvalue.data[2][1] = 0;
	rvalue.data[2][2] = 1;

	return rvalue;
}

Matrix scale(Pt p, float alpha) {
	Matrix rvalue;

	rvalue.data[0][0] = alpha;
	rvalue.data[0][1] = 0;
	rvalue.data[0][2] = ((1-alpha)*p.x);

	rvalue.data[1][0] = 0;
	rvalue.data[1][1] = alpha;
	rvalue.data[1][2] = ((1 - alpha)*p.y);

	rvalue.data[2][0] = 0;
	rvalue.data[2][1] = 0;
	rvalue.data[2][2] = 1;

	return rvalue;
}

Matrix nscale(Pt p, Vec v, float alpha) {
	Matrix rvalue;

	rvalue.data[0][0] = 1 + (alpha - 1)*v.x*v.x;
	rvalue.data[0][1] = (alpha - 1)*v.x*v.y;
	rvalue.data[0][2] = v.x*(p.x*v.x + p.y*v.y)*(1 - alpha);

	rvalue.data[1][0] = (alpha - 1)*v.x*v.y;
	rvalue.data[1][1] = 1 + (alpha - 1)*v.y*v.y;
	rvalue.data[1][2] = v.y*(p.x*v.x + p.y*v.y)*(1 - alpha);

	rvalue.data[2][0] = 0;
	rvalue.data[2][1] = 0;
	rvalue.data[2][2] = 1;

	return rvalue;
}

Matrix image(Pt p1, Pt p2, Pt p3, Pt q1, Pt q2, Pt q3) {
	Matrix new_img, old_img;

	new_img.data[0][0] = q1.x;
	new_img.data[0][1] = q2.x;
	new_img.data[0][2] = q3.x;

	new_img.data[1][0] = q1.y;
	new_img.data[1][1] = q2.y;
	new_img.data[1][2] = q3.y;

	new_img.data[2][0] = 0;
	new_img.data[2][1] = 0;
	new_img.data[2][2] = 1;

	old_img.data[0][0] = p1.x;
	old_img.data[0][1] = p2.x;
	old_img.data[0][2] = p3.x;

	old_img.data[1][0] = p1.y;
	old_img.data[1][1] = p2.y;
	old_img.data[1][2] = p3.y;

	old_img.data[2][0] = 0;
	old_img.data[2][1] = 0;
	old_img.data[2][2] = 1;

	return compose(inverse(new_img), old_img);
}

Matrix compose(Matrix m2, Matrix m1) {
	/*

	m2	   m1         rvalue
	[a b c][r s t]    [ar + bu + cx][as + bv + cy][at + bw + cz]
	[d e f][u v w] == [dr + eu + fx][ds + ev + fy][dt + ew + fz]
	[g h i][x y z]    [gr + hu + ix][gs + hv + iy][gt + hw + iz]

	*/

	//set up variables to read easier
	float a = m2.data[0][0];	float b = m2.data[0][1];	float c = m2.data[0][2];
	float d = m2.data[1][0];	float e = m2.data[1][1];	float f = m2.data[1][2];
	float g = m2.data[2][0];	float h = m2.data[2][1];	float i = m2.data[2][2];

	float r = m1.data[0][0];	float s = m1.data[0][1];	float t = m1.data[0][2];
	float u = m1.data[1][0];	float v = m1.data[1][1];	float w = m1.data[1][2];
	float x = m1.data[2][0];	float y = m1.data[2][1];	float z = m1.data[2][2];

	//calculate composition of two matricies
	Matrix rvalue;
	rvalue.data[0][0] = a*r + b*u + c*x;
	rvalue.data[0][1] = a*s + b*v + c*y;
	rvalue.data[0][2] = a*t + b*w + c*z;

	rvalue.data[1][0] = d*r + e*u + f*x;
	rvalue.data[1][1] = d*s + e*v + f*y;
	rvalue.data[1][2] = d*t + e*w + f*z;

	rvalue.data[2][0] = g*r + h*u + i*x;
	rvalue.data[2][1] = g*s + h*v + i*y;
	rvalue.data[2][2] = g*t + h*w + i*z;

	return rvalue;
}

Matrix compose_all(vector<Matrix> transformations) {
	//create identity matrix to begin composition of all transformations
	Matrix mat;
	mat.data[0][0] = 1;
	mat.data[1][1] = 1;
	mat.data[2][2] = 1;

	for (unsigned int i = 0; i < transformations.size(); i++) {
		mat = compose(transformations[i], mat);
	}

	return mat;
}

//data used to draw fractals
vector<Pt> condensation_set;
vector<Matrix> transformation;
unsigned int iterations = 10;
bool draw_stepwise = false;
bool fill_condensation = true;

void setCondensationSet(vector<Pt> pts) {
	condensation_set = pts;
}

void setIATTransformations(vector<Matrix> transformations) {
	transformation = transformations;
}

void setIterations(unsigned int iter) {
	iterations = iter;
}

void fillCondensationSet(bool fill) {
	fill_condensation = fill;
}

void draw_frame(vector<Pt> curr_iter) {
	switch (condensation_set.size()) {
	case 0: //use default point
	case 1: // all as points
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_POINTS);
		for (unsigned int i = 0; i < curr_iter.size(); i++) {
			glVertex2f(curr_iter[i].x, curr_iter[i].y);
		}
		glEnd();
		glFlush();
		break;
	case 2: //draw as lines
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_LINES);
		for (unsigned int i = 0; i < curr_iter.size(); i += 2) {
			glVertex2f(curr_iter[i].x, curr_iter[i].y);
			if (i + 1 > curr_iter.size()) {
				glVertex2f(curr_iter[i + 1].x, curr_iter[i + 1].y);
			}
		}
		glEnd();
		glFlush();
		break;
	default: //draw as polygon
		glClear(GL_COLOR_BUFFER_BIT);
		for (unsigned int i = 0; i < curr_iter.size(); i += condensation_set.size()) {
			if(fill_condensation) glBegin(GL_POLYGON);
			else glBegin(GL_LINE_LOOP);
			for (unsigned int j = 0; j < condensation_set.size(); j++) {
				glVertex2f(curr_iter[i+j].x, curr_iter[i+j].y);
			}
			glEnd();
		}
		glFlush();
		break;
	}
}

// Draws the current IAT
void display() {
	if (transformation.size() > 0) {
		glColor3f(0, 0, 0);
		unsigned int init_set = condensation_set.size();
		vector<Pt> prev_iter, curr_iter;

		//start by putting all initial points into the fractal and draw it if 
		// we are watching it draw stepwise
		if (init_set == 0) {
			curr_iter.push_back(Pt(0, 0));
		}
		else {
			curr_iter = condensation_set;
		}
		if (draw_stepwise) draw_frame(curr_iter);

		/*
		for each iteration
			set prev_iter to curr_iter
			clear curr_iter
			for each transformation
				for each point in prev_iter
					transform point and add curr_iter
		*/

		for (unsigned int i = 0; i < iterations; i++) {
			prev_iter = curr_iter;
			curr_iter.clear();
			for (unsigned int j = 0; j < transformation.size(); j++) {
				for (unsigned int k = 0; k < prev_iter.size(); k++) {
					curr_iter.push_back(transform(transformation[j], prev_iter[k]));
				}
			}
			if (draw_stepwise) {
				Sleep(1000);
				draw_frame(curr_iter);
			}
		}

		draw_frame(curr_iter);

	}
}


/* do not modify the reshape function */
void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '1': 
		hangman();
		break;
	case '2':
		staircase();
		break;
	case '3':
		snowflake();
		break;
	case '4':
		flower();
		break;
	case '5':
		sierpinski();
		break;
	case '6':
		treetop();
		break;
	case '7':
		circlefield();
		break;
	case 'p':
		draw_stepwise = (draw_stepwise) ? false : true;
		break;
	default:
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(600, 100);
	glutCreateWindow("Casey Brooks - Homework 3");
	glClearColor(1, 1, 1, 1);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	init();
	glutMainLoop();
	return 0;
}
