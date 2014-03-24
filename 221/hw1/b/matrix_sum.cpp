#include "std_lib_facilities.h"
using namespace std;

namespace matrix_sum {
    int n;
    vector<vector<int>> my_matrix(1, vector<int>(1));
    
    void populate_matrix() {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                my_matrix[i][j] = rand() % 100 + 1;
            }
        }
    }
    
    void add() {
        vector<long long> row_sums;
        long long number_of_additions = 0;
        long long sum = 0;
        
        //sums up all the elements in each row and stores them in another vector
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                sum += my_matrix[i][j];
                ++number_of_additions;
            }
            row_sums.push_back(sum);
            sum = 0;
        }
        
        //sums up all the sums of rows, giving the final sum
        for(int i = 0; i < n; ++i) {
            sum += row_sums[i];
        }
        
        cout << "n: " << n << ", sum: " << sum << ", number of additions: " << number_of_additions << endl;
    }
    
    void start(int size) {
        if(size < 0) {
            error("matrix size must be nonnegative");
        }
        else {
            n = size;
            vector<vector<int>> m(n, vector<int>(n));
            my_matrix = m;
            populate_matrix();
            add();
        }
    }
}