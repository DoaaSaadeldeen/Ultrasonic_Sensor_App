/*
 * lcd.c
 *
 * Created: 11/12/2022 10:41:09 AM
 *  Author: safifi
 */ 
#include "lcd.h"
#include "lcd_cfg.h"

/*****************************************************************************
* Function Name: LCD_init
* Purpose      : initialize LCD to work in 4-bit mode - clear lcd - cursor off
* Parameters   : void
* Return value : void
*****************************************************************************/
void LCD_init(void){
	INIT_LCD_PINS();
	LCD_write_command(0x3);
	_delay_ms(4);
	LCD_write_command(0x3);
	_delay_ms(4);
	LCD_write_command(0x3);
	_delay_ms(4);
	
	LCD_write_command(0x2);
	LCD_write_command(0x28);
	LCD_write_command(0x1); // clear
	LCD_write_command(0x06); // cursor incr right
	LCD_write_command(0x0c); // turn on diplay
	_delay_ms(20);	
}
/*****************************************************************************
* Function Name: LCD_write_char
* Purpose      : Write a specific Ascii char (data) to lcd (valid only with 4-bit mode)
* Parameters   : data  (data to be written on lcd)
* Return value : void
*****************************************************************************/
void LCD_write_char(uint8_t data){
	LCD_RS(1);
	LCD_D7(READBIT(data,7));
	LCD_D6(READBIT(data,6));
	LCD_D5(READBIT(data,5));
	LCD_D4(READBIT(data,4));
	LCD_EN(1); _delay_ms(1);
	LCD_EN(0); _delay_ms(1);
	
	LCD_D7(READBIT(data,3));
	LCD_D6(READBIT(data,2));
	LCD_D5(READBIT(data,1));
	LCD_D4(READBIT(data,0));
	LCD_EN(1); _delay_ms(1);
	LCD_EN(0); _delay_ms(1);
	
}
/*****************************************************************************
* Function Name: LCD_write_string
* Purpose      : Write a string (*txt) to lcd (valid only with 4-bit mode)
*                (assume the end char of string is NULL (Ascii:'\0' - decimal:0 ))
* Parameters   : *txt  (array of char to be written on lcd)
* Return value : void
*****************************************************************************/
void LCD_write_string(uint8_t *txt){
	while(*txt)
	{
		 LCD_write_char(*txt);
	     txt++;
	}
}
/*****************************************************************************
* Function Name: LCD_write_command
* Purpose      : Send a specific command (cmd) to lcd (valid only with 4-bit mode)
* Parameters   : cmd  (command to be done by lcd)
* Return value : void
*****************************************************************************/
void LCD_write_command(uint8_t cmd){
	LCD_RS(0);
	LCD_D7(READBIT(cmd,7));
	LCD_D6(READBIT(cmd,6));
	LCD_D5(READBIT(cmd,5));
	LCD_D4(READBIT(cmd,4));
	LCD_EN(1);
	_delay_ms(1);
	LCD_EN(0);
	_delay_ms(1);
	
	LCD_D7(READBIT(cmd,3));
	LCD_D6(READBIT(cmd,2));
	LCD_D5(READBIT(cmd,1));
	LCD_D4(READBIT(cmd,0));
	LCD_EN(1);
	_delay_ms(1);
	LCD_EN(0);
	_delay_ms(1);	
}

/*****************************************************************************
* Function Name: LCD_write_num
* Purpose      : Write a specific number (num) on lcd (valid only with 4-bit mode)
* Parameters   : num  (num to be written on lcd)
* Return value : void
*****************************************************************************/
void LCD_write_number(int32_t num){
	int32_t dig=0,i=0,arr[10],neg=0;
	if(num<0)neg=1,num*=-1;
	while(num>=0)
	{
		dig=num%10;
		num/=10;
		arr[i++]=dig;
		if(num==0)break;
	}
	if(neg)LCD_write_char('-');
	while(i>0)
	{
		//LCD_write_command(0xc0);
		LCD_write_char(arr[--i]+'0');
	}
	
}