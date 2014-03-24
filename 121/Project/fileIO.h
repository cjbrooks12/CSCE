#include "chrono.h"

namespace fileIO {
class Appt {
	Chrono::Date d;
	string s;

public:
	Appt();
	Appt(Chrono::Date dd, string ss);
	Chrono::Date get_date() const {return d;}
	string get_appointment() const {return s;}
};

Vector<Appt> read_file(string file);
void write_file(Vector<Appt>& appt_list, string file);

void add_appointment(Vector<Appt>& appt_list, Appt a);
void delete_appointment(Vector<Appt>& appt_list, Appt a);
void sort_appts(Vector<Appt>& appt_list);
Chrono::Date search_appointments(Vector<Appt>& appt_list, string s);

bool operator==(const Appt& a, const Appt& b);
bool operator!=(const Appt& a, const Appt& b);
bool operator>(const Appt& a, const Appt& b);
bool operator<(const Appt& a, const Appt& b);
ostream& operator<<(ostream& os, const Appt& d);
istream& operator>>(istream& is, Appt& d);

}
