#include "number_game.cpp"
using namespace number_game;

int main() try {
    int tests[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
        
    //Test for input equal to 2^n
    for(auto i = 0; i < 12; ++i) {
        test_number = i;
        start(tests[test_number]);
    }
    print_data();
    
    //Test for input equal to 2^n - 1
    for(auto i = 0; i < 12; ++i) {
        if(i == 0) {
            test_number = i;
            start(tests[test_number]);
        }
        else {
            test_number = i;
            start(tests[test_number] - 1);
        }
    }
    print_data();
}
catch(exception& e) {
    cerr << "error: " << e.what() << endl;
}