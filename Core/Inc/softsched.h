#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "ringbuf_spsc.h"

typedef enum { SCHED_HIGH=0, SCHED_MED=1, SCHED_LOW=2 } sched_prio_t;

#ifdef __cplusplus
extern "C" {
#endif

void SoftSched_Init(void);
bool SoftSched_PostFromISR(sched_prio_t p, work_fn_t fn, uintptr_t arg);
void SoftSched_TriggerPendSV(void);
void SoftSched_RunOnce(void);

#ifdef __cplusplus
}
#endif

