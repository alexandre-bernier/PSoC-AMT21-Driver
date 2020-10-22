# PSoC-AMT21-Driver
Self-contained implementation of CUI Devices' encoder AMT21 Series for PSoC.

# Requirements
## Transceiver
The AMT21 encoder communicates via RS485 which isn't supported by PSoC. You need to connect a transceiver inbetween the PSoC and the encoder to convert the RS485 signal into UART. CUI Devices suggest using Texas Instruments SN65HVD75 (for data rate at 2Mbps) or SN65HVD72 (for adjustable data rate). See datasheet page 3 and 5 to know which one you have.

## Load resistance
If you have a long cable between the PSoC and the encoder, make sure to have a load resistance (CUI Devices suggest 54Ω) at both end of the cable.

# Compatibility
This project has been tested on the following hardware:
* PSoC 5LP (CY8C5888LTI-LP097)
* CUI Devices AMT212C-V

# References
AMT21 Series encoder product page: https://www.cuidevices.com/product/motion/rotary-encoders/absolute/modular/amt21-series

AMT21 Series encoder datasheet: https://www.cuidevices.com/product/resource/amt21.pdf.

# Example (main.c)
The following code shows how to read the absolute position and the number of turns of the encoder.

    #include <project.h>
    #include "amt21_driver.h"
    
    int main(void)
    {
        uint16 absolute_position = 0;
        int16 number_of_turns = 0
        
        // Initializations
        CyGlobalIntEnable;  // Enable global interrupts
        amt21_init();       // Start and setup the AMT21 driver
        
        // Application
        for(;;) {
            // Get absolute position
            absolute_position = amt21_get_pos();
            
            // Get number of turns
            number_of_turns = amt21_get_turns();
        }
    }

# Setup
## TopDesign
Add the following components:
* 1 x UART (named 'UART_AMT21')
* 1 x Digital Input Pin connected to UART/rx
* 1 x Digital Ouptut Pin connected to UART/tx
* 1 x Digital Ouptut Pin connected to UART/tx_en
* 1 x Logic Low '0' connected to UART/reset

If you have an encoder with a 2Mbsp data rate, you'll also need the following:
* 1 x Clock (set at 32Mhz) connected to UART/clock (this pin will appear once you select "External clock" in UART component configuration, see below)

## UART component configuration
Configure tab:
* Mode = "Full UART (TX + RX)"
* Bits per second = see Datasheet page 5 (ignore if data rate is 2Mbps)
* Data bits = "8"
* Parity type = "None"
* Stop bits = "1"
* Flow control = "None"

Advanced tab:
* Clock selection = "External clock" if data rate is 2Mbsp, "Internal clock" otherwise
* RS-485 Configuration options = "Hardware TX-Enable" ticked
* Oversampling rate = "16x"

## Clocks configurations (.cydwr)
If data rate is 2Mbps:
* PLL = 64MHz (or a multiple of 32MHz)

## Macros (see amt21_driver.h)
* AMT21_RESOLUTION = Resolution of your encoder as per its part number (see datasheet, page 5)
* AMT21_NODE_ADDR = RS485 node address of your encoder (see datasheet, page 3)
* AMT21_SINGLE_TURN = Uncomment if your encoder is single-turn (see datasheet, page 5)
