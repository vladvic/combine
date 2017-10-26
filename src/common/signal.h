/***************************************************
 * signal.h
 * Created on Thu, 19 Oct 2017 10:37:25 +0000 by vladimir
 *
 * $Author$
 * $Rev$
 * $Date$
 ***************************************************/
#ifndef SIGNAL_H_
#define SIGNAL_H_

#include <sys/types.h>

struct device_s {
  int d_type;
  int d_mb_id;
};

struct device_reg_s {
  int dr_type;
  int dr_addr;
  int dr_bit;
  struct device_s dr_device;
};

struct signal_s {
  int s_id;
  char *s_name;
  int s_value;
  int s_rw;
  struct device_reg_s s_register;
  struct signal_s *next;
};

int str_to_signal(char *str, struct signal_s *signal);
int signal_to_str(struct signal_s *signal, char *str, size_t buflen);
void print_signal(struct signal_s *signal);

#endif
