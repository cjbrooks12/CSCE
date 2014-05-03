module D_latch(q, qbar, C, D);
    output q, qbar;
    input C, D;

    wire D0, S, R;

    not not1(D0, D);

    nand #1 (S, D, C);
    nand #1 (R, D0, C);

    nand #1 (q, qbar, S);
    nand #1 (qbar, q, R);

endmodule