#include "softsched.h"
#include "stm32f4xx.h"

static ringbuf_spsc_t q_high, q_med, q_low;

static inline ringbuf_spsc_t* selq(sched_prio_t p) {
  switch (p) { case SCHED_HIGH: return &q_high; case SCHED_MED: return &q_med; default: return &q_low; }
}

void SoftSched_Init(void) {
  q_high.head = q_high.tail = 0;
  q_med.head  = q_med.tail  = 0;
  q_low.head  = q_low.tail  = 0;
  // Make PendSV lowest preempt priority
  NVIC_SetPriority(PendSV_IRQn, 15);
}

bool SoftSched_PostFromISR(sched_prio_t p, work_fn_t fn, uintptr_t arg) {
  work_item_t w = { .fn = fn, .arg = arg, .prio = (uint8_t)p };
  bool ok = rb_push_isr(selq(p), w);
  if (ok) SoftSched_TriggerPendSV();
  return ok;
}

void SoftSched_TriggerPendSV(void) {
  SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
}

void SoftSched_RunOnce(void) {
  work_item_t w;
  if (rb_pop(&q_high, &w) || rb_pop(&q_med, &w) || rb_pop(&q_low, &w)) {
    w.fn(w.arg);
    if (!rb_is_empty(&q_high) || !rb_is_empty(&q_med) || !rb_is_empty(&q_low)) {
      SoftSched_TriggerPendSV();
    }
  }
}

// Hook PendSV (put this in an IRQ file if you prefer; function name must be global)
void PendSV_Handler(void) {
  SoftSched_RunOnce();
}

