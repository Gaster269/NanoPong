#include "usart0.h"

int putchar_block_USART0(char c, FILE *stream) {
  // Wait until the data register is available for transmission
  loop_until_bit_is_set(UCSR0A, UDRE0);
  // Write the char to the data register
  UDR0 = c;
  return 0;
}

FILE *init_block_USART0() {
  // Set baud rate
  UBRR0L = UBRRL_VALUE;
  UBRR0H = UBRRH_VALUE;
  // Frame format: 8 data bits, no parity, 1 stop bit
  UCSR0C |= _BV(UCSZ01) | _BV(UCSZ00);
  // Enable transmission and reception
  UCSR0B |= _BV(TXEN0);
  // return fdevopen(putchar_block_USART0, getchar_block_USART0);
  return fdevopen(putchar_block_USART0, NULL);
}
