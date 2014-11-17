#ifndef ASSIGNMENT_3_H
#define ASSIGNMENT_3_H

#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

/**
* You should not change any of the definitions in this file.
* We will be providing new init.cpp files to test your program
* on new factals.  These functions define the interface between
* the two files!
*/

class Matrix {
public:
	float data[3][3];

	Matrix() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++)	{
				data[i][j] = 0;
			}
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const Matrix& a) {
		for (int i = 0; i < 3; i++) {
			os << "[";
			for (int j = 0; j < 3; j++) {
				os << setw(4) << a.data[i][j];
			}
			os << "]\n";
		}
		return os;
	}
};

class Pt {
public:
	float x, y;

	Pt(float newX, float newY) {
		x = newX;
		y = newY;
	}

	Pt() {
		x = y = 0;
	}

	friend std::ostream& operator<<(std::ostream& os, const Pt& a) {
		os << "<" << a.x << "," << a.y << ">";
		return os;
	}
};

typedef Pt Vec;

//Utilities
//------------------------------------------------------------------------------
/**
* Transform the given point by the matrix 
*/
Pt transform(Matrix m, Pt v);

Matrix inverse(Matrix m);

//Transformations
//------------------------------------------------------------------------------
/**
* Constructs a matrix to translate by the vector "v"
*/
Matrix translate(Vec v); //done

/**
* Constructs a matrix to rotate about the point "p" by the angle "theta"
*/
Matrix rotate(Pt p, float theta); //done

/**
* Constructs a matrix to uniformly scale about
* the point "p" by the scalar "alpha"
*/
Matrix scale(Pt p, float alpha); //done

/**
* Constructs a matrix to non-uniformly scale about
* the point "p" in the direction "v" by the scalar "alpha"
*/
Matrix nscale(Pt p, Vec v, float alpha); //done

/**
* Constructs a matrix representing the affine transformation that takes the
* points "p1", "p2", "p3" to the deformed points "q1", "q2", "q3"
*/
Matrix image(Pt p1, Pt p2, Pt p3, Pt q1, Pt q2, Pt q3);

/**
* Multiplies the matrices "m2", "m1" to produce
* the product m2 * m1 (in that order).
*/
Matrix compose(Matrix m2, Matrix m1);

/**
* Multiplies the list of transformations together 
* in the order they were inserted.
*/
Matrix compose_all(vector<Matrix> transformations);

/**
* Sets the condensation set for this IAT.
* If pts.size ( ) == 0, then there is no condensation set for this fractal
* If pts.size ( ) == 1, then the set is a point
* If pts.size ( ) == 2, then the set is a line
* If pts.size ( ) > 2, then the set should be a
*    poly-line (line with first and last points connected)
*/
void setCondensationSet(vector<Pt> pts);

/**
* Sets the transformations for the current IAT.
*/
void setIATTransformations(vector<Matrix> transformations);

/**
* Sets the number of iterations to calculate
*/
void setIterations(unsigned int iter);

void fillCondensationSet(bool fill);

#endif