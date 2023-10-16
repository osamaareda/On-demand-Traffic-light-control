/* 
 * File:   app.c
 * Author: osama reda
 * 
 * Created on September 11, 2023, 11:22 PM
 */
 
 
#include"app.h"

Std_ReturnType ret=E_NOT_OK;
uint8 flag_mode=CARS_MODE,counter=0;
/*========================INT0 configuration==========================*/
interrupt_INTx_t MY_INT0={.EXT_InterruptHandler=APP_INT_ISR,
                          .INTx_pin.port=PORTB_INDEX,
                          .INTx_pin.pin=PIN0,
                          .edge=RISING_EDGE,
                          .source=_INT0};

/*===================custom character for stop sign====================*/
uint8 customChar1[] = {0x1F,0x10,0x10,0x13,0x14,0x18,0x1F,0x00};
uint8 customChar2[] = {0x1F,0x03,0x05,0x19,0x01,0x01,0x1F,0x00};

/*===================custom character for move sign====================*/
uint8 customChar3[] = {0x00,0x00,0x1F,0x1F,0x1F,0x00,0x00,0x00};
uint8 customChar4[] = {0x08,0x0C,0x1E,0x1F,0x1E,0x0C,0x08,0x00};

/*=============================main code===============================*/
void app_init(void){
    //component initialization
    ecual_init();
    //interrupt initialization
    ret=interrupt_INTx_init(&MY_INT0);
}
int main() {
    
    app_init();
    
    
while(1)
{
    /*===============cars mode===============*/
    /*this part allow the pedestrians to cross the street
     * showing car's red led on and pedestrian's green led on
     * with green counter and move sign*/
    move_sign();
    ret=led_on(&car_led_red);
    ret=led_on(&pedestrian_led_green);
    for(counter=5;counter>0;counter--){
        ret=seven_segment_write(&seg_green,counter);
        __delay_ms(900);
    }
    ret=seven_segment_write(&seg_green,0);
    
    /*this part represent alert to make pedestrians stop after 5 sec
     * blinking yellow leds
     * with harry up sign*/
    harry_up_sign();
    for(counter=0;counter<20;counter++){
        ret=led_toggle(&car_led_yellow);
        ret=led_toggle(&pedestrian_led_yellow);
        modes_checker();
        __delay_ms(250);
    }
    ret=led_off(&car_led_red);
    ret=led_off(&pedestrian_led_green);
    ret=led_off(&car_led_yellow);
    ret=led_off(&pedestrian_led_yellow);
    
    /*this part stop the pedestrians 
     * showing car's green led on and pedestrian's red led on
     * with red counter and stop sign*/
    stop_sign();
    ret=led_on(&car_led_green);
    ret=led_on(&pedestrian_led_red);
    for(counter=5;counter>0;counter--){
        modes_checker();  //this function used to check the flag to swith to pedestrian modes
        ret=seven_segment_write(&seg_red,counter);
        __delay_ms(900);
    }
    ret=seven_segment_write(&seg_red,0);
    
    /*this part represent alert to make pedestrians move after 5 sec
     * blinking yellow leds
     * with wait sign*/
    wait_sign();
    for(counter=0;counter<20;counter++){
        ret=led_toggle(&car_led_yellow);
        ret=led_toggle(&pedestrian_led_yellow);
        modes_checker();  //this function used to check the flag to swith to pedestrian modes
        __delay_ms(250);
    }
    ret=led_off(&car_led_green);
    ret=led_off(&pedestrian_led_red);
}  
    return (EXIT_SUCCESS);
}

