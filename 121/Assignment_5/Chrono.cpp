//Chrono.cpp
#include "../bin/std_lib_facilities_3.h"
#include "Chrono.h"
using namespace Chrono;

namespace Chrono {
//member function definitions:

Date::Date(int yy, Month mm, int dd)
	:y(yy), m(mm), d(dd)
{
	if(!is_date(yy,mm,dd)) throw Invalid();
}

const Date& default_date()
{
	static Date dd(2001, Date::jan, 1); //start of 21st century
	return dd;
}

Date::Date()
	:y(default_date().year()),
	m(default_date().month()),
	d(default_date().day())
{
}

void Date::add_day(int n)
{
	for(int i = 0; i < n; i++) {
		switch(m) {
		case apr:
		case jun:
		case sep:
		case nov:
			if(d == 30) {
				d = 1;
				add_month(1);
			}
			else d += 1;
			break;
		case jan:
		case mar:
		case may:
		case jul:
		case aug:
		case oct:
			if(d == 31) {
				d = 1;
				add_month(1);
			}
			else d += 1;
			break;
		case dec:
			if(d == 31) {
				d = 1;
				add_month(1);
				add_year(0);
			}
			break;
		case feb:
			if(!leapyear(y)) {
				if(d < 28) d += 1;
				if(d == 28) {
					d = 1;
					add_month(1);
				}
			}
			if(leapyear(y)) {
				if(d < 29) d += 1;
				if(d == 29) {
					d = 1;
					add_month(1);
				}
			}
			break;
		}
	}
}

void Date::add_month(int n)
{
	for(int i = 0; i < n; i++) {
		switch(m) {
			case jan: m = feb; break;
			case feb: m = mar; break;
			case mar: m = apr; break;
			case apr: m = may; break;
			case may: m = jun; break;
			case jun: m = jul; break;
			case jul: m = aug; break;
			case aug: m = sep; break;
			case sep: m = oct; break;
			case oct: m = nov; break;
			case nov: m = dec; break;
			case dec: m = jan; add_year(1); break;
		}
	}
}

void Date::add_year(int n)
{
	if(m == Date::feb && d == 29 && !leapyear(y+n)) { //Beware of leap years!
		m = mar;
		d = 1;
	}
	y += n;
}

//helper functions:

bool is_date(int y, Date::Month m, int d)
{
	//assume that y is valid

	if(d <= 0) return false; //d must be positive
	if(m < Date::jan || m > Date::dec) return false;

	int days_in_month = 31; //most months have 31 days
	switch(m) {
	case Date::feb: //the length of February varies
		days_in_month = (leapyear(y))?29:28;
		break;
	case Date::apr:
	case Date::jun:
	case Date::sep:
	case Date::nov:
		days_in_month = 30; //the rest have 30 days
		break;
	}

	if(days_in_month < d) return false;

	return true;
}

bool leapyear(int y)
{
	if(y % 4 == 0 && y % 100 != 0) {
		return true;
	}
	else if(y % 400 == 0) {
		return true;
	}
	else return false;
}

bool operator==(const Date& a, const Date& b)
{
	return a.year() == b.year()
		&& a.month() == b.month()
		&& a.day() == b.day();
}

bool operator!=(const Date& a, const Date& b)
{
	return !(a == b);
}

Date& Date::operator++(){
	add_day(1);

	return *this;
}


ostream& operator<<(ostream& os, const Date& d)
{
	return os << '('
		<< d.year()
		<< ',' << d.month()
		<< ',' << d.day() << ')';
}

istream& operator>>(istream& is, Date& dd)
{
	int y,d,m;
	char ch1,ch2,ch3,ch4;
	is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
	if(ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') { //oops: format error
		cout << "formatting error\n";
		is.clear(ios_base::failbit);
		return is;
	}

	dd = Date(y,Date::Month(m),d); //update dd

	return is;
}

enum Day {
	sunday, monday, tuesday, wednesday, thursday, friday, saturday
};

Day day_of_week(const Date& d)
{
	return sunday;
}

Date next_Sunday(const Date& d)
{
	return d;
}

Date next_weekday(const Date& d)
{
	return d;
}

} //Chrono
