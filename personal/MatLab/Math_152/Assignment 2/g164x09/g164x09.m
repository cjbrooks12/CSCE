clear; clc; close all; echo on; delete g164x09.txt; diary g164x09.txt;

x = linspace(-4,8,1000);
y = (x.^2 - 4.*x - 5) ./ (x - 2);

plot(x,y)

diary off; echo off;