/*
 * icu_app.c
 *
 * Created: 9/2/2022 10:02:57 AM
 *  Author: safifi
 */ 


#include "LCD.h"
#include "TIMER0.h"
uint16_t timer1_init_input_capture_usec(void);
#define CLOCK_CYCLE_USEC (1000000.0/F_CPU)
#define MAX_VALUE_TIMER1 65537
int main(void)
{
	LCD_init();
	uint8_t count = 119;
    TIMER0_freqGen_init(count); // (120*2)/8 = 30usec
    while(1)
    {
	uint16_t T = timer1_init_input_capture_usec();

	LCD_write_command(0x1);
	LCD_write_number(T);  // measured 
	LCD_write_command(0xc0);
	LCD_write_number((count+1)*2*CLOCK_CYCLE_USEC); // actual 

	_delay_ms(500);

	}
}
uint8_t ovf_num = 0;
ISR(TIMER1_OVF_vect){
	ovf_num++;
}

