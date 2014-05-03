module RegFile(readData1, readData2, readAddr1, readAddr2, writeData, writeAddr, writeEn, clk);
    output [31:0] readData1, readData2;
    input [4:0] readAddr1, readAddr2, writeAddr;
    input clk, writeEn;
    input [31:0] writeData;

    reg [31:0] readData1, readData2;
    reg [31:0] reg_file[0:31];

    initial begin
        reg_file[0] = 0;
        reg_file[1] = 0;
        reg_file[2] = 0;
        reg_file[3] = 0;
        reg_file[4] = 0;
        reg_file[5] = 0;
        reg_file[6] = 0;
        reg_file[7] = 0;
        reg_file[8] = 0;
        reg_file[9] = 0;
        reg_file[10] = 0;
        reg_file[11] = 0;
        reg_file[12] = 0;
        reg_file[13] = 0;
        reg_file[14] = 0;
        reg_file[15] = 0;
        reg_file[16] = 0;
        reg_file[17] = 0;
        reg_file[18] = 0;
        reg_file[19] = 0;
        reg_file[20] = 0;
        reg_file[21] = 0;
        reg_file[22] = 0;
        reg_file[23] = 0;
        reg_file[24] = 0;
        reg_file[25] = 0;
        reg_file[26] = 0;
        reg_file[27] = 0;
        reg_file[28] = 0;
        reg_file[29] = 0;
        reg_file[30] = 0;
        reg_file[31] = 0;
    end

    always @(readAddr1 or readAddr2) begin
        //Delay is given by:
        // 4: demux to select register to write to
        //      1 NOT followed by AND (critical path)
        // 6: D flip-flip
        //      NOT-->NOR-->NOR for one latch. flip flop is two latches
        // 7: mux to select output for reading
        //      NOT-->AND-->OR
        #10 //demux-->flip flop
        readData1 <= reg_file[readAddr1];
        readData2 <= reg_file[readAddr2];
        // $display("Reading: D1 %d %d, D2 %d %d", readAddr1, readData1, readAddr2, readData2);
    end

    always@(negedge clk) begin
        // $display("writeEn=%d writeAddr=%d writeData=%d", writeEn, writeAddr, writeData);
        #13 //flip flip-->mux
        if(writeEn == 1) begin
            // $display("Writing data %d to register %d", writeData, writeAddr);
            reg_file[writeAddr] <= writeData;
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
//         $monitor($time,
//             " clock=%b RSAddr=%d RSData=%d RTAddr=%d RTData=%d",
//             clk,       RSAddr,   RSData,   RTAddr,   RTData);
//             for (i = 0; i < 32; i = i+1) begin
//                 writeEn = 1; RSAddr = 0; RTAddr = 0; writeAddr = i; writeData = i;
//                 #100;
//             end

//             $display("\n");

//             for (i = 0; i < 32; i = i+1) begin
//                 writeEn = 0; RSAddr = i; RTAddr = i; writeAddr = 0; writeData = 0;
//                 #100;
//             end
//         $finish;
//     end

// endmodule