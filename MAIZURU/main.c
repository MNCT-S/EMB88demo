/*
 * MAIZURU.c
 * Author : magara
 */ 
 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#define CTOP	2000UL
#define SIZEOF(a)	( sizeof(a) / sizeof(a[0]) )

unsigned char	led_m[] = {
	0b10000010,
	0b11000110,
	0b10101010,
	0b10010010,
	0b10010010,
	0b10000010,
	0b10000010,
	0b10000010
};
unsigned char	led_a[] = {
	0b00010000,
	0b00101000,
	0b01000100,
	0b10000010,
	0b11111110,
	0b10000010,
	0b10000010,
	0b10000010
};
unsigned char	led_i[] = {
	0b01111110,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b01111110
};
unsigned char	led_z[] = {
	0b11111110,
	0b10000100,
	0b00001000,
	0b00010000,
	0b00100000,
	0b01000000,
	0b10000010,
	0b11111110,
};
unsigned char	led_u[] = {
	0b10000010,
	0b10000010,
	0b10000010,
	0b10000010,
	0b10000010,
	0b10000010,
	0b10000010,
	0b01111100
};
unsigned char	led_r[] = {
	0b11111100,
	0b10000010,
	0b10000010,
	0b10000010,
	0b11111100,
	0b10001000,
	0b10000100,
	0b10000010
};
unsigned char	led_space[] = {
	0, 0, 0, 0, 0, 0, 0, 0
};

unsigned char	led_now[8];
unsigned char*	doc[] = {
	led_m, led_a, led_i, led_z, led_u, led_r, led_u, led_space
};
uint8_t		doc_id = 0;
uint8_t		ovf = 0;

////////////////////

uint8_t nextDoc()
{
	uint8_t result = doc_id + 1;
	return result<SIZEOF(doc) ? result : 0;
}

void setLED()
{
	static	uint8_t		scan = 0;
			uint8_t		nxt_id = nextDoc();

	for ( int i=0; i<SIZEOF(led_now); i++ ) {
		led_now[i] = (doc[doc_id][i] << scan) | (doc[nxt_id][i] >> (8-scan));
	}
	scan = (scan + 1) & 7;
	if ( scan == 0 ) doc_id = nxt_id;
}

void viewLED()
{
	static	unsigned char	sc = 0xfe;
	static	uint8_t			scan = 0;

	PORTB = 0;
	sc = (sc << 1) | (sc >> 7);
	PORTD = (PORTD & 0x0f) | (sc & 0xf0);
	PORTC = (PORTC & 0xf0) | (sc & 0x0f);
	scan = (scan + 1) & 7;
	PORTB = led_now[scan];
}

int main(void)
{
	unsigned long	cnt = 0;

	DDRB = 0xff;
	DDRC = 0x0f;
	DDRD = 0xfe;
	PORTB = 0xff;
	PORTC = 0;
	PORTD = 0;

	TCCR0B = _BV(CS02) | _BV(CS00);
	TIMSK0 = _BV(TOIE0);

	setLED();
	sei();

    while (1) {
		wdt_reset();
		cnt++;
		if ( cnt >= CTOP ) {
			cnt = 0;
//			cli();	// ï\é¶íÜÇÕäÑçûÇ›ã÷é~ÅiÇ»Ç≠ÇƒÇ‡ÇøÇÁÇ¬Ç´Ç»ÇµÅj
			viewLED();
//			sei();
		}
    }
}

ISR(TIMER0_OVF_vect)
{
	if ( ++ovf == 10 ) {	// 1/8M * 1024 * 256 * 10cnt = 0.3s
		ovf = 0;
		setLED();
	}
}