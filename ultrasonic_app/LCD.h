/*
 * lcd.h
 *
 * Created: 11/12/2022 10:41:26 AM
 *  Author: safifi
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "std_macros.h"


void LCD_init(void);
void LCD_write_char(uint8_t);
void LCD_write_string(uint8_t *);
void LCD_write_command(uint8_t);
void LCD_write_number(int32_t);



#endif /* LCD_H_ */