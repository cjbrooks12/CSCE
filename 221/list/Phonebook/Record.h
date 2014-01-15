#include<iostream>
#include<string>
#include<cstdio>
#include<sstream>
using namespace std;

class Record {
public:
	string last_name, first_name;
	long uin, phone_number;
	

	Record() : last_name(""), first_name(""), uin(0), phone_number(0) {}
	Record(string last, string first, long u, long n) 
		: last_name(last), first_name(first), uin(u), phone_number(n) {}
		
	bool operator()(const Record& r);
	friend ostream& operator<<(ostream &out, const Record& r);
	friend istream& operator>>(istream &in, Record &r);
};


ostream& operator<<(ostream &out, const Record& r) {
	out << r.last_name << endl;
	out << r.first_name << endl;
	out << r.uin << endl;
	out << r.phone_number << endl;
	
	return out;
}

istream& operator>>(istream &in, Record &r) {
	in >> r.last_name;
	in >> r.first_name;
	in >> r.uin;
	in >> r.phone_number;
	
	return in;
}

//returns true if object is strictly less than the input object

bool Record::operator()(const Record& r) {
	if(last_name > r.last_name) return true;
	else if(last_name == r.last_name && first_name > r.first_name) return true;
	else if(last_name == r.last_name && first_name == r.first_name && uin < r.uin) return true;
	else return false;
}