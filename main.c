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
    uint8_t digit_data[BUFFERS][NUMBER_OF_DIGITS] = {
        {S7_DEG + S7_COLON, S7_DP + S7_A, S7_DP + S7_C, S7_E + S7_DP, S7_DP + S7_FIVE},
        {S7_DEG + S7_COLON, S7_DP + S7_A, S7_DP + S7_C, S7_E + S7_DP, S7_DP + S7_FIVE}
    };
    uint8_t digit_index = 0;
    State_t data_state = _W;
    uint8_t temp = 0;
    bool current_buffer = 0;
    uint32_t count = 0;

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
            setDisplay(&digit_index, &digit_data[current_buffer][digit_index]);
            digit_index++;
            if (digit_index == NUMBER_OF_DIGITS) digit_index = 0;
            count++;
            if (count == 1000) {
                count = 0;
                EUSART_Write('X');
            }
        }
        if (EUSART_DataReady) {
            while (EUSART_DataReady) {
                temp = EUSART_Read();
                switch (data_state) {
                    case _W:
                        if (temp == data_state) data_state = _D0;
                        break;
                    case _D0:
                        digit_data[!current_buffer][data_state] = temp;
                        data_state = _D1;
                        break;
                    case _D1:
                        digit_data[!current_buffer][data_state] = temp;
                        data_state = _D2;
                        break;
                    case _D2:
                        digit_data[!current_buffer][data_state] = temp;
                        data_state = _D3;
                        break;
                    case _D3:
                        digit_data[!current_buffer][data_state] = temp;
                        data_state = _D4;
                        break;
                    case _D4:
                        digit_data[!current_buffer][data_state] = temp;
                        data_state = _w;
                        break;
                    case _w:
                        if (temp == data_state) {
                            data_state = _W;
                            current_buffer = !current_buffer;
                        }
                    default:
                        break;
                }
                temp = 0;
            }
        }
    }
}

void setDisplay(uint8_t *digit, uint8_t *value) {

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