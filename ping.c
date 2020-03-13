#include "timer.h"
#include "driverlib/interrupt.h"

void ping_init() {
    SYSCTL_RCGCGPIO_R |= 0x2;
    while ((SYSCTL_PRGPIO_R & 0x2) ==0) {}
    GPIO_PORTB_DIR_R |= 0x08;
    GPIO_PORTB_DEN_R |= 0x08;

    GPIO_PORTB_PCTL_R |= 0x00007000;
    SYSCTL_RCGCTIMER_R |= 0x08;
    while ((SYSCTL_PRTIMER_R & 0x8) ==0) {}
    TIMER3_CTL_R &= ~0x0100;
    TIMER3_CFG_R = 0x4;
    TIMER3_TBMR_R |= 0x0007;
    TIMER3_TBMR_R &= ~0x0010;
    TIMER3_CTL_R |= 0x0C00;
    TIMER3_TBPR_R |= 0xFF;
    TIMER3_TBILR_R |= 0xFFFF;
    TIMER3_IMR_R |= 0x0400;
    TIMER3_CTL_R |= 0x0100;
}


void ping_trigger() {
    GPIO_PORTB_DATA_R &= ~0x08;
    GPIO_PORTB_DATA_R |= 0x08;
    timer_waitMicros(5);
    GPIO_PORTB_DATA_R &= ~0x08;

}


float ping_getDistance() { //Assuming PB3 is in output mode at start
    float dist;
    ping_outMode();
    ping_trigger();

    TIMER3_ICR_R = 0x0400; //TODO

    ping_toggle();

    return dist;
}


void ping_toggle() {
    if (GPIO_PORTB_DIR_R & 0x08) {
        GPIO_PORTB_DIR_R &= ~0x08;
        GPIO_PORTB_AFSEL_R |= 0x08;
    }
    else {
        ping_outMode();
    }
}


void ping_outMode() {
    GPIO_PORTB_DIR_R |= 0x08;
    GPIO_PORTB_AFSEL_R &= ~0x08;
}
