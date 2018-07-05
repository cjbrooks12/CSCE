#include "bin/std_lib_facilities_3.h"

void begin() {
	ofstream ofs("file_rename.sh");
    if(!ofs) error("cannot open file");
    else {
        ofs << "#!/bin/bash \n\n";
    }
    
    
    ofs << "\n\n\n<string name=\"onekings\">1 Kings</string>\n";
	for(int i=1; i<=22; ++i) {
        ofs << "\t<string-array name=\"onekings" << i << "\"></string-array>\n";
   	}
       
    ofs << "\n\n\n<string name=\"twokings\">2 Kings</string>\n";
    for(int i=1; i<=25; ++i) {
        ofs << "\t<string-array name=\"twokings" << i << "\"></string-array>\n";
   	}
    
    
    
}


//ofs << "rename 's/2013-06-" << i+2018 << ".JPG/"  << i+225 << ".jpg/' IMG_" << i+2018 << ".JPG;\n";
//ofs << "\t<string-array name=\"1chronicles" << i << "\"></string-array>\n";
//ofs << "R.array.genesis" << i << ", ";
//ofs << "<string name=\"ch" << i << "\">Chapter " << i << "</string>\n";
//ofs << "case " << i << ": return getString(R.string.ch" << i+1 << ").toUpperCase(l);\n";

int main() try {
    begin();
}
catch(exception& e) {
    cerr << "exception: " << e.what() << '\n';
	return 1;
}
catch (...) {
	cerr << "Something went wrong\n";
	return 2;
}