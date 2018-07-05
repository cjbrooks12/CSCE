clear; clc; close all; echo on; delete g060x32.txt; diary g060x32.txt;

A = [0.1 0.2 0.3 0.4 0.5 0.6 0.7; 14 12 10 8 6 4 2; 1 1 1 1 0 0 0; 3 6 9 12 15 18 21]

B = A(1:3,1:4)
C = A(2:3,1:7)

diary off; echo off;