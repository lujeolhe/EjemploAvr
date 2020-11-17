/*
 * GccApplication1.c
 *
 * Created: 15/11/2020 03:39:35 p. m.
 * Author : lujeo
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



int main(void)
{
    /* Blink
	DDRB |= (1<<PINB0);
	PORTB &= ~(1<<PINB0);
	
    while (1) 
    {
		PORTB ^= (1<<PINB0);
		_delay_ms(500);
    }
	*/
	/* Blink whith interrupt */
	sei();
	
}

