/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB® Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC16F1938
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X v2.35 or v3.00
 */

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

#include "mcc_generated_files/mcc.h"
#include "main.h"

//global values

volatile ISR_Flags_t Flags;

/*
   Main application
 */
void main(void) {
    // initialize the device
    SYSTEM_Initialize();
    uint8_t digit_data[NUMBER_OF_DIGITS] = {S7_DEG + S7_COLON, S7_DP + S7_A, S7_DP + S7_C, S7_E + S7_DP, S7_DP + S7_FIVE};
    uint8_t digit_index = 0;
    //DIGIT1 = 1;
    //SEGMENTS = SEG_DATA[0xA] + S7_DP;

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1) {
        // Add your application code
        NOP();
        if (Flags.NewTick_ms) {
            Flags.NewTick_ms = FALSE;
            setDisplay(&digit_index, &digit_data[digit_index]);
            digit_index++;
            if(digit_index == NUMBER_OF_DIGITS) digit_index = 0;
        }

    }
}

void setDisplay(uint8_t *digit, uint8_t *value) {
    //First, get the segment values from eeprom
    //unsigned char segments = *value;
    //unsigned char charIndex = 0;
    //Get the correct nibble from the data using the digit
    //0xWXYZ => {0x000W, 0x00WX, 0x0WXY, 0xWXYZ} Shift by 4 x '4-digit'
    //       => {0x000W, 0x000X, 0x000Y, 0x000Z} Mask off what we don't want
    //charIndex = (unsigned char) ((*data >> 4 * (4 - *digit))&(0x000f));
    //segments = SEG_DATA[charIndex]; //eeprom_read(char_index);

    //Turn off the display before changing digits
    DIGITS &= DIGITS_OFF;

    //Set the segments to display
    SEGMENTS = *value;

    //Turn on the appropriate digit
    switch (*digit) {
        case 0:
            DIGIT0 = 1;
            break;
        case 1:
            DIGIT1 = 1;
            break;
        case 2:
            DIGIT2 = 1;
            break;
        case 3:
            DIGIT3 = 1;
            break;
        case 4:
            DIGIT4 = 1;
            break;
        default:
            break;
    }
    return;
}
/**
 End of File
 */