`include "half_adder.v"

module lab6_2();
	reg    a, b;
    wire   s, c;
	
	half_adder ha(s, c ,a, b);
	
	initial begin
        $monitor ($time,"\t a=%b \t b=%b \t c=%b \t s=%b", a, b, c, s);
        a = 0; b = 0;
        #1 
        a = 0; b = 1;
        #1
        a = 1; b = 0;
        #1
        a = 1; b = 1;
        #1 
        $finish;
    end
endmodule 