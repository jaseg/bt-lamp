
#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"

int main(void){
	usart_init(BAUDRATE);
	sei();
	rx_check = 1;
	usart_write("atz0\r");
	_delay_ms(500);
	usart_write("atn=lelamp");
	_delay_ms(200);
	usart_write("atp=1234");
	_delay_ms(200);
	usart_status.usart_ready = 0;
	rx_check = 0;
	while(1){
		if(usart_status.usart_ready){
			usart_write_str(usart_rx_buffer);
			usart_status.usart_ready = 0;
		}
	}
}

