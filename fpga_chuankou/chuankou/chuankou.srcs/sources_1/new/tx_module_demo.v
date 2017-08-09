`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/08/04 21:56:40
// Design Name: 
// Module Name: tx_module_demo
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


module tx_module_demo(
    input clk,
    input rst,
    input [7:0] x,
    input [7:0] y,
    output tx_pin_out,
    output led
    );
    wire [7:0] tx_data;
    wire tx_en_sig;
    wire iRST_N;
    assign iRST_N = ~rst;
    control_module u1(.clk(clk),.rst(iRST_N),.tx_done_sig(tx_done_sig),.x(x),.y(y),.tx_en_sig(tx_en_sig),.tx_data(tx_data));
    
    tx_module u2(.clk(clk),.rst(iRST_N),.tx_data(tx_data),.tx_en_sig(tx_en_sig),.tx_done_sig(tx_done_sig),.tx_pin_out(tx_pin_out));
    
    assign led=1;
endmodule
