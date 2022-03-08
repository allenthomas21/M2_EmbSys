#ifndef __AVR_ATmega328__
#define __AVR_ATmega328__
#endif


#include "i2c_lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

uint8_t LCD_BL_Status = 1;     

unsigned char bit_test(uint8_t nibble, uint8_t bit_num) {
	if ((nibble & (1 << bit_num)))
		return TRUE;
	else
		return FALSE;

}

void Write_to_LCD(unsigned char data_to_write) {

	send_start();

	if (check_TWI_status(START) == FAIL)
		DEBUG_LED(ON);

	send_address( LCD_SLAVE_ADDR, write_bit);

	if (check_TWI_status(MT_SLA_ACK) == FAIL)
		DEBUG_LED(ON);

	transmit_data(data_to_write);
	if (check_TWI_status(MT_SLA_DATA_ACK) == FAIL)
		DEBUG_LED(ON);

	send_stop();

	_delay_ms(3);

}

void LCD_BL(uint8_t status) {
	LCD_BL_Status = status;
	LCD_Write_Byte(0x00, 0x00);
}

void LCD_Initial() {

	
	LCD_Write_Byte(0x00, 0x03);
	_delay_ms(10);                
	LCD_Write_Byte(0x00, 0x03);   //
	_delay_ms(10);                
	LCD_Write_Byte(0x00, 0x03);   //
	_delay_ms(10);                
	LCD_Write_Byte(0x00, 0x02); 
	_delay_ms(10);
	LCD_Write_Byte(0x00, 0x02);  
	_delay_ms(10);                 
	LCD_Write_Byte(0x00, 0x01);    
	_delay_ms(10);                 
	LCD_Write_Byte(0x00, 0x0C);    
	_delay_ms(10);                
	LCD_Write_Byte(0x00, 0x01);   
	_delay_ms(10);                 
	LCD_Write_Byte(0x00, 0x06);    
	_delay_ms(10);                 

}

void LCD_Goto(uint8_t x, uint8_t y) {
	uint8_t address;

	switch (y) {
	case 1:
		address = LCD_PIC_LINE_1_ADDRESS;
		break;

	case 2:
		address = LCD_PIC_LINE_2_ADDRESS;
		break;

	case 3:
		address = LCD_PIC_LINE_3_ADDRESS;
		break;

	case 4:
		address = LCD_PIC_LINE_4_ADDRESS;
		break;

	default:
		address = LCD_PIC_LINE_1_ADDRESS;
		break;
	}

	address += x - 1;
	LCD_Write_Byte(0, 0x80 | address);
}


void LCD_Write_Str(const char *str) {
	
	pin_RS = 1;
	pin_RW = 0;
	pin_E = 0;
	pin_BL = LCD_BL_Status;

	while (*str) {
	
		_LCD_Write_Upper_Nibble(*str);

		
		_LCD_Write_Lower_Nibble(*str);

		str++;
	}
}

void LCD_Write_Char(char c) {
	LCD_Write_Byte(0x01, c);
}

void LCD_Write_Int(int32_t num) {
	if (num < 0) {
		LCD_Write_String("-");
		num *= -1;
	}

	uint8_t number[10];
	uint8_t num_count = 0;

	do {
		number[num_count] = num % 10;
		num_count++;
		num /= 10;
	} while (num > 0);

	for (int i = num_count - 1; i >= 0; i--) {
		LCD_Write_Char(number[i] + 0b00110000);
	}
}

void LCD_Write_Byte(uint8_t address, uint8_t n) {
	if (address) {
		pin_RS = 1;  
	} else {
		pin_RS = 0;   
	}

	pin_RW = 0;
	pin_E = 0;
	pin_BL = LCD_BL_Status;

	
	_LCD_Write_Upper_Nibble(n);

	
	_LCD_Write_Lower_Nibble(n);
}

void LCD_Clear() {
	LCD_Write_Byte(0x00, 0x01);
	_delay_ms(1);
}

void LCD_ClearLine(uint8_t line) {
	LCD_Goto(1, line);
	for (int i = 0; i < 20; i++) {
		LCD_Write_Str(" ");
	}
	LCD_Goto(1, line);
}

void _LCD_Write_Upper_Nibble(uint8_t u) {
	uint8_t nibble_to_send;
	
	if (bit_test(u, 7))
		pin_D7 = 1;
	else
		pin_D7 = 0;

	if (bit_test(u, 6))
		pin_D6 = 1;
	else
		pin_D6 = 0;

	if (bit_test(u, 5))
		pin_D5 = 1;
	else
		pin_D5 = 0;

	if (bit_test(u, 4))
		pin_D4 = 1;
	else
		pin_D4 = 0;

	pin_E = 0;
	nibble_to_send = _LCD_Build_Byte();
	Write_to_LCD(nibble_to_send);

	pin_E = 1;
	nibble_to_send = _LCD_Build_Byte();
	Write_to_LCD(nibble_to_send);

	pin_E = 0;
	nibble_to_send = _LCD_Build_Byte();
	Write_to_LCD(nibble_to_send);
}

void _LCD_Write_Lower_Nibble(uint8_t l) {
	uint8_t nibble_to_send;
	
	if (bit_test(l, 3))
		pin_D7 = 1;
	else
		pin_D7 = 0;

	if (bit_test(l, 2))
		pin_D6 = 1;
	else
		pin_D6 = 0;

	if (bit_test(l, 1))
		pin_D5 = 1;
	else
		pin_D5 = 0;

	if (bit_test(l, 0))
		pin_D4 = 1;
	else
		pin_D4 = 0;

	pin_E = 0;
	nibble_to_send = _LCD_Build_Byte();
	Write_to_LCD(nibble_to_send);

	pin_E = 1;
	nibble_to_send = _LCD_Build_Byte();
	Write_to_LCD(nibble_to_send);

	pin_E = 0;
	nibble_to_send = _LCD_Build_Byte();
	Write_to_LCD(nibble_to_send);
}

uint8_t _LCD_Build_Byte() {
	uint8_t ret = 0x00;

	ret |= pin_E << 2;
	ret |= pin_RW << 1;
	ret |= pin_RS << 0;
	ret |= pin_D4 << 4;
	ret |= pin_D5 << 5;
	ret |= pin_D6 << 6;
	ret |= pin_D7 << 7;
	ret |= pin_BL << 3;

	return ret;
}

