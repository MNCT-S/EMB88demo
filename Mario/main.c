#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

volatile uint16_t ovf = 0;
volatile uint8_t id = 0, code = 0;

static uint8_t maxid[] = {
    31, 20
};
static uint8_t sound[][31] = {
    { 94, 0, 94, 0, 0, 0, 0, 94, 0,  0, 0,  0, 118, 0, 94, 0,   0, 0,   0,  79, 0, 0, 0, 0, 0, 0, 0, 0, 0, 158, 158},
    {126, 0, 88, 0, 0, 0, 0, 88, 0, 88, 0, 94,   0, 0,  0, 0, 105, 0, 118, 118, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0}
};
volatile uint8_t* play = 0;

ISR(TIMER0_OVF_vect)
{
    if ( play ) {
        if ( ++ovf >= 250 ) {
            ovf=0;
            OCR2A = play[code++];
            if ( code >= maxid[id] ) {
                OCR2A = 0;
                PORTB = 0;
                code = 0;
                play = 0;
            }
        }
    }
}

int main()
{
    DDRB = 0xff;
    DDRC = 0x0f;
    DDRD = 0xfe;

    PORTB = 0x00;
    PORTC = 0x30;
    PORTD = 0x00;

    TCCR2B = _BV(CS22);
    TCCR2A = _BV(COM2B0)|_BV(WGM21);
    TCCR0A = 0;
    TCCR0B = _BV(CS01)|_BV(CS11);
    TIMSK0 = _BV(TOIE0);
    OCR2A = 0;
    OCR2B = 0;

    sei();

    while(1) {
        wdt_reset();

        if ( play==0 ) {
            if ( (PINC&_BV(4))==0 ) {
                PORTB = 0xf0;
                id = 0;
                play = sound[id];
            }
            if ( (PINC&_BV(5))==0 ) {
                PORTB = 0x0f;
                id = 1;
                play = sound[id];
            }
        }
    }

    return 0;
}