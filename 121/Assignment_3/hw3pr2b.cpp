#include "std_lib_facilities_3.h"

//converts degrees celsius to Kelvin
double ctok(double c)
{
	double k = c + 273.15;
	return k;
}

int main()
{
	double c = 0;
	cin >> c;
	double k = ctok(c);
	cout << k << endl;
	
	return 0;
}
