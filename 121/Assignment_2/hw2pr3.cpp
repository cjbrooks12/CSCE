#include "../bin/std_lib_facilities_3.h"

int main()
{
	string input;
	int counter = 0;
	cout << "Please enter a string. The number of times 'Aggie' or 'Aggies' is entered will be counted. Enter 'quit' to exit.\n";
	while(cin >> input) {
		if (input == "Aggie" || input == "aggie" || input == "AGGIE" || 
			input == "Aggies" || input == "aggies" || input == "AGGIES") {
			counter++;
		}
		if(input == "quit" || input == "Quit" || input == "QUIT") {
		cout << "The word Aggie has been typed " << counter << " times.\n";
		break; //when "quit" is typed, will return the total number of times "Aggie" has been entered and terminate the program
		}	
	}
	cout << "Thank you for playing with this.\n";
}
