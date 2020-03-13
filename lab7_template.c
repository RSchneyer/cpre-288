/**
 * lab6_template.c
 *
 * Template file for CprE 288 lab 6
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
#include "ping.h"


#define REPLACEME 0



int main(void) {
    button_init();
    timer_init(); // Must be called before lcd_init(), which uses timer functions
    lcd_init();

    float distance;
    ping_init();
    while (true) {
        distance = ping_getDistance();
        lcd_printf("%.2f", distance);
        timer_waitMillis(500);
    }
}
