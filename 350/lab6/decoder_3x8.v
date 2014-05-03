module decoder_3x8(d, a, b, c);
	output [7:0] d;
	input a, b, c;

	wire a0, b0, c0;

	not nota(a0, a);
	not notb(b0, b);
	not notc(c0, c);

	and and0(d[0], a0, b0, c0);
	and and1(d[1], a, b0, c0);
	and and2(d[2], a0, b, c0);
	and and3(d[3], a, b, c0);
	and and4(d[4], a0, b0, c);
	and and5(d[5], a, b0, c);
	and and6(d[6], a0, b, c);
	and and7(d[7], a, b, c);
endmodule
