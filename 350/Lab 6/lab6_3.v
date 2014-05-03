`include "full_adder.v"

module lab6_3();
    reg    a, b, c_in;
    wire   s, c_out;

    full_adder fa(s, c_out, a, b, c_in);

    initial begin
        $monitor ($time,"\t  c_in=%b \t a=%b \t b=%b \t c_out=%b \t s=%b",c_in, a, b, c_out, s);
        c_in = 0; a = 0; b = 0;
        #1
        c_in = 0; a = 0; b = 1;
        #1
        c_in = 0; a = 1; b = 0;
        #1
        c_in = 0; a = 1; b = 1;
        #1
		c_in = 1; a = 0; b = 0;
        #1
        c_in = 1; a = 0; b = 1;
        #1
        c_in = 1; a = 1; b = 0;
        #1
        c_in = 1; a = 1; b = 1;
        #1
        $finish;
    end
endmodule