/*===========function will be execute when interrupt happen===========*/
void APP_INT_ISR(void){
    if((PORTCbits.RC2==HIGH) && (PORTCbits.RC3==HIGH) && (PORTBbits.RB1==HIGH)){
       flag_mode=WHEN_GREEN_ON;      //set flag to mode one
    }
    else if((PORTCbits.RC0==HIGH) && (PORTCbits.RC5==HIGH) && (PORTBbits.RB1==LOW)){
       flag_mode=WHEN_YELLOW_BLINK;  //set flag to mode two
    }
}
void modes_checker(void){
    /*===============cars mode===============*/
    /* MODE ONE:
     * if the button pressed when cars green led on
     * 1-blinking yellow leds to alert pedestrians to move after 5 sec
     * 2-howing car's red led on and pedestrian's green led on with green counter and move sign
     * 3-after counter finish yellow leds blinking with harry up sign
     * 4-back to cars mode
     */
    if(flag_mode==WHEN_GREEN_ON){
        ret=seven_segment_write(&seg_red,0);
        wait_sign();
        yellow_leds_toggle();
        move_sign();
        ret=led_off(&car_led_green);
        ret=led_off(&pedestrian_led_red);
        ret=led_on(&car_led_red);
        ret=led_on(&pedestrian_led_green);
        pedestrian_green_traffic_counter(5);
        ret=seven_segment_write(&seg_green,0);
        harry_up_sign();
        yellow_leds_toggle();
        ret=led_off(&car_led_red);
        ret=led_off(&pedestrian_led_green);
        stop_sign();
        ret=led_on(&pedestrian_led_red);
        ret=led_on(&car_led_green);
        counter=0;
        flag_mode=CARS_MODE;
     }
    /* MODE TWO:
     * if the button pressed when yellow leds blinking
     * 1-showing car's red led on and pedestrian's green led on with green counter and move sign
     * 2-after counter finish back to cars mode
     */
    else if(flag_mode==WHEN_YELLOW_BLINK && (PORTCbits.RC5==HIGH)){
        ret=led_off(&car_led_yellow);
        ret=led_off(&pedestrian_led_yellow);
        move_sign();
        ret=led_on(&car_led_red);
        ret=led_on(&pedestrian_led_green);
        pedestrian_green_traffic_counter(5);
        ret=seven_segment_write(&seg_green,0);
        harry_up_sign();
        counter=0;
        flag_mode=CARS_MODE;
     }
}
/*========================toggle yellow leds==========================*/
void yellow_leds_toggle(void){
    uint8 counter;
    for(counter=0;counter<20;counter++){
        ret=led_toggle(&car_led_yellow);
        ret=led_toggle(&pedestrian_led_yellow);
        __delay_ms(250);
    }
}
/*=======================to show stop sign============================*/
void stop_sign(void){
    ret=lcd_send_string_pos(&lcd,2,8,"STOP    ");
    ret=lcd_send_custom_char(&lcd,2,12,customChar1,0);
    ret=lcd_send_custom_char(&lcd,2,13,customChar2,1);
}
/*=======================to show move sign============================*/
void move_sign(void){
    ret=lcd_send_string_pos(&lcd,2,8,"MOVE    ");
    ret=lcd_send_custom_char(&lcd,2,12,customChar3,0);
    ret=lcd_send_custom_char(&lcd,2,13,customChar4,1);
}
/*=======================to show wait sign============================*/
void wait_sign(void){
    ret=lcd_send_string_pos(&lcd,2,8,"WAIT... ");
}
/*=======================to show wait sign============================*/
void harry_up_sign(void){
    ret=lcd_send_string_pos(&lcd,2,8,"HARRY UP");
}
/*=======================to count on red trafic=======================*/
void pedestrian_red_traffic_counter(uint8 time){
    uint8 counter;
    for(counter=time;counter>0;counter--){
         ret=seven_segment_write(&seg_red,counter);
         __delay_ms(900);
    }
}
/*=====================to count on green trafic======================*/

void pedestrian_green_traffic_counter(uint8 time){
    uint8 counter;
    for(counter=time;counter>0;counter--){ 
        seven_segment_write(&seg_green,counter);
        __delay_ms(900);
    }
}
