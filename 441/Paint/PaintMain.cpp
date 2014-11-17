#include <iostream>
#include <gl/glut.h>
#include <gl/gl.h>
#include <math.h>

#define PI 3.14159265
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

//openGL callbacks
//------------------------------------------------------------------------------
int NUM_VERTICES = 36;

int _red, _green, _blue;
int _size;
int _brush;
int _angle;
bool _spray;

void display() {

}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a': //turn on spray mode
		_spray = (_spray == true) ? false : true;
		break;
	case 'b': //change the brush
		_brush = (_brush + 1) % 4;
		break;
	case 'c': //clear the screen
		glClear(GL_COLOR_BUFFER_BIT);
		glEnd();
		glFlush();
		break;
	case 'r': //rotate the brush;
		_angle = (_angle + 10) % 360;
		std::cout << _angle << " ";
		break;
	case '=': //increase brush size
		if (_size < 128) _size *= 2;
		break;
	case '-': //decrease brush size
		if (_size > 1) _size /= 2;
		break;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
		//check if bit is on by subtracting ASCII '0' from key then testing each bit

		//check red bit
		if ((key - '0') & (1 << 0)) _red = 1.0;
		else _red = 0.0;

		//check green bit
		if ((key - '0') & (1 << 1)) _green = 1.0;
		else _green = 0.0;

		//check blue bit
		if ((key - '0') & (1 << 2)) _blue = 1.0;
		else _blue = 0.0;

		break;
	}
}

void mouseMove(int x, int y) {
	glPushMatrix();

	glTranslatef(x, y, 0.0);
	glRotatef(_angle, 0.0, 0.0, 1.0);
	glColor4f(_red, _green, _blue, 1.0);

	switch (_brush) {
	case 0: //draw square
		glBegin(GL_QUADS);
		glVertex2f(-_size, -_size);
		glVertex2f(_size, -_size);
		glVertex2f(_size, _size);
		glVertex2f(-_size, _size);
		break;
	case 1: //draw triangle
		glBegin(GL_TRIANGLES);
		glVertex2f(-_size, -_size);
		glVertex2f(_size, -_size);
		glVertex2f(0, _size);
		break;
	case 2: //draw line
		glBegin(GL_LINES);
		glVertex2f(0, -_size);
		glVertex2f(0, _size);
		break;
	case 3: //draw circle
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0, 0); //center point
		for (int i = 0; i <= NUM_VERTICES; i++){
			if (_spray) glColor4f(_red, _green, _blue, 0.0);
			float theta = 2 * PI * i / NUM_VERTICES;
			float x = (_size)* cosf(theta);
			float y = (_size)* sinf(theta);
			glVertex2f(_size*cosf(theta), _size*sinf(theta)); //point along edge of circle
		}
		break;
	default:
		break;
	}

	glEnd();
	glFlush();
	glPopMatrix();

	glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		mouseMove(x, y);
	}
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1, 0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_BLEND); //Enable blending.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	_size = 16;
	_brush = 0;
	_angle = 0;
	_spray = false;

	_red = 1.0;
	_green = 0.0;
	_blue = 0.0;
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Casey Brooks - Assignment 1");
	init();
	glutDisplayFunc(display);
	glutMotionFunc(mouseMove);
	glutMouseFunc(mouseClick);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}