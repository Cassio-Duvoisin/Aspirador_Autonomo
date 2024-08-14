#ifndef DIGITAL_H
#define DIGITAL_H

#include "stm32f4xx_hal.h"

// Estrutura para encapsular o GPIO
typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
} Digital_TypeDef;

//---------------------------Funções públicas---------------------------//

/**
 * @brief Inicializa um pino digital como entrada.
 * 
 * @param digital Ponteiro para a estrutura Digital_TypeDef que representa o pino digital.
 */
void Digital_InitInput(Digital_TypeDef *digital);

/**
 * @brief Inicializa um pino digital como saída.
 * 
 * @param digital Ponteiro para a estrutura Digital_TypeDef que representa o pino digital.
 * @param initial_state Estado inicial do pino (GPIO_PIN_RESET ou GPIO_PIN_SET).
 */
void Digital_InitOutput(Digital_TypeDef *digital, GPIO_PinState initial_state);

/**
 * @brief Lê o estado de um pino digital.
 * 
 * @param digital Ponteiro para a estrutura Digital_TypeDef que representa o pino digital.
 * @return Estado atual do pino (GPIO_PIN_RESET ou GPIO_PIN_SET).
 */
GPIO_PinState Digital_Read(Digital_TypeDef *digital);
/**
 * @brief Escreve um estado em um pino digital.
 * 
 * @param digital Ponteiro para a estrutura Digital_TypeDef que representa o pino digital.
 * @param state Estado a ser escrito no pino (GPIO_PIN_RESET ou GPIO_PIN_SET).
 */
void Digital_Write(Digital_TypeDef *digital, GPIO_PinState state);

/**
 * @brief Habilita a interrupção em um pino digital.
 * 
 * @param digital Ponteiro para a estrutura Digital_TypeDef que representa o pino digital.
 * @param callback Função de callback a ser chamada na interrupção.
 */
void Digital_EnableInterrupt(Digital_TypeDef *digital, void (*callback)(void));

#endif /* DIGITAL_H */
