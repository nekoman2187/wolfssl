

#ifndef BISM_LOG_H
#define BISM_LOG_H

typedef struct bism_log_t_d {
  uint32_t len;
  uint8_t dat[1+1+4+8+22];
} bism_log;

void bism_init(uint8_t* log_file);
void bism_close();
int8_t bism_set_event(bism_log *blog, uint32_t bevent_cls, ...);
void bism_write(bism_log *blog);
void bism_push();
#define bism_get_time eptpc_get_clock
#endif
