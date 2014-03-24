#include "fileIO.h"

using namespace fileIO;

namespace fileIO {
/* Constructors of appointment objects */
//------------------------------------------------------------------------------
Appt::Appt()
	:d(Chrono::Date()), s("")
{
}
Appt::Appt(Chrono::Date dd, string ss)
	:d(dd), s(ss)
{
}

/*Reads appointments from a file and stores them in a vector. This vector
	is passed around the program and modified, then at request this vector is
	saved to the file. */
//------------------------------------------------------------------------------
vector<Appt> read_file(string file) {
	vector<Appt> appt_list;
	Appt appts;

	ifstream ifs(file);
	if(!ifs) error("cannot open appointments file");

	while(ifs >> appts){
		appt_list.push_back(appts); 
	}

	ifs.close();
	return appt_list;
}

/* Deletes the current appointments file to save a new one */
void write_file(vector<Appt>& appt_list, string file)
{
	ofstream ofs(file);
	if(!ofs) error("cannot open appointments file");
	for(int i=0; i<appt_list.size(); ++i) {
		ofs << appt_list[i];
	}
}

/* Add and remove appointments from main vector. Sort the vector and check
	for copies of appointments*/
//------------------------------------------------------------------------------
void add_appointment(vector<Appt>& appt_list, Appt a) {
	appt_list.push_back(a);
}

void delete_appointment(vector<Appt>& appt_list, Appt a) {
	for(int i=0; i<appt_list.size(); ++i) {
		if(appt_list[i] == a) appt_list.erase(appt_list.begin() + i);
	}
}

void sort_appts(vector<Appt>& appt_list)
{
	sort(appt_list.begin(), appt_list.end());
	for(int i=0; i<appt_list.size() - 1; ++i) {
		if(appt_list[i] == appt_list[i+1]) {
			appt_list.erase(appt_list.begin() + i);
		}
	}
}

Chrono::Date search_appointments(Vector<Appt>& appt_list, string s)
{
	string memo = s;
	Chrono::Date d;
 
	for(int i = 0; i < appt_list.size(); i++)
	{
		if(memo == appt_list[i].get_appointment())
		{
   			d = appt_list[i].get_date();
  			return d;
  		}
	}

}


/* Checks for equality of both date and string value of appointment object */
//------------------------------------------------------------------------------
bool operator==(const Appt& a, const Appt& b)
{
	return a.get_date() == b.get_date()
			&& a.get_appointment() == b.get_appointment();
}

bool operator!=(const Appt& a, const Appt& b)
{
	return !(a == b);
}

/* Comparison of date member of appointment only, ignores string value */
//------------------------------------------------------------------------------
bool operator>(const Appt& a, const Appt& b)
{
	if(a.get_date() > b.get_date() ||
		(a.get_date() == b.get_date() && a.get_appointment() > b.get_appointment()))
		return true;
	else return false;}

bool operator<(const Appt& a, const Appt& b)
{
	if(a.get_date() < b.get_date() ||
		(a.get_date() == b.get_date() && a.get_appointment() < b.get_appointment()))
		return true;
	else return false;
}

/* I/O streams for appointment objects */
//------------------------------------------------------------------------------
ostream& operator<<(ostream& os, const Appt& d)
{
	if((d.get_date()).year() == 0) {
		return os << (d.get_date()).month() << '/' << (d.get_date()).day()
		<< d.get_appointment() << '\n';
	}
	else {
		return os << (d.get_date()).month() << '/' << (d.get_date()).day() << '/'
		<< (d.get_date()).year() << d.get_appointment() << '\n';
	}
}

istream& operator>>(istream& is, Appt& d)
{
	string s;
	int day, m, y;
	char c1, c2;
	
	is >> m >> c1 >> day;
	c2 = is.get();
	if(c1 == '/' && c2 != '/' && !is.eof()) {
		is.putback(c2);
		getline(is, s);
		Chrono::Date dd(Chrono::Date::Month(m),day);
		d = Appt(dd,s);
		return is;
	}
	else if(c1 == '/' && c2 == '/'  && !is.eof()) {
		//is.putback(c2);
		is >> y;
		getline(is, s);
		Chrono::Date dd(y,Chrono::Date::Month(m),day);
		d = Appt(dd,s);
		return is;
	}
	else if(c1 != '/' && c2 != '/'  && !is.eof()) {
		is.putback(c2);
		is.clear(ios_base::failbit);
		cout << "formatting errors\n";
		return is;
	}
	else{
		is.putback(c2);
		return is;
	}
}
//------------------------------------------------------------------------------
}
