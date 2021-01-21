/*
 * ExBoardSTM.c
 *		Stepping Motor Demo
 * Created: 2020/11/26 11:23:56
 * Author : magara
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#define SW1_ON()	!(PINC & _BV(4))
#define SW2_ON()	!(PINC & _BV(5))
#define SLOW_MODE
#define DEG45		60		// 45deg/0.75

enum MODE
{
	MODE1=0, MODE12=1, MODE2=2	
}	mode = MODE1;			// pattern
unsigned char	pattern[][8] = {
	{0b00010000, 0b00100000, 0b01000000, 0b10000000, 0b00010000, 0b00100000, 0b01000000, 0b10000000},
	{0b00010000, 0b00110000, 0b00100000, 0b01100000, 0b01000000, 0b11000000, 0b10000000, 0b10010000},
	{0b00110000, 0b01100000, 0b11000000, 0b10010000, 0b00110000, 0b01100000, 0b11000000, 0b10010000},
};
volatile int	ovf = 0, idx = 0, add = 0, stm = 0;

////////

ISR(TIMER0_OVF_vect)
{
#ifdef SLOW_MODE
	ovf++;
	if ( ovf > 10 && add != 0 ) {
		ovf = 0;
#else
	if ( stm > 0 ) {
		stm--;
#endif
		idx += add;
		if ( idx > 7 )
			idx = 0;
		else if ( idx < 0 )
			idx = 7;
		PORTB &= 0x0f;
		PORTB |= pattern[mode][idx];
	}
}

int main(void)
{
	// STM
	DDRB   = 0xf0;		// H:PB7-PB4 L:PB3-PB0
	// Mode SW pullup
	PORTB  = 0x04;		// PB1, PB2
	// matrix led + SW
	DDRD   = 0xf0;
	PORTD  = 0x70;	// L:bottom led(PD7)
	DDRC   = 0x0f;	// PC4, PC5 is input-switch
	PORTC  = 0x3f;	// PC4, PC5 is pullup

	// Mode Check -> can't input ???
//	if ( !(PINB & _BV(1)) ) mode = MODE2;
//	else if ( !(PINB & _BV(2)) ) mode = MODE12;

	PORTB &= 0x0f;
	PORTB |= pattern[mode][idx];

	// Timer0
#ifdef SLOW_MODE
	TCCR0B |= _BV(CS02) | _BV(CS00);	// 1/1024
#else
	TCCR0B |= _BV(CS02);				// 1/256
#endif
	TIMSK0 |= _BV(TOIE0);

	sei();
    while (1) {
		wdt_reset();
		if ( SW1_ON() ) {
			add = 1;
#ifndef SLOW_MODE
			if ( stm == 0 ) stm = DEG45;
#endif
		}
		else if ( SW2_ON() ) {
			add = -1;
#ifndef SLOW_MODE
			if ( stm == 0 ) stm = DEG45;
#endif
		}
		else {
#ifndef SLOW_MODE
			if ( stm == 0 ) add = 0;
#else
			add = 0;
#endif
		}
    }
}

