#pragma once
#include <stdint.h>
#include <stdbool.h>

#ifndef RB_CAP
#define RB_CAP 128  // power of 2
#endif

typedef void (*work_fn_t)(uintptr_t arg);

typedef struct {
  work_fn_t fn;
  uintptr_t arg;
  uint8_t   prio; // 0=high,1=med,2=low
} work_item_t;

typedef struct {
  volatile uint16_t head;
  volatile uint16_t tail;
  work_item_t buf[RB_CAP];
} ringbuf_spsc_t;

bool rb_push_isr(ringbuf_spsc_t* rb, work_item_t w);
bool rb_pop(ringbuf_spsc_t* rb, work_item_t* out);
bool rb_is_empty(ringbuf_spsc_t* rb);

