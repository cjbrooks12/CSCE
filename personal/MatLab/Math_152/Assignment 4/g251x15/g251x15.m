clear; clc; close all; echo on; delete g251x15.txt; diary g251x15.txt;



A = [1.5, 2.1, 4];
B = [11, 15, 9];

C = [1, 0, 0];
D = [0,1, 0]; 

E = [-11, 3, -2];
F = [-13, -4, -5];


u1 = unitvec(A,B);
u2 = unitvec(C,D);
u3 = unitvec(E,F);

echo off; diary off;