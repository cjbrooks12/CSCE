function u = unitvec(A,B)

    if length(A) == 2
        ax = A(1);
        ay = A(2);
        
        bx = B(1);
        by = B(2);
        
        x = bx - ax;
        y = by - ay;
        
        vector = [x, y];
        v = sqrt(x^2 + y^2);
    else
        ax = A(1);
        ay = A(2);
        az = A(3);

        bx = B(1);
        by = B(2);
        bz = B(3);

        x = bx - ax;
        y = by - ay;
        z = bz - az;
        
        vector = [x, y, z];
        v = sqrt(x^2 + y^2 + z^2);
  
    end

        u = vector / v
end
