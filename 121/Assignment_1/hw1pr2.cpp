#include "std_lib_facilities_3.h"

int main()
{
cout << "Please enter in two integer values\n";
double val1, val2;
cin >> val1 >> val2;

if (val1 > val2)
	cout << "Smallest: " << val2 << "\n";
	cout << "Largest: " << val1 << "\n";
if (val2 > val1)
	cout << "Smallest: " << val1 << "\n";
	cout << "Largest: " << val2 << "\n";
if (val1 == val2)
	cout << "Both numbers are equal.\n";

cout << "Sum: " << val1 + val2 << "\n";
cout << "Difference: " << val1 - val2 << "\n";
cout << "Product: " << val1 * val2 << "\n";
cout << "Ratio: " << val1 / val2 << "\n";

return 0;
}
