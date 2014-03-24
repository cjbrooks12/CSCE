#include "Chrono.cpp"

int main() {
	Date now;
	while(cin >> now) {
		cout << "this is the date: " << now << endl;
		now.add_month(2);
		now.add_day(2);
		cout << "Two months and two days later will be " << now << endl;
	}
}
