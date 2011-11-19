/*----------------------------------------------------------------------------
 Copyright:      Radig Ulrich  mailto: mail@ulrichradig.de
 Author:         Radig Ulrich
 Remarks:        
 known Problems: none
 Version:        17.10.2008
 Description:    RS232 Routinen

 Dieses Programm ist freie Software. Sie können es unter den Bedingungen der 
 GNU General Public License, wie von der Free Software Foundation veröffentlicht, 
 weitergeben und/oder modifizieren, entweder gemäß Version 2 der Lizenz oder 
 (nach Ihrer Option) jeder späteren Version. 

 Die Veröffentlichung dieses Programms erfolgt in der Hoffnung, 
 daß es Ihnen von Nutzen sein wird, aber OHNE IRGENDEINE GARANTIE, 
 sogar ohne die implizite Garantie der MARKTREIFE oder der VERWENDBARKEIT 
 FÜR EINEN BESTIMMTEN ZWECK. Details finden Sie in der GNU General Public License. 

 Sie sollten eine Kopie der GNU General Public License zusammen mit diesem 
 Programm erhalten haben. 
 Falls nicht, schreiben Sie an die Free Software Foundation, 
 Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA. 
------------------------------------------------------------------------------*/

#ifndef _UART_H
	#define _UART_H

#define BUFFER_SIZE	50

volatile unsigned char buffercounter;
char usart_rx_buffer[BUFFER_SIZE];
unsigned char rx_check;
volatile unsigned char get_char;

struct {
		volatile unsigned char usart_ready:1;
		volatile unsigned char usart_rx_ovl:1;
		}usart_status ;
		
//----------------------------------------------------------------------------
	
	#include <avr/interrupt.h>
	#include <avr/pgmspace.h>
	#include <stdlib.h>
	#include <stdarg.h>
	#include <ctype.h>
	#include <string.h>
	#include <avr/io.h>

//----------------------------------------------------------------------------

//Der Quarz auf dem Experimentierboard
#ifndef SYSCLK
		#define SYSCLK 14745600UL
#endif //SYSCLK	
	
	#if defined (__AVR_ATmega8__)
		#define USR UCSRA
		#define UCR UCSRB
		#define UBRR UBRRL
        #define USART_RX USART_RXC_vect 
	#endif
	
void usart_init(unsigned long baudrate); 
void usart_write_char(char c);
void usart_write_str(char *str);
	
void usart_write_P (const char *Buffer,...);
#define usart_write(format, args...)   usart_write_P(PSTR(format) , ## args)
	
//----------------------------------------------------------------------------

#endif //_UART_H

