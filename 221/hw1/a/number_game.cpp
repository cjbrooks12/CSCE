#include "std_lib_facilities.h"
using namespace std;

namespace number_game {
//Data Members
//------------------------------------------------------------------------------
    int max, absolute_max, min, absolute_min, secret_number, number_of_guesses, test_number;
    Vector<int> range, number, guesses;
    
    int max_number_of_guesses(int n) {
        //change-of-base formula returns the value of worst-case-scenario log_2(n)
        if(n > 1) return (ceil(log10(n) / log10(2))) + 1;
        else if(n == 1) return 1;
        else error("out of range");
    }
    
    void print_data() {
        for(int i = 0; i < 12; ++i) {
            cout << "[1," << range[i] << "], " << number[i] << ", " << guesses[i] << endl;
        } 
        range.clear();
        number.clear();
        guesses.clear();
    }
    
    //Gets the value of the element at the midpoint of the current range
    int get_guess() {
        int guess;
        if(max == min) {
            if(max == absolute_max) {
                guess = absolute_max;
            }
            if(min == absolute_min) {
                guess = absolute_min;
            }
        }
        else if(max != min) {
            guess = ((max - min) / 2) + min;
        }
        if(min == absolute_max - 1) {
                guess = absolute_max;
            }
        return guess;
    }
    
    //Tests the guess and sets the upper bound and lower bound for a new 
      //range to get a number within
    void test_guess(int guess) {
        ++number_of_guesses;
        if(guess < secret_number) {
            //cout << "guess of " << guess << " too low" << endl;
            min = guess;
            test_guess(get_guess());
        }
        else if(guess > secret_number) {
            //cout << "guess of " << guess << " too high" << endl;
            max = guess;
            test_guess(get_guess());
        }
        else if(guess == secret_number) {
            range.push_back(absolute_max);
            number.push_back(secret_number);
            guesses.push_back(number_of_guesses);
        }
    }
    
    void start(int n) {
        if(n < 1) error("upper bound is less than lower bound");
        max = n;
        absolute_max = n;
        min = 1;
        absolute_min = 1;
        number_of_guesses = 0;
        secret_number = max;
        
        test_guess(get_guess());
    }
}
    