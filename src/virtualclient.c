/***************************************************
 * virtualclient.c
 * Created on Sun, 22 Oct 2017 19:31:13 +0000 by vladimir
 *
 * $Author$
 * $Rev$
 * $Date$
 ***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common/signal.h"
#include "common/subscription.h"
#include "common/ringbuffer.h"
#include "client/client.h"
#include "client/signalhelper.h"

void event_update_signal(struct signal_s *signal, int value, struct execution_context_s *ctx) {
  printf("*** EVENT HANDLER: Signal %s updating from value %d to value %d\n", signal->s_name, signal->s_value, value);
  if(value == 20) {
    post_unsubscribe_command(ctx, "dev.485.rsrs2.sound2_ledms", SUB_UPDATE);
  }
}

void event_write_signal(struct signal_s *signal, int value, struct execution_context_s *ctx) {
  printf("*** EVENT HANDLER: Writing value %d to signal %s\n", value, signal->s_name);
  post_update_command(ctx, "dev.485.rsrs2.sound2_ledms", value);
}

void client_init(struct execution_context_s *ctx) {
  get_and_subscribe(&ctx->signals, ctx->hash, "dev.485", ctx->socket, SUB_WRITE);
  subscribe(&ctx->signals, ctx->hash, "dev.485", ctx->socket, SUB_UPDATE);
  ctx->clientstate = NULL;
  printf("Client initialized\n");
}

void client_thread_proc(struct execution_context_s *ctx) {
  printf("Started proc thread\n");
  while(ctx->running) {
    int val = signal_get(ctx, "dev.485.rsrs2.sound2_ledms");
    post_write_command(ctx, "dev.485.rsrs2.sound2_ledms", val + 1);
    post_process(ctx);
    usleep(500000);
  }
}
