`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/08/04 20:46:46
// Design Name: 
// Module Name: tx_bps_module
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module tx_bps_module(
    input clk,
    input rst,
    input count_sig,
    output bps_clk
    );
    reg[14:0] count_bps;
    always@(posedge clk or negedge rst)
    begin
    if(!rst)
    count_bps<=15'd0;
    else if(count_bps == 15'd10416)  
    count_bps<=15'd0;
    else if(count_sig)
    count_bps<=count_bps+1'b1;
    else count_bps<=15'd0;
    end
    
    assign bps_clk= (count_bps==15'd5280)? 1'b1:1'b0;
    
endmodule
