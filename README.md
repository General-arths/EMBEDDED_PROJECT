# stm32f446re-softsched

Preemptive, deterministic interrupt architecture on STM32F446RE using:
- NVIC preempt priorities (no RTOS)
- Super-short top halves (ISRs) that just ack+enqueue
- Bottom half via PendSV draining high/med/low work queues
- DWT cycle counter + GPIO pulse on PA5 to measure latency/jitter

## Peripherals
- TIM1 @ 20 kHz (highest prio) → critical tick
- USART2 RX via DMA (circular) + IDLE (medium prio)
- TIM6 @ 1 kHz (low prio) → housekeeping
- PendSV (lowest prio) → bottom half

## Build & Run
- STM32CubeIDE → NUCLEO-F446RE → enable HSE or HSI PLL to 168 MHz
- USART2 (PA2/PA3), DMA1_Stream5/Ch4 RX, circular, IDLE interrupt enabled
- PA5 as output (latency probe)
- Start: TIM1/6 base IT, UART2 DMA, enable UART IDLE

Probe PA5 with an oscilloscope to see ISR entry/exit as a pulse.
# EMBEDDED_PROJECT
