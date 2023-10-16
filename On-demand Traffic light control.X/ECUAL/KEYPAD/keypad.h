/* 
 * File:   keypad.h
 * Author: osama reda
 *
 * Created on September 27, 2023, 6:50 PM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

/*-----------------------includes-------------------------*/
#include"../../MCAL/GPIO/gpio.h"
#include"ecual_keypad_cfg.h"

/*----------------macros declaration-----------------*/
#define KEYPAD_ROWS     4
#define KEYPAD_COLUMNS  4

/*---------------data type declaration---------------*/
typedef struct{
    pin_config_t keypad_rows_pins[KEYPAD_ROWS];       /* @ref  pin_config_t */
    pin_config_t keypad_columns_pins[KEYPAD_COLUMNS]; /* @ref  led_status_t */
}keypad_config_t;

/*----------------function declaration-----------------*/
Std_ReturnType keypad_init(keypad_config_t *keypad);
Std_ReturnType keypad_read(keypad_config_t *keypad, uint8 *num);

#endif	/* KEYPAD_H */