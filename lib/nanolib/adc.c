#include "adc.h"

void init_pin_ADC(t_nano_pin pin) {
  // Disable the input buffer for enabled analog pins
  if (pin < 14 || pin > 18) {
    return;
  }
  DIDR0 |= _BV(pin - 14);
}

void init_ADC(uint8_t voltage_reference,uint8_t left_adjust, uint8_t interrupt, uint8_t prescaler) {
  // Set the voltage reference and the format adjustment
  ADMUX = (_BV(REFS0) & (voltage_reference << REFS0)) | (_BV(ADLAR) & (left_adjust << ADLAR));
  // Enable the ADC, set the the interrupt and select the prescaling
  ADCSRA = _BV(ADEN) | (_BV(ADIE) & (interrupt << ADIE)) | prescaler;
}

uint16_t analog_read(t_nano_pin pin) {
  // Select the pin
  ADMUX = (ADMUX & 0b11110000) | (pin - 14);
  // Start the conversion and wait for it to finish
  ADCSRA |= _BV(ADSC);
  loop_until_bit_is_clear(ADCSRA, ADSC);
  // Read the value
  uint16_t adc_value;
  if (!bit_is_set(ADMUX, ADLAR)) {
    adc_value = ADC;
  } else {
    adc_value = ADCL >> 6;
    adc_value |= ADCH << 2;
  }
  return adc_value;
}
