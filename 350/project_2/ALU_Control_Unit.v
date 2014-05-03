module ALU_Control_Unit(control, funct, ALUOp);
    input [5:0] funct;
    input [1:0] ALUOp;
    output [3:0] control;

    assign control[0] = ALUOp[1] & (funct[0] | funct[3]);
    assign control[1] = ~funct[2] | ~ALUOp[1];
    assign control[2] = ALUOp[0] | (ALUOp[1] & funct[1]);
endmodule
