/* 
 * File:   app.h
 * Author: osama reda
 *
 * Created on September 11, 2023, 11:21 PM
 */

#ifndef APP_H
#define	APP_H

/*-----------------------includes-------------------------*/
#include"ECUAL/ecual_init.h"
#include "MCAL/INTERRUPT/mcal_external_interrupt.h"

/*----------------macros declaration-----------------*/
//frequency
#define _XTAL_FREQ          8000000
//modes
#define CARS_MODE           0
#define WHEN_GREEN_ON       1
#define WHEN_YELLOW_BLINK   2

/*----------------function declaration-----------------*/
void app_init(void);
void APP_INT_ISR(void);
void cars_mode_yellow_leds_toggle(void);
void yellow_leds_toggle(void);
void stop_sign(void);
void move_sign(void);
void wait_sign(void);
void pedestrian_red_traffic_counter(uint8 time);
void pedestrian_green_traffic_counter(uint8 time);
void action_one(void);
void action_two(void);
void harry_up_sign(void);
void modes_checker(void);
#endif	/* APP_H */