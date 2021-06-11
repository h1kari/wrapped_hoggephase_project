/*
 * SPDX-FileCopyrightText: 2020 Efabless Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "verilog/dv/caravel/defs.h"
#include "verilog/dv/caravel/stub.c"

/*
	IO Test:
		- Configures MPRJ lower 8-IO pins as outputs
		- Observes counter value through the MPRJ lower 8 IO pins (in the testbench)
*/

// design ID
#define ID                      13

// offset we shift our gpio to put on LA bus
#define LA_OFF                  4
#define HP_VCC_OFF              0
#define HP_ALARM_RST_OFF        1
#define HP_ALARM_CTR_RST_OFF    2
#define HP_GLITCH_EN_OFF        3
#define HP_ALARM_OFF            4
#define HP_ALARM_LATCH_OFF      5
#define HP_ALARM_CTR_OFF        6
#define HP_DESIGN_SEL_OFF       14

// offsets of register bits on LA bus
#define LA_HP_RESET_OFF         1
#define LA_HP_VCC_OFF           (LA_OFF+HP_VCC_OFF)
#define LA_HP_ALARM_RST_OFF     (LA_OFF+HP_ALARM_RST_OFF)
#define LA_HP_ALARM_CTR_RST_OFF (LA_OFF+HP_ALARM_CTR_RST_OFF)
#define LA_HP_GLITCH_EN_OFF     (LA_OFF+HP_GLITCH_EN_OFF)
#define LA_HP_ALARM_OFF         (LA_OFF+HP_ALARM_OFF)
#define LA_HP_ALARM_LATCH_OFF   (LA_OFF+HP_ALARM_LATCH_OFF)
#define LA_HP_ALARM_CTR_OFF     (LA_OFF+HP_ALARM_CTR_OFF)
#define LA_HP_DESIGN_SEL_OFF    (LA_OFF+HP_DESIGN_SEL_OFF)

// bit masks we can use for set/clear on WB bus
#define HP_VCC                  (1<<HP_VCC_OFF)
#define HP_ALARM_RST            (1<<HP_ALARM_RST_OFF)
#define HP_ALARM_CTR_RST        (1<<HP_ALARM_CTR_RST_OFF)
#define HP_GLITCH_EN            (1<<HP_GLITCH_EN_OFF)
#define HP_DESIGN_SEL           (3<<HP_DESIGN_SEL_OFF)

// bit masks we can use for set/clear on LA bus
#define LA_HP_RESET             (1<<LA_HP_RESET_OFF)
#define LA_HP_VCC               (1<<LA_HP_VCC_OFF)
#define LA_HP_ALARM_RST         (1<<LA_HP_ALARM_RST_OFF)
#define LA_HP_ALARM_CTR_RST     (1<<LA_HP_ALARM_CTR_RST_OFF)
#define LA_HP_GLITCH_EN         (1<<LA_HP_GLITCH_EN_OFF)
#define LA_HP_DESIGN_SEL        (3<<LA_HP_DESIGN_SEL_OFF)

// macros for parsing values from register on WB bus
#define HP_ALARM(x)             (((x) >> (HP_ALARM_OFF))       & 1)
#define HP_ALARM_LATCH(x)       (((x) >> (HP_ALARM_LATCH_OFF)) & 1)
#define HP_ALARM_CTR(x)         (((x) >> (HP_ALARM_CTR_OFF))   & 0xff)

// macros for parsing values from register on LA bus
#define LA_HP_ALARM(x)          (((x) >> (LA_HP_ALARM_OFF))       & 1)
#define LA_HP_ALARM_LATCH(x)    (((x) >> (LA_HP_ALARM_LATCH_OFF)) & 1)
#define LA_HP_ALARM_CTR(x)      (((x) >> (LA_HP_ALARM_CTR_OFF))   & 0xff)

// failure bits to decode what went wrong
#define FAIL_LA_HP_INIT          0x1
#define FAIL_LA_HP_GLITCH_EN     0x2
#define FAIL_LA_HP_ALARM_RST     0x4
#define FAIL_LA_HP_ALARM_CTR_RST 0x8
#define FAIL_WB_HP_INIT          0x10
#define FAIL_WB_HP_GLITCH_EN     0x20
#define FAIL_WB_HP_ALARM_RST     0x40
#define FAIL_WB_HP_ALARM_CTR_RST 0x80

