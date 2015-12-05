//Defines
//The digits are the pins for each segment char
#define DIGITS PORTB
//Mask with 1110 0000 (0xE0) to turn off
#define DIGITS_OFF 0xE0
#define DIGIT0 RB4
#define DIGIT1 RB3
#define DIGIT2 RB2
#define DIGIT3 RB1
#define DIGIT4 RB0
// RB5 is unused
// PGC is RB6
// PGD is RB7
//These are the maps to the pins
#define SEGMENTS PORTA
#define SEGMENT_A RA0 //To Pin 14
#define SEGMENT_B RA1 //To Pin 16
#define SEGMENT_C RA2 //To Pin 13
#define SEGMENT_D RA3 //To Pin 3
#define SEGMENT_E RA4 //To Pin 5
#define SEGMENT_P RA5 //To Pin 7
#define SEGMENT_F RA6 //To Pin 11
#define SEGMENT_G RA7 //To Pin 15

//values for the 7Seg display
//                            RA : 76543210
// AAA      L3  000      0 |>  0 = 01011111 = 5f
//F   B	       6   1	   |>  1 = 00000110 = 06
//F   B	 L1    6   1   1   |>  2 = 10011011 = 9b
//F   B	       6   1	   |>  3 = 10001111 = 8f
// GGG	        777        |>  4 = 11000110 = c6
//E   C	       4   2	   |>  5 = 11001101 = cd
//E   C	 L2    4   2   2   |>  6 = 11011101 = dd
//E   C	       4   2	   |>  7 = 01000111 = 47
// DDD  P       333  5     |>  8 = 11011111 = df
//				           |>  9 = 11001111 = cf
//				           |>  A = 11010111 = d7
//				           |>  B = 11011100 = dc
//				           |>  C = 01011001 = 59
//				           |>  D = 10011110 = 9e
//                         |>  E = 11011001 = d9
//				           |>  F = 11010001 = d1
//				           |>  . = 00100000 = 20
//				           |>  : = xxxxx011 = 03
//				           |>  ' = xxxxx100 = 04
//
//Display values from 0-F; RA5 is not useable

#define S7_DP		0x20	//Add this to get the decimal point
#define S7_DEG		0x04	//Only valid for DIGIT0
#define S7_COLON	0x03    //Only valid for DIGIT0
#define S7_ZERO     0x5f
#define S7_ONE      0x06
#define S7_TWO      0x9b
#define S7_THREE    0x8f
#define S7_FOUR     0xc6
#define S7_FIVE     0xcd
#define S7_SIX      0xdd
#define S7_SEVEN    0x47
#define S7_EIGHT    0xdf
#define S7_NINE     0xcf
#define S7_A        0xd7
#define S7_B        0xdc
#define S7_C        0x59
#define S7_D        0x9e
#define S7_E        0xd9
#define S7_F        0xd1

//init defines
#define INIT_OSCCON 0x70    //sets internal clock to 8MHz
#define INIT_ADCON1 0x06
#define INIT_TRISA	0x00	//Set all of Port A to output, RA5 is ignored
#define INIT_TRISB	0x12	//RB0,2,3,5 are output; Pins 1,4 are input for I2C; Pins 6,7 for ICSP
#define INIT_T1CON  0x00    //Default setting for T1CON
#define INIT_TMR1L_25ms 0xAF    //This sets the Timer1 count to count 50000
#define INIT_TMR1H_25ms 0x3C    //For an interupt every 25ms
#define INIT_TMR1L_4ms  0xE0    //This sets the Timer1 count to count 8000
#define INIT_TMR1H_4ms  0xBF    //For an interupt every 4ms
#define INIT_TMR1L_1ms  0x2F    //Count 2000 for 1ms interupt
#define INIT_TMR1H_1ms  0xF8
#define INIT_TMR1L_Debug    0xF0
#define INIT_TMR1H_Debug    0xFF
#define INIT_SSPCON_SSPM    0xE

//other defines
#define TRUE 1
#define FALSE 0
#define NUMBER_OF_SEGMENTS 5

//functions
void setDisplay(unsigned char *digit, unsigned int *value);