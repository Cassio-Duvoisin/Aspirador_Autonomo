/**
 * @file Analog.c
 * @brief Implementação das funções de leitura de sinal analógico.
 */

#include "Analog.h"

void Analog_Init(ADC_HandleTypeDef* hadc, uint32_t channel) {
    // Habilita o clock para o ADC
    if (hadc->Instance == ADC1) {
        __HAL_RCC_ADC1_CLK_ENABLE();
    } else if (hadc->Instance == ADC2) {
        __HAL_RCC_ADC2_CLK_ENABLE();
    } else if (hadc->Instance == ADC3) {
        __HAL_RCC_ADC3_CLK_ENABLE();
    }
    
    // Configura o ADC
    hadc->Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc->Init.Resolution = ADC_RESOLUTION_12B;
    hadc->Init.ScanConvMode = DISABLE;
    hadc->Init.ContinuousConvMode = DISABLE;
    hadc->Init.DiscontinuousConvMode = DISABLE;
    hadc->Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc->Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc->Init.NbrOfConversion = 1;
    HAL_ADC_Init(hadc);

    // Configura o canal do ADC
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = channel;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    HAL_ADC_ConfigChannel(hadc, &sConfig);
}

uint32_t Analog_Read(ADC_HandleTypeDef* hadc) {
    HAL_ADC_Start(&hadc);
    HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
    return HAL_ADC_GetValue(&hadc);
}
