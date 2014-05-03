`include "full_adder_4.v"

module lab6_4();
	reg 	[3:0] A, B;
	reg		C0;
    wire   	[3:0] S;
	wire 	Cout;

    full_adder_4 fa(S, Cout, A, B, C0);

	initial begin
		$monitor($time, "\t A=%d \t B=%d \t Cin=%b \t Cout=%b \t S=%d", A, B, C0, Cout, S);
		
		A = 0;	B = 0;	C0 = 0;
		#1 A = 0;	B = 0;	C0 = 1;
		#1 A = 0;	B = 1;	C0 = 0;
		#1 A = 1;	B = 0;	C0 = 0;
		#1 A = 1;	B = 1;	C0 = 0;
		#1 A = 1;	B = 1;	C0 = 1;
		#1 A = 7;	B = 7;	C0 = 0;
		#1 A = 7;	B = 7;	C0 = 1;
		#1 A = 15;	B = 0;	C0 = 0;
		#1 A = 15;	B = 0;	C0 = 1;
		#1 A = 15;	B = 1;	C0 = 0;
		#1 A = 15;	B = 1;	C0 = 1;
		#1 A = 0;	B = 15;	C0 = 0;
		#1 A = 0;	B = 15;	C0 = 1;
		#1 A = 1;	B = 15;	C0 = 0;
		#1 A = 1;	B = 15;	C0 = 1;
		#1 A = 15;	B = 15;	C0 = 0;
		#1 A = 15;	B = 15;	C0 = 1;
		#1 
		$finish;
	end

endmodule 





































