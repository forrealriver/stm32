`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/08/04 21:23:58
// Design Name: 
// Module Name: tx_control_module
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


module tx_control_module(
    input clk,
    input rst,
    input tx_en_sig,
    input [7:0]tx_data,
    input bps_clk,
    output tx_done_sig,
    output tx_pin_out
    );
    reg [3:0] i;
    reg rtx;
    reg isdone;
    always@(posedge clk or negedge rst)
    begin
    if(!rst)
        begin
            i<=4'd0;
            rtx<=1'b1;
            isdone<=1'b0;
        end
    else if(tx_en_sig)
    case (i)
       4'd0: if(bps_clk) begin i<=i+1'b1;rtx<=1'b0;end
       4'd1,4'd2,4'd3,4'd4,4'd5,4'd6,4'd7,4'd8:
       if(bps_clk) begin i<=i+1'b1;rtx<=tx_data[i-1];end
       4'd9: if(bps_clk) begin i<=i+1'b1;rtx<=1'b1;end
       4'd10: if(bps_clk) begin i<=i+1'b1;rtx<=1'b1;end
       4'd11: if(bps_clk) begin i<=i+1'b1;isdone<=1'b1;end
       4'd12: begin i<=1'b0;isdone<=1'b0;end
     endcase
     end
     assign tx_pin_out=rtx;
     assign tx_done_sig=isdone;
endmodule
