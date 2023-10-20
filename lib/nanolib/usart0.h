#ifndef usart0_h
#define usart0_h

#ifndef BAUD
#define BAUD 9600
#endif

#include <util/setbaud.h>
#include "nanolib.h"

int putchar_block_USART0(char c, FILE *stream);
FILE *init_block_USART0();

#endif