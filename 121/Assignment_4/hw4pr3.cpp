#include "../bin/std_lib_facilities_3.h"

struct Sequence {
	int first;
	int second;
	vector<int> fib;
	int number_elements;

	Sequence() : first(0), second(0), fib(0), number_elements(0) {}

	vector<int> fibonacci(int first, int second, vector<int> fib, int number_elements);
	void print(vector<int> fib);
};

//Creates a fibonacci sequence out of any two starting numbers of any length and
//	stores it in a vector<int>
vector<int> Sequence::fibonacci(int first, int second, vector<int> fib, int number_elements) {
	int buffer;
	if(second < first) {
		error("second value must be greater than the first");
	}
	if(first < 0 || second < 0 || number_elements < 0) {
		error("Enter positive integers only");
	}

	fib.push_back(first);
	fib.push_back(second);
	for(int i = 0; i < number_elements - 2; i++) {
		buffer = first + second;
		fib.push_back(buffer);
		first = second;
		second = buffer;
	}
	return fib;
}

//Prints out any vector passed to it, along with the ratio of the final two elements
void Sequence::print(vector<int> fib) {
	for(unsigned int i = 0; i < fib.size(); i++) {
		cout << fib[i] << endl;
	}
	double div = (fib[fib.size() - 1] * 1.0) / (fib[fib.size() - 2]);
	cout << "Ratio of last two elements: " << div << endl;
}

int main() {
	try {
		vector<int> fib;
		Sequence f;
		int x,y,n;
		cout << "Enter the first number, the second number, and sequence length\n";
		cin >> x >> y >> n;
		fib = f.fibonacci(x,y,fib,n);
		f.print(fib);

		return 0;
	}
	catch(exception& e) {
		cerr << "Error: " << e.what() << endl;
		return 1;
	}
	catch(...) {
		cerr << "Something went wrong\n";
		return 2;
	}
}
