module ProgramCounter(PC_in, PC_out, zero, sign_extended);
    input [31:0] PC_in, sign_extended;
    input zero;
    output [31:0] PC_out;

    // reg [31:0] PC_out;

    wire [31:0] pc_jump, pc_add, pc_mux;
    LSHIFT2(sign_extended, pc_jump);
    assign pc_add = PC_in + pc_jump;
    MUX32_2to1(PC_in, pc_add, zero, PC_out);


endmodule