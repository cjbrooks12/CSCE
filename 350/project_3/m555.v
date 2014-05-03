module m555 (CLK);
   parameter StartTime = 0, Ton = 50, Toff = 50, Tcc = Ton+Toff; //

   output CLK;
   reg 	  CLK;

   initial begin
      #StartTime CLK = 0;
   end

   // The following is correct if clock starts at LOW level at StartTime //
   always begin
      #Toff CLK = ~CLK;
      #Ton CLK = ~CLK;
   end
endmodule