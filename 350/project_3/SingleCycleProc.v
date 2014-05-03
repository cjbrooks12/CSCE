`timescale 1ns/1ps

// Texas A&M University          //
// cpsc350 Computer Architecture //
// $Id: SingleCycleProc.v,v 1.1 2002/04/08 23:16:14 miket Exp miket $ //

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
//       (starting address of test program).
//
// Output Port
// -----------
// dmemOut - contains the data word read out from data memory. This is used
//           by the test module to verify the correctness of program
//           execution.
//-------------------------------------------------------------------------

module SingleCycleProc(clk, reset, startPC, RDData);
    input    reset, clk;
    input [31:0] startPC;
    output [31:0] RDData;

    //Fetch instruction and get new program counter
    wire [31:0] instruction, PC_out;
    reg [31:0] PC;
    InstrMem(PC, instruction);
    wire [31:0] sign_extended;

    ProgramCounter(PC, PC_out, zero, sign_extended);


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
    wire [3:0] alu_control;
    CPU_Control_unit(opcode, funct, alu_control, regDST, ALUSrc, memToReg, regWrite, memRead, memWrite, branch);

    //Generate the input addresses to the regfile, and retrieve data from regfile
    wire [4:0] out;
    MUX5_2to1(RTAddr, RDAddr, regDST, out);


    RegFile(RSData, RTData, RSAddr, RTAddr, RDData, out, regWrite, clk);

    //select intputs to the ALU and do calculation
    wire [31:0] alu_in1;
    MUX32_2to1(RTData, sign_extended, ALUSrc, alu_in1);

    wire overflow, cin, cout, zero, PCSrc;
    assign cin = 0;
    wire [31:0] result;
    and(PCSrc, branch, zero);
    ALU_behav(RSData, alu_in1, alu_control, result, overflow, cin, cout, zero);

    wire [31:0] memReadData;
    DataMem(result, clk, memRead, memWrite, RTData, memReadData);
    MUX32_2to1(result, memReadData, memToReg, RDData);

    always @(negedge clk) begin
        assign opcode = instruction[31:26];
        assign funct = instruction[5:0];
        assign immediate = instruction[15:0];
        assign address = instruction[25:0];
        assign RSAddr = instruction[25:21];
        assign RTAddr = instruction[20:16];
        assign RDAddr = instruction[15:11];
        // assign dmemOut = RDData;
    end

    // always @(~Reset_L) assign PC = startPC;


    //Monitors memory writes
    always @(clk) begin
        // #1 $display($time, " clk=%b RSData=%d alu_in1=%d result=%d RDData=%d", clk, RSData, alu_in1, result, RDData);
        // #1 $display($time, " clk=%b instruction=%d dmemout=%d", clk, instruction, RDData);
        // #1 $display($time, " clk=%b opcode=%b funct=%b", clk, opcode, funct);
        // #1 $display($time, " clk=%b regWrite=%b RSAddr=%d RSData=%d RTAddr=%d RTData=%d out=%d", clk, regWrite, RSAddr, RSData, RTAddr, RTData, out);
        // #1 $display($time, " clk=%b regDST=%b regWrite=%b ALUSrc=%b memRead=%b memWrite=%b memToReg=%b branch=%b alu_control=%b ", clk, regDST, regWrite, ALUSrc, memRead, memWrite, memToReg, branch, alu_control);
        // #1 $display($time, " clk=%b R_type: %b %d %d %d _____ %b", clk, opcode, RSAddr, RTAddr, RDAddr, funct);
        // #1 $display($time, " clk=%b I_type: %b %d %d %b", clk, opcode, RSAddr, RTAddr, immediate);
        // #1 $display($time, " clk=%b J_type: %b %d %b", clk, opcode, address);
    end
    always @(PC) $display($time, " PC=%d", PC);

endmodule

module testCPU(clk, Reset_L, startPC, testData);
    input clk;
    input [31:0] testData;
    output Reset_L;
    output [31:0] startPC;
    reg  Reset_L;
    reg [31:0] startPC;

    reg [31:0] instruction;
    SingleCycleProc(clk, Reset_L, startPC, testData);

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
    testCPU(clk, Reset_L, startPC, testData);
endmodule // TopProcessor
