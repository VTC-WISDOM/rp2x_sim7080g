
bool sim7080g_cn_activate(sim7080g_inst_t sim, uint pdpidx, uint active) {
  
  uint8_t _cmd[128] = {0}; //command to send
  uint8_t _exp[128] = {0}; //expected response
  uint8_t _buf[128] = {0}; //received response buffer


  sprintf(_cmd, "+CPIN?");
  printf("%s", _cmd);
  sim7080g_send_at_command(sim, _cmd);
  while(!sim7080g_get_response(sim, _buf, sizeof(_buf))) sleep_ms(1);
  printf("%s", _buf);
  
  sprintf(_cmd, "+CNACT=%u,%u",pdpidx, active);
  printf("%s", _cmd);
  sim7080g_send_at_command(sim, _cmd);
  while(!sim7080g_get_response(sim, _buf, sizeof(_buf))) sleep_ms(1);
  printf("%s", _buf);

}

bool sim7080g_cn_get_status(sim7080g_inst_t sim, uint available, uint active) {
  
}

bool sim7080g_sim_get_status() {
  
}
