#include "../bin/std_lib_facilities_3.h"

struct Numbers {
	void fibonacci(int first, int second, vector<int> vect, int number_elements);
	void hailstone();
	void pascal(int number_lines);
	void println(vector<int> vect);
	void print(vector<int> vect, int number_lines);
};

//Creates a fibonacci sequence out of any two starting numbers of any length and stores it in a vector<int>
void Numbers::fibonacci(int first, int second, vector<int> vect, int number_elements) {
	int buffer;
	if(second < first) {
		error("second value must be greater than the first");
	}
	if(first < 0 || second < 0 || number_elements < 0) {
		error("Enter positive integers only");
	}

	vect.push_back(first);
	vect.push_back(second);
	for(int i = 0; i < number_elements - 2; i++) {
		buffer = first + second;
		vect.push_back(buffer);
		first = second;
		second = buffer;
	}
	for(unsigned int i = 1; i < vect.size() - 1; i++) {
		cout << vect[i] << " ";
	}
}

void Numbers::hailstone() {
	cout << "Enter a number to start the sequence at:\n";
	long long int first = 0;
	long long int vect_size = 0;
	long long int max = 0;
	vector<long long int> vect;
	cin >> first;

	if(first < 0) {
		error("Enter positive integers only");
	}

	vect.push_back(first);
	while(true) {
		if(first % 2 == 0) {
			first /= 2;
			vect.push_back(first);
			vect_size = vect.size();
			if(vect[vect_size - 1] > max) {
				max = vect[vect_size - 1];
			}
			if(first <= 1) break;
		}
		if(first % 2 != 0) {
			first = ((first * 3) + 1);
			vect.push_back(first);
			vect_size = vect.size();
			if(vect[vect_size - 1] > max) {
				max = vect[vect_size - 1];
			}
			if(first <= 1) break;
		}
	}
	for(unsigned int i = 0; i < vect.size(); i++) {
		cout << vect[i] << endl;
	}
	cout << "\nNumber of iterations: " << vect_size << endl;
	cout << "Highest number in sequence: " << max << endl;
}

void Numbers::pascal(int number_lines) {
	int print_lines = number_lines;
	vector<int> upper, lower;
	upper = {0, 1, 0};
	while(number_lines > 0) {
		lower.push_back(0);
		for(unsigned int i = 0; i < upper.size() - 1; i++) {
				lower.push_back(upper[i] + upper[i+1]);
		}
		lower.push_back(0);
		print(upper, print_lines);
		cout << endl;
		upper = lower;
		lower.clear();
		number_lines--;
	}

}

void Numbers::print(vector<int> vect, int number_lines) {
	for(unsigned int i = 1; i < vect.size() - 1; i++) {
		cout << setw(18 - number_lines) << vect[i] << " ";
	}
}

int main() {
	try {
		vector<int> vect;
		Numbers f;
		f.fibonacci(16, 24, vect, 10);
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
