// Texas A&M University          //
// cpsc350 Computer Architecture //
// $Id: signextend.v,v 1.1 2001/11/07 19:25:23 miket Exp miket $ //
// A insize->outsize sign extender //
module SIGN_EXTEND(in, out);
   parameter INSIZE = 16, OUTSIZE = 32;

   input [INSIZE-1:0] in;
   output [OUTSIZE-1:0] out;

   //Just AND higher 16 bits with in[15] to get sign extended version
   assign 	 out = {{ OUTSIZE-INSIZE {in[INSIZE-1]}}, in};
endmodule // SIGN_EXTEND
