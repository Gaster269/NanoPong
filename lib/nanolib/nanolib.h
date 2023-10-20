#ifndef NANOLIB_H
#define NANOLIB_H

#include <stdbool.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <stdlib.h>

typedef enum e_nano_pin_id {
  D0,
  D1,
  D2,
  D3,
  D4,
  D5,
  D6,
  D7,
  D8,
  D9,
  D10,
  D11,
  D12,
  D13,
  A0,
  A1,
  A2,
  A3,
  A4,
  A5,
  A6,
  A7
} t_nano_pin;

#include "gpio.h"
#include "adc.h"
#include "usart0.h"
#include "spi.h"
#include "max7219.h"
#include "time.h"

#define set_bit(byte, bit) (byte |= _BV(bit))
#define clear_bit(byte, bit) (byte &= ~_BV(bit))
#define toggle_bit(byte, bit) (byte ^= _BV(bit))

#endif
