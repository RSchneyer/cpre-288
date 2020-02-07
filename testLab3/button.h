/*
 * button.h
 *
 *  Created on: Jul 18, 2016
 *      Author: Eric Middleton
 *
 * @edit: Phillip Jones 05/30/2019 : Removed uneeded helper functions
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <stdint.h>
#include <inc/tm4c123gh6pm.h>

//initialize the push buttons
void button_init();


///Non-blocking call
///Returns highest value button being pressed, 0 if no button pressed
uint8_t button_getButton();

void button_set_out();
void button_LED_control();
void LED_set();

#endif /* BUTTON_H_ */
