#ifndef WISDOM_MODEM_H
#define WISDOM_MODEM_H
#include <stdbool.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "sim7080g_defs.h"

#define SIM_UART_BAUD 115200
#define AT_MAX_BUFFER_SIZE (562)
#define SIM_UART_TIMEOUT_US 5000
#define SIM_RESET_PIN_MS 12600
#define SIM_START_ATTEMPTS 16


//all functions return 1 for OK and 0 for any error

bool sim7080g_get_response(sim7080g_inst_t sim, uint8_t *dst, size_t len);
bool sim7080g_send_at_command(sim7080g_inst_t sim, const uint8_t *command); 

//initialize the uart and gpio stuff
//and also send the start command (pwrkey)
//*the module will not be ready for 15 seconds*
bool sim7080g_start(sim7080g_inst_t sim);

//check if the device responds to commands 1 for yes 0 for no
bool sim7080g_is_active(sim7080g_inst_t sim);

bool sim7080g_config(sim7080g_inst_t sim, sim7080g_config_t config);

bool sim7080g_power_off(sim7080g_inst_t sim);

#endif // WISDOM_MODEM_H
