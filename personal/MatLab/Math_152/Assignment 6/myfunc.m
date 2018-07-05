function y = myfunc(x);

    a = 7.786 * (10^6);
    b = 7.769 * (10^6);

    k = (sqrt(a^2 - b^2))/a;
    
    y = sqrt(1-((k^2)*(sin(x)).^2));
end