`include "full_adder_32.v"

module lab6_4();
    reg     [31:0] A, B;
    reg     C0;
    wire    [31:0] S;
    wire    Cout;

    full_adder_32 fa(S, Cout, A, B, C0);

    initial begin
        $monitor($time, "\tA=%d\tB=%d\tCin=%b\tS=%d\tCout=%b", A, B, C0, S, Cout);

        A = 0;      B = 0;      C0 = 0;
        #1
        A = 0;      B = 0;      C0 = 1;
        #1
        A = 0;      B = 1;      C0 = 0;
        #1
        A = 1;      B = 0;      C0 = 0;
        #1
        A = 1;      B = 1;      C0 = 0;
        #1
        A = 1;      B = 1;      C0 = 1;
        #1
        A = 16777215;   B = 16777215;   C0 = 0;
        #1
        A = 16777215;   B = 16777215;   C0 = 1;
        #1
        A = 4294967295; B = 0;      C0 = 0;
        #1
        A = 4294967295; B = 0;      C0 = 1;
        #1
        A = 4294967295; B = 1;      C0 = 0;
        #1
        A = 4294967295; B = 1;      C0 = 1;
        #1
        A = 0;      B = 4294967295; C0 = 0;
        #1
        A = 0;      B = 4294967295; C0 = 1;
        #1
        A = 1;      B = 4294967295; C0 = 0;
        #1
        A = 1;      B = 4294967295; C0 = 1;
        #1
        A = 4294967295; B = 4294967295; C0 = 0;
        #1
        A = 4294967295; B = 4294967295; C0 = 1;
        #1
        $finish;
    end

endmodule