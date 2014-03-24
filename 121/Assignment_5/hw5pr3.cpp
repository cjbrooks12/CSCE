#include "Chrono.cpp"

int main() {
	Date now;
	while(cin >> now) {
		cout << "this is the date: " << now << endl;
		++now;
		cout << "Tomorrow will be " << now << endl;
	}
}
