#include <iostream>
#include <vector>
#include <algorithm>
#include <GL/glut.h>
#include <time.h>
#include <Windows.h>

using namespace std;

/******************************************************************
Notes:
Image size is 400 by 400 by default.  You may adjust this if
you want to.
You can assume the window will NOT be resized.
Call clearFramebuffer to clear the entire framebuffer.
Call setFramebuffer to set a pixel.  This should be the only
routine you use to set the color (other than clearing the
entire framebuffer).  drawit() will cause the current
framebuffer to be displayed.
As is, your scan conversion should probably be called from
within the display function.  There is a very short sample
of code there now.
You may add code to any of the subroutines here,  You probably
want to leave the drawit, clearFramebuffer, and
setFramebuffer commands alone, though.
*****************************************************************/

#define ImageW 800
#define ImageH 600

float framebuffer[ImageH][ImageW][3];

//Set colors to pixels in frame buffer
//------------------------------------------------------------------------------

// Sets pixel x,y to the color RGB
// I've made a small change to this function to make the pixels match
// those returned by the glutMouseFunc exactly - Scott Schaefer 
void setFramebuffer(int x, int y, float R, float G, float B) {
	// changes the origin from the lower-left corner to the upper-left corner
	y = ImageH - y - 1;

	//set red componenent of pixel
	if (R <= 1.0)
	if (R >= 0.0) framebuffer[y][x][0] = R;
	else framebuffer[y][x][0] = 0.0;
	else framebuffer[y][x][0] = 1.0;

	//set green componenent of pixel
	if (G <= 1.0)
	if (G >= 0.0) framebuffer[y][x][1] = G;
	else framebuffer[y][x][1] = 0.0;
	else framebuffer[y][x][1] = 1.0;

	//set blue componenent of pixel
	if (B <= 1.0)
	if (B >= 0.0) framebuffer[y][x][2] = B;
	else framebuffer[y][x][2] = 0.0;
	else framebuffer[y][x][2] = 1.0;
}

// Draws the scene
void drawit() {
	glDrawPixels(ImageW, ImageH, GL_RGB, GL_FLOAT, framebuffer);
}

// Clears framebuffer to black
void clearFramebuffer() {
	int i, j;

	for (i = 0; i<ImageH; i++) {
		for (j = 0; j<ImageW; j++) {
			framebuffer[i][j][0] = 0.0;
			framebuffer[i][j][1] = 0.0;
			framebuffer[i][j][2] = 0.0;
		}
	}
}

//structures needed to create, fill, and clip polygons
//------------------------------------------------------------------------------
class point{
public:
	int x, y;

	point() : x(0), y(0) {}
	point(int _x, int _y) : x(_x), y(_y) {}
};

struct edge {
	point begin, end;
	float maxY, currX, xIncr;

	edge(point a, point b) : begin(a), end(b) {
		maxY = (end.y >= begin.y) ? end.y : begin.y;
		currX = (begin.y <= end.y) ? begin.x : end.x;
		xIncr = ((float)end.x - begin.x) / (end.y - begin.y);
	}

	bool operator<(const edge& obj) {
		return (currX < obj.currX);
	}
};

class polygon {
private:
	vector<point> points;
	vector<edge> edges;

	polygon *clipped_region;

	float red, green, blue;
	int min_y, max_y;

public:
	polygon() {
		red = (rand() / (double)(RAND_MAX + 1));
		green = (rand() / (double)(RAND_MAX + 1));
		blue = (rand() / (double)(RAND_MAX + 1));
		min_y = 0;
		max_y = ImageH;
		points.reserve(100);
		edges.reserve(100);
	}

	void setColor(float _red, float _green, float _blue) {
		red = _red;
		green = _green;
		blue = _blue;
	}

