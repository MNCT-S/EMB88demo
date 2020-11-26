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

enum MODE
{
	MODE1=0, MODE12=1, MODE2=2	
}	mode = MODE12;				// pattern
unsigned char	pattern[][8] = {
	{0b00010000, 0b00100000, 0b01000000, 0b10000000, 0b00010000, 0b00100000, 0b01000000, 0b10000000},
	{0b00010000, 0b00110000, 0b00100000, 0b01100000, 0b01000000, 0b11000000, 0b10000000, 0b10010000},
	{0b00110000, 0b01100000, 0b11000000, 0b10010000, 0b00110000, 0b01100000, 0b11000000, 0b10010000},
};
volatile int	ovf = 0, idx = 0, add = 0;

////////

ISR(TIMER0_OVF_vect)
{
#ifdef SLOW_MODE
	ovf++;
	if ( ovf > 10 ) {
#endif
		ovf = 0;
		idx += add;
		if ( idx > 7 )
			idx = 0;
		else if ( idx < 0 )
			idx = 7;
		PORTB &= 0x0f;
		PORTB |= pattern[mode][idx];
#ifdef SLOW_MODE
	}
#endif
}

int main(void)
{
	// STM
	DDRB   = 0xf0;		// H:PB7-PB4 L:PB3-PB0
	// matrix led + SW
	DDRD   = 0xf0;
	PORTD  = 0x70;	// L:bottom led(PD7)
	DDRC   = 0x0f;	// PC4, PC5 is input-switch
	PORTC  = 0x3f;	// PC4, PC5 is pullup

	PORTB = pattern[mode][idx];

	// Timer0
	TCCR0B |= _BV(CS02) | _BV(CS00);	// 1/1024
	TIMSK0 &= ~_BV(TOIE0);

	sei();
    while (1) {
		wdt_reset();
		if ( SW1_ON() ) {
			add = 1;
			TIMSK0 |= _BV(TOIE0);
		}
		else if ( SW2_ON() ) {
			add = -1;
			TIMSK0 |= _BV(TOIE0);
		}
		else {
			add = 0;
			TIMSK0 &= ~_BV(TOIE0);
		}
    }
}

