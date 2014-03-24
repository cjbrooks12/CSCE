#include "std_lib_facilities_3.h"
#include <ctime>

namespace Chrono {

class Date {
public:
	enum Month {
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	//Vector<Appt> appt_list;

	class Invalid {}; //to throw as exception

	Date(int y, Month m, int d); //check for calid date and initialize default constructor
	Date(Month mm, int dd);
	
	Date();
	//the default copy operations are fine
	//current_date();
	//nonmodifying operations:
	int day() const {return d;}
	Month month() const {return m;}
	int year() const {return y;}
	
	//modifying operations
	void change_date(int dd, int mm, int yy);
	void add_day(int n);
	void add_month(int n);
	void sub_month(int n);
	void add_year(int n);
	void sub_year(int n);
	int day_of_week();
	Date& operator++();


private:
	int y;
	Month m;
	int d;
	int day_of;
	int row;

};

int days_in_month(int y, Date::Month m);
bool is_date(int y, Date::Month m, int d); //true for valid date
bool leapyear(int y); //true if y is a leap year

bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);
bool operator>(const Date& a, const Date& b);
bool operator<(const Date& a, const Date& b);
ostream& operator<<(ostream& os, const Date& d);
istream& operator>>(istream& is, Date& dd);

} //Chrono
