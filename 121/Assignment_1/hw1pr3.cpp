#include "std_lib_facilities_3.h"

int main()
{
//declares and initializes the variables to be used
	cout << "Enter an expression to be solved. Enter a number first, followed by the operator, then the last number(all separated by spaces), then hit enter.\n";
	double val1 = 0;
	double val2 = 0;
	double val3 = 0;
	string op = "";

//Selects the operation to use based on user input
	cin >> val1 >> op >> val2;
	if (op == "+" || op == "plus") {
		val3 = val1 + val2;
		cout << val3 << "\n"; 
	}
	if (op == "-" || op == "minus")
	{
		val3 = val1 - val2;
		cout << val3 << "\n"; 
	}
	if (op == "*" || op == "mul")
	{
		val3 = val1 * val2;
		cout << val3 << "\n"; 
	}
	if (op == "/" || op == "div")
	{
		val3 = val1 / val2;
		cout << val3 << "\n"; 
	}
	return 0;
}











