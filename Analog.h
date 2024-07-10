#ifndef ANALOG_H
#define ANALOG_H

#include "stm32f4xx_hal.h"

// Estrutura para encapsular o ADC
typedef struct {
    ADC_HandleTypeDef hadc;  // Estrutura do ADC
} Analog_TypeDef;

// Funções públicas

/**
 * @brief Inicializa o ADC.
 * 
 * @param analog Ponteiro para a estrutura Analog_TypeDef que representa o ADC.
 */
void Analog_Init(Analog_TypeDef *analog);

/**
 * @brief Realiza a leitura de um canal específico do ADC.
 * 
 * @param analog Ponteiro para a estrutura Analog_TypeDef que representa o ADC.
 * @param channel Canal do ADC a ser lido.
 * @return Valor lido do canal especificado.
 */
uint16_t Analog_Read(Analog_TypeDef *analog, uint32_t channel);

//void DAC_Write(uint16_t value);  // Se necessário, implemente no main.c

#endif /* ANALOG_H */
