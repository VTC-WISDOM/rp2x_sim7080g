

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


