#include "Hardware_Proxy.h"

int main(void)
{
    // Variáveis para ADC, GPIO e PWM
    Analog_TypeDef analog;
    Digital_TypeDef digital_in;
    Digital_TypeDef digital_out;
    PWM_TypeDef pwm;

    HAL_Init();  			                            // Inicialização do HAL
    SystemConfig_Init();  	                            // Configuração do clock do sistema

    // Inicialização do ADC
    Analog_Init(&analog);

    // Inicialização do pino digital como entrada
    digital_in.port = GPIOA;  		                    // Exemplo: Porta A
    digital_in.pin = GPIO_PIN_0;  	                    // Exemplo: Pino 0
    Digital_InitInput(&digital_in);

    // Inicialização do pino digital como saída
    digital_out.port = GPIOB;  		                    // Exemplo: Porta B
    digital_out.pin = GPIO_PIN_5;  	                    // Exemplo: Pino 5
    Digital_InitOutput(&digital_out, GPIO_PIN_RESET);   // Estado inicial: Baixo

    // Inicialização dos LEDs
    LED_Init();

    // Inicialização do PWM
    pwm.channel = TIM_CHANNEL_1;                        // Canal 1 do TIM2
    PWM_Init(&pwm, 1000);                               // Frequência do PWM: 1000 Hz

    while (1)
    {
        // Exemplo de leitura de pino digital
        GPIO_PinState digital_state = Digital_Read(&digital_in);

        // Exemplo de escrita em pino digital
        Digital_Write(&digital_out, GPIO_PIN_SET);      // Define o pino para Alto

        // Exemplo de leitura do ADC
        uint16_t adc_value = Analog_Read(&analog, ADC_CHANNEL_0);

        // Exemplo de controle dos LEDs
        LED_On(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET);  // Ativa LED Vermelho e Azul, Desativa LED Laranja e Verde

        // Exemplo de controle do PWM (varia de 0% a 100% do ciclo de trabalho)
        for (float duty = 0.1; duty <= 1.0; duty += 0.1) {
            PWM_SetDutyCycle(&pwm, duty);
            HAL_Delay(500);  // Delay de 500 ms
        }

        PWM_Stop(&pwm);  // Para o PWM

        HAL_Delay(1000);  // Delay de 1 segundo
    }
}
