/*
 * movement.c
 *
 *  Created on: Jan 31, 2020
 *      Author: brcortez
 */
#include "lcd.h"
#include "open_interface.h"

#define ANGLE_MOD 15
#define BUMP_BACKTRACK_MM 150
#define BUMP_SIDESTEP_MM 250

void move_forward_smart(oi_t *sensor_data, double distance_mm, int move_speed){
    double linear_dist_moved_mm = 0;
    int r_bump_status = 0;
    int l_bump_status = 0;
    while(linear_dist_moved_mm < distance_mm){
        oi_setWheels(move_speed, move_speed);
        r_bump_status = sensor_data -> bumpRight;
        l_bump_status = sensor_data -> bumpLeft;
        while((l_bump_status == 0) && (r_bump_status == 0))
        {
            oi_update(sensor_data);
            linear_dist_moved_mm += sensor_data -> distance;
            r_bump_status = sensor_data -> bumpRight;
            l_bump_status = sensor_data -> bumpLeft;
        }
        if(l_bump_status != 0){//left bumper triggered
            oi_setWheels(0,0); //stop
            move_forward(sensor_data, BUMP_BACKTRACK_MM, -125);
            linear_dist_moved_mm -= BUMP_BACKTRACK_MM;
            turn_right(sensor_data, 90);
            move_forward(sensor_data, BUMP_SIDESTEP_MM, 125);
            turn_left(sensor_data, 90);
        }
        if(r_bump_status != 0){//right bumper triggered
            oi_setWheels(0,0); //stop
            move_forward(sensor_data, BUMP_BACKTRACK_MM, -125);
            linear_dist_moved_mm -= BUMP_BACKTRACK_MM;
            turn_left(sensor_data, 90);
            move_forward(sensor_data, BUMP_SIDESTEP_MM, 125);
            turn_right(sensor_data, 90);
        }

    }
    oi_setWheels(0,0);
}
//void move_forward_smart(oi_t *sensor_data, double distance_mm, int move_speed){
//    oi_setWheels(250, 250);
//    oi_update(sensor_data);
//    while((sensor_data ->bumpLeft == 0) && (sensor_data -> bumpRight == 0)){
//        oi_update(sensor_data);
//    }
//    oi_setWheels(0,0);
//}

double move_forward(oi_t *sensor_data, double distance_mm, int moveSpeed)
{
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(moveSpeed,moveSpeed); //move forward at speed
    while (sum < distance_mm)
    {
        oi_update(sensor_data);
        sum += sensor_data -> distance; // use -> notation since pointer

    }
    lcd_printf("%f", &sum);
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
    lcd_printf("%f", &currAngle);
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
    lcd_printf("%f", &currAngle);
    oi_setWheels(0,0);
}


