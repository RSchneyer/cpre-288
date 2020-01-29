/**
* @file main.c
* @brief Code for Lab 01 of CPRE 288. Displays the text "Microcontrollers are lots of fun!"
* on the first line of the Cybot's LCD display, and scrolls it to the left every 300ms.
*
* @author Reid Schneyer & Brandon Cortez
* @date 1/28/2020
*/

#include <string.h>
#include "lib/Timer.h"
#include "lib/lcd.h"

int main(void){
    char str[ ] = "                    Microcontrollers are lots of fun!";
    char disp[21];
    int i, j, x;
    int str_len = 54;
    int disp_len = 20;
    int LOOP_COUNT = 5l
    int WAIT_TIME_MILLIS = 300;
    timer_init();
    lcd_init();

    for(x=0; x<LOOP_COUNT; x++){
	for(i=0; i<str_len; i++){
	    str[str_len] = str[0];
	    for(j=0; j<str_len; j++){
		str[j] = str[j+1];
	    }
	    str[str_len] = '\0';
	    strncpy(disp, str, disp_len);
	    disp[disp_len] = '\0';

	    lcd_printf(disp);
	    timer_waitMillis(WAIT_TIME_MILLIS);
	}
    }
    return 0;
}
