#include "time.h"

static volatile uint32_t time = 0;

ISR(TIMER0_COMPA_vect) { ++time; }

void init_time() {
  // Timer 0 in CTC mode
  TCCR0A |= _BV(WGM01);
  // Timer 0 prescaler /64
  TCCR0B |= _BV(CS01) | _BV(CS00);
  // Timer 0 output compare A: 249 (=1khz)
  OCR0A = 249;
  // Enable timer 0 output compare A interrupt
  TIMSK0 |= _BV(OCIE0A);
}

uint32_t get_time() {
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    uint32_t now = time;
    return now;
  }
}
