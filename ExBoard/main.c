/*
 * ExBoard.c
 *		Motor & Servo Demo
 * Created: 2020/08/06 12:52:48
 * Author : magara
 */ 
#include <avr/io.h>
#include <avr/wdt.h>

#define SW1_ON()	!(PINC & _BV(4))
#define SW2_ON()	!(PINC & _BV(5))

#define TMAX	   10000	// T=10,000us * 8MHz / 8(Prescaling)
#define	T800		9600	// Ton=0.8ms (10000 -  800/2)
#define	T1500		9250	// Ton=1.5ms (10000 - 1500/2)
#define T2200		8900	// Ton=2.2ms (10000 - 2200/2)

int main(void)
{
	// Motor Driver IN1/IN2
	DDRD   =   _BV(6) | _BV(5);
	PORTD  = 0;
	// SW
	DDRC   = ~(_BV(4) | _BV(5));
	PORTC  = 0;
	PORTC |=   _BV(4) | _BV(5);
	// Servo
	TCCR1A = _BV(COM1A1) | _BV(COM1A0) | _BV(COM1B1) | _BV(COM1B0);
	TCCR1B = _BV(WGM13) | _BV(CS11);	// PWM, 1/8(Prescaling)
	ICR1 = TMAX;
	OCR1A = T1500;
	OCR1B = T800;
	DDRB  = _BV(1) | _BV(2);	// Compare output (OC1A/OC1B)

    while (1) {
		wdt_reset();	// Ç±ÇÍÇ»Ç¢Ç∆ìÆÇ©ÇÒÅH

		if ( SW1_ON() ) {
			PORTD |=  _BV(6);	// IN1(H)
			OCR1A = T800;		// left
			OCR1B = T800;
		}
		else {
			PORTD &= ~_BV(6);	// IN1(L)
			if ( !SW2_ON() ) {
				OCR1A = T1500;		// center
			}
		}

		if ( SW2_ON() ) {
			PORTD |=  _BV(5);	// IN2(H)
			OCR1A = T2200;		// right
			OCR1B = T2200;
		}
		else {
			PORTD &= ~_BV(5);	// IN2(L)
			if ( !SW1_ON() ) {
				OCR1A = T1500;		// center
			}
		}
    }
}
