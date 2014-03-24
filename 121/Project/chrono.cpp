#include "chrono.h"
using namespace Chrono;

namespace Chrono {
//member function definitions:

//Date Constructor, takes in year, month, and day parameters
Date::Date(int yy, Month mm, int dd):y(yy), m(mm), d(dd)
{
}

//Considering there is no "year 0", a value of 0 in year will indicate a yearly date
Date::Date(Month mm, int dd):y(0), m(mm), d(dd)
{
}
// Default Date constructor
const Date& default_date()
{
	static Date dd(2001, Date::jan, 1); //start of 21st century
	return dd;
}

//Returns the current Date
const Date& current_date()
{
	time_t now = time(0);
	struct tm* tm=localtime(&now);
	int dy = tm->tm_mday;
	
	int mth = tm->tm_mon+1;
	int yr = tm->tm_year+1900;
	static Date dd(yr, Date::Month(mth), dy);
	return dd;
}

//Date Constructor
Date::Date()
	:y(current_date().year()),
	m(current_date().month()),
	d(current_date().day())
{
}

//Changes the date to a specified date
void Date::change_date(int yy, int mm, int dd){
	d = dd;
	m = Date::Month(mm);
	y = yy;
}

//Adds n days to the Date
void Date::add_day(int n)
{

	if (n<0) error("add_day(): can't handle negative n");
	while (days_in_month(y,m)<n) {
		add_month(1);
		n -= days_in_month(y,m);
	}
	d += n;
	if (!is_date(y,m,d)){
		d=d-days_in_month(y,m);
		add_month(1);
	}
}

//Adds a certain amount of months to the Date
void Date::add_month(int n)
{
	while (12<n){
		add_year(1);
		n-=12;
	}

	if (Date::Month(m+n) > dec){
		add_year(1);
		m=Date::Month((m+n)-12);

	}
	else
		m=Date::Month(m+n);
	
	if (!is_date(y, m, d))
		d=days_in_month(y,m);
}

//Subtracts a specified amount of months from the date
void Date::sub_month(int n)
{
	for(int i = 0; i < n; i++) {
		switch(m) {
			case dec: m = nov; break;
			case nov: m = oct; break;
			case oct: m = sep; break;
			case sep: m = aug; break;
			case aug: m = jul; break;
			case jul: m = jun; break;
			case jun: m = may; break;
			case may: m = apr; break;
			case apr: m = mar; break;
			case mar: m = feb; break;
			case feb: m = jan; break;
			case jan: m = dec; sub_year(1); break;
		}
	}
}

//Adds a year to the Date
void Date::add_year(int n)
{
	if(m == Date::feb && d == 29 && !leapyear(y+n)) { //Beware of leap years!
		m = mar;
		d = 1;
	}
	y += n;
}

//Subtracts a year from the Date
void Date::sub_year(int n)
{
	if(m == Date::feb && d == 29 && !leapyear(y-n)) { //Beware of leap years!
		m = mar;
		d = 1;
	}
	y -= n;
}

//helper functions:

//Returns the days in the Month
int days_in_month(int y, Date::Month m){
	switch(m) {
	case Date::feb: //the length of February varies
		return (leapyear(y))?29:28;
	case Date::apr:case Date::jun:case Date::sep:case Date::nov:
		return 30;
	default:
		return 31;
	}
}

//Checks to see if the date is valid
bool is_date(int y, Date::Month m, int d)
{
	//assume that y is valid

	if(d <= 0) return false; //d must be positive
	if(m < Date::jan || m > Date::dec) return false;

	

	if(days_in_month(y,m) < d) return false;

	return true;
}

//Checks to see if the year is a leap year
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
	if(d.year() == 0) {
		return os << '('
		<< "Yearly" << ',' << d.month() << ',' << d.day() << ')';
	}
	else {
		return os << '(' << d.year() << ',' << d.month() << ',' << d.day() << ')';
	}
}

bool operator>(const Date& a, const Date& b)
{
	if((a.year() > b.year()) || //year is greater
		(a.year() == b.year() && a.month() > b.month()) || //same year, month is greater
		(a.day() > b.day() &&a.year() == b.year() && a.month() == b.month())) return true; //same year and month, day is greater
	else return false;
}

bool operator<(const Date& a, const Date& b)
{
	if((a.year() < b.year()) || //year is greater
		(a.year() == b.year() && a.month() < b.month()) || //same year, month is greater
		(a.day() < b.day() && a.year() == b.year() && a.month() == b.month())) return true; //same year and month, day is greater
	else return false;
}

istream& operator>>(istream& is, Date& dd)
{
	int y,d,m;
	char ch1,ch2,ch3,ch4;
	is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
	if(ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') { 
		cout << "formatting error\n";
		is.clear(ios_base::failbit);
		return is;
	}

	dd = Date(y,Date::Month(m),d); //update dd

	return is;
}

enum Day {saturday, sunday, monday, tuesday, wednesday, thursday, friday};


//Returns the day of the week for a Date
int Date::day_of_week()
{
	int k = year()%100;
	int j = year()/100;

	return int((day() + ((26*(month() + 1)) / 10) + k + (k / 4) +(j / 4) + (5 * j)) % 7);
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
