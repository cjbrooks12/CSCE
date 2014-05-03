module half_adder(s, c, a, b);
	input a, b;
	output s, c;
	
	xor 	s_out(s, a, b);
	and 	c_out(c, a, b);
endmodule  