void main()
{
    reg_mprj_io_31 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_30 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_29 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_28 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_27 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_26 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_25 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_24 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_23 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_22 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_21 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_20 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_19 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_18 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_17 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_16 = GPIO_MODE_MGMT_STD_OUTPUT;

    reg_mprj_io_15 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_14 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_13 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_12 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_11 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_10 = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_9  = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_8  = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_7  = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_5  = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_4  = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_3  = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_2  = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_1  = GPIO_MODE_USER_STD_OUTPUT;
    reg_mprj_io_0  = GPIO_MODE_USER_STD_OUTPUT;

    // 1 input for input signal
    reg_mprj_io_8 =   GPIO_MODE_USER_STD_INPUT_NOPULL;

    // 1 output for segments, starting at 9
    reg_mprj_io_9 =   GPIO_MODE_USER_STD_OUTPUT;

    /* Apply configuration */
    reg_mprj_xfer = 1;
    while (reg_mprj_xfer == 1);

    // activate the project by setting the 1st bit of 2nd bank of LA - depends on the project ID
    reg_la1_iena = 0; // input enable off
    reg_la1_oenb = 0; // output enable on
    reg_la1_data = 1 << ID;

    // Flag start of the test
    reg_mprj_datal = 0xAB600000;

    // Configure LA[64] LA[65] as outputs from the cpu
    reg_la0_iena = reg_la0_oenb = 0xFFF3FF00;


    int fail = 0;


    /************************
     * START LA TESTS       *
     ************************/

    // set design sel to test both p & n cores
    unsigned long reg_la0_data_val = 0 | LA_HP_DESIGN_SEL;
    reg_la0_data = reg_la0_data_val;

    // turn on core by holding resets while turning on VCC/enable, then release resets
    reg_la0_data_val |= LA_HP_ALARM_RST | LA_HP_ALARM_CTR_RST;
    reg_la0_data = reg_la0_data_val;
    reg_la0_data_val |= LA_HP_VCC;
    reg_la0_data = reg_la0_data_val;
    reg_la0_data_val &= ~(LA_HP_ALARM_RST | LA_HP_ALARM_CTR_RST);
    reg_la0_data = reg_la0_data_val;

    // should be at 0 glitches upon boot up
    if(LA_HP_ALARM_CTR(reg_la0_data) != 0)
        fail |= FAIL_LA_HP_INIT;

    // inject glitches
    reg_la0_data_val |= LA_HP_GLITCH_EN;
    reg_la0_data = reg_la0_data_val;
    reg_la0_data = reg_la0_data_val;
    reg_la0_data = reg_la0_data_val;
    reg_la0_data_val &= ~(LA_HP_GLITCH_EN);
    reg_la0_data = reg_la0_data_val;

    // glitch count should have increased!
    if(LA_HP_ALARM_CTR(reg_la0_data) == 0)
        fail |= FAIL_LA_HP_GLITCH_EN;

    // toggle CTR rst and test
    reg_la0_data_val |= LA_HP_ALARM_CTR_RST;
    reg_la0_data = reg_la0_data_val;
    reg_la0_data_val &= ~(LA_HP_ALARM_CTR_RST);
    reg_la0_data = reg_la0_data_val;

    // now glitch count should be zero after reset
    if(LA_HP_ALARM_CTR(reg_la0_data) != 0)
        fail |= FAIL_LA_HP_ALARM_CTR_RST;

    // glitch latch should be high!
    if(LA_HP_ALARM_LATCH(reg_la0_data) == 0)
        fail |= FAIL_LA_HP_GLITCH_EN;

    // toggle latch rst and test
    reg_la0_data_val |= LA_HP_ALARM_RST;
    reg_la0_data = reg_la0_data_val;
    reg_la0_data_val &= ~(LA_HP_ALARM_RST);
    reg_la0_data = reg_la0_data_val;

    // glitch latch should be reset
    if(LA_HP_ALARM_LATCH(reg_la0_data) != 0)
        fail |= FAIL_LA_HP_ALARM_RST;

    // reset LA bus to do clean test of WB
    reg_la0_data_val = 0 | LA_HP_DESIGN_SEL | LA_HP_RESET;
    reg_la0_data = reg_la0_data_val;
    reg_la0_data_val = 0;
    reg_la0_data = reg_la0_data_val;


    /************************
     * START WISHBONE TESTS *
     ************************/

    // set design sel to test both p & n cores
    reg_mprj_slave = HP_DESIGN_SEL;

    // turn on core by holding resets while turning on VCC/enable, then release resets
    reg_mprj_slave |= HP_ALARM_RST | HP_ALARM_CTR_RST;
    reg_mprj_slave |= HP_VCC;
    reg_mprj_slave &= ~(HP_ALARM_RST | HP_ALARM_CTR_RST);

    // should be at 0 glitches upon boot up
    if(HP_ALARM_CTR(reg_mprj_slave) != 0)
        fail |= FAIL_WB_HP_INIT;

    // inject glitches
    reg_mprj_slave |= HP_GLITCH_EN;
    reg_mprj_slave |= HP_GLITCH_EN;
    reg_mprj_slave |= HP_GLITCH_EN;
    reg_mprj_slave &= ~(HP_GLITCH_EN);

    // glitch count should have increased!
    if(HP_ALARM_CTR(reg_mprj_slave) == 0)
        fail |= FAIL_WB_HP_GLITCH_EN;

    // toggle CTR rst and test
    reg_mprj_slave |= HP_ALARM_CTR_RST;
    reg_mprj_slave &= ~(HP_ALARM_CTR_RST);

    // now glitch count should be zero after reset
    if(HP_ALARM_CTR(reg_mprj_slave) != 0)
        fail |= FAIL_WB_HP_ALARM_CTR_RST;

    // glitch latch should be high!
    if(HP_ALARM_LATCH(reg_mprj_slave) == 0)
        fail |= FAIL_WB_HP_GLITCH_EN;

    // toggle latch rst and test
    reg_mprj_slave |= HP_ALARM_RST;
    reg_mprj_slave &= ~(HP_ALARM_RST);

    // glitch latch should be reset
    if(HP_ALARM_LATCH(reg_mprj_slave) != 0)
        fail |= FAIL_WB_HP_ALARM_RST;

    // flag end of test
    reg_mprj_datal = 0xAB610000 | fail;
}