	void addPoint(int x, int y) {
		glColor3f(red, green, blue);

		//set initial point
		if (points.size() == 0) {
			points.push_back(point(x, y));

			glBegin(GL_POINTS);

			glVertex2f(x, y);
			glEnd();
			glFlush();

			min_y = y;
			max_y = y;
		}

		//set subsequent points
		else {
			point p_0 = points[points.size() - 1];

			point p_i(x, y);

			points.push_back(point(x, y));

			if (p_i.y != p_0.y) {
				edges.push_back(edge(p_0, p_i));
			}

			glBegin(GL_LINES);

			glVertex2f(p_0.x, p_0.y);
			glVertex2f(p_i.x, p_i.y);
			glEnd();
			glFlush();

			if (p_i.y < min_y) min_y = p_i.y;
			if (p_i.y > max_y) max_y = p_i.y;
		}
	}

	bool addEndPoint(int x, int y) {
		if (points.size() >= 2) {
			point p_0 = points[points.size() - 1];

			point p_i(x, y);
			points.push_back(point(x, y));

			point p_begin = points[0];

			if (p_i.y != p_0.y) {
				edges.push_back(edge(p_0, p_i));
			}
			if (p_i.y != p_begin.y) {
				edges.push_back(edge(p_i, p_begin));
			}

			points.push_back(point(x, y));

			glBegin(GL_LINES);
			glColor3f(red, green, blue);

			glVertex2f(p_0.x, p_0.y);
			glVertex2f(p_i.x, p_i.y);
			glVertex2f(p_i.x, p_i.y);
			glVertex2f(p_begin.x, p_begin.y);
			glEnd();
			glFlush();

			if (p_i.y < min_y) min_y = p_i.y;
			if (p_i.y > max_y) max_y = p_i.y;

			return true;
		}
		else return false;
	}

	//fill the polygon using scan conversion
	void fill() {
		//create active edge table
		vector<vector<edge> > table;
		table.reserve(edges.size());
		for (unsigned int i = 0; i < ImageH; i++) {
			table.push_back(vector<edge>());
		}

		for (unsigned int i = 0; i < edges.size(); i++) {
			if (edges[i].begin.y <= edges[i].end.y) {
				table[edges[i].begin.y].push_back(edges[i]);
			}
			else {
				table[edges[i].end.y].push_back(edges[i]);
			}
		}

		vector<edge> active_edge_list;
		active_edge_list.reserve(edges.size());
		int lower_bound, upper_bound;
		lower_bound = (min_y > 0) ? min_y : 0;
		upper_bound = (max_y < ImageH) ? max_y : ImageH;
		for (int line = lower_bound; line < upper_bound; line++) {
			//add edges to active edge list from table that start at line 
			if (table[line].size() > 0) {
				for (unsigned int i = 0; i < table[line].size(); i++) {
					active_edge_list.push_back(table[line][i]);
				}
			}

			//remove edges that end at line
			for (unsigned int i = 0; i < active_edge_list.size(); i++) {
				if (active_edge_list[i].maxY == line) {
					active_edge_list.erase(active_edge_list.begin() + i);
					i--;
				}
			}

			sort(active_edge_list.begin(), active_edge_list.end());

			//fill line
			for (unsigned int i = 0; i < active_edge_list.size(); i += 2) {
				for (int j = active_edge_list[i].currX; j < active_edge_list[i + 1].currX; j++) {
					setFramebuffer(j, line, red, green, blue);
				}
			}

			//update x values
			for (unsigned int i = 0; i < active_edge_list.size(); i++) {
				active_edge_list[i].currX += (float)active_edge_list[i].xIncr;
			}
		}
	}

