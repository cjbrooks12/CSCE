`include "mux_4x1.v"

module full_adder_mux(s, c_out, a, b, c_in);
    output s, c_out;
    input a, b, c_in;

    wire [3:0] dataA, dataB;
    wire [1:0] select;
    wire a0;

    not not1(a0, a);

    assign select[0] = c_in;
    assign select[1] = b;

    assign dataA[0] = a;
    assign dataA[1] = a0;
    assign dataA[2] = a0;
    assign dataA[3] = a;

    assign dataB[0] = 0;
    assign dataB[1] = a;
    assign dataB[2] = a;
    assign dataB[3] = 1;

    mux_4x1 mux1(s, dataA, select);
    mux_4x1 mux2(c_out, dataB, select);

endmodule