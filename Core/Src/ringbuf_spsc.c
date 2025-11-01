#include "ringbuf_spsc.h"

#define RB_MASK (RB_CAP - 1)

bool rb_push_isr(ringbuf_spsc_t* rb, work_item_t w) {
  uint16_t h = rb->head;
  uint16_t n = (h + 1) & RB_MASK;
  if (n == rb->tail) return false;   // full
  rb->buf[h] = w;
  rb->head = n;                      // publish
  return true;
}

bool rb_pop(ringbuf_spsc_t* rb, work_item_t* out) {
  uint16_t t = rb->tail;
  if (t == rb->head) return false;   // empty
  *out = rb->buf[t];
  rb->tail = (t + 1) & RB_MASK;
  return true;
}

bool rb_is_empty(ringbuf_spsc_t* rb) {
  return rb->head == rb->tail;
}

