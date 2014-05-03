`include "full_adder_dec.v"

module lab6_5();
    reg    a, b, c_in;
    wire   s, c_out;

    full_adder_dec fad(s, c_out, a, b, c_in);
    initial begin
        $monitor ("a=%b \t b=%b \t c_in=%b \t c_out=%b s=%b", a, b, c_in, c_out, s);

        c_in = 0; a = 0; b = 0;
        #1
        c_in = 0; a = 1; b = 0;
        #1
        c_in = 0; a = 0; b = 1;
        #1
        c_in = 0; a = 1; b = 1;
        #1
        c_in = 1; a = 0; b = 0;
        #1
        c_in = 1; a = 1; b = 0;
        #1
        c_in = 1; a = 0; b = 1;
        #1
        c_in = 1; a = 1; b = 1;
        #1
        $finish;
    end
endmodule