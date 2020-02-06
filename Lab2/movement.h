/*
 * movement.h
 *
 *  Created on: Jan 31, 2020
 *      Author: brcortez
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

void move_forward_smart(oi_t *sensor_data, double distance_mm, int move_speed);

double move_forward(oi_t *sensor_data, double distance_mm, int moveSpeed);

double move_backward(oi_t *sensor_data, double distance_mm, int moveSpeed);


void turn_right(oi_t *sensor_data, double degrees);

void turn_left(oi_t *sensor_data, double degrees);




#endif /* MOVEMENT_H_ */
