#include "dwt_cycle.h"
#include "core_cm4.h"

void DWT_CycleCounterInit(void) {
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  // Some cores gate write; unlock if present (harmless if not)
  if ((*(volatile uint32_t*)0xE0001FB0) == 0) {
    // do nothing; LAR not implemented on F4
  }
  DWT->CYCCNT = 0;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

uint32_t DWT_GetCycles(void) {
  return DWT->CYCCNT;
}

