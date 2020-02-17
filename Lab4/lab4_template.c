/**
 * lab4_template.c
 *
 * Template file for CprE 288 lab 4
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 *
 * @author Phillip Jones, updated 6/4/2019
 */
#include <stdio.h>
#include "button.h"
#include "timer.h"
#include "lcd.h"

#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART1)
// PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1

#include "cyBot_Scan.h"  // For scan sensors


#warning "Possible unimplemented functions"
#define REPLACEME 0



int main(void) {
    button_init();
    timer_init(); // Must be called before lcd_init(), which uses timer functions
    lcd_init();

    // initialize the cyBot UART1 before trying to use it

    // (Uncomment ME for PuTTy to CyBot UART init part of lab)
    cyBot_uart_init_clean();  // Clean UART initialization, before running your UART GPIO init code

    // Complete this code for configuring the GPIO PORTB part of UART1 initialization (your UART GPIO init code)
    SYSCTL_RCGCGPIO_R |= 0x00000002;
    while ((SYSCTL_PRGPIO_R & 0x00000002) == 0) {};
    GPIO_PORTB_AFSEL_R |= 0x03;
    GPIO_PORTB_PCTL_R &= 0x00000011;     // Force 0's in the desired locations
    GPIO_PORTB_PCTL_R |= 0x00000011;     // Force 1's in the desired locations
    // Or see the notes for a coding alternative to assign a value to the PCTL field
    GPIO_PORTB_DEN_R |= 0xF;
    GPIO_PORTB_DIR_R &= 0b11111101;      // Force 0's in the desired locations
    GPIO_PORTB_DIR_R |= 0b00000010;      // Force 1's in the desired locations

    // (Uncomment ME for UART init part of lab)
    cyBot_uart_init_last_half();  // Complete the UART device configuration

    // Initialze scan sensors
    cyBOT_init_Scan();


    char rec;// YOUR CODE HERE
    cyBOT_Scan_t data;
    int a, x;
    char header[] = "Angle\tPING distance\tIR raw value\r\n";// 34
    char data_line[50];
    int header_length = 34;
    while(1)
    {
        rec = cyBot_getByte_blocking();

        if (rec == 'm')
        {

            for(x=0;x<header_length;x++){cyBot_sendByte(header[x]);}

            for (a=0;a<=180;a+=5)
            {
                cyBOT_Scan(a, &data);// YOUR CODE HERE

                sprintf(data_line, "%d\t%.2f\t\t%d\r\n", a,data.sound_dist, data.IR_raw_val);
                char* data_line_pos = data_line;
                while(*data_line_pos !='\0'){cyBot_sendByte(*data_line_pos++);}
            }
            lcd_printf("DONE");
        }

    }

}
