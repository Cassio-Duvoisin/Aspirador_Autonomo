#include "Analog.h"

// Inicializa o DAC.
void Analog_Init(Analog_TypeDef *analog)
{
    // Configuração do ADC
    analog->hadc.Instance = ADC1;
    analog->hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
    analog->hadc.Init.Resolution = ADC_RESOLUTION_12B;
    analog->hadc.Init.ScanConvMode = DISABLE;
    analog->hadc.Init.ContinuousConvMode = DISABLE;
    analog->hadc.Init.DiscontinuousConvMode = DISABLE;
    analog->hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    analog->hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    analog->hadc.Init.NbrOfConversion = 1;
    HAL_ADC_Init(&(analog->hadc));
}

// Realiza a leitura de um canal específico do ADC.
uint16_t Analog_Read(Analog_TypeDef *analog, uint32_t channel)
{
    ADC_ChannelConfTypeDef sConfig;

    // Configuração do canal do ADC
    sConfig.Channel = channel;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    HAL_ADC_ConfigChannel(&(analog->hadc), &sConfig);

    // Início da conversão e aguarda a leitura do valor
    HAL_ADC_Start(&(analog->hadc));
    if (HAL_ADC_PollForConversion(&(analog->hadc), 1000) == HAL_OK) {
        return HAL_ADC_GetValue(&(analog->hadc));
    } else {
        return 0;
    }
}
