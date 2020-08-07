/*
 * MAIZURU.c
 *  各文字の表示テストはOK
 *  ここからスクロールさせる
 * Author : magara
 */ 
 
#include <avr/io.h>
#include <avr/wdt.h>

#define CTOP	2000UL

unsigned char	m[] = {
	0b10000010,
	0b11000110,
	0b10101010,
	0b10010010,
	0b10010010,
	0b10000010,
	0b10000010,
	0b10000010
};
unsigned char	a[] = {
	0b00010000,
	0b00101000,
	0b01000100,
	0b10000010,
	0b11111110,
	0b10000010,
	0b10000010,
	0b10000010
};
unsigned char	i[] = {
	0b01111110,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000,
	0b01111110
};
unsigned char	z[] = {
	0b11111110,
	0b10000100,
	0b00001000,
	0b00010000,
	0b00100000,
	0b01000000,
	0b10000010,
	0b11111110,
};
unsigned char	u[] = {
	0b10000010,
	0b10000010,
	0b10000010,
	0b10000010,
	0b10000010,
	0b10000010,
	0b10000010,
	0b01111100
};
unsigned char	r[] = {
	0b11111100,
	0b10000010,
	0b10000010,
	0b10000010,
	0b11111100,
	0b10001000,
	0b10000100,
	0b10000010
};

void update_led()
{
	static	unsigned char	sc = 0xfe;
	static	unsigned char	scan = 0;

	PORTB = 0;
	sc = (sc << 1) | (sc >> 7);
	PORTD = (PORTD & 0x0f) | (sc & 0xf0);
	PORTC = (PORTC & 0xf0) | (sc & 0x0f);
	scan = (scan + 1) & 7;
	PORTB = r[scan];
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

    while (1) {
		wdt_reset();
		cnt++;
		if ( cnt >= CTOP ) {
			cnt = 0;
			update_led();
		}
    }
}

