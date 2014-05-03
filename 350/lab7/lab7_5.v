module DFF_PC(Q, Qbar, clock, data, PREbar, CLRbar, Wen);
    input data, clock, PREbar, CLRbar, Wen;
    output Q, Qbar;

    wire a, b, c, d;
    wire PREbar0, CLRbar0;

    not (PREbar0, PREbar);
    not (CLRbar0, CLRbar);

    nand #1 (d, c, CLRbar0, data, Wen);
    nand #1 (c, d, clock, b);
    nand #1 (b, a, CLRbar0, clock);
    nand #1 (a, PREbar0, d, b);

    nand #1 (Q, PREbar0, b, Qbar);
    nand #1 (Qbar, Q, CLRbar0, c);
endmodule

module DFF32_PC(Q, Qbar, clock, data, PREbar, CLRbar, Wen);
    input  [31:0] data;
    input  clock, PREbar, CLRbar, Wen;
    output [31:0] Q, Qbar;

    DFF_PC a0(Q[0], Qbar[0], clock, data[0], PREbar, CLRbar, Wen);
    DFF_PC a1(Q[1], Qbar[1], clock, data[1], PREbar, CLRbar, Wen);
    DFF_PC a2(Q[2], Qbar[2], clock, data[2], PREbar, CLRbar, Wen);
    DFF_PC a3(Q[3], Qbar[3], clock, data[3], PREbar, CLRbar, Wen);
    DFF_PC a4(Q[4], Qbar[4], clock, data[4], PREbar, CLRbar, Wen);
    DFF_PC a5(Q[5], Qbar[5], clock, data[5], PREbar, CLRbar, Wen);
    DFF_PC a6(Q[6], Qbar[6], clock, data[6], PREbar, CLRbar, Wen);
    DFF_PC a7(Q[7], Qbar[7], clock, data[7], PREbar, CLRbar, Wen);

    DFF_PC b0(Q[8], Qbar[8], clock, data[8], PREbar, CLRbar, Wen);
    DFF_PC b1(Q[9], Qbar[9], clock, data[9], PREbar, CLRbar, Wen);
    DFF_PC b2(Q[10], Qbar[10], clock, data[10], PREbar, CLRbar, Wen);
    DFF_PC b3(Q[11], Qbar[11], clock, data[11], PREbar, CLRbar, Wen);
    DFF_PC b4(Q[12], Qbar[12], clock, data[12], PREbar, CLRbar, Wen);
    DFF_PC b5(Q[13], Qbar[13], clock, data[13], PREbar, CLRbar, Wen);
    DFF_PC b6(Q[14], Qbar[14], clock, data[14], PREbar, CLRbar, Wen);
    DFF_PC b7(Q[15], Qbar[15], clock, data[15], PREbar, CLRbar, Wen);

    DFF_PC c0(Q[16], Qbar[16], clock, data[16], PREbar, CLRbar, Wen);
    DFF_PC c1(Q[17], Qbar[17], clock, data[17], PREbar, CLRbar, Wen);
    DFF_PC c2(Q[18], Qbar[18], clock, data[18], PREbar, CLRbar, Wen);
    DFF_PC c3(Q[19], Qbar[19], clock, data[19], PREbar, CLRbar, Wen);
    DFF_PC c4(Q[20], Qbar[20], clock, data[20], PREbar, CLRbar, Wen);
    DFF_PC c5(Q[21], Qbar[21], clock, data[21], PREbar, CLRbar, Wen);
    DFF_PC c6(Q[22], Qbar[22], clock, data[22], PREbar, CLRbar, Wen);
    DFF_PC c7(Q[23], Qbar[23], clock, data[23], PREbar, CLRbar, Wen);

    DFF_PC d0(Q[24], Qbar[24], clock, data[24], PREbar, CLRbar, Wen);
    DFF_PC d1(Q[25], Qbar[25], clock, data[25], PREbar, CLRbar, Wen);
    DFF_PC d2(Q[26], Qbar[26], clock, data[26], PREbar, CLRbar, Wen);
    DFF_PC d3(Q[27], Qbar[27], clock, data[27], PREbar, CLRbar, Wen);
    DFF_PC d4(Q[28], Qbar[28], clock, data[28], PREbar, CLRbar, Wen);
    DFF_PC d5(Q[29], Qbar[29], clock, data[29], PREbar, CLRbar, Wen);
    DFF_PC d6(Q[30], Qbar[30], clock, data[30], PREbar, CLRbar, Wen);
    DFF_PC d7(Q[31], Qbar[31], clock, data[31], PREbar, CLRbar, Wen);
endmodule

module m555(clock);
    parameter InitDelay = 10, Ton = 50, Toff = 50;
    output clock;
    reg clock;

    initial begin
        #InitDelay clock = 1;
    end

    always begin
        #Ton clock = ~clock;
        #Toff clock = ~clock;
    end
endmodule

module testD32(q, qbar, clock, data, PREbar, CLRbar, Wen);
    input  clock;
    input  [31:0] q, qbar;
    output PREbar, CLRbar, Wen;
    output [31:0] data;
    reg    PREbar, CLRbar, Wen;
    reg    [31:0] data;

    initial begin
        $monitor ($time, " q = %d, qbar = %d, clock = %d, data = %d Wen = %d", q, qbar,  clock, data, Wen);
        data = 0; Wen = 1; PREbar = 1; CLRbar = 1;
        #25
        data = -1;
        #100

        data = 1815681630;
        #50
        data = 4168106685;
        #50
        data = 1815681630;
        #100
        data = 4168106685;
        #50
        data = 1815681630;
        #50
        data = 4168106685;
        #100

        Wen = 0;

        data = 1815681630;
        #50
        data = 4168106685;
        #50
        data = 1815681630;
        #100
        data = 4168106685;
        #50
        data = 1815681630;
        #50
        data = 4168106685;
        #100

        Wen = 1;

        data = 4089469290;
        #50
        data = 2336693550;
        #50
        data = 4089469290;
        #100
        data = 2336693550;
        #50
        data = 4089469290;
        #50
        data = 2336693550;
        #100

        CLRbar = 0;

        data = 1815681630;
        #50
        data = 4168106685;
        #50
        data = 1815681630;
        #100
        data = 4168106685;
        #50
        data = 1815681630;
        #50
        data = 4168106685;
        #100

        CLRbar = 1;

        PREbar = 0;

        data = 1815681630;
        #50
        data = 4168106685;
        #50
        data = 1815681630;
        #100
        data = 4168106685;
        #50
        data = 1815681630;
        #50
        data = 4168106685;
        #100

        PREbar = 1;

        data = 1815681630;
        #50
        data = 4168106685;
        #50
        data = 1815681630;
        #100
        data = 4168106685;
        #50
        data = 1815681630;
        #50
        data = 4168106685;
        #100

        $finish;
    end
endmodule

module testBenchD;
    wire clock, PREbar, CLRbar, Wen;
    wire [31:0] data, q, qbar;

    m555 clk(clock);
    DFF32_PC dff(q, qbar, clock, data, PREbar, CLRbar, Wen);
    testD32 td(q, qbar, clock, data, PREbar, CLRbar, Wen);
endmodule