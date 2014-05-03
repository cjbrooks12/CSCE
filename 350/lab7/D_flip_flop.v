`include "D_latch.v"

module D_flip_flop(q, qbar, C, D);
    output q, qbar;
    input C, D;

    wire C0, q_master, qbar_master;

    not (C0, C);

    D_latch latch1(q_master, qbar_master, C, D);
    D_latch latch2(q, qbar, C0, q_master);

endmodule