/**
 * @file main.c
 * @brief Função principal do programa.
 */

#include "SystemConfig.h"
#include "HardwareProxy.h"
#include "Interrupt_Handlers.h"
#include "Motor.h"

//----------------------------------- Global Variables -------------------------------


//-------------------------------------------------------------------------------------

// All function prototypes
void System_Init(Blackboard* board, TIM_HandleTypeDef* tim, uint32_t Timer_1, uint32_t Timer_2);
void Assemble_BlackBoard(Blackboard* board, TIM_HandleTypeDef* tim, uint32_t Timer_1, uint32_t Timer_2);
void Watchdog_Init(void);
void Error_Handler(void);

int main(void) {
    // Instância do Blackboard
    Blackboard_Type blackboard;  

    // Variável para o Watchdog Timer
    IWDG_HandleTypeDef hiwdg;
    
    TIM_HandleTypeDef  htim4;

    HAL_Init();  // Inicializa o HAL
    System_Init(&blackboard, htim4, TIM_CHANNEL_1, TIM_CHANNEL_2);  


    while (1) {

        // Alimenta o Watchdog Timer
        HAL_IWDG_Refresh(&hiwdg);
        
        // Check se o Interrupt foi acionado
        EmergencyButton_IRQHandler(&blackboard);

        // Pega o valor do sensor de proximidade 
        blackboard.adc_value = HardwareProxy_ReadAnalog(&blackboard.distance_pin);

        Motor_Run(&blackboard);

        BMS_BatteryCheck(&blackboard);

        // Adiciona um pequeno delay
        HAL_Delay(10);  // Delay de 10 ms
    }
}


// Função de Inicialização do Sistema
void System_Init(Blackboard* board, TIM_HandleTypeDef* tim, uint32_t Timer_1, uint32_t Timer_2) {
    SystemClock_Config();  // Configura o clock do sistema
    HardwareProxy_Init(&board);  // Inicializa todos os componentes de hardware
    Watchdog_Init(hiwdg);    // Inicialização do Watchdog Timer
    Assemble_BlackBoard(board, tim, Timer_1, Timer_2);
}

// Função de Inicialização dos Periféricos
void Assemble_BlackBoard(Blackboard* board, TIM_HandleTypeDef* tim, uint32_t Timer_1, uint32_t Timer_2) {

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

    Motor_Init(tim,Timer_1,Timer_2);
    // Inicializa o estado do botão
    board->button_state = GPIO_PIN_RESET;
}

// Função de Inicialização do Watchdog Timer
void Watchdog_Init(IWDG_HandleTypeDef* hiwdg) {
    hiwdg.Instance = IWDG;
    hiwdg.Init.Prescaler = IWDG_PRESCALER_64;
    hiwdg.Init.Reload = 1250;  // Timeout de 1 segundo aproximadamente (32kHz / 64 / 1250)
    if (HAL_IWDG_Init(&hiwdg) != HAL_OK) {
        Error_Handler();
    }
}

// Função para Rodar a Rotina Principal
void Run_Routine(Blackboard* blackboard){
    // Verifica se o botão foi pressionado para alternar o LED
    if (blackboard.button_state == GPIO_PIN_SET) {
        HardwareProxy_ToggleLED(GPIO_PIN_12);  // Alterna o estado do LED verde
    }

    // Controla o estado dos LEDs azul e verde com base no estado do pino digital
    if (blackboard.digitalState == GPIO_PIN_SET) {
        HardwareProxy_SetLED(GPIO_PIN_13, GPIO_PIN_SET);  // Liga o LED azul
    } else {
        HardwareProxy_SetLED(GPIO_PIN_13, GPIO_PIN_RESET);  // Desliga o LED azul
    }

    // Notifica observadores se o PWM estiver em 50%
    if (blackboard.pwmValue >= 5000 && blackboard.pwmValue < 5100) {
        NotifyObservers();  // Notifica todos os observadores registrados
    }
}

// Função de Tratamento de Erro
void Error_Handler(void) {
    // Pode incluir códigos de diagnóstico, como acender LEDs ou enviar mensagens de depuração
    while(1) {
        // TODO
    }
}