	void clip(point a, point b) {
		vector<point> input;
		vector<point> output = points;

		for (unsigned int i = 0; i < 4; i++) {
			int boundary = i; //order: top, right, bottom, left
			input = output;
			output.clear();
			output.reserve(input.size());

			for (unsigned int j = 0; j < input.size(); j++) {
				point S = input[j];
				point E;
				if (j == input.size() - 1) E = input.front();
				else E = input[j + 1];

				//determine clip edge
				point clip_a, clip_b;
				if (boundary == 0) {
					clip_a = point(a.x, b.y);
					clip_b = point(b.x, b.y);
				}
				else if (boundary == 1) {
					clip_a = point(b.x, b.y);
					clip_b = point(b.x, a.y);
				}
				else if (boundary == 2) {
					clip_a = point(b.x, a.y);
					clip_b = point(a.x, a.y);
				}
				else if (boundary == 3) {
					clip_a = point(a.x, a.y);
					clip_b = point(a.x, b.y);
				}

				if (is_inside(a, b, boundary, S) && is_inside(a, b, boundary, E)) {
					//S and E inside, output E
					output.push_back(E);
				}
				if (!is_inside(a, b, boundary, S) && !is_inside(a, b, boundary, E)) {
					//S and E outside, output nothing
				}
				if (is_inside(a, b, boundary, S) && !is_inside(a, b, boundary, E)) {
					//S inside, E outside, output I
					point I = intersect(clip_a, clip_b, S, E);
					if (I.x > 0 && I.y > 0) output.push_back(I);
				}
				if (!is_inside(a, b, boundary, S) && is_inside(a, b, boundary, E)) {
					//S outside, E inside, output I and E
					point I = intersect(clip_a, clip_b, S, E);
					if (I.x > 0 && I.y > 0) {
						output.push_back(I);
						output.push_back(E);
					}
				}
			}
		}

		clipped_region = new polygon();
		clipped_region->setColor(red, green, blue);

		for (unsigned int i = 0; i < output.size(); i++) {
			if (i == output.size() - 1) {
				clipped_region->addEndPoint(output[i].x, output[i].y);
			}
			else {
				clipped_region->addPoint(output[i].x, output[i].y);
			}
		}
	}

	void fill_clipped_region() {
		if (clipped_region->points.size() >= 3) {
			clipped_region->fill();
		}
	}

private:
	point intersect(point a_begin, point a_end, point b_begin, point b_end) {
		point p1, p2, p3, p4;

		if (a_begin.x == a_end.x) { //clip boundary vertical
			if (b_begin.x == b_end.x) return point(-1, -1); //both lines vertical
			else {
				p1 = a_begin;
				p2 = a_end;
				p3 = b_begin;
				p4 = b_end;
			}
		}
		else if (b_begin.x == b_end.x) { //polygon line vertical
			p1 = b_begin;
			p2 = b_end;
			p3 = a_begin;
			p4 = a_end;
		}
		else { //neither line vertical
			p1 = a_begin;
			p2 = a_end;
			p3 = b_begin;
			p4 = b_end;
		}

		float m1, m2, b1, b2;

		if (p1.x == p2.x) { //we are dealing with a vertical line
			m2 = ((float)(p4.y - p3.y) / (float)(p4.x - p3.x));
			b2 = p4.y - m2*p4.x;

			return point(p1.x, (m2*p1.x + b2));
		}
		else { //we have two non-vertical lines
			m1 = ((float)(p2.y - p1.y) / (float)(p2.x - p1.x));
			b1 = p1.y - m1*p1.x;

			m2 = ((float)(p4.y - p3.y) / (float)(p4.x - p3.x));
			b2 = p4.y - m2*p4.x;

			if (m1 == m2) return point(-1, -1);
			else {
				point intersection;

				intersection.x = (int)(((float)b2 - b1) / ((float)m1 - m2));
				intersection.y = (int)(((float)b2 - b1) / ((float)m1 - m2))*m1 + b1;

				return intersection;
			}
		}
	}


