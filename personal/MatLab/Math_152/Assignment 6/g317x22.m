clear; clc; close all; echo on; delete g317x22.txt; diary g317x22.txt;

x = linspace(0,pi/2,1000);

a = 7.786 * (10^6);

P = 4*a*quad(@myfunc,0,pi/2)

T = 11.86*365*24

V = P / T

echo off; diary off;
