//error format
enum CMEE {
  cmee_disable = 0,
  cmee_numeric = 1,
  cmee_verbose = 2
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

enum CFUN {
  cfun_minimum = 0,
  cfun_full = 1,
  cfun_disable_phone = 4,
  cfun_factory_test = 5,
  cfun_reset = 6,
  cfun_offline = 7
};

enum COPS_MODE {
  cops_mode_auto = 0,
  cops_mode_manual = 1,
  cops_mode_manual_deregister = 2,
  cops_mode_set_format = 3,
  cops_mode_manual_auto = 4
};

enum CGREG_N {
  cgreg_disable_unsolicited = 0,
  cgreg_enable_unsolicited = 1,
  cgreg_enable_gprs_rau = 4
};

//ip modes
#define CGDCONT_IP "IP",
#define CGDCONT_IPV6 "IPV6"
#define CGDCONT_IPV4V6 "IPV4V6"
#define CGDCONT_NONIP "Non-IP"

typedef struct _sim7080g_inst_t {
  uart_inst_t *uart;
  uint uart_pin_tx;
  uint uart_pin_rx;
  uint pin_pwr;
} sim7080g_inst_t;

typedef struct _sim7080g_config_t {
  const char *apn;
  const char *cgdcont_pdp_type;
  uint sim_cmee;
  uint sim_cmgf;
  uint sim_cnmp;
  uint sim_cmnb;
  uint sim_cfun;
  uint sim_cops_mode;
  uint sim_cgreg;
} sim7080g_config_t;
