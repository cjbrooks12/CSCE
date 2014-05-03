module full_adder(s, c_out, a, b, c_in);
	input 	a, b, c_in;
	output  s, c_out;
	
	wire 	t1;
	nand 	nand1(t1, a, b);
	
	wire 	t2;
	nand 	nand2(t2, a, t1);
	
	wire 	t3;
	nand 	nand3(t3, b, t1);
	
	wire 	t4;
	nand 	nand4(t4, t2, t3);
	
	wire 	t5;
	nand 	nand5(t5, c_in, t4);
	
	wire 	t6;
	nand 	nand6(t6, t4, t5);
	
	wire 	t7;
	nand 	nand7(t7, c_in, t5);
	
	nand 	nand8(s, t6, t7);
	nand 	nand9(c_out, t1, t5);
endmodule 