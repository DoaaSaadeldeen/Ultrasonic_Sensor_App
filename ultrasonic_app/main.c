/*
 * ultrasonic_app.c
 *
 * Created: 4/11/2023 5:46:11 PM
 * Author : Dell_G3
 */ 

#include "LCD.h"
#define CLOCK_CYCLE_USEC (1000000.0/F_CPU)
#define MAX_VALUE_TIMER1 65537
#define enable_interupt() SETBIT(TIMSK,TOIE1) ;SETBIT(SREG,7);
uint32_t timer1_init_input_capture_usec(void);
uint32_t ovf_num = 0;

int main(void)
{
    LCD_init();
	enable_interupt();
	SETBIT(DDRD,4);//output (red led)
	SETBIT(DDRD,5);//output (green led)
	CLRBIT(PORTD,4);CLRBIT(PORTD,5);//output zero voltage by default
	CLRBIT(DDRD,6);//icp1 input pin
	SETBIT(DDRD,7);//output (signal)
    uint16_t sp_air;
	uint32_t distance;
    while (1) 
    {
		SETBIT(PORTD,7);
		_delay_ms(50);      //any value more than 10us 
	    CLRBIT(PORTD,7);
		
		uint32_t T = timer1_init_input_capture_usec();//time
		
	  // speed_air=34600 ->>>> 331.3+0.606 *Temp;
	   distance=(34600*T)/(2*F_CPU);
	   LCD_write_command(0x01);//clear
	
	   LCD_write_string("distance = ");
	   LCD_write_number(distance);
	   if(distance>=50){
		    SETBIT(PORTD,5);//green led on
		    CLRBIT(PORTD,4);//red led  off
	        
	   }
	   else{
		   SETBIT(PORTD,4);//red led  on
		   CLRBIT(PORTD,5);//green led  off
	   }
	     _delay_ms(400);

    }
}

ISR(TIMER1_OVF_vect){
	ovf_num++;
}
uint32_t timer1_init_input_capture_usec(void){
	uint16_t t1,t2,t3;
	 ovf_num = 0; TCCR1A = 0;
	TCCR1B |= 1<<CS00 | 1<<ICES1; // detect rising edge
	TIFR |= 1<<ICF1;              // clear ICU flag bit
	
	while(READBIT(TIFR,ICF1) == 0 ); // wait until first rising edge detect
	   
	t1 = ICR1;                      // store value of first rising edge
	CLRBIT(TCCR1B,ICES1);           // detect failing edge
	TIFR |= 1<<ICF1;                // clear IC flag

	while(READBIT(TIFR,ICF1) == 0); // wait until first falling edge detect
	t2 = ICR1;                      // store value of first falling edge
	
	TCCR1B = 0;                     // stop timer 1
	TIFR |= 1<<ICF1;                // clear IC flag
	ICR1 = 0;
	TCNT1 = 0;
		
	return ((ovf_num * MAX_VALUE_TIMER1)  + (t2-t1) );//the time of high signal
}
