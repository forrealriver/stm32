`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/08/04 21:36:06
// Design Name: 
// Module Name: tx_module
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


module tx_module(
     input clk,
     input rst,
     input [7:0]tx_data,
     input tx_en_sig,
     output tx_done_sig,
     output tx_pin_out
    );
    wire bps_clk;
    tx_bps_module u1(.clk(clk),.rst(rst),.count_sig(tx_en_sig),.bps_clk(bps_clk));
    
    tx_control_module u2(.clk(clk),.rst(rst),.tx_en_sig(tx_en_sig),.tx_data(tx_data),.bps_clk(bps_clk),.tx_done_sig(tx_done_sig),.tx_pin_out(tx_pin_out));
endmodule
