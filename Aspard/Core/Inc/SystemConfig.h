/**
 * @file systemconfig.h
 * @brief Header file for system configuration on STM32F407VG.
 */

#ifndef SYSTEMCONFIG_H
#define SYSTEMCONFIG_H

#include "stm32f4xx_hal.h"

/**
 * @brief Initializes the system configuration.
 *
 * This function initializes the STM32F407VG system configuration including
 * the clocks and other necessary configurations.
 */
void SystemConfig_Init(void);

#endif /* SYSTEMCONFIG_H */
