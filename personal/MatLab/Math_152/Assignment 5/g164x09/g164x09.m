clear; clc; close all; echo on; delete g164x09.txt; diary g164x09.txt;

syms F1 F2 F3 F4 F5 F6 F7 F8 F9;

a = (cosd(45) * F1) + F2 == 0;
b = F4 + (cosd(48.81) * F5) - (cosd(45) * F1) == 0;
c = (-sind(48.81) * F5) - F3 - (sind(45) * F1) == 1000;
d = (cosd(48.81) * F8) - F4 == 0;
e = (-sind(48.81) * F8) - F7 == 500;
f = F9 - (cosd(48.81) * F5) - F6 == 0;
g = F7 + (sind(48.81) * F5) == 4000;
h = (sind(48.81)) * F8 == -1107.14;
i = (-cosd(48.81) * F8) - F9 == 0;

[F1, F2, F3, F4, F5, F6, F7, F8, F9] = solve(a, b, c, d, e, f, g, h, i);

vpa(F1)
vpa(F2)
vpa(F3)
vpa(F4)
vpa(F5)
vpa(F6)
vpa(F7)
vpa(F8)
vpa(F9)

echo off; diary off;
