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
	double pos_x;
	double pos_y;
	double pos_z;

public:
	Position();
	Position(double x, double y, double z);

	void set_position(double x, double y, double z);
	Position get_position() {return Position(pos_x, pos_y, pos_z);}
	double magnitude() const;
	double x() const {return pos_x;}
	double y() const {return pos_y;}
	double z() const {return pos_z;}
};

//double error(Position a, Position b);

ostream& operator<<(ostream& os, const Position& p);
istream& operator>>(istream& is, Position& p);

bool operator==(const Position& a, const Position& b);
bool operator!=(const Position& a, const Position& b);
bool operator>(const Position& a, const Position& b);
bool operator<(const Position& a, const Position& b);
bool operator<=(const Position& a, const Position& b);
bool operator>=(const Position& a, const Position& b);
//------------------------------------------------------------------------------
}