function u = unitvec(A,B)



ax = A(1,1);
ay = A(1,2);
az = A(1,3);

bx = B(1,1);
by = B(1,2);
bz = B(1,3);

x = bx - ax;
y = by - ay;
z = bz - az;

vector = [x, y, z];
v = sqrt(x^2 + y^2 + z^2);

u = vector / v





end
