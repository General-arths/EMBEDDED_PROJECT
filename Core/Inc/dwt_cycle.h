#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void     DWT_CycleCounterInit(void);
uint32_t DWT_GetCycles(void);

#ifdef __cplusplus
}
#endif

