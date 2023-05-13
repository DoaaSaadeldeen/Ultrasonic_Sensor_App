/*
 * headers.h
 *
 * Created: 11/5/2022 10:52:05 AM
 *  Author: safifi
 */ 


#ifndef HEADERS_H_
#define HEADERS_H_

#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h> // this header is necessary when you deal with interrupt

#define SETBIT(REG,BIT)  (REG |= 1 << BIT)
#define CLRBIT(REG,BIT)  (REG &= ~(1 << BIT))
#define TOGBIT(REG,BIT)  (REG ^= 1 << BIT)
#define READBIT(REG,BIT)  ((REG >> BIT) & 1)

#endif /* HEADERS_H_ */