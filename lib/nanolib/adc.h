#ifndef adc_h
#define adc_h

#include "nanolib.h"

// ADC voltage references
#define ADC_AREF 0
#define ADC_AVCC 1

// ADC adjustment
#define ADC_RIGHT_ADJUST 0
#define ADC_LEFT_ADJUST 1

// ADC interrupt enable
#define ADC_NO_INTERRUPT 0
#define ADC_INTERRUPT 1

// ADC prescaler
#define ADC_PRESCALER_2 1
#define ADC_PRESCALER_4 2
#define ADC_PRESCALER_8 3
#define ADC_PRESCALER_16 4
#define ADC_PRESCALER_32 5
#define ADC_PRESCALER_64 6
#define ADC_PRESCALER_128 7

/**
 * @brief Initializes a pin for ADC use by disabling its corresponding DIDR bit.
 * 
 * @param pin 
 */
void init_pin_ADC(t_nano_pin pin);

/**
 * @brief Initializes the ADC.
 *
 * @param voltage_reference
 * @param left_adjust
 * @param interrupt
 * @param prescaler
 *
 * @example init_ADC(ADC_AREF, ADC_RIGHT_ADJUST,
 * ADC_NO_INTERRUPT, ADC_PRESCALER_8);
 * @note Enables the ADC, set the ADC to right adjust, disables interrupt mode
 * and sets the prescaler to /8
 */
void init_ADC(uint8_t voltage_reference, uint8_t left_adjust, uint8_t interrupt, uint8_t prescaler);

/**
 * @brief Reads an analog pin.
 *
 * @param pin
 *
 * @example uint16_t value = analog_read(A0);
 */
uint16_t analog_read(t_nano_pin pin);

#endif