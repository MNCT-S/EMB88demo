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
	TCCR1B = _BV(WGM13) | _BV(CS11);	// PWM, 1/8
	ICR1 = 10000;	// T=10+10ms
	OCR1A = 8900;	// Ton=2.2ms
	OCR1B = 9600;	// Ton=0.8ms
	DDRB  = _BV(1) | _BV(2);	// Compare output

    while (1) {
		wdt_reset();	// Ç±ÇÍÇ»Ç¢Ç∆ìÆÇ©ÇÒÅH

		if ( SW1_ON() ) {
			PORTD |=  _BV(6);
			OCR1A = 9600;
		}
		else {
			PORTD &= ~_BV(6);
			OCR1A = 8900;
		}
		if ( SW2_ON() ) {
			PORTD |=  _BV(5);
			OCR1B = 8900;
		}
		else {
			PORTD &= ~_BV(5);
			OCR1B = 9600;
		}
    }
}
