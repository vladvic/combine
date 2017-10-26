/***************************************************
 * mbclient.h
 * Created on Tue, 24 Oct 2017 05:57:58 +0000 by vladimir
 *
 * $Author$
 * $Rev$
 * $Date$
 ***************************************************/
#ifndef MBCLIENT_H_
#define MBCLIENT_H_

#include <stdint.h>
#include "common/signal.h"

#define MAX_REG 50
#define MAX_DEVS 256

struct mb_signal_list_s {
  struct signal_s *signal;
  struct mb_signal_list_s *next;
};

struct mb_reg_write_request_s {
  struct mb_device_reg_s *reg;
  uint16_t write_value;
  uint16_t write_mask;
  uint16_t dev_id;
  uint16_t reg_id;
  struct mb_reg_write_request_s *next;
};

struct mb_device_reg_s {
  uint16_t value;
  uint16_t write_value;
  uint16_t write_mask;
  struct mb_signal_list_s *signals;
};

struct mb_device_s {
  int    mb_id;
  int    mb_reg_max;
  int    needs_sync;
  struct mb_device_reg_s reg[MAX_REG];
};

struct mb_device_list_s {
  void   *mb_context;
  int    (*mb_read_device)(struct mb_device_list_s *ctx, int mb_id, int reg);
  int    (*mb_write_device)(struct mb_device_list_s *ctx, int mb_id, int reg, int value);
  struct mb_device_s device[MAX_DEVS];
  int    dev_max;
  pthread_mutex_t mutex;
  struct mb_reg_write_request_s *writes;
};

void mb_dev_list_init(struct mb_device_list_s *dlist);
int  mb_dev_add_signal(struct mb_device_list_s *dlist, struct signal_s *signal);
void mb_dev_add_write_request(struct mb_device_list_s *dlist, struct signal_s *signal, int value);
int  mb_dev_update(struct mb_device_list_s *dlist);
int  mb_dev_check_signal(struct mb_device_list_s *dlist, struct signal_s *signal);

#endif
