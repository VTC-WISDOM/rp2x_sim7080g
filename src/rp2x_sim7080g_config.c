

bool sim7080g_config(sim7080g_inst_t sim, sim7080g_config_t config) {

  uint8_t _cmd[128] = {0}; //command to send
  uint8_t _exp[128] = {0}; //expected response
  uint8_t _buf[128] = {0}; //received response buffer

  //delete sms buffer
  sprintf(_cmd, "+CMGD=,4");
  printf("%s", _cmd);
  sim7080g_send_at_command(sim, _cmd);
  while(!sim7080g_get_response(sim, _buf, sizeof(_buf))) sleep_ms(1);
  printf("%s", _buf);

  //error mode
  sprintf(_cmd, "+CMEE=%i", config.sim_cmee);
  printf("%s", _cmd);
  sim7080g_send_at_command(sim, _cmd);
  while(!sim7080g_get_response(sim, _buf, sizeof(_buf))) sleep_ms(1);
  printf("%s", _buf);

  //sms format
  sprintf(_cmd, "+CMGF=%i", config.sim_cmgf);
  printf("%s", _cmd);
  sim7080g_send_at_command(sim, _cmd);
  while(!sim7080g_get_response(sim, _buf, sizeof(_buf))) sleep_ms(1);
  printf("%s", _buf);

  //cell mode selection
  sprintf(_cmd, "+CNMP=%i", config.sim_cnmp);
  printf("%s", _cmd);
  sim7080g_send_at_command(sim, _cmd);
  while(!sim7080g_get_response(sim, _buf, sizeof(_buf))) sleep_ms(1);
  printf("%s", _buf);

  //cat-m/nb-iot selection
  sprintf(_cmd, "+CMNB=%i", config.sim_cmnb);
  printf("%s", _cmd);
  sim7080g_send_at_command(sim, _cmd);
  while(!sim7080g_get_response(sim, _buf, sizeof(_buf))) sleep_ms(1);
  printf("%s", _buf);

  sleep_ms(10);
  //phone functionality mode
  sprintf(_cmd, "+CFUN=%i", config.sim_cfun);
  printf("%s", _cmd);
  sim7080g_send_at_command(sim, _cmd);
  while(!sim7080g_get_response(sim, _buf, sizeof(_buf))) sleep_ms(1);
  printf("%s", _buf);

  sleep_ms(10);
  //operator selection mode
  sprintf(_cmd, "+COPS=%i", config.sim_cops_mode);
  printf("%s", _cmd);
  sim7080g_send_at_command(sim, _cmd);
  while(!sim7080g_get_response(sim, _buf, sizeof(_buf))) sleep_ms(1);
  printf("%s", _buf);

  sleep_ms(10);
  //network registration unsolicited result codes
  sprintf(_cmd, "+CGREG=%i", config.sim_cgreg);
  printf("%s", _cmd);
  sim7080g_send_at_command(sim, _cmd);
  while(!sim7080g_get_response(sim, _buf, sizeof(_buf))) sleep_ms(1);
  printf("%s", _buf);

  
}

bool sim7080g_pdp_config(sim7080g_inst_t sim, sim7080g_pdp_inst_t pdp_inst) {

  uint8_t _cmd[128] = {0}; //command to send
  uint8_t _exp[128] = {0}; //expected response
  uint8_t _buf[128] = {0}; //received response buffer

  //full pdp config with apn and ip settings
  sprintf(_cmd, "+CGDCONT=%i,\"%s\",\"%s\"", pdp_inst.cid, pdp_inst.pdp_type, pdp_inst.apn);
  printf("%s", _cmd);
  sim7080g_send_at_command(sim, _cmd);
  while(!sim7080g_get_response(sim, _buf, sizeof(_buf))) sleep_ms(1);
  printf("%s", _buf);

}

bool sim7080g_pdp_inst_activate(sim7080g_inst_t sim, uint cid, uint active) {
  
  uint8_t _cmd[128] = {0}; //command to send
  uint8_t _exp[128] = {0}; //expected response
  uint8_t _buf[128] = {0}; //received response buffer

  sprintf(_cmd, "+CGACT=%u,%u", active, cid);
  printf("%s", _cmd);
  sim7080g_send_at_command(sim, _cmd);
  while(!sim7080g_get_response(sim, _buf, sizeof(_buf))) sleep_ms(1);
  printf("%s", _buf);
}
