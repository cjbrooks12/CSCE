`include "decoder_3x8.v"

module full_adder_dec(s, c_out, a, b, c_in);
	output s, c_out;
	input a, b, c_in;

    wire [7:0] d;

	decoder_3x8 decoder1(d, a, b, c_in);

    or or1(s, d[1], d[2], d[4], d[7]);
    or or2(c_out, d[3], d[5], d[6], d[7]);
endmodule