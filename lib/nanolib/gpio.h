#ifndef gpio_h
#define gpio_h

#include "nanolib.h"

typedef struct s_nano_port {
    volatile uint8_t *pinx;
    volatile uint8_t *portx;
    volatile uint8_t *ddrx;
} t_nano_port;

typedef enum e_port_id {
    B,
    C,
    D
} t_port_id;

typedef struct s_pin_port_map {
    t_port_id port_id;
    uint8_t bit;
} t_pin_port_map;


typedef enum e_input_mode { NO_PULLUP, PULLUP } t_input_mode;

typedef enum e_pin_state {LOW, HIGH} t_pin_state;

void init_input_GPIO(t_nano_pin pin, t_input_mode mode);
void init_output_GPIO(t_nano_pin pin);

t_pin_state read_input_GPIO(t_nano_pin pin);
void write_output_GPIO(t_nano_pin pin, t_pin_state state);

#endif