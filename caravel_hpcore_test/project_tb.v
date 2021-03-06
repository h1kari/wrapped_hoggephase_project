// SPDX-FileCopyrightText: 2020 Efabless Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// SPDX-License-Identifier: Apache-2.0

`default_nettype none

`timescale 1 ns / 1 ps

`include "uprj_netlists.v" // this file gets created automatically by multi_project_tools from the source section of info.yaml
`include "caravel_netlists.v"
`include "spiflash.v"

module project_tb;
    initial begin
        $dumpfile ("project.vcd");
        $dumpvars (0, project_tb);
        #1;
    end

    reg clk = 0;
    always #12.5 clk <= !clk;
    reg RSTB;
    reg power1, power2;
    reg power3, power4;

    wire gpio;
    wire [37:0] mprj_io;
    wire [15:0] checkbits = mprj_io[31:16];
    wire fail = mprj_io[0];
    initial begin
        wait(checkbits == 16'hab60);
        $display("Monitor: Hogge Phase Test MPRJ-WB Started");
        wait(checkbits == 16'hab61);
        if(fail)
            $display("Monitor: Hogge Phase Test MPRJ-WB !! FAIL !!");
        else
            $display("Monitor: Hogge Phase Test MPRJ-WB pass");
        $finish;
    end

    initial begin
        RSTB <= 1'b0;
        #2000;
        RSTB <= 1'b1;
        #2000000;
        $finish;
    end

    initial begin
        power1 <= 1'b0;
        power2 <= 1'b0;
        power3 <= 1'b0;
        power4 <= 1'b0;
        #200;
        power1 <= 1'b1;
        power3 <= 1'b1;
        #200;
        power2 <= 1'b1;
        power4 <= 1'b1;
    end

    wire flash_csb;
    wire flash_clk;
    wire flash_io0;
    wire flash_io1;

    wire VDD3V3 = power1;
    wire VDD1V8 = power2;
    wire USER_VDD3V3 = power3;
    wire USER_VDD1V8 = power4;
    wire VSS = 1'b0;


    caravel uut (
        .vddio    (VDD3V3),
        .vssio    (VSS),
        .vdda     (VDD3V3),
        .vssa     (VSS),
        .vccd     (VDD1V8),
        .vssd     (VSS),
        .vdda1    (USER_VDD3V3),
        .vdda2    (USER_VDD3V3),
        .vssa1    (VSS),
        .vssa2    (VSS),
        .vccd1    (USER_VDD1V8),
        .vccd2    (USER_VDD1V8),
        .vssd1    (VSS),
        .vssd2    (VSS),
        .clock    (clk),
        .gpio     (gpio),
        .mprj_io  (mprj_io),
        .flash_csb(flash_csb),
        .flash_clk(flash_clk),
        .flash_io0(flash_io0),
        .flash_io1(flash_io1),
        .resetb   (RSTB)
    );

    spiflash #(
        .FILENAME("project.hex")
    ) spiflash (
        .csb(flash_csb),
        .clk(flash_clk),
        .io0(flash_io0),
        .io1(flash_io1),
        .io2(),            // not used
        .io3()            // not used
    );

endmodule
`default_nettype wire
