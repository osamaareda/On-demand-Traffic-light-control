/* 
 * File:   keypad.h
 * Author: osama reda
 *
 * Created on September 27, 2023, 6:50 PM
 */
#include"keypad.h"

uint8 keypad_btns[KEYPAD_ROWS][KEYPAD_COLUMNS]={
                                                  {'7','8','9','/'},
                                                  {'4','5','6','*'},
                                                  {'1','2','3','-'},
                                                  {'#','0','=','+'}
                                               };
/**
 * @brief  : initialize keypad pins 4 to be output and 4 to be input
 * @param  : keypad -> pointer to (keypad_config_t) structure @ref keypad_config_t
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if KEYPAD_CONFIG==ENABLE
Std_ReturnType keypad_init(keypad_config_t *keypad){
    
    uint8 row,column;
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==keypad){
        ret=E_NOT_OK;
    }
    else{
        for(row=0;row<KEYPAD_ROWS;row++){
            gpio_ret=gpio_pin_output_low_init(&(keypad->keypad_rows_pins[row]));
            
        }
        for(column=0;column<KEYPAD_COLUMNS;column++){
            gpio_ret=gpio_pin_input_init(&(keypad->keypad_columns_pins[column]));
        }
        
        ret=E_OK;
    }
    
    return ret;
}
#endif
/**
 * @brief  : inform me about the pressed number
 * @param  : keypad -> pointer to (keypad_config_t) structure @ref keypad_config_t
 * @param  : num -> uint8 variable
 * @return : state of the function
 *           (E_OK) func done successfully
 *           (E_NOT_OK) func has issue
 */
#if KEYPAD_CONFIG==ENABLE
Std_ReturnType keypad_read(keypad_config_t *keypad, uint8 *num){
    
    uint8 row,column,counter,column_logic;
    Std_ReturnType ret=E_NOT_OK;
    Std_ReturnType gpio_ret=E_NOT_OK;
    if(NULL==keypad || NULL==num){
        ret=E_NOT_OK;
    }
    else{
        for(row=0;row<KEYPAD_ROWS;row++){
            for(counter=0;counter<KEYPAD_ROWS;counter++){
                gpio_ret=gpio_pin_logic_write(&(keypad->keypad_rows_pins[counter]),LOW);
            }
            gpio_ret=gpio_pin_logic_write(&(keypad->keypad_rows_pins[row]),HIGH);
            for(column=0;column<KEYPAD_COLUMNS;column++){
                gpio_ret=gpio_pin_logic_read(&(keypad->keypad_columns_pins[column]),&column_logic);
                if(column_logic==HIGH){
                    *num=keypad_btns[row][column];
                }
            }
        }
        
        ret=E_OK;
    }
    
    return ret;
}
#endif