/*
 * movement.c
 *
 *  Created on: Jan 31, 2020
 *      Author: brcortez
 */
#include <string.h>
#include "Timer.h"
#include "lcd.h"
#include "open_interface.h"

#define ANGLE_MOD 15
#define BUMP_BACKTRACK_MM 150
#define BUMP_SIDESTEP_MM 250

void move_forward_smart(oi_t *sensor_data, double distance_mm, int move_speed)
{
    double dist_moved_mm = 0;
    int r_bump_status = 0;
    int l_bump_status = 0;
    oi_setWheels(move_speed, move_speed);

    while(dist_moved_mm < distance_mm)
    {
        oi_update(sensor_data); //update sensor data
        dist_moved_mm += sensor_data -> distance; //update distance value
        r_bump_status = sensor_data -> bumpRight; //update the value of the right bump sensor
        l_bump_status = sensor_data -> bumpLeft; //update the value of the left bump sensor
        lcd_printf("%f", &dist_moved_mm); // displays distance covered on LCD screen

        if(r_bump_status == 0) //left bumper triggered
        {
            oi_setWheels(0,0); //stop
            move_forward(sensor_data, BUMP_BACKTRACK_MM, -125); //backup after hitting obstacle
            dist_moved_mm += BUMP_BACKTRACK_MM; //add distance backed up to total distance covered

            turn_right(sensor_data, 90); //turn to the right away from the obstacle
            move_forward(sensor_data, BUMP_SIDESTEP_MM, 125); //move in the opposite direction of the obstacle
            dist_moved_mm += BUMP_SIDESTEP_MM; //add distance moved to total distance covered

            turn_left(sensor_data, 90); //turn back to face original direction
            oi_setWheels(move_speed, move_speed); //resume
        }
        if(l_bump_status == 0) //right bumper triggered
        {
            oi_setWheels(0,0); //stop
            move_forward(sensor_data, BUMP_BACKTRACK_MM, -125); //backup after hitting obstacle
            dist_moved_mm += BUMP_BACKTRACK_MM; //add distance backed up to total distance covered

            turn_left(sensor_data, 90); //turn to the left away from the obstacle
            move_forward(sensor_data, BUMP_SIDESTEP_MM, 125); //move in the opposite direction of the obstacle
            dist_moved_mm += BUMP_SIDESTEP_MM; //add distance moved to total distance covered

            turn_right(sensor_data, 90); //turn back to face original direction
            oi_setWheels(move_speed, move_speed); //resume
        }

    }
    oi_setWheels(0,0); //stop
}

double move_forward(oi_t *sensor_data, double distance_mm, int moveSpeed)
{
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(moveSpeed,moveSpeed); //move forward at speed
    while (sum < distance_mm)
    {
        oi_update(sensor_data);
        sum += sensor_data -> distance; // use -> notation since pointer

    }
    //lcd_printf("%f", &sum);
    oi_setWheels(0,0); //stop

    return sum;
}

void turn_right(oi_t *sensor_data, double degrees){
    degrees -= ANGLE_MOD;
    double currAngle = 0;
    oi_setWheels(-250, 250);
    while(currAngle < degrees){
        oi_update(sensor_data);
        currAngle -= sensor_data -> angle;
    }
    //lcd_printf("%f", &currAngle);
    oi_setWheels(0,0);
}

void turn_left(oi_t *sensor_data, double degrees){
    degrees -= ANGLE_MOD;
    double currAngle = 0;
    oi_setWheels(250, -250);

    while(currAngle<degrees){
        oi_update(sensor_data);
        currAngle += sensor_data -> angle;
    }
    //lcd_printf("%f", &currAngle);
    oi_setWheels(0,0);
}
