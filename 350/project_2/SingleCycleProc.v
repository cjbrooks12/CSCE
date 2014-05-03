`timescale 1ns/1ps

// Texas A&M University          //
// cpsc350 Computer Architecture //
// $Id: SingleCycleProc.v,v 1.1 2002/04/08 23:16:14 miket Exp miket $ //

// instruction opcode
//R-Type (Opcode 000000)
`define OPCODE_ADD     6'b000000
`define OPCODE_SUB     6'b000000
`define OPCODE_ADDU    6'b000000
`define OPCODE_SUBU    6'b000000
`define OPCODE_AND     6'b000000
`define OPCODE_OR      6'b000000
`define OPCODE_SLL     6'b000000
`define OPCODE_SRA     6'b000000
`define OPCODE_SRL     6'b000000
`define OPCODE_SLT     6'b000000
`define OPCODE_SLTU    6'b000000
`define OPCODE_XOR     6'b000000
`define OPCODE_JR      6'b000000
//I-Type (All opcodes except 000000, 00001x, and 0100xx)
`define OPCODE_ADDI    6'b001000
`define OPCODE_ADDIU   6'b001001
`define OPCODE_ANDI    6'b001100
`define OPCODE_BEQ     6'b000100
`define OPCODE_BNE     6'b000101
`define OPCODE_BLEZ    6'b000110
`define OPCODE_BLTZ    6'b000001
`define OPCODE_ORI     6'b001101
`define OPCODE_XORI    6'b001110
`define OPCODE_NOP     6'b110110
`define OPCODE_LUI     6'b001111
`define OPCODE_SLTI    6'b001010
`define OPCODE_SLTIU   6'b001011
`define OPCODE_LB      6'b100000
`define OPCODE_LW      6'b100011
`define OPCODE_SB      6'b101000
`define OPCODE_SW      6'b101011
// J-Type (Opcode 00001x)
`define OPCODE_J       6'b000010
`define OPCODE_JAL     6'b000011

// Top Level Architecture Model //
// `include "ALU_behav.v"
// `include "lshift2.v"
// `include "signextend.v"
// `include "mux.v"
// `include "IdealMemory.v"


/*-------------------------- CPU -------------------------------
 * This module implements a single-cycle
 * CPU similar to that described in the text book
 * (for example, see Figure 5.19).
 *
 */

//
// Input Ports
// -----------
// clock - the system clock (m555 timer).
//
// reset - when asserted by the test module, forces the processor to
//         perform a "reset" operation.  (note: to reset the processor
//         the reset input must be held asserted across a
//         negative clock edge).
//
//         During a reset, the processor loads an externally supplied
//         value into the program counter (see startPC below).
//
// startPC - during a reset, becomes the new contents of the program counter
//	     (starting address of test program).
//
// Output Port
// -----------
// dmemOut - contains the data word read out from data memory. This is used
//           by the test module to verify the correctness of program
//           execution.
//-------------------------------------------------------------------------

module SingleCycleProc(clk, Reset_L, startPC, dmemOut);
	input 	Reset_L, clk;
    input [31:0] startPC;
	output [31:0] dmemOut;
	reg [31:0] dmemOut;

	//Fetch instruction and get new program counter
	wire [31:0] instruction, PC_out;
	reg [31:0] PC;
	InstrMem(PC, instruction);
	wire [31:0] sign_extended;

	//ProgramCounter(PC, PC_out, zero, sign_extended);


	//Break up instruction into basic components
	reg [5:0] opcode;
	reg [5:0] funct;
	reg [15:0] immediate;
	reg [25:0] address;

	reg [4:0] RSAddr, RTAddr, RDAddr;
	wire [31:0] RSData, RTData, RDData;


	SIGN_EXTEND(immediate, sign_extended);

	//Generate CPU and ALU control bits
	wire regDST, ALUSrc, memToReg, regWrite, memRead, memWrite, branch;
	wire [1:0] ALUOp;
	CPU_Control_unit(opcode, regDst, ALUSrc, memToReg, regWrite, memRead, memWrite, branch, ALUOp);

	wire [3:0] alu_control;
	ALU_Control_Unit(alu_control, funct, ALUOp);

	//Generate the input addresses to the regfile, and retrieve data from regfile
	wire [4:0] out;
	MUX5_2to1(instruction[20:16], instruction[15:11], regDST, out);


	RegFile(RSData, RTData, RSAddr, RTAddr, RDData, RDAddr, regWrite, clk);

	//select intputs to the ALU and do calculation
	wire [31:0] alu_in1;
	MUX32_2to1(RTData, sign_extended, ALUSrc, alu_in1);

	wire [31:0] alu_out;
	wire overflow, cin, cout, zero, PCSrc;
	wire [31:0] result;
	and(PCSrc, branch, zero);
	ALU_behav(RSData, alu_in1, alu_control, result, overflow, cin, cout, zero);

	wire [31:0] memReadData;
	DataMem(result, clk, memRead, memWrite, RTData, memReadData);
	MUX32_2to1(result, memReadData, memToReg, RDData);

	always @(negedge clk) begin
		assign PC = PC + 4;
		assign opcode = instruction[31:26];
	  	assign funct = instruction[5:0];
	  	assign immediate = instruction[15:0];
	  	assign address = instruction[25:0];
	  	assign RSAddr = instruction[25:21];
	  	assign RTAddr = instruction[20:16];
	  	assign RDAddr = instruction[15:11];
	  	assign dmemOut = RDData;
	end

   	always @(~Reset_L) assign PC = startPC;

    //Monitor changes in the program counter
    always @(PC)
    	#10 $display($time," PC=%d Instr: op=%d rs=%d rt=%d rd=%d imm16=%d funct=%d",
		PC,instruction[31:26],instruction[25:21],instruction[20:16],instruction[15:11],instruction[15:0],instruction[5:0]);


    //Monitors memory writes
 //   	always @(MemWrite)
	// 	begin
	// 	#1 $display($time," MemWrite=%b clock=%d addr=%d data=%d",
	//             MemWrite, clock, dmemaddr, rportb);
	// end

endmodule

module testCPU(clk, Reset_L, startPC, testData);
	input clk;
	input [31:0] testData;
	output Reset_L;
	output [31:0] startPC;
	reg  Reset_L;
	reg [31:0] startPC;

   	initial begin
      	// Your program 1
		Reset_L = 0;  startPC = 0 * 4;
		#101 // insures reset is asserted across negative clock edge
		Reset_L = 1;
		#10000; // allow enough time for program 1 to run to completion
		Reset_L = 0;
		#1 $display("Program 1: Result: %d", testData);
      $finish;
   end
endmodule // testCPU

module TopProcessor;
    wire reset, clk, Reset_L;
    wire [31:0] startPC;
    wire [31:0] testData;

    m555 system_clock(clk);
    testCPU tcpu(clk, Reset_L, startPC, testData);
    SingleCycleProc SSProc(clk, Reset_L, startPC, testData);


endmodule // TopProcessor
