#include "std_lib_facilities_3.h"

int main()
try {
	string input;
	int counter = 0;
	//Seeds the spellchecker with a list of words. To add more words, add "seed.push_back(" "); with the desired word in 
	//the qotations at the end of the list
	vector<string> seed;
		seed.push_back("hello"); 
		seed.push_back("world");
		seed.push_back("I");
		seed.push_back("a");
		seed.push_back("am");
		seed.push_back("the");
		seed.push_back("computer");
		seed.push_back("is");
		seed.push_back("was");
		seed.push_back("can");
		seed.push_back("do");
		seed.push_back("computation");
		seed.push_back("fast");
		seed.push_back("slow");
		seed.push_back("program");
		seed.push_back("C++");
	cout << "Start typing: " << endl;
	//Checks to see if the input word is in the dictionary list. If not, will print an error message saying which word is misspelled
	while(cin >> input) {
		counter = 0;
		for(int i = 0; i < seed.size(); i++) {
			if(input == seed[i]) {
				++counter;
			}
		}
		if(counter < 1) {
			cout << "Misspelled word: " << input << endl;
		}	
	}
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
