/*
 * GccApplication1.c
 *
 * Created: 15/11/2020 03:39:35 p. m.
 * Author : lujeo
 */ 
#define F_CPU 1000000

/*//////////////////////////////////////////////////
/			LIBRERIAS
//////////////////////////////////////////////////*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*//////////////////////////////////////////////////
/			DEFINICION DE FUNCIONES
//////////////////////////////////////////////////*/
uint8_t bcd_2_7seg(uint8_t bcd);

/*//////////////////////////////////////////////////
/			VARIBALES GLOBALES
//////////////////////////////////////////////////*/

uint8_t display0=0;
uint8_t display1=0;
/*//////////////////////////////////////////////////
/					MAIN
//////////////////////////////////////////////////*/
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
	| or  & and ^exor ~not
	
	ddrb => XXXX_XXXX
			0000_0001
	or		XXXX_XXX1
	ddrb <= XXXX_XXX1
	*/
	/* Blink with interrupt */
	sei();
	DDRB =0b11111111;
	DDRD =0b00000011;
	//config del ADC
	ADCSRA|=1<<ADEN|1<<ADIE|1<<ADPS2|1<<ADPS1|1<<ADPS0;
	ADMUX|= 1<<REFS1|1<<REFS0;
	
	//config para prescalador de 8
	TCCR1B |= 1<<CS11 | 1<<WGM12;
	TIMSK|=1<<OCIE1A;
	//valor para un retardo de 0.1s
	OCR1A =6249;
	
	while(1){
		PORTB=bcd_2_7seg(display0);
		PORTD=0b00000001;
		_delay_ms(8);
		PORTB=bcd_2_7seg(display1);
		PORTD=0b00000010;
		_delay_ms(8);	
	}
}

/*//////////////////////////////////////////////////
/			FUNCIONES DE INTERRUPCION
//////////////////////////////////////////////////*/
ISR(TIMER1_COMPA_vect){
	ADCSRA|=1<<ADSC;	
}
ISR(ADC_vect){
	//el valor del registro ADC(ADCH y ADCL) solo puede ser leido una vez cada conversion
	uint16_t lecturaADC=ADC;
	uint8_t valorAjustado=lecturaADC/11;
	uint8_t decenas=valorAjustado/10;
	uint8_t unidades=valorAjustado%10;
	display0=unidades;
	display1=decenas;
}

////////////////BCD to 7seg//////////////////

uint8_t bcd_2_7seg(uint8_t bcd){
	
  uint8_t display7Seg=0;
  switch (bcd){
	case 0:	display7Seg=0b00111111;
			break;
	case 1:	display7Seg=0b00000110;
			break;
	case 2:	display7Seg=0b01011011;
			break;
	case 3:	display7Seg=0b01001111;
			break;
	case 4:	display7Seg=0b01100110;
			break;
	case 5:	display7Seg=0b01101101;
			break;
	case 6:	display7Seg=0b01111101;
			break;
	case 7:	display7Seg=0b00000111;
			break;
	case 8:	display7Seg=0b01111111;
			break;
	case 9:	display7Seg=0b01101111;
			break;
	case 10:display7Seg=0b01110111;
			break;
	case 11:display7Seg=0b01111100;
			break;
	case 12:display7Seg=0b00111001;
			break;
	case 13:display7Seg=0b01011110;
			break;
	case 14:display7Seg=0b01111001;
			break;
	case 15:display7Seg=0b01110001;
			break;
	default:display7Seg=0b00000000;
			break;
  }
  return display7Seg;
   
}