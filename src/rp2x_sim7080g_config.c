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
