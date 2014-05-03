module RegFile(readData1, readData2, readAddr1, readAddr2, writeData, writeAddr, writeEn, clk);
    output [31:0] readData1, readData2;
    input [4:0] readAddr1, readAddr2, writeAddr;
    input clk, writeEn;
    input [31:0] writeData;

    reg [31:0] readData1, readData2;
    reg [31:0] reg_file[31:0];

    always @(negedge clk) begin
        readData1 = reg_file[readAddr1];
        readData2 = reg_file[readAddr2];
    end

    always@(posedge clk) begin
        if(writeEn == 1) begin
            reg_file[writeAddr] = writeData;
        end
    end
endmodule

// module reg_file_test;
//     wire clk;
//     reg writeEn;
//     wire [31:0] RSData, RTData;
//     reg [5:0] RSAddr, RTAddr, writeAddr;
//     reg [31:0] writeData;

//     integer i;

//     m555 system_clock(clk);
//     RegFile(RSData, RTData, RSAddr, RTAddr, writeAddr, clk, writeEn, writeData);


//     initial begin
//         $monitor($time, " clk: %d, RS: %d RT: %d", clk, RSData, RTData);
//             for (i = 0; i < 32; i = i+1) begin
//                 writeEn = 1; RSAddr = 0; RTAddr = 0; writeAddr = i; writeData = i;
//                 #100;
//             end

//             $display("\n\n");

//             for (i = 0; i < 32; i = i+1) begin
//                 writeEn = 0; RSAddr = i; RTAddr = i; writeAddr = 0; writeData = 0;
//                 #100;
//             end
//         $finish;
//     end

// endmodule