	bool is_inside(point clip_a, point clip_b, int boundary, point test) {
		//test against top edge
		if (boundary == 0) {
			if (clip_a.y >= clip_b.y) {
				if (test.y < clip_a.y) return true;
			}
			else {
				if (test.y < clip_b.y) return true;
			}
		}

		//test against right edge
		if (boundary == 1) {
			if (clip_a.x >= clip_b.x) {
				if (test.x < clip_a.x) return true;
			}
			else {
				if (test.x < clip_b.x) return true;
			}
		}

		//test against bottom edge
		if (boundary == 2) {
			if (clip_a.y <= clip_b.y) {
				if (test.y > clip_a.y) return true;
			}
			else {
				if (test.y > clip_b.y) return true;
			}
		}

		//test against left edge
		if (boundary == 3) {
			if (clip_a.x <= clip_b.x) {
				if (test.x > clip_a.x) return true;
			}
			else {
				if (test.x > clip_b.x) return true;
			}
		}

		return false;
	}
};

//data members
//------------------------------------------------------------------------------
vector<polygon> polygons;
polygon *curr_polygon;

point anchor_a, anchor_b;
bool clip_mode;

//utility functions
//------------------------------------------------------------------------------
void clear_screen() {
	glClear(GL_COLOR_BUFFER_BIT);
	clearFramebuffer();

	polygons.clear();
	polygons.push_back(polygon());
	curr_polygon = &polygons[0];

	glBegin(GL_LINES);
	glEnd();
	glFlush();
}

//callback functions
//------------------------------------------------------------------------------
void display() {
	// should not be necessary but some GPUs aren't displaying anything until a clear call.
	glClear(GL_COLOR_BUFFER_BIT);
	drawit();

	glBegin(GL_LINES);
	glEnd();
	glFlush();
}

void mouse_draw(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		curr_polygon->addPoint(x, y);
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		if (curr_polygon->addEndPoint(x, y)) {
			curr_polygon->fill();

			drawit();
			glBegin(GL_LINES);
			glEnd();
			glFlush();

			//we've filled one polygon, add a new one
			polygons.push_back(polygon());
			curr_polygon = &polygons[polygons.size() - 1];
		}
	}
}

void mouse_move(int x, int y) {
	anchor_b = point(x, y);

	//ensure that the anchors to calculate from are based off the upper left 
	//and lower right corners of the clip box
	point temp_a, temp_b;
	temp_a.x = (anchor_a.x < anchor_b.x) ? anchor_a.x : anchor_b.x;
	temp_a.y = (anchor_a.y < anchor_b.y) ? anchor_a.y : anchor_b.y;

	temp_b.x = (anchor_a.x > anchor_b.x) ? anchor_a.x : anchor_b.x;
	temp_b.y = (anchor_a.y > anchor_b.y) ? anchor_a.y : anchor_b.y;

	clearFramebuffer();

	for (unsigned int i = 0; i < polygons.size(); i++) {
		polygons[i].clip(temp_a, temp_b);
		polygons[i].fill_clipped_region();
	}

	drawit();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);

	glVertex2f(anchor_a.x, anchor_a.y);
	glVertex2f(anchor_b.x, anchor_a.y);
	glVertex2f(anchor_b.x, anchor_b.y);
	glVertex2f(anchor_a.x, anchor_b.y);

	glEnd();
	glFlush();
}

void mouse_clip(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		anchor_a = point(x, y);
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		mouse_move(x, y);

		for (unsigned int i = 0; i < polygons.size(); i++) {
			polygons[i].fill_clipped_region();
		}
	}
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'c':
		if (!clip_mode) {
			//enter clipping mode
			clip_mode = true;
			glutMouseFunc(mouse_clip);
			glutMotionFunc(mouse_move);
		}
		else {
			clip_mode = false;
			glutMouseFunc(mouse_draw);
			glutMotionFunc(NULL);
		}
		break;
	case 127: clear_screen();
		break;
	}
}

//main and initialization functions
//------------------------------------------------------------------------------
void init(void) {
	gluOrtho2D(0, ImageW - 1, ImageH - 1, 0);
	clearFramebuffer();
	srand(time(NULL));

	polygons.push_back(polygon());
	curr_polygon = &polygons[0];
	clip_mode = false;
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ImageW, ImageH);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Casey Brooks - Homework 2");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouse_draw);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
