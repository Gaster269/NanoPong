#ifndef max7219_h
#define max7219_h

#include "nanolib.h"

typedef enum e_max7219_command {
  MAX7219_NOOP = 0x00,
  MAX7219_COLUMN0 = 0x01,
  MAX7219_COLUMN1 = 0x02,
  MAX7219_COLUMN2 = 0x03,
  MAX7219_COLUMN3 = 0x04,
  MAX7219_COLUMN4 = 0x05,
  MAX7219_COLUMN5 = 0x06,
  MAX7219_COLUMN6 = 0x07,
  MAX7219_COLUMN7 = 0x08,
  MAX7219_DECODE = 0x09,
  MAX7219_INTENSITY = 0x0a,
  MAX7219_SCAN_LIMIT = 0x0b,
  MAX7219_SHUTDOWN = 0x0c,
  MAX7219_DISPLAY_TEST = 0x0d
} t_max7219_command;

/**
 * @brief Initializes the SPI connection to the MAX7219 device. Disables
 * shutdown, test and decode mode. Sets scan limit to 8.
 */
void init_MAX7219();

/**
 * @brief Sets the brightness.
 *
 * @param brightness The brightness amount (from 0 to 16).
 */
void set_brightness_MAX7219(uint8_t brightness);

/**
 * @brief Resets the led matrix.
 */
void clear_MAX7219();

/**
 * @brief Writes the led matrix.
 *
 * @param matrix An array of 8 bytes. Each bytes represents a column. Each bit
 * represents a led in the column.
 */
void write_MAX7219(uint8_t matrix[8]);

/**
 * @brief Writes a single column.
 * 
 * @param column The column to be written.
 * @param leds The leds to write.
 */
void write_column_MAX7219(uint8_t column, uint8_t leds);

#endif