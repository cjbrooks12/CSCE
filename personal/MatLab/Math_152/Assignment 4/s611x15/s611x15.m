clear; clc; close all; echo on; delete s611x15.txt; diary s611x15.txt;




n = 1;
y = (-1)^(n-1) / factorial(2*n - 1);
S = 0;
while abs(y) > .0001
    S = S + y
    n = n+1;
    y = (-1)^(n+1) / factorial(2*n - 1);
end

diary off;