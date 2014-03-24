//file Chrono.

namespace Chrono {

class Date {
public:
	enum Month {
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	class Invalid {}; //to throw as exception

	Date(int y, Month m, int d); //check for calid date and initialize default constructor
	Date();
	//the default copy operations are fine

	//nonmodifying operations:
	int day() const {return d;}
	Month month() const {return m;}
	int year() const {return y;}

	//modifying operations
	void add_day(int n);
	void add_month(int n);
	void add_year(int n);
	Date& operator++();


private:
	int y;
	Month m;
	int d;
};

bool is_date(int y, Date::Month m, int d); //true for valid date

bool leapyear(int y); //true if y is a leap year

bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);


ostream& operator<<(ostream& os, const Date& d);

istream& operator>>(istream& is, const Date& dd);

} //Chrono
