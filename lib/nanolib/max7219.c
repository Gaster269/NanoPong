#include "max7219.h"

void init_MAX7219() {
  init_master_SPI(SPI_MODE_0, SPI_MSB_FIRST, SPI_PRESCALER_8);

  uint8_t no_shutdown[] = {MAX7219_SHUTDOWN, 1};
  transfer_n_SPI(no_shutdown, NULL, 2);

  uint8_t no_decode[] = {MAX7219_DECODE, 0};
  transfer_n_SPI(no_decode, NULL, 2);

  uint8_t scan_all[] = {MAX7219_SCAN_LIMIT, 7};
  transfer_n_SPI(scan_all, NULL, 2);

  uint8_t no_test[] = {MAX7219_DISPLAY_TEST, 0};
  transfer_n_SPI(no_test, NULL, 2);
}

void set_brightness_MAX7219(uint8_t brightness) {
  uint8_t set_brightness[] = {MAX7219_INTENSITY, brightness};
  transfer_n_SPI(set_brightness, NULL, 2);
}

void clear_MAX7219() {
  for (uint8_t i = 1; i <= 8; i++) {
    uint8_t clear_column[] = {i, 0};
    transfer_n_SPI(clear_column, NULL, 2);
  }
}

void write_MAX7219(uint8_t matrix[]) {
  for (uint8_t i = 1; i <= 8; i++) {
    uint8_t set_column[] = {i, matrix[i-1]};
    transfer_n_SPI(set_column, NULL, 2);
  }
}

void write_column_MAX7219(uint8_t column, uint8_t leds) {
    uint8_t set_column[] = {column, leds};
    transfer_n_SPI(set_column, NULL, 2);
}