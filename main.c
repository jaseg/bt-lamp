
#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"

#ifdef MASTER
#define OA_NUM 0
#define OB_NUM 1
#else
#define OA_NUM 2
#define OB_NUM 3
#endif

int main(void){
	usart_init(BAUDRATE);
	TCCR1A |= (1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);
	TCCR1B |= (1<<WGM12)|(1<<WGM13)|(1<<CS10);
	ICR1=0xFFFF;
	sei();
#ifdef MASTER
	rx_check = 1;
	usart_write("atz0\r");
	_delay_ms(500);
	usart_write("atn=lelamp");
	_delay_ms(200);
	usart_write("atp=1234");
	_delay_ms(200);
	usart_status.usart_ready = 0;
	rx_check = 0;
#endif
	while(1){
		if(usart_status.usart_ready){
			uint16_t val = usart_rx_buffer[1]<<8|usart_rx_buffer[2];
			if(usart_rx_buffer[0] == OA_NUM){
				OCR1A = val;
			}else if(usart_rx_buffer[0] == OB_NUM){
				OCR1B = val;
			}else{ //if command not found: echo.
				usart_write_str(usart_rx_buffer);
			}
			usart_status.usart_ready = 0;
		}
	}
}

