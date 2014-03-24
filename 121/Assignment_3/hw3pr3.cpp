#include "std_lib_facilities_3.h"

//converts degrees celsius to Kelvin
double ctok(double c)
{
	if(!(c >= -273.15)) {
		throw runtime_error("Absolute zero is at -273.15 C, please enter a number greater than -273.15\n");
	}
	double k = c + 273.15;
	return k;
}

int main()
try {
	double c = 0;
	cin	>> c;
	double k = ctok(c);
	cout << k << endl;	
	
	return 0;
}
catch(exception& e)
{
	cerr << "Error: " << e.what() << endl;
	return 1;
}
catch(...) 
{
	cerr << "Something went wrong\n";
	return 2;
}
