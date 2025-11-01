#pragma once
#include "stm32f4xx_hal.h"
#include "board_pins.h"

// Ultra-fast set/reset using BSRR (atomic)
#define LAT_HIGH() (LAT_GPIO_Port->BSRR = LAT_Pin)
#define LAT_LOW()  (LAT_GPIO_Port->BSRR = ((uint32_t)LAT_Pin << 16u))

