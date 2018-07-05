clear; clc; close all; delete g213x20.txt; diary g213x20.txt;


matrix = [1, 18, 60; 2, 20, 61; 3, 3, 50];

class = 0;
while class <= 2
    class = class + 1;
    for n = 1:1:2
        time = matrix(class, n + 1);
    
        if class == 3
                if time >=1 && time <=6 
                    rent = time * 27;
                elseif time >=7 && time <=27
                    rent = 162 + ((time-6) * 25);
                elseif time >=28 && time <=60
                    rent = 662 + ((time-27) * 23);
                else 
                    disp('Class 3 rental is not available for more than 60 days.')
                end
        elseif class == 2
                if time >=1 && time <=6 
                    rent = time * 34;
                elseif time >=7 && time <=27
                    rent = 204 + ((time-6) * 31);
                elseif time >=28 && time <=60
                    rent = 824 + ((time-27) * 28);
                else 
                    disp('Class 2 rental is not available for more than 60 days.') 
                end
        elseif class == 1
                if time >=1 && time <=6 
                    disp('Class 1 cars cannot be rented for fewer than 7 days.')
                elseif time >=7 && time <=27
                    rent = 276 + ((time-6) * 43);
                elseif time >=28 && time <=60
                    rent = 1136 + ((time-27) * 38);
                else 
                    disp('Class 1 rental is not available for more than 60 days.')
                end
        end
         if time <=60
             fprintf('A car of class %0.0f', class)
             fprintf(' will cost $%0.0f', rent)
             fprintf(' to rent for %0.0f days.', time)
             disp(' ')
         elseif class == 1 && time >=7 && time <=60
             disp(' ')
         end
    end
end

diary off;