`include "full_adder_4.v"

module full_adder_32(s, c_out, a, b, c_in);
	output [31:0] 	s;
	output			c_out;

	input [31:0] 	a;
	input [31:0] 	b;
	input 			c_in;

	wire [6:0] temp;

	full_adder_4 fa0(s[3:0],   temp[0], a[3:0],   b[3:0],   c_in);
	full_adder_4 fa1(s[7:4],   temp[1], a[7:4],   b[7:4],   temp[0]);
	full_adder_4 fa2(s[11:8],  temp[2], a[11:8],  b[11:8],  temp[1]);
	full_adder_4 fa3(s[15:12], temp[3], a[15:12], b[15:12], temp[2]);

    full_adder_4 fa4(s[19:16], temp[4], a[19:16], b[19:16], temp[3]);
    full_adder_4 fa5(s[23:20], temp[5], a[23:20], b[23:20], temp[4]);
    full_adder_4 fa6(s[27:24], temp[6], a[27:24], b[27:24], temp[5]);
    full_adder_4 fa7(s[31:28], c_out,   a[31:28], b[31:28], temp[6]);
endmodule