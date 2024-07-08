#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

// Declaração das funções de configuração do sistema
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
