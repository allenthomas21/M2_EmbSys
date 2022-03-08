/**
 * @file main.c
 * @author allen thomas
 * @brief Obstacle Awarness System progrm
 * @version 0.1
 * @date 2022-03-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef __AVR_ATmega328__
#define __AVR_ATmega328__
#endif



#include "i2c_lcd.h"
#include "inputCapture_timer.h"
#include "usart.h"



#define SPEED_OF_SOUND_IN_CM_S (331/10)

volatile float temp = 0;
volatile float distance = 0;
volatile uint16_t dist_whole = 0;
volatile uint16_t dist_dec = 0;
volatile uint16_t ticks_t1 = 0;
volatile uint16_t ticks_t2 = 0;
volatile uint16_t elapsed_time = 0;
volatile static uint16_t tick_count = 0;
char value_buf[7] = { 0 };
char dec_val_buf[7] = { 0 };

void init_input_capture() {
	TIMSK1 = ((1 << ICIE1)); 
	TCCR1B = ((1 << ICES1) | (1 << ICNC1) | (1 << CS12)); 
	edge.current_edge = INIT_RISING;
	edge.next_edge = INIT_RISING;
}

void init_timer2() {
	TIFR2 = 1 << OCF2A; 
	TIMSK2 = 1 << OCIE2A; 
	TCCR2A = 1 << WGM21; 
	TCCR2B = ((1 << CS21));
}

int main() {

	DDRC = 0xFF;
	PORTC = 0x00;   
	DDRB = 0b00000010;
	PORTB = (1 << PB0) | (1 << PB1);

	OCR2A = (uint8_t) OCR2A_VALUE; 
	usart_init(BAUD_VAL);
	set_i2c_clock(100);

	LCD_Initial();

	LCD_Clear();
	LCD_Write_Str("Distance: ");
	LCD_Clear();


	init_input_capture();
	init_timer2();

	sei();

	while (1) {

		if (edge.current_edge == FALLING) {
			cli();
			if (ticks_t2 > ticks_t1)
				temp = (float) (ticks_t2 - ticks_t1) / (float) TICKS_VAL;
			else
				temp = (float) ((65535 - ticks_t1) + ticks_t2)
						/ (float) TICKS_VAL;
			temp *= 1000000; 
			elapsed_time = (uint16_t) temp;

			distance = ((float) SPEED_OF_SOUND_IN_CM_S * (float) elapsed_time)
					/ (float) 2000;
			dist_whole = (uint16_t) distance; 
			dist_dec = (uint16_t) (((float) distance - (float) dist_whole)
					* 1000); 
			sei();
			sprintf(dec_val_buf, "%1u", dist_dec);
			sprintf(value_buf, "%u", dist_whole);
			strcat(value_buf, ".");
			strcat(value_buf, dec_val_buf);

		}

#ifdef DEBUG_ON
		USART_Tx_string(value_buf);
#endif

		
		LCD_Goto(1, 1);
		LCD_Write_Str("Dist:");
		LCD_Write_Str(value_buf);
		LCD_Write_String("cm");

	}

	return 0;
}

ISR(TIMER1_CAPT_vect) {

	cli();

	switch (edge.next_edge) {
	case INIT_RISING: {

		ticks_t1 = ICR1L;
		ticks_t1 |= (ICR1H << 8);
		TCCR1B &= ~(1 << ICES1); 
		edge.next_edge = FALLING;

	}
		break;

	case RISING: {
		ticks_t1 = (uint16_t) ICR1L;
		ticks_t1 |= (uint16_t) (ICR1H << 8);
		TCCR1B &= ~(1 << ICES1); 
		edge.current_edge = RISING;
		edge.next_edge = FALLING;

	}
		break;

	case FALLING: {
		ticks_t2 = (uint16_t) ICR1L;
		ticks_t2 |= (uint16_t) (ICR1H << 8);
		TCCR1B |= (1 << ICES1); 
		edge.current_edge = FALLING;
		edge.next_edge = RISING;
	}
		break;

	default:
		break;
	}
	sei();

}

ISR(TIMER2_COMPA_vect) {
	cli();
	tick_count++;

	if (tick_count == 1) {
		PORTB |= 1 << PB1;

	}

	if (tick_count == 2) {
		PORTB &= ~(1 << PB1);

	}

	if (tick_count == 700) {
		tick_count = 0;
	}

	sei();
}
