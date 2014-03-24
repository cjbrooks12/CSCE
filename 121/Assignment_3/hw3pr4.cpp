#include "std_lib_facilities_3.h"

//Square root function based on a polynomial centeres around the interval from 4 to 16
double my_sqrt_3(double n)
{
	double result = 1;
	double sf = 0; //scaling factor
	if(n > 16) {
		while(true) {
			n /= 4;
			result *= 2;
			if(n <= 16) {
				break;
			}
		}
	}
	else if(n <=4) {
		while(true) {
			n *= 4;
			result /= 2;
			if(n > 4) {
				break;
			}
		}
	}
	sf = 4 / (-0.00467674*n*n + 0.256498*n + 1.06993);
	result /= sf;
	return result*((-0.002123*(n*sf*sf) + 0.158939)*((n*sf*sf) - 16) + 4);
}

int main()
try{
	double n;
	double relative_error;
	cout << setw(14) << "n" << setw(14) << "sqrt(n)" << setw(14) << "my_sqrt_3(n)" << setw(14) << "error\n";
	
	for(auto k : {-100, -10, -1, 0, 1, 10, 100}){
		n = 3.14159 * pow(10.0, k);
		relative_error = ((my_sqrt_3(n) - sqrt(n))/(sqrt(n)))*100;
		cout << setw(14) << n << setw(14) << sqrt(n) << setw(14) << setw(14) << my_sqrt_3(n) << setw(14) << relative_error << "\n";
	}

	return 0;
}
catch(...)
{
	cerr << "Something went wrong\n";
	return 2;
}

