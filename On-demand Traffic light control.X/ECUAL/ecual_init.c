/* 
 * File:   ecual_init.h
 * Author: osama reda
 *
 * Created on September 27, 2023, 9:22 PM
 */
#include "ecual_init.h"
/*===========================leds configuration==========================*/
//car's leds
led_config_t car_led_red={.led_pin.port=PORTC_INDEX,.led_pin.pin=PIN0};
led_config_t car_led_yellow={.led_pin.port=PORTC_INDEX,.led_pin.pin=PIN1};
led_config_t car_led_green={.led_pin.port=PORTC_INDEX,.led_pin.pin=PIN2};
//pedestrian's leds
led_config_t pedestrian_led_red={.led_pin.port=PORTC_INDEX,.led_pin.pin=PIN3};
led_config_t pedestrian_led_yellow={.led_pin.port=PORTC_INDEX,.led_pin.pin=PIN4};
led_config_t pedestrian_led_green={.led_pin.port=PORTC_INDEX,.led_pin.pin=PIN5};

/*====================7 segments configuration===========================*/
//green traffic
seven_segment_config_t seg_red={.seven_segment_pins[0].port=PORTD_INDEX,.seven_segment_pins[0].pin=PIN0,
                                  .seven_segment_pins[1].port=PORTD_INDEX,.seven_segment_pins[1].pin=PIN1,
                                  .seven_segment_pins[2].port=PORTD_INDEX,.seven_segment_pins[2].pin=PIN2,
                                  .seven_segment_pins[3].port=PORTD_INDEX,.seven_segment_pins[3].pin=PIN3};  
//red traffic
seven_segment_config_t seg_green={.seven_segment_pins[0].port=PORTD_INDEX,.seven_segment_pins[0].pin=PIN4,
                                .seven_segment_pins[1].port=PORTD_INDEX,.seven_segment_pins[1].pin=PIN5,
                                .seven_segment_pins[2].port=PORTD_INDEX,.seven_segment_pins[2].pin=PIN6,
                                .seven_segment_pins[3].port=PORTD_INDEX,.seven_segment_pins[3].pin=PIN7};   

/*==========================lcd configuration============================*/
//instruction lcd
lcd_config_t lcd={.lcd_pins[0].port=PORTB_INDEX,.lcd_pins[0].pin=PIN1,
                  .lcd_pins[1].port=PORTB_INDEX,.lcd_pins[1].pin=PIN2,
                  .lcd_pins[2].port=PORTB_INDEX,.lcd_pins[2].pin=PIN3,
                  .lcd_pins[3].port=PORTB_INDEX,.lcd_pins[3].pin=PIN4,
                  .lcd_rs.port=PORTB_INDEX,.lcd_rs.pin=PIN5,
                  .lcd_en.port=PORTB_INDEX,.lcd_en.pin=PIN6};


void ecual_init(void){
    Std_ReturnType ret=E_NOT_OK;
    //led initialization
    ret=led_init(&car_led_red);
    ret=led_init(&car_led_yellow);
    ret=led_init(&car_led_green);
    ret=led_init(&pedestrian_led_red);
    ret=led_init(&pedestrian_led_yellow);
    ret=led_init(&pedestrian_led_green);
    //7 segment initializiation
    ret=seven_segment_init(&seg_green);
    ret=seven_segment_init(&seg_red);
    //lcd initializiation
    ret=lcd_init(&lcd);
}