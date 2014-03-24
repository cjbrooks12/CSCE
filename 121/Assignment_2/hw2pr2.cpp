#include "../bin/std_lib_facilities_3.h"

//Square root function based on the Taylor Series centered at x=0
double my_sqrt_1(double n)
{
	double x = n-1;
	x = 1 + x/2 - (1.0/8.0)*pow(x,2) + (1.0/16.0)*pow(x,3) - (5.0/128.0)*pow(x,4);

	return x;
}

int main()
{
	double n;
	double relative_error;
	cout << setw(16) << "n" << setw(16) << "sqrt(n)" << setw(16) << "my_sqrt_1(n)" << setw(16) << "error\n";

	for(auto k : {-100, -10, -1, 0, 1, 10, 100}){
		n = 3.14159 * pow(10.0, k);
		relative_error = ((my_sqrt_1(n) - sqrt(n))/(sqrt(n)))*100;
		cout << setw(16) << n << setw(16) << sqrt(n) << setw(16) << my_sqrt_1(n) << setw(16) << relative_error << "\n";
	}

	return 0;
}
