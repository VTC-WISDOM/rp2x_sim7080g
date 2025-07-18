#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "hardware/gpio.h"

#include "rp2x_sim7080g.h"

bool sim7080g_uart_write(sim7080g_inst_t sim, const uint8_t *buf, size_t len) {

  bool status = 0;
  
  for(int written = 0; written < len; written++) {
    if(!uart_is_writable(sim.uart)) break;
    uart_write_blocking(sim.uart, buf++, 1);
    if(written == len - 1) {
      uart_write_blocking(sim.uart, "\r", 1);
      status = 1;
      }
  }

return status;
}

bool sim7080g_send_at_command(sim7080g_inst_t sim, const uint8_t *command) {

  bool status = 0;
  
  uint8_t atcommand[AT_MAX_BUFFER_SIZE] = "AT";
  strcat(atcommand, command);

/*
  for(int i = 0; i < strlen(atcommand); i++) {
    if(isprint(atcommand[i])) printf("%c", atcommand[i]);
    else if(atcommand[i] == '\r') printf("\\r");
    else if(atcommand[i] == '\n') printf("\\n");
    else printf("\'0x%x\'", atcommand[i]);
  }
  printf("... ");
*/

  int written = 0;
  for(written = 0; written < strlen(atcommand); written++) {
    if(!uart_is_writable(sim.uart)) break;
    uart_putc_raw(sim.uart, atcommand[written]);
    }
    if(written == strlen(atcommand)) status = 1;
    uart_putc_raw(sim.uart, '\r');

  return status;
}


bool sim7080g_get_response(sim7080g_inst_t sim, uint8_t *dst, size_t len) {

  uint index = 0;
  bool status = 0;

  if(!uart_is_readable_within_us(sim.uart, 10000)) return status;

  while(uart_is_readable_within_us(sim.uart, 10000)) {
    if(index >= len) break;
    uart_read_blocking(sim.uart, dst+(index++), 1);
  }
  
  if(dst[0] != '\r') return status;
  if(index <= len && index > 4) status = 1;

  return status;
}

void sim7080g_init(sim7080g_inst_t sim) {
  
  //init gpios and uart
  if(!uart_is_enabled(sim.uart)) uart_init(sim.uart, SIM_UART_BAUD);
  uart_set_hw_flow(sim.uart, 0, 0);
  uart_set_format(sim.uart, 8, 1, UART_PARITY_NONE);
  
  gpio_init(sim.pin_pwr);
  gpio_set_dir(sim.pin_pwr, 0);
  gpio_disable_pulls(sim.pin_pwr);
  
  
  gpio_init(sim.uart_pin_tx);
  gpio_init(sim.uart_pin_rx);
  gpio_set_function(sim.uart_pin_tx, GPIO_FUNC_UART);
  gpio_set_function(sim.uart_pin_rx, GPIO_FUNC_UART);

}

bool sim7080g_start(sim7080g_inst_t sim) {

  bool status = 0;

  //send startup signal
  gpio_set_dir(sim.pin_pwr, 1);
  gpio_put(sim.pin_pwr, 0);
  sleep_ms(15000);
  gpio_set_dir(sim.pin_pwr, 0);


  sleep_ms(5000);

  uint8_t _buf[128] = {0};
  for(int i = 0; i < SIM_START_ATTEMPTS; i++) {
    printf("sim7080g start: %i\n", i);
    sim7080g_send_at_command(sim, "E0");
    if(sim7080g_get_response(sim, _buf, sizeof(_buf))) {
      printf("\n%s\n", _buf);
      status = 1;
      break;
      }
    sleep_ms(1000);
  }

  return status;
}

bool sim7080g_config(sim7080g_inst_t sim, sim7080g_config_t config) {
  uint8_t _cmd[128] = {0}; //command to send
  uint8_t _exp[128] = {0}; //expected response
  uint8_t _buf[128] = {0}; //received response buffer

  sprintf(_cmd, "+CMGD=,4");
  printf("%s", _cmd);
  sim7080g_send_at_command(sim, _cmd);
  while(!sim7080g_get_response(sim, _buf, sizeof(_buf))) sleep_ms(1);
  printf("%s", _buf);
  
  sprintf(_cmd, "+CMEE=%i", config.sim_cmee);
  printf("%s", _cmd);
  sim7080g_send_at_command(sim, _cmd);
  while(!sim7080g_get_response(sim, _buf, sizeof(_buf))) sleep_ms(1);
  printf("%s", _buf);
 
  sprintf(_cmd, "+CMGF=%i", config.sim_cmgf);
  printf("%s", _cmd);
  sim7080g_send_at_command(sim, _cmd);
  while(!sim7080g_get_response(sim, _buf, sizeof(_buf))) sleep_ms(1);
  printf("%s", _buf);
 
  sprintf(_cmd, "+CNMP=%i", config.sim_cnmp);
  printf("%s", _cmd);
  sim7080g_send_at_command(sim, _cmd);
  while(!sim7080g_get_response(sim, _buf, sizeof(_buf))) sleep_ms(1);
  printf("%s", _buf);
 
  sprintf(_cmd, "+CMNB=%i", config.sim_cmnb);
  printf("%s", _cmd);
  sim7080g_send_at_command(sim, _cmd);
  while(!sim7080g_get_response(sim, _buf, sizeof(_buf))) sleep_ms(1);
  printf("%s", _buf);
 
  
  
}


bool sim7080g_power_off(sim7080g_inst_t sim) {
  bool status = 0;
  
  if(!sim7080g_send_at_command(sim, "+CPOWD=1")) return status;

  uint8_t _buf[64] = {0};
  int count = 0;
  while(!sim7080g_get_response(sim, _buf, sizeof(_buf))) {
    if(count++ > SIM_START_ATTEMPTS) return status;
    sleep_ms(1);
  }
  printf("\n%i ms : %s\n", count, _buf);
  uint8_t expected_string[] = "NORMAL POWER DOWN";
  if(strncmp(_buf, expected_string, strlen(expected_string))) status = 1;
  
  return status;
}


bool sim7080g_power_on(sim7080g_inst_t sim) {
  
  bool status = 0;

  //send startup signal
  gpio_set_dir(sim.pin_pwr, 1);
  gpio_put(sim.pin_pwr, 0);
  sleep_ms(1100);
  gpio_set_dir(sim.pin_pwr, 0);

  sleep_ms(2500);
  
  uint8_t _buf[128] = {0};
  for(int i = 0; i < SIM_START_ATTEMPTS; i++) {
    printf("sim7080g start: %i\n", i);
    sim7080g_send_at_command(sim, "E0");
    if(sim7080g_get_response(sim, _buf, sizeof(_buf))) {
      printf("\n%s\n", _buf);
      status = 1;
      break;
      }
    sleep_ms(1000);
  }

  return status;

}


