#ifndef USART_H
#define USART_H

#include <STC32G.H>
#include <stdio.h>

void UartInit(void);
void SendByte(unsigned char dat);
char putchar(char character_string);
#endif
