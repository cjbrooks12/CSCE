`include "full_adder.v"

module full_adder_4(s, c_out, a, b, c_in);
	output [3:0] 	s;
	output			c_out;

	input [3:0] 	a;
	input [3:0] 	b;
	input 			c_in;

	wire [3:0] temp;

	full_adder fa0(s[0], temp[0], a[0], b[0], c_in);
	full_adder fa1(s[1], temp[1], a[1], b[1], temp[0]);
	full_adder fa2(s[2], temp[2], a[2], b[2], temp[1]);
	full_adder fa3(s[3], c_out,   a[3], b[3], temp[2]);
endmodule