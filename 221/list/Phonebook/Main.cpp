#include "Record.h"
#include "TemplateDoublyLinkedList.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

namespace phone_book {
	vector< DoublyLinkedList<Record> > phonebook;
	DoublyLinkedList<Record> pages;
	const char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 
		'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
		
	void print_vector(vector<Record> r) {
		for(int i = 0; i < r.size(); ++i) {
			cout << r[i] << endl;
		}
	}
		
	void quit() {
		
	}
	
	void display_all() {
		for(int i = 0; i < 26; ++i) {
			cout << "-------------------------------------------------------------------------------\n"
			<< "* * " << letters[i] << " * * \n"
			<< "-------------------------------------------------------------------------------\n"
			<< phonebook[i]
			<< "-------------------------------------------------------------------------------\n\n\n";
		}
	}
	
	void display_page(int page) {
		cout << "-------------------------------------------------------------------------------\n"
		<< "* * " << letters[page] << " * * \n"
		<< "-------------------------------------------------------------------------------\n"
		<< phonebook[page]
		<< "-------------------------------------------------------------------------------\n\n\n";
	}
	
	void display_name(string name) {
	
		cout << "Entered last name: " << name << endl;
		/*char fl = name.at(0); //first letter of the last name
		int char_pos = 0;
		for(int i = 0; i < 26; ++i) {
			if(fl == letters[i]) {
				char_pos = i;
			}
		}
		
		//search for a given last name
		vector<Record> last_names_search;
		for(int i = 0; i < phonebook[char_pos].size(); ++i) {
			if(phonebook[char_pos][i].last_name == name) {
				last_names_search.push_back(phonebook[char_pos][i]);
			}
		}
		
		//if one one entry with that last name is given, print. Otherwise, prompt
		//user to enter a first name
		if(last_names_search.size() > 1) {
			vector<Record> first_names_search;
			string fname;
			cout << "Multiple entries with last name " << name << " found, please enter the first name: \n> ";
			cin >> fname;
			
			for(int i = 0; i < last_names_search.size(); ++i) {
				if(last_names_search[i].first_name == fname) {
					first_names_search.push_back(last_names_search[i]);
				}
			}
						
			//if one one entry with that first and last name is given, print. Otherwise, prompt
			//user to enter a uin
			if(first_names_search.size() > 1) {
				vector<Record> uin_search;
				long myuin;
				cout << "Multiple entries with last name " << name << " and first name " << fname << " found, please enter the uin: \n> ";
				cin >> myuin;
				
				for(int i = 0; i < first_names_search.size(); ++i) {
					if(first_names_search[i].uin == myuin) {
						uin_search.push_back(first_names_search[i]);
					}
				}
				
				if(uin_search.size() == 0) {
					cout << "Entry Not Found.\n";
				}
				else {
					print_vector(uin_search);
				}
			}
			else {
				print_vector(first_names_search);
			}
		}
		else {
			print_vector(last_names_search);
		} */
	}
	
	void insert_record(Record r) {
		if(r.last_name.size() > 0) {
			char fl = r.last_name.at(0); //first letter of the last name
			
			for(int i = 0; i < 26; ++i) {
				if(fl == letters[i]) {
					phonebook[i].insert(r);
					break;
				}
			}	
		}
	}
	
	void display_phone_book();
	
	void select_display() {
		string decision;
		char letter;
		
		cout << "> ";
		cin >> decision;
		
		if(decision == "quit") {
			quit();
		}
		else if(decision == "all") {
			display_all();
			display_phone_book();
		}
		else if(decision == "page") {
			cin >> letter;
			letter = toupper(letter);
			bool found = false;
			int i = 0;
			while(!found) {
				if(letter == letters[i]) {
					found = true;
				}
				else {
					++i;
				}
				if(i > 26) {
					cout << "Please enter valid letters only\n";
					i = 0;
					select_display();
				}
			}
			display_page(i);
			display_phone_book();
		}
		else if(decision == "add") {
			Record r;
			cout << "> ";
			cin >> r;
			insert_record(r);
			display_phone_book();
		}
		else {
			display_name(decision);
			display_phone_book();
		}
		
	}
	
	void display_phone_book() {
		cout << "Your personal phonebook \n" 
			<< "    -Entries are sorted by last name, first name, and then UIN \n" 
			<< "    -To display the entire phonebook, enter 'all' \n"
			<< "    -To narrow your search by letter of last name, enter 'page' followed by the letter \n"
			<< "    -To search for a specific name, enter the last name \n" 
			<< "    -To add a new entry, enter 'add' \n" 
			<< "    -To quit, type 'quit'\n\n\n";
		select_display();
	}
	
	void populate_phonebook() {
		for(int i = 0; i < 26; ++i) {
			DoublyLinkedList<Record> list;
			phonebook.push_back(list);
		}
	
		ifstream ifs("PhoneBook.txt");
		
		vector<Record> myRecords;
		while(!ifs.eof()) {
			Record r;
			ifs >> r;
			
			insert_record(r);
		}
		ifs.close();
	}
	
	void start() {
		populate_phonebook();
		display_phone_book();
	}
};

int main() {
	phone_book::start();

	return 0;
}