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


// -- rp2x_sim7080g.c -- 
//helpers to format and send commands
//and to grab responses and just return a simple string
bool sim7080g_get_response(sim7080g_inst_t sim, uint8_t *dst, size_t len);
bool sim7080g_send_at_command(sim7080g_inst_t sim, const uint8_t *command); 
//initialize the uart and gpio stuff
void sim7080g_init(sim7080g_inst_t sim);


// -- rp2x_sim7080g_power.c --
//full restart the device - takes ~15 seconds
bool sim7080g_start(sim7080g_inst_t sim);
//power commands when we already know the state of the device
bool sim7080g_power_off(sim7080g_inst_t sim);
bool sim7080g_power_on(sim7080g_inst_t sim);



// -- rp2x_sim7080g_config.c
//config - set all of the important settings in the chip
bool sim7080g_config(sim7080g_inst_t sim, sim7080g_config_t config);
//specifically the pdp stuff - instance id, apn, ip settings
bool sim7080g_pdp_config(sim7080g_inst_t sim, sim7080g_pdp_inst_t pdp_inst);

// -- rp2x_sim7080g_cell.c
bool sim7080g_cn_activate(sim7080g_inst_t sim, uint pdpidx, uint active);



// -- rp2x_sim7080g_tcp.c
//open tcp connection

// -- rp2x_sim7080g_mqtt.c
bool sim7080g_mqtt_config(sim7080g_inst_t sim, sim7080g_mqtt_config_t config);
 
// -- rp2x_sim7080g_gnss.c
//gnss

#endif // WISDOM_MODEM_H
