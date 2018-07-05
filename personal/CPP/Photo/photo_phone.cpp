#include "bin/std_lib_facilities_3.h"

void begin() {
	ofstream ofs("file_rename.sh");
    if(!ofs) error("cannot open file");
    else {
        ofs << "#!/bin/bash \n\n";
    }
	for(int i=0; i<=157; ++i) {
            ofs << "rename 's/IMG_" << i+2018 << ".JPG/"  << i+225 << ".jpg/' IMG_" << i+2018 << ".JPG;\n";
        
	}
}


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