#include "gpio.h"

static const t_nano_port port_list[] = {
    {&PINB, &PORTB, &DDRB}, {&PINC, &PORTC, &DDRC}, {&PIND, &PORTD, &DDRD}};

static const t_pin_port_map pin_port_map[] = {
    {D, 0}, {D, 1}, {D, 2}, {D, 3}, {D, 4}, {D, 5}, {D, 6},
    {D, 7}, {B, 0}, {B, 1}, {B, 2}, {B, 3}, {B, 4}, {B, 5},
    {C, 0}, {C, 1}, {C, 2}, {C, 3}, {C, 4}, {C, 5}};

void init_input_GPIO(t_nano_pin pin, t_input_mode mode) {
  if (pin == A6 || pin == A7) {
    return;
  }
  t_pin_port_map mapped_port = pin_port_map[pin];
  *port_list[mapped_port.port_id].ddrx &= ~_BV(mapped_port.bit);
  *port_list[mapped_port.port_id].portx |= _BV(mapped_port.bit) & (mode << mapped_port.bit);
}

void init_output_GPIO(t_nano_pin pin) {
  if (pin == A6 || pin == A7) {
    return;
  }
  t_pin_port_map mapped_port = pin_port_map[pin];
  *port_list[mapped_port.port_id].ddrx |= _BV(mapped_port.bit);
}

t_pin_state read_input_GPIO(t_nano_pin pin) {
  t_pin_port_map mapped_port = pin_port_map[pin];
  return (*port_list[mapped_port.port_id].pinx & _BV(mapped_port.bit)) >> mapped_port.bit;
}

void write_output_GPIO(t_nano_pin pin, t_pin_state state) {
  t_pin_port_map mapped_port = pin_port_map[pin];

  if (state == LOW) {
    *port_list[mapped_port.port_id].portx &= ~_BV(mapped_port.bit);
  } else {
    *port_list[mapped_port.port_id].portx |= _BV(mapped_port.bit);
  }
}