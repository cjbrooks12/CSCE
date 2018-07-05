/* Class Point, containing all information relevant to plotting points of a
 * 	fractal. Created by making several subclasses, and the main Point class
 * 	is a container of all these subclass values. The subclasses are as follows:
 *
 * POSITION - the cartesian, or xy-plane, position of a point. Denoted as a pair
 * 	of integers, it plots the position from the top left-hand corner of the
 * 	window in pixels.
 *
 * COLOR - the RGB value of the color the point should be. Denoted as a set of
 * 	three integers, Red, Green, and Blue, which together give the color value.
 *
 * DENSITY - the vertical position of a pixel. Can also be thought of as the
 * 	importance of the pixel. Denoted as a single integer, a point with a higher
 * 	density will be plotted over a point with a lower density, should multiple
 * 	points be calculated at the same position
*/

#include "../bin/std_lib_facilities_3.h"
#include "Position.h"
//#include "fractal.h"
//#include "calculate.cpp"
using namespace fractal;

namespace fractal {
//Position value of a Point. It will be calculated as a mathematical vector,
//and all operations will behave as mathematical vector operations
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Position::Position() :pos_x(0), pos_y(0), pos_z(0) {}
Position::Position(double x, double y, double z) :pos_x(x), pos_y(y), pos_z(z) {}

void Position::set_position(double x, double y, double z) {
	if(x>=0) pos_x=x;
	if(y>=0) pos_y=y;
	if(z>=0) pos_z=z;
}

//Arithmetic Operators
//------------------------------------------------------------------------------
double Position::magnitude() const {
	return (sqrt((x()*x()) + (y()*y()) + (z()*z())));
}
//double error(Position a, Position b) {
	//double error_x;
		//if(a.x() + b.x() == 0) return -1;
		//else error_x = ((a.x() - b.x()) / ((a.x() + b.x())/2))*100;
	//double error_y;
		//if(a.y() + b.y() == 0) return -1;
		//else return error_y = ((a.y() - b.y()) / ((a.y() + b.y())/2))*100;
	//double error_z;
		//if(a.z() + b.z() == 0) return -1;
		//else return error_z = ((a.z() - b.z()) / ((a.z() + b.z())/2))*100;
//
	//if(((error_x + error_y + error_z)/3) < 0) {
		//return (-1*(error_x + error_y + error_z)/3);
	//}
	//else return (-1*(error_x + error_y + error_z)/3);
//
//
//}



//Stream Operators
//------------------------------------------------------------------------------
ostream& operator<<(ostream& os, const Position& p) {
	return os << '(' << p.x() << ',' << p.y() << ',' << p.z() << ')';
}
istream& operator>>(istream& is, Position& p) {
	double x,y,z;
	char ch1,ch2,ch3,ch4;
	is >> ch1 >> x >> ch2 >> y >> ch3 >> z >> ch4;
	if(ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') { //oops: format error
		cout << "formatting error\n";
		is.setstate(ios_base::failbit);
		return is;
	}
	p = Position(x,y,z); //update p
	return is;
}

//Comparison Operators
//------------------------------------------------------------------------------
//if the x, y, and z components of both vectors are both equal, return true
bool operator==(const Position& a, const Position& b) {
	if((a.x() == b.x()) && (a.y() == b.y()) && (a.z() == b.z())) return true;
	else return false;
}
bool operator!=(const Position& a, const Position& b) {
	return !(a==b);
}
//if |a| is less than |b|, return true
bool operator<(const Position& a, const Position& b) {
	if(a.magnitude() < b.magnitude()) return true;
	else return false;
}
bool operator>(const Position& a, const Position& b) {
	return (b<a);
}
bool operator<=(const Position& a, const Position& b) {
	return !(a>b);
}
bool operator>=(const Position& a, const Position& b) {
	return !(a<b);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
}

int main()
try {

	Position p(1,0,0);
	Position q(0,1,0);
	//Position r;
//
	//r.set_position(0,0,1);
//
	//cout << r << " get " << r.get_position() << endl;
//
//
	//if(p==r) cout << "p==q\n";
	//if(p!=r) cout << "p!=q\n";
	//if(p>=r) cout << "p>=q\n";
	//if(p<=r) cout << "p<=q\n";
	//if(p>r)  cout << "p>q\n";
	//if(p<r)  cout << "p<q\n";

	//double g;

	//g = error(p,q);
	//cout << p.magnitude() << " " << g << endl;


	return 0;
}
catch(exception& e){
	cerr << "error: " << e.what() << endl;
}
catch(...) {
	cerr << "something went wrong\n";
}