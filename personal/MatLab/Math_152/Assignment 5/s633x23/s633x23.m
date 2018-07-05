clear; clc; close all; echo on; delete s633x23.txt; diary s633x23.txt;



x = linspace(-4,4,1000);
f = sqrt(1+x);
g = 1 + x./2;
h = 1 + x./2 - (x.^2)./8;
i = 1 + x./2 - (x.^2)./8 + (x.^3)./16;

plot(x,f);
hold on;
plot(x,g);
hold on;
plot(x,h);
hold on;
plot(x,i);
hold off;





echo off; diary off;