#include "PriorityQueueHeap.h"
using namespace std;

int main() {
	cout << "Do you want to use an unsorted linked list [type LIST] or a binary heap [type HEAP]? \n > ";
	string selection;
	cin >> selection;
	if(selection == "LIST") {
		PriorityQueueList pq;
		Locator* locators = new Locator[26];

		// create PQ; assign locators randomly
		pq.createPriorityQueue("test.txt", locators);
		cout << "Read in from file: \n" << pq << endl;
			

		// heap sort
		Locator* loc;
		while (!pq.isEmpty()) {
			Locator* l = pq.min();
			loc = pq.min();
			cout << "min= " << *l << endl;
			pq.remove(loc);
		}
		cout << endl;

		// create PQ again; and assign locators according to the city name
		pq.insert(2467,-1,&locators['S'-'A']);
		pq.insert(3288,-1,&locators['L'-'A']);
		pq.insert(621,0,&locators['O'-'A']);
		pq.insert(1423,-1,&locators['D'-'A']);
		pq.insert(84,0,&locators['J'-'A']);
		pq.insert(371,1,&locators['B'-'A']);
		pq.insert(328,1,&locators['P'-'A']);
		pq.insert(0,0,&locators['W'-'A']);
		pq.insert(946,0,&locators['M'-'A']);    
		cout << "Inserted Items:\n" << pq << endl;

		// decrease the key of LAX to 2658, as in Figure 13.14(h)
		pq.decreaseKey(locators['L'-'A'],2658);
		cout << "replace key of LAX by 2658:\n" << pq << endl;  
		
		cout << "SFO " << pq.getElement(locators['S'-'A']) << endl;
		cout << "LAX " << pq.getElement(locators['L'-'A']) << endl;
		cout << "ORD " << pq.getElement(locators['O'-'A']) << endl;
		cout << "DFW " << pq.getElement(locators['D'-'A']) << endl;
		cout << "JFK " << pq.getElement(locators['J'-'A']) << endl;
		cout << "BOS " << pq.getElement(locators['B'-'A']) << endl;
		cout << "PVD " << pq.getElement(locators['P'-'A']) << endl;
		cout << "BWI " << pq.getElement(locators['W'-'A']) << endl;
		cout << "MIA " << pq.getElement(locators['M'-'A']) << endl;  

	}
	else if(selection == "HEAP") {
		PriorityQueueHeap pq;
		Locator* locators = new Locator[26];

		// create PQ; assign locators randomly
		pq.createPriorityQueue("test.txt", locators);
		cout << " Read in from file: \n" << pq << endl;
			
		// heap sort
		//Locator* loc;
		// while (!pq.isEmpty()) {
			// Locator* l = pq.min();
			// loc = pq.min();
			// cout << "min= " << *l << endl;
			// pq.remove(loc);
		// }
		// cout << endl;

		// create PQ again; and assign locators according to the city name
		// pq.insert(2467,-1,&locators['S'-'A']);
		// pq.insert(3288,-1,&locators['L'-'A']);
		// pq.insert(621,0,&locators['O'-'A']);
		// pq.insert(1423,-1,&locators['D'-'A']);
		// pq.insert(84,0,&locators['J'-'A']);
		// pq.insert(371,1,&locators['B'-'A']);
		// pq.insert(328,1,&locators['P'-'A']);
		// pq.insert(0,0,&locators['W'-'A']);
		// pq.insert(946,0,&locators['M'-'A']);    
		// cout << "Inserted Items:\n" << pq << endl;

		// decrease the key of LAX to 2658, as in Figure 13.14(h)
		// pq.decreaseKey(locators['L'-'A'],2658);
		// cout << "replace key of LAX by 2658:\n" << pq << endl;  
		
		// cout << "SFO " << pq.getElement(locators['S'-'A']) << endl;
		// cout << "LAX " << pq.getElement(locators['L'-'A']) << endl;
		// cout << "ORD " << pq.getElement(locators['O'-'A']) << endl;
		// cout << "DFW " << pq.getElement(locators['D'-'A']) << endl;
		// cout << "JFK " << pq.getElement(locators['J'-'A']) << endl;
		// cout << "BOS " << pq.getElement(locators['B'-'A']) << endl;
		// cout << "PVD " << pq.getElement(locators['P'-'A']) << endl;
		// cout << "BWI " << pq.getElement(locators['W'-'A']) << endl;
		// cout << "MIA " << pq.getElement(locators['M'-'A']) << endl;  
	}
	else {
		cerr << "Invalid selection: Terminating.\n";
	}
}