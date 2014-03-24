#include "std_lib_facilities_3.h"

int main() 
{
	int x = 1;

	for (int i = 1; i <= 11; i++) {
		int x2 = x * x;
		double y = sqrt(x2);
		cout << "Square root of (" << x << " squared) is " << y << '\n';
		x *= 10;
	}

	return 0;
}
