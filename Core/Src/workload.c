#include "workload.h"
#include "dwt_cycle.h"
#include "isr_latency.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>

// NOTE: keep these bottom-half functions reasonably short; heavy math/logging can live here.
// You can add ring buffers & a non-blocking UART writer for logs.

void w_ctrl_tick(uintptr_t arg) {
  (void)arg;
  // Example: control math / PID; keep deterministic
  // For demo, do nothing. Measure jitter via TIM1 ISR toggle on PA5.
}

void w_uart_rx_frame(uintptr_t arg) {
  (void)arg;
  // Parse RX frame here (we'll compute length at IDLE in ISR and pass as arg if desired)
}

void w_log_flush(uintptr_t arg) {
  (void)arg;
  // Flush buffered logs at 1kHz (avoid blocking)
}

