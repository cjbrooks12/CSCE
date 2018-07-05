clear; clc; close all; delete g343x13.txt; diary g343x13.txt;

C = 15*(10^-6);
L = 240*(10^-3);
w = 60:0.1:100;
r = 10:0.1:40;

[W,R] = meshgrid(w, r);

I = 24 ./ sqrt(R.^2 + (W*L - 1./(W*C)).^2);

mesh(W,R,I);
xlabel('x'); ylabel('y'); zlabel('z');
figure;
mesh(W,R,I);
view(0,0);

diary off;