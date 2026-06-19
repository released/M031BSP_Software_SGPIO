#ifndef __SGPIO_SLAVE_H__
#define __SGPIO_SLAVE_H__

#include <stdint.h>
#include "NuMicro.h"

/*
 * Pico SGPIO master wiring, shared GPIO port ISR capture path:
 *   GP21 SCLK      -> M032 PC6 GPIO input, shared GPIO ISR rising sampler
 *   GP20 SDATA OUT -> M032 PA7 GPIO input, sampled by SCLK
 *   GP19 SLOAD     -> M032 PA6 GPIO input, sampled by SCLK
 */
#define SGPIO_SLAVE_SLOAD_PORT           (PA)
#define SGPIO_SLAVE_SLOAD_PIN_NUM        (6UL)
#define SGPIO_SLAVE_SLOAD_PIN_MASK       (BIT6)

#define SGPIO_SLAVE_SDOUT_PORT           (PA)
#define SGPIO_SLAVE_SDOUT_PIN_NUM        (7UL)
#define SGPIO_SLAVE_SDOUT_PIN_MASK       (BIT7)

#define SGPIO_SLAVE_SCLK_PORT            (PC)
#define SGPIO_SLAVE_SCLK_PIN_NUM         (6UL)
#define SGPIO_SLAVE_SCLK_PIN_MASK        (BIT6)

#define SGPIO_SLAVE_GPIO_IRQn            (GPIO_PCPDPEPF_IRQn)

#define SGPIO_SLAVE_MAX_SLOTS            (16U)
#define SGPIO_SLAVE_RX_MAX_BYTES         (8U)

void SGPIO_Init(void);
void SGPIO_Process(void);
void SGPIO_OnClockRisingSampledIrq(uint8_t sload_value, uint8_t sdata_value);

#endif
