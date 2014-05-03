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

module testD(q, qbar, clock, data, PREbar, CLRbar, Wen);
    input  q, qbar, clock;
    output data, PREbar, CLRbar, Wen;
    reg    data, PREbar, CLRbar, Wen;

    initial begin
        $monitor ($time, " q = %d, qbar = %d, clock = %d, data = %d Wen = %d", q, qbar,  clock, data, Wen);
        data = 0; Wen = 1; PREbar = 1; CLRbar = 1;
        #25
        data = 1;
        #100

        data = 0;
        #50
        data = 1;
        #50
        data = 0;
        #100
        data = 1;
        #50
        data = 0;
        #50
        data = 1;
        #100

        Wen = 0;

        data = 0;
        #50
        data = 1;
        #50
        data = 0;
        #100
        data = 1;
        #50
        data = 0;
        #50
        data = 1;
        #100

        Wen = 1;

        data = 0;
        #50
        data = 1;
        #50
        data = 0;
        #100
        data = 1;
        #50
        data = 0;
        #50
        data = 1;
        #100

        CLRbar = 0;

        data = 0;
        #50
        data = 1;
        #50
        data = 0;
        #100
        data = 1;
        #50
        data = 0;
        #50
        data = 1;
        #100

        CLRbar = 1;

        PREbar = 0;

        data = 0;
        #50
        data = 1;
        #50
        data = 0;
        #100
        data = 1;
        #50
        data = 0;
        #50
        data = 1;
        #100

        PREbar = 1;

        data = 0;
        #50
        data = 1;
        #50
        data = 0;
        #100
        data = 1;
        #50
        data = 0;
        #50
        data = 1;
        #100

        $finish;
    end
endmodule

module testBenchD;
    wire clock, q, qbar, data, PREbar, CLRbar, Wen;
    m555 clk(clock);
    DFF_PC dff(q, qbar, clock, data, PREbar, CLRbar, Wen);
    testD td(q, qbar, clock, data, PREbar, CLRbar, Wen);
endmodule