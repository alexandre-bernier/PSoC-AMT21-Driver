/*******************************************************************************
*
* CUI AMT21XX-V Encoder driver for PSoC
* Copyright (C) 2020, Alexandre Bernier
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in the
* documentation and/or other materials provided with the distribution.
*
* 3. Neither the name of the copyright holder nor the names of its contributors
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
********************************************************************************
*
* Summary:
*  Handles communication with the CUI AMT21 series encoder.
*  You are required to convert the RS-485 (encoder) to UART (PSoC).
*
* Required components in TopDesign:
*  1 x UART (named 'UART_AMT21')
*  1 x Digital Input Pin connected to UART_AMT21/rx
*  1 x Digital Output Pin connected to UART_AMT21/tx
*  1 x Digital Output Pin connected to UART_AMT21/tx_en
*
*  If Data Rate = 2Mbps (see datasheet, page 5)
*    1 x Clock (set at 32MHz) connected to UART_AMT21/clock
*
* Configuration of component UART_enc (TopDesign):
*  Configure tab
*    Mode            = "Full UART (TX + RX)"
*    Bits per second = Data rate of your encoder (see datasheet, page 5)
*    Data bits       = "8"
*    Parity type     = "None"
*    Stops bits      = "1"
*    Flow control    = "None"
*
*  Advanced tab
*    RS-485 Configuration options = "Harware TX-Enable" ticked
*    Oversampling rate            = "16x"
*
*    If Data Rate = 2Mbps (see datasheet, page 5)
*      Clock selection            = "External clock"
*	 Otherwise
*	   Clock selection			  = "Internal clock"
*
* Clocks configurations (.cydwr):
*  If Data Rate = 2Mbps (see datasheet, page 5)
*    PLL = 64MHz (or a multiple of 32MHz)
*
* Macros (see below):
*  AMT21_RESOLUTION  = Resolution of your encoder as per its part number
*                      (see datasheet, page 5)
*  AMT21_NODE_ADDR   = RS485 node address of your encoder
*                      (see datasheet, page 3)
*  AMT21_SINGLE_TURN = Uncomment if your encoder is single-turn
*                      (see datasheet, page 5)
*
* References:
*  https://www.cuidevices.com/product/motion/rotary-encoders/absolute/modular/amt21-series
*
********************************************************************************
*
* Revisions:
*  1.0: First.
*
*******************************************************************************/

#ifndef _AMT21_DRIVER_H
#define _AMT21_DRIVER_H
    
#include <project.h>
#include <sys/param.h>
#include <stdbool.h>

/*******************************************************************************
* MACROS
*******************************************************************************/
// Characteristics
#define AMT21_RESOLUTION (12u)  // 12-bit or 14-bit (see datasheet, page 5)
#define AMT21_NODE_ADDR (0x54u) // Default is 0x54
//#define AMT21_SINGLE_TURN   // Uncomment if single-turn (see datasheet, page 5)


/*******************************************************************************
* PUBLIC PROTOTYPES
*******************************************************************************/
// Init
void amt21_init();

// Read commands
uint16 amt21_get_pos();
int16 amt21_get_turns();

// Write commands
void amt21_reset_enc();

#ifdef AMT21_SINGLE_TURN
void amt21_set_zero_pos();
#endif

#endif // _AMT21_DRIVER_H
/* [] END OF FILE */
