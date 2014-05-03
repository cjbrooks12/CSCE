module mux_4x1(out, data, select);
    output out;
    input [3:0] data;
    input [1:0] select;

    wire [3:0] temp;
    wire [1:0] select0;

    not notselect0(select0[0], select[0]);
    not notselect1(select0[1], select[1]);

    and and0(temp[0], select0[0], select0[1], data[0]);
    and and1(temp[1], select[0], select0[1], data[1]);
    and and2(temp[2], select0[0], select[1], data[2]);
    and and3(temp[3], select[0], select[1], data[3]);

    or or1(out, temp[0], temp[1], temp[2], temp[3]);

endmodule