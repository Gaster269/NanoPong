#ifndef time_h
#define time_h

#include "nanolib.h"

// Initializes timer0 to fire an interrupt service routine every 1kHz
// The ISR should increment a variable counting the number of milliseconds since startup
// Note: You should enable the global interrupt bit: 
void init_time();

// Returns the current number of ellapsed milliseconds in an atomic way.
uint32_t get_time();

#endif