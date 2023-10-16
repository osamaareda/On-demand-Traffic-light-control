/* 
 * File:   ecual_init.h
 * Author: osama reda
 *
 * Created on September 27, 2023, 9:22 PM
 */

#ifndef ECUAL_INIT_H
#define	ECUAL_INIT_H
/*-------------------includes---------------------*/
#include "LED/led.h"
#include "7_SEGMENT/seven_segment.h"
#include "LCD/lcd.h"

/*--------------function declaration--------------*/
void ecual_init(void);

/*--------------------externs---------------------*/
extern led_config_t car_led_red;
extern led_config_t car_led_yellow;
extern led_config_t car_led_green;
extern led_config_t pedestrian_led_red;
extern led_config_t pedestrian_led_yellow;
extern led_config_t pedestrian_led_green;
extern seven_segment_config_t seg_green;
extern seven_segment_config_t seg_red;
extern lcd_config_t lcd;
#endif	/* ECUAL_INIT_H */