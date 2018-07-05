clear; clc; close all; delete g215x27.txt; diary g215x27.txt;


for test = 1:1:80
	
	count = 0;
    prime = 0;
    number = 1;
    while number <= test
        prime = rem(test, number);
        number = number + 1;
            if prime == 0 && number ~= test
                count = count + 1;
            elseif prime == 0
                count = count + 1;
            end
    end
    if count == 2
        fprintf('%0.0f ', test)
    end
end


diary off;