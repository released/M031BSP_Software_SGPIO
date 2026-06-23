#ifndef __SGPIO_SLAVE_H__
#define __SGPIO_SLAVE_H__

#include <stdint.h>
#include "NuMicro.h"

/*
 * Select the SGPIO GPIO pin map here.
 * The PA0/PA2/PA3 map is the active wiring. The legacy PA6/PA7/PC6 map is
 * kept selectable because it has already been verified on hardware.
 */
#define SGPIO_SLAVE_PINMAP_LEGACY_PA6_PA7_PC6 (0U)
#define SGPIO_SLAVE_PINMAP_PA0_PA2_PA3        (1U)

#ifndef SGPIO_SLAVE_PINMAP
#define SGPIO_SLAVE_PINMAP                    SGPIO_SLAVE_PINMAP_PA0_PA2_PA3
#endif

#if (SGPIO_SLAVE_PINMAP == SGPIO_SLAVE_PINMAP_PA0_PA2_PA3)
/*
 * Active Pico SGPIO master wiring, shared GPIO port ISR capture path:
 *   GP21 SCLK      -> M032 PA2 GPIO input, shared GPIO ISR rising sampler
 *   GP20 SDATA OUT -> M032 PA0 GPIO input, sampled by SCLK
 *   GP19 SLOAD     -> M032 PA3 GPIO input, sampled by SCLK
 */
#define SGPIO_SLAVE_SLOAD_PORT           (PA)
#define SGPIO_SLAVE_SLOAD_PIN_NUM        (3UL)
#define SGPIO_SLAVE_SLOAD_PIN_MASK       (BIT3)

#define SGPIO_SLAVE_SDOUT_PORT           (PA)
#define SGPIO_SLAVE_SDOUT_PIN_NUM        (0UL)
#define SGPIO_SLAVE_SDOUT_PIN_MASK       (BIT0)

#define SGPIO_SLAVE_SCLK_PORT            (PA)
#define SGPIO_SLAVE_SCLK_PIN_NUM         (2UL)
#define SGPIO_SLAVE_SCLK_PIN_MASK        (BIT2)

#define SGPIO_SLAVE_GPIO_IRQn            (GPIO_PAPBPGPH_IRQn)
#define SGPIO_SLAVE_GPIO_IRQHandler      GPABGH_IRQHandler

#define SGPIO_SLAVE_SLOAD_PIN_NAME       "PA3"
#define SGPIO_SLAVE_SDOUT_PIN_NAME       "PA0"
#define SGPIO_SLAVE_SCLK_PIN_NAME        "PA2"

#elif (SGPIO_SLAVE_PINMAP == SGPIO_SLAVE_PINMAP_LEGACY_PA6_PA7_PC6)
/*
 * Legacy verified Pico SGPIO master wiring:
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
#define SGPIO_SLAVE_GPIO_IRQHandler      GPCDEF_IRQHandler

#define SGPIO_SLAVE_SLOAD_PIN_NAME       "PA6"
#define SGPIO_SLAVE_SDOUT_PIN_NAME       "PA7"
#define SGPIO_SLAVE_SCLK_PIN_NAME        "PC6"

#else
#error "Unsupported SGPIO_SLAVE_PINMAP selection"
#endif

#define SGPIO_SLAVE_SLOAD_IO             ((uint8_t)(((GPIO_GET_IN_DATA(SGPIO_SLAVE_SLOAD_PORT) & SGPIO_SLAVE_SLOAD_PIN_MASK) != 0UL) ? 1U : 0U))
#define SGPIO_SLAVE_SDOUT_IO             ((uint8_t)(((GPIO_GET_IN_DATA(SGPIO_SLAVE_SDOUT_PORT) & SGPIO_SLAVE_SDOUT_PIN_MASK) != 0UL) ? 1U : 0U))

#define SGPIO_SLAVE_MAX_SLOTS            (16U)
#define SGPIO_SLAVE_RX_MAX_BYTES         (8U)

void SGPIO_Init(void);
void SGPIO_Process(void);
void SGPIO_OnClockRisingSampledIrq(uint8_t sload_value, uint8_t sdata_value);

#endif
