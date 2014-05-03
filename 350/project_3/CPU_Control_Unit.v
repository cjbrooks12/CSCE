// instruction opcode
//R-Type, use funct for ALU control
`define OPCODE_R_TYPE  6'b000000
`define FUNCT_ADD      6'b100000
`define FUNCT_ADDU     6'b100001
`define FUNCT_SUB      6'b100010
`define FUNCT_SUBU     6'b100011
`define FUNCT_AND      6'b100100
`define FUNCT_OR       6'b100101
`define FUNCT_XOR      6'b100110
`define FUNCT_SLL      6'b000000
`define FUNCT_SRA      6'b000011
`define FUNCT_SRL      6'b000010
`define FUNCT_SLT      6'b101010
`define FUNCT_SLTU     6'b101001

//I-Type (All opcodes except 000000, 00001x, and 0100xx)
`define OPCODE_ADDI    6'b001000
`define OPCODE_ADDIU   6'b001001
`define OPCODE_ANDI    6'b001100
`define OPCODE_BEQ     6'b000100
`define OPCODE_BNE     6'b000101
`define OPCODE_ORI     6'b001101
`define OPCODE_XORI    6'b001110
`define OPCODE_NOP     6'b110110
`define OPCODE_SLTI    6'b001010
`define OPCODE_SLTIU   6'b001011
`define OPCODE_LW      6'b100011
`define OPCODE_SW      6'b101011

// J-Type (Opcode 00001x)
`define OPCODE_J       6'b000010
`define OPCODE_JAL     6'b000011


module CPU_Control_unit(opcode, funct, ALUControl, regDst, ALUSrc, memToReg, regWrite, memRead, memWrite, branch);
    input [5:0] opcode, funct;
    output [3:0] ALUControl;
    output regDst, ALUSrc, memToReg, regWrite, memRead, memWrite, branch;

    reg regDst, ALUSrc, memToReg, regWrite, memRead, memWrite, branch;
    reg [3:0] ALUControl;

    always @(opcode or funct) begin
    case(opcode)
        //all R-type
        6'b000000: begin
        regDst <= 1'b1;
        ALUSrc <= 1'b0;
        memToReg <= 1'b0;
        regWrite <= 1'b1;
        memRead <= 1'b0;
        memWrite <= 1'b0;
        branch <= 1'b0;
    end

    //lw
    6'b100011: begin
        regDst <= 1'b0;
        ALUSrc <= 1'b1;
        memToReg <= 1'b1;
        regWrite <= 1'b1;
        memRead <= 1'b1;
        memWrite <= 1'b0;
        branch <= 1'b0;
    end

    //sw
    6'b101011: begin
        regDst <= 1'b0;
        ALUSrc <= 1'b0;
        memToReg <= 1'b0;
        regWrite <= 1'b1;
        memRead <= 1'b0;
        memWrite <= 1'b0;
        branch <= 1'b0;
    end

    //beq, bne
    6'b000100, 6'b000101: begin
        regDst <= 1'b0;
        ALUSrc <= 1'b0;
        memToReg <= 1'b0;
        regWrite <= 1'b0;
        memRead <= 1'b0;
        memWrite <= 1'b0;
        branch <= 1'b1;
    end

    //All other instructions follow this format
    default: begin
        regDst <= 1'b0;
        ALUSrc <= 1'b1;
        memToReg <= 1'b0;
        regWrite <= 1'b1;
        memRead <= 1'b0;
        memWrite <= 1'b0;
        branch <= 1'b0;
    end
    endcase


    //ALUControl is determined by opcode of I-type or funct of R-type
    if((opcode == `OPCODE_R_TYPE & funct == `FUNCT_ADD)  | opcode == `OPCODE_ADDI)  ALUControl <= 4'b0111;
    if((opcode == `OPCODE_R_TYPE & funct == `FUNCT_ADDU) | opcode == `OPCODE_ADDIU) ALUControl <= 4'b0001;
    if((opcode == `OPCODE_R_TYPE & funct == `FUNCT_SUB))                            ALUControl <= 4'b0010;
    if((opcode == `OPCODE_R_TYPE & funct == `FUNCT_SUBU))                           ALUControl <= 4'b0011;
    if((opcode == `OPCODE_R_TYPE & funct == `FUNCT_AND)  | opcode == `OPCODE_ANDI)  ALUControl <= 4'b0100;
    if((opcode == `OPCODE_R_TYPE & funct == `FUNCT_OR)   | opcode == `OPCODE_ORI)   ALUControl <= 4'b0101;
    if((opcode == `OPCODE_R_TYPE & funct == `FUNCT_XOR)  | opcode == `OPCODE_XORI)  ALUControl <= 4'b0110;
    if((opcode == `OPCODE_R_TYPE & funct == `FUNCT_SLL))                            ALUControl <= 4'b1110;
    if((opcode == `OPCODE_R_TYPE & funct == `FUNCT_SRA))                            ALUControl <= 4'b1100;
    if((opcode == `OPCODE_R_TYPE & funct == `FUNCT_SRL))                            ALUControl <= 4'b1101;
    if((opcode == `OPCODE_R_TYPE & funct == `FUNCT_SLT))                            ALUControl <= 4'b1010;
    if((opcode == `OPCODE_R_TYPE & funct == `FUNCT_SLTU))                           ALUControl <= 4'b1011;
end

endmodule