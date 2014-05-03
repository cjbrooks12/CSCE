module CPU_Control_unit(opcode, regDst, ALUSrc, memToReg, regWrite, memRead, memWrite, branch, ALUOp);
    input [5:0] opcode;
    output regDst, ALUSrc, memToReg, regWrite, memRead, memWrite, branch;
    output [1:0] ALUOp;

    wire [5:0] opcode;
    reg regDst, ALUSrc, memToReg, regWrite, memRead, memWrite, branch;
    reg [1:0] ALUOp;

    //Set control lines for R-Type instructions
    always @(opcode) begin
    if(opcode == 6'b000000) begin
        regDst <= 1'b1;
        ALUSrc <= 1'b0;
        memToReg <= 1'b0;
        regWrite <= 1'b1;
        memRead <= 1'b0;
        memWrite <= 1'b0;
        branch <= 1'b0;
        ALUOp <= 2'b10;
    end

    //lw
    else if(opcode == 6'b100011) begin
        regDst <= 1'b0;
        ALUSrc <= 1'b1;
        memToReg <= 1'b1;
        regWrite <= 1'b1;
        memRead <= 1'b1;
        memWrite <= 1'b0;
        branch <= 1'b0;
        ALUOp <= 2'b00;
    end

    //sw
    else if(opcode == 6'b101011) begin
        regDst <= 1'b0;
        ALUSrc <= 1'b0;
        memToReg <= 1'b0;
        regWrite <= 1'b0;
        memRead <= 1'b0;
        memWrite <= 1'b1;
        branch <= 1'b0;
        ALUOp <= 2'b00;
    end

    //beq
    else  begin
        regDst <= 1'b0;
        ALUSrc <= 1'b0;
        memToReg <= 1'b0;
        regWrite <= 1'b0;
        memRead <= 1'b0;
        memWrite <= 1'b0;
        branch <= 1'b1;
        ALUOp <= 2'b01;
    end

end

endmodule