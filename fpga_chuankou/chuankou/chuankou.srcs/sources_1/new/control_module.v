`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/08/04 21:47:08
// Design Name: 
// Module Name: control_module
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


module control_module(
    input clk,
    input rst,
    input tx_done_sig,
    input  [7:0] x,
    input  [7:0] y,
    output tx_en_sig,
    output [7:0]tx_data
    );
    reg isen;
    reg [7:0] rdata;
    reg [1:0] flag;
    always@(posedge clk or negedge rst)
    if(!rst)
    begin 
        isen<=1'b0;
        rdata<=8'h0;
        flag<=1'b0;
    end
    else if (tx_done_sig)
    begin
       if(flag==0)
       begin
        rdata<=8'h0;
        flag<=1;
       end 
        else if(flag==1)
        begin
          rdata<=x;
          flag<=2;
        end 
        else if(flag==2)
        begin
          rdata<=y;
          flag<=0;
         end 
        isen<=1'b0;
    end 
    else isen<=1'b1;
        
    assign tx_data=rdata;
    assign tx_en_sig=isen;
endmodule
