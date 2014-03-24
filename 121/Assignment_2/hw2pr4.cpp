#include "std_lib_facilities_3.h"

//Square root function based on the Taylor Series centered at x=0
double my_sqrt_1(double n)
{
	double x = n-1;
	x = 1+ x/2 - (1.0/8.0)*pow(x,2) + (1.0/16.0)*pow(x,3) - (5.0/128.0)*pow(x,4);	

	return x;
}

//Creates a scalar multiple that will bring the my_sqrt_1 value much closer to the actual value
double my_sqrt_2(double n)
{
	//If a number is greater than 8/5, will repeatedly do the function until it is less than 8/5
	double result = 1;
	if(n > 8.0/5.0) {
		while(true) {
			n /= 4.0;
			result *= 2.0;
			if(n <= 8.0/5.0) {
				break;
			}
		}
		
	}
	//If a number is less than 2/5, will repeatedly do the function until it is greater than 2/5
	if(n < 2.0/5.0) {
		while(true){
			n *= 4.0;
			result /= 2.0;
			if(n >= 2.0/5.0) {
				break;
			}
		}
	}
	else {
	}
	return result * my_sqrt_1(n);
	
}

int main()
{
	double n;
	double relative_error;
	cout << setw(16) << "n" << setw(16) << "sqrt(n)" << setw(16) << "my_sqrt_2(n)" << setw(16) << "error\n";
	
	for(auto k : {-100, -10, -1, 0, 1, 10, 100}){
		n = 3.14159 * pow(10.0, k);
		relative_error = ((my_sqrt_2(n) - sqrt(n))/(sqrt(n)))*100;
		cout << setw(16) << n << setw(16) << sqrt(n) << setw(16) << my_sqrt_2(n) << setw(16) << relative_error << "\n";
	}

	return 0;
}
