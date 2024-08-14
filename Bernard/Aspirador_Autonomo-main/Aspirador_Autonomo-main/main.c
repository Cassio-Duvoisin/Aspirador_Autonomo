#include "Hardware_Proxy.h"
#include "stm32f4xx_hal.h"

// Definição do pino de emergência
#define EMERGENCY_BUTTON_PORT GPIOC
#define EMERGENCY_BUTTON_PIN GPIO_PIN_13
#define EMERGENCY_BUTTON_IRQn EXTI15_10_IRQn

// Variáveis para ADC, GPIO e PWM
Analog_TypeDef analog;
Digital_TypeDef digital_in;
Digital_TypeDef digital_out;
PWM_TypeDef pwm;

// Variável para o Watchdog Timer
IWDG_HandleTypeDef hiwdg;

void EmergencyButton_IRQHandler(void) {
    // Verifica se a interrupção é do botão de emergência
    if (__HAL_GPIO_EXTI_GET_IT(EMERGENCY_BUTTON_PIN) != RESET) {
        // Limpa a interrupção
        __HAL_GPIO_EXTI_CLEAR_IT(EMERGENCY_BUTTON_PIN);

        // Desativa todos os periféricos
        Analog_DeInit(&analog);
        Digital_DeInit(&digital_in);
        Digital_DeInit(&digital_out);
        PWM_Stop(&pwm);
        LED_Off();
        
        // Loop infinito para manter o sistema desativado
        while(__HAL_GPIO_EXTI_GET_IT(EMERGENCY_BUTTON_PIN) != RESET){
            HAL_Delay(1000);
        }
    }
}

int main(void)
{
    HAL_Init();  			                            // Inicialização do HAL
    SystemConfig_Init();  	                            // Configuração do clock do sistema

    // Inicialização do IWDG (Watchdog Timer)
    hiwdg.Instance = IWDG;
    hiwdg.Init.Prescaler = IWDG_PRESCALER_64;
    hiwdg.Init.Reload = 1250;  // Timeout de 1 segundo aproximadamente (32kHz / 64 / 1250)
    if (HAL_IWDG_Init(&hiwdg) != HAL_OK) {
        // Initialization Error
        Error_Handler();
    }

    // Configuração do pino de emergência como entrada com interrupção
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = EMERGENCY_BUTTON_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(EMERGENCY_BUTTON_PORT, &GPIO_InitStruct);

    // Configuração do NVIC para a interrupção do botão de emergência
    HAL_NVIC_SetPriority(EMERGENCY_BUTTON_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EMERGENCY_BUTTON_IRQn);

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

    // Variável para armazenar o estado anterior do botão
    GPIO_PinState button_state = GPIO_PIN_RESET;

    while (1)
    {
        // Alimenta o Watchdog Timer
        HAL_IWDG_Refresh(&hiwdg);

        // Leitura do estado atual do botão
        GPIO_PinState current_button_state = Digital_Read(&digital_in);

        // Exemplo de controle dos LEDs
        LED_On(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET);  // Ativa LED Vermelho e Azul, Desativa LED Laranja e Verde

        // Verifica se houve uma transição de estado (botão pressionado)
        if (current_button_state == GPIO_PIN_SET && button_state == GPIO_PIN_RESET) {
            // Inverte o estado dos LEDs
            LED_Toggle(GPIO_PIN_0);
            LED_Toggle(GPIO_PIN_1);
            LED_Toggle(GPIO_PIN_2);
            LED_Toggle(GPIO_PIN_3);
        }

        // Atualiza o estado anterior do botão
        button_state = current_button_state;
        
        // Exemplo de leitura de pino digital
        GPIO_PinState digital_state = Digital_Read(&digital_in);

        // Exemplo de escrita em pino digital
        Digital_Write(&digital_out, GPIO_PIN_SET);      // Define o pino para Alto

        // Exemplo de leitura do ADC
        uint16_t adc_value = Analog_Read(&analog, ADC_CHANNEL_0);

        // Exemplo de controle do PWM (varia de 0% a 100% do ciclo de trabalho)
        for (float duty = 0.1; duty <= 1.0; duty += 0.1) {
            PWM_SetDutyCycle(&pwm, duty);
            HAL_Delay(500);  // Delay de 500 ms
        }

        PWM_Stop(&pwm);  // Para o PWM

        HAL_Delay(1000);  // Delay de 1 segundo
    }
}

void Error_Handler(void) {
    // Função de tratamento de erro
    // Pode incluir códigos de diagnóstico, como acender LEDs ou enviar mensagens de depuração
    while(1) {
        // Loop infinito para indicar erro
    }
}
