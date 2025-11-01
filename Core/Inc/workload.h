#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void w_ctrl_tick(uintptr_t arg);     // high-priority (TIM1)
void w_uart_rx_frame(uintptr_t arg); // medium (USART2 IDLE)
void w_log_flush(uintptr_t arg);     // low (TIM6)

#ifdef __cplusplus
}
#endif

