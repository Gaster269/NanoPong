#ifndef spi_h
#define spi_h

#include "nanolib.h"

typedef enum e_spi_mode {
  SPI_MODE_0,
  SPI_MODE_1,
  SPI_MODE_2,
  SPI_MODE_3
} t_spi_mode;

typedef enum e_spi_data_order { SPI_MSB_FIRST, SPI_LSB_FIRST } t_spi_data_order;

typedef enum e_spi_prescaler {
  SPI_PRESCALER_2,
  SPI_PRESCALER_4,
  SPI_PRESCALER_8,
  SPI_PRESCALER_16,
  SPI_PRESCALER_32,
  SPI_PRESCALER_64,
  SPI_PRESCALER_128
} t_spi_prescaler;

/**
 * @brief Initializes the SPI peripheral as master using the default pins
 * (SS: PB2, MOSI: PB3, MISO: PB4, SCK: PB5).
 *
 * @param mode The spi mode.
 * @param data_order The data order.
 * @param prescaler The prescaler selection.
 */
void init_master_SPI(t_spi_mode mode, t_spi_data_order data_order,
                     t_spi_prescaler prescaler);

/**
 * @brief Sends and receives n bytes through SPI.
 *
 * @param send_bytes An array of bytes to send in order.
 * @param receive_bytes An array of bytes received in order.
 * @param n The number of bytes to send/receive.
 */
void transfer_n_SPI(uint8_t send_bytes[], uint8_t receive_bytes[], uint8_t n);

#endif