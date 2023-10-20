#include "spi.h"

#define SS 2
#define MOSI 3
#define MISO 4
#define SCK 5

/**
 * @brief Initializes the SPI peripheral as master using the default pins
 * (SS: PB2, MOSI: PB3, MISO: PB4, SCK: PB5).
 *
 * @param mode The spi mode.
 * @param data_order The data order.
 * @param prescaler The prescaler selection.
 */
void init_master_SPI(t_spi_mode mode, t_spi_data_order data_order, t_spi_prescaler prescaler)
{
  DDRB |= _BV(SS) | _BV(MOSI) | _BV(SCK);
  // init_output_GPIO(PB2);
  // init_output_GPIO(PB3);
  // init_output_GPIO(PB5);
  init_input_GPIO(PB4, NO_PULLUP);

  SPCR = 0;
  SPCR |= _BV(MSTR);
  SPCR |= _BV(DORD) & (data_order << DORD);
  SPCR |= (prescaler & 0x07);
  
  if (mode == SPI_MODE_2 || mode == SPI_MODE_3)
    SPCR |= _BV(CPOL);

  if (mode == SPI_MODE_1 || mode == SPI_MODE_3)
    SPCR |= _BV(CPHA);
    
  if (prescaler == SPI_PRESCALER_2 || prescaler == SPI_PRESCALER_8 || prescaler == SPI_PRESCALER_16) 
    SPSR |= _BV(SPI2X);
  
  if (prescaler == SPI_PRESCALER_16 || prescaler == SPI_PRESCALER_8 || prescaler == SPI_PRESCALER_128)
    SPCR |= _BV(SPR0);

  if (prescaler == SPI_PRESCALER_32 || prescaler == SPI_PRESCALER_64 || prescaler == SPI_PRESCALER_128)
    SPCR |= _BV(SPR1);

  SPCR |= _BV(SPE);
}

void transfer_n_SPI(uint8_t send_bytes[], uint8_t receive_bytes[], uint8_t n)
{
  uint8_t i;
  PORTB &= ~_BV(SS);

  for (i = 0; i < n; i++) 
  {
    SPDR = send_bytes[i];
    loop_until_bit_is_set(SPSR, SPIF);
    if (receive_bytes) 
      receive_bytes[i] = SPDR;
  }

  PORTB |= _BV(SS);
}