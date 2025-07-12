//error format
enum CMEE {
  cmee_disable = 0,
  cmee_numeric = 1,
  cmee_vverbose = 2
};

//sms format
enum CMGF {
  cmgf_pdu = 0,
  cmgf_txt = 1
};

//preferred mode selection
enum CNMP {
  cnmp_auto = 2,
  cnmp_gsm = 13,
  cnmp_lte = 38,
  cnmp_gsm_lte = 51
};

enum CMNB {
  cmnb_catm = 1,
  cmnb_nbiot = 2,
  cmnb_both = 3
};

typedef struct _sim7080g_inst_t {
  uart_inst_t *uart;
  uint uart_pin_tx;
  uint uart_pin_rx;
  uint pin_pwr;
} sim7080g_inst_t;

typedef struct _sim7080g_config_t {
  const char *apn;
  uint sim_cmee;
  uint sim_cmgf;
  uint sim_cnmp;
  uint sim_cmnb;
} sim7080g_config_t;
