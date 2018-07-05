/* Need to include value checking for all classes. Position is valid for all
 * 	positive integers, Color is valid for all integers from 0 to 255, inclusive,
 * 	and Density is valid for all positive and negative integers
 *
 * Need to add assignment operations
*/

namespace fractal {
//Position value of a Point
//------------------------------------------------------------------------------
class Position {
	int pos_x;
	int pos_y;

public:
	Position();
	Position(int x, int y, int z);

	void set_position(int x, int y);
	Position get_position() {return Position(pos_x, pos_y);}
	int x() const {return pos_x;}
	int y() const {return pos_y;}

	Position& operator++(); //prefix
	Position operator++(int); //postfix
	Position& operator+=(const Position& rhs);
	Position& operator--();
	Position operator--(int);
	Position& operator-=(const Position& rhs);

};
Position operator+(Position lhs, const Position& rhs);
Position operator-(Position lhs, const Position& rhs);

ostream& operator<<(ostream& os, const Position& p);
istream& operator>>(istream& is, const Position& p);

bool operator==(const Position& a, const Position& b);
bool operator!=(const Position& a, const Position& b);
bool operator>(const Position& a, const Position& b);
bool operator<(const Position& a, const Position& b);
bool operator<=(const Position& a, const Position& b);
bool operator>=(const Position& a, const Position& b);

//Color value of a Point
//------------------------------------------------------------------------------
class Color {
	int color_r;
	int color_g;
	int color_b;

public:
	Color();
	Color(int r, int g, int b);

	void set_color(int r, int g, int b);
	Color get_color() {return Color(color_r, color_g, color_b);}

	int r() const {return color_r;}
	int g() const {return color_g;}
	int b() const {return color_b;}

	Color& operator++();
};
ostream& operator<<(ostream& os, const Color& c);
istream& operator>>(istream& is, const Color& c);
bool operator==(const Color& a, const Color& b);
bool operator!=(const Color& a, const Color& b);
bool operator>(const Color& a, const Color& b);
bool operator<(const Color& a, const Color& b);
bool operator>=(const Color& a, const Color& b);
bool operator<=(const Color& a, const Color& b);

//Density value of a Point
//------------------------------------------------------------------------------
class Density {
	int den;

public:
	Density();
	Density(int d);

	void set_density(int d);
	int d() const {return den;}

	Density& operator++();
};
ostream& operator<<(ostream& os, const Density& d);
istream& operator>>(istream& is, const Density& dd);
bool operator==(const Density& a, const Density& b);
bool operator!=(const Density& a, const Density& b);
bool operator>(const Density& a, const Density& b);
bool operator<(const Density& a, const Density& b);


//The actual Point object, containing indepently calculatable position, color, and density values
//------------------------------------------------------------------------------
class Point {
	Position xy;
	Color rgb;
	Density dd;

public:
	Point( );
	Point(Position p, Color c, Density d);

	void set_position(int x, int y);
	void set_color(int r, int g, int b);
	void set_density(int d);

	Position get_position() const {return xy;}
	Color get_color() const {return rgb;}
	Density get_density() const {return dd;}

	Point& operator++();
};
ostream& operator<<(ostream& os, const Point& d);
istream& operator>>(istream& is, const Point& dd);
bool operator==(const Point& a, const Point& b);
bool operator!=(const Point& a, const Point& b);
bool operator>(const Point& a, const Point& b);
bool operator<(const Point& a, const Point& b);

} //namespace: fractal
