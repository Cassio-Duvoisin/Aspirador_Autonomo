#include "Analog.h"

/**
 * @brief Inicializa o DAC.
 * 
 * @param analog Ponteiro para a estrutura Analog_TypeDef que representa o DAC.
 */
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

/**
 * @brief Realiza a leitura de um canal específico do ADC.
 * 
 * @param analog Ponteiro para a estrutura Analog_TypeDef que representa o ADC.
 * @param channel Canal do ADC a ser lido.
 * @return Valor lido do canal especificado.
 */
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

/**
 * @brief Escreve um valor analógico no DAC.
 * 
 * @param analog Ponteiro para a estrutura Analog_TypeDef que representa o DAC.
 * @param value Valor a ser escrito no DAC (de 0 a 4095, correspondendo a 0 a Vref).
 */
void Analog_Write(Analog_TypeDef *analog, uint16_t value) {
    HAL_DAC_SetValue(&analog->hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, value);
    /* DAC_CHANNEL_1 indica o canal 1 do DAC */
    /* DAC_ALIGN_12B_R indica alinhamento de 12 bits, à direita */
}
