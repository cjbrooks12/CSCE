#include "std_lib_facilities_3.h"

void url() {
	string webpage, webpage_get;
	cout << "Please enter the full URL of a .pdf file: \n";
	cin >> webpage;
	webpage_get = webpage;

//Converts first 7 and last 4 characters to lowercase, so they can be checked
	for(unsigned int i = 0; i < 7; i++) {
		webpage[i] = tolower(webpage[i]);
	}
	for(unsigned int i = webpage.size() - 1; i > webpage.size() - 4; i--) {
		webpage[i] = tolower(webpage[i]);
	}
	if(webpage.substr(0,7) == "http://") { //if name is a proper URL, will call the system "wget" function
		if(webpage.substr(webpage.size() - 4, webpage.size() - 1) == ".pdf") {
			cout << webpage_get;
			webpage_get = "wget " + webpage_get + " -O webfile.pdf";
			cout << "\n\n\n\n\n\n" << webpage_get << "\n\n\n\n\n\n";
			system(webpage_get.c_str());
			system("/pub/daugher/ubuntu/10.04LTS/xpdf.bin webfile.pdf");
		}
	}
}


int main() {
	try {
		url();
		return 0;
	}
	catch(exception& e) {
		cerr << "Error: " << e.what() << endl;
	}
	catch(...) {
		cerr << "Something went wrong\n";
	}
}
