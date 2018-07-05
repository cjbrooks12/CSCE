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
#include "fractal.h"
#include "calculate.cpp"
using namespace fractal;

namespace fractal {
//Position value of a Point
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Position::Position() :pos_x(0), pos_y(0) {}
Position::Position(int x, int y) :pos_x(x), pos_y(y) {}

void Position::set_position(int x, int y) {
	if(x>=0) pos_x=x;
	if(y>=0) pos_y=y;
}

//Arithmetic Operators
//------------------------------------------------------------------------------
Position& Position::operator++() {
	++pos_x;
	++pos_y;
	return *this;
}
Position Position::operator++(int) {
    Position tmp(*this);
    operator++();
    return tmp;
}
Position& Position::operator+=(const Position& rhs) {
    *this->x() + rhs->x();
    *this->y() + rhs->y();
    return *this;
}
Position operator+(Position lhs, const Position& rhs) {
  lhs += rhs;
  return lhs;
}
Position& Position::operator--() {
	--pos_x;
	--pos_y;
	return *this;
}
Position Position::operator--(int) {
    Position tmp(*this);
    operator--();
    return tmp;
}
Position& Position::operator-=(const Position& rhs) {
    *this-x() - rhs->x();
    *this->y() - rhs->y();
    return *this;
}
Position operator-(Position lhs, const Position& rhs) {
  lhs -= rhs;
  return lhs;
}


//Stream Operators
//------------------------------------------------------------------------------
ostream& operator<<(ostream& os, const Position& p) {
	return os << '(' << p.x() << ',' << p.y() <<')';
}
istream& operator>>(istream& is, const Position& p) {
	int x,y;
	char ch1,ch2,ch3;
	is >> ch1 >> x >> ch2 >> y >> ch3;
	if(ch1 != '(' || ch2 != ',' || ch3 != ')') { //oops: format error
		cout << "formatting error\n";
		is.setstate(ios_base::failbit);
		return is;
	}
	p = Position(x,y); //update p
	return is;
}

//Comparison Operators
//------------------------------------------------------------------------------
bool operator==(const Position& a, const Position& b) {
	return (a.x() == b.x()) && (a.y() == b.y());
}
bool operator!=(const Position& a, const Position& b) {
	return !(a==b);
}
bool operator<(const Position& a, const Position& b) {
	return (a.x() < b.x()) && (a.y() < b.y());
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


int main()
try {

	Position p(10,10);
	Position q(5,5);
	Position r;

	p++;
	q++;

	cout << p << ' ' << q << '\n';

	return 0;
}
catch(exception& e){
	cerr << "error: " << e.what() << endl;
}
catch(...) {
	cerr << "something went wrong\n";
}