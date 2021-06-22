/*
 * myUART.h
 *
 *  Created on: May 18, 2021
 *      Author: NgTP
 */

#ifndef INC_MYUART_H_
#define INC_MYUART_H_

void UART_Configure(void);

void UART_SendChar (uint8_t c);

void UART_SendString (char *String);

uint8_t UART_GetChar (void);

void USART2_IRQHandler();


#endif /* INC_MYUART_H_ */
