#include "1b.cpp"

int main() try {
    int tests[] = {10, 20, 100, 1000, 10000};
    
    for(int i = 0; i < 5; ++i) {
        matrix_sum::start(tests[i]);
    }
}
catch(exception& e) {
    cerr << "error: " << e.what() << endl;
}