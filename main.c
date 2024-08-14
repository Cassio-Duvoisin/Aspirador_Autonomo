#include "Hardware_Proxy.h"


static Blackboard blackboard;  

// Variável para o Watchdog Timer
static IWDG_HandleTypeDef hiwdg;

// Funções de Inicialização de Sistema
void System_Init(void);
void Peripheral_Init(Blackboard* board);
void Watchdog_Init(void);
void Error_Handler(void);

// Funções de Camada de Serviço
void LED_Control(GPIO_PinState red, GPIO_PinState blue, GPIO_PinState orange, GPIO_PinState green);
void Button_Handler(Blackboard* board);
void PWM_Control(Blackboard* board, float duty_cycle);
void Run_Routine(Blackboard* board);

// Função Principal
int main(void) {
    HAL_Init();  			                            // Inicialização do HAL
    System_Init();  	                                // Configuração do Sistema

    // Inicialização do Watchdog Timer
    Watchdog_Init();

    // Inicialização do Blackboard e Periféricos
    Assemble_BlackBoard(&blackboard);

    while (1) {
        // Alimenta o Watchdog Timer
        HAL_IWDG_Refresh(&hiwdg);

        // Roda a rotina principal
        Run_Routine(&blackboard);
    }
}

// Função de Inicialização do Sistema
void System_Init(void) {
    SystemConfig_Init();    // Configuração do clock do sistema
}

// Função de Inicialização dos Periféricos
void Assemble_BlackBoard(Blackboard* board) {

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
    Analog_Init(&board->Parameters.analog);

    // Inicialização do pino digital como entrada
    board->Parameters.digital_in.port = GPIOA;  		             // Exemplo: Porta A
    board->Parameters.digital_in.pin = GPIO_PIN_0;  	             // Exemplo: Pino 0
    Digital_InitInput(&board->Parameters.digital_in);

    // Inicialização do pino digital como saída
    board->Parameters.digital_out.port = GPIOB;  		             // Exemplo: Porta B
    board->Parameters.digital_out.pin = GPIO_PIN_5;  	             // Exemplo: Pino 5
    Digital_InitOutput(&board->Parameters.digital_out, GPIO_PIN_RESET);   // Estado inicial: Baixo

    // Inicialização do PWM
    board->Parameters.pwm.channel = TIM_CHANNEL_1;                  // Canal 1 do TIM2
    PWM_Init(&board->Parameters.pwm, 1000);                         // Frequência do PWM: 1000 Hz

    // Inicializa o estado do botão
    board->button_state = GPIO_PIN_RESET;
}

// Função de Inicialização do Watchdog Timer
void Watchdog_Init(void) {
    hiwdg.Instance = IWDG;
    hiwdg.Init.Prescaler = IWDG_PRESCALER_64;
    hiwdg.Init.Reload = 1250;  // Timeout de 1 segundo aproximadamente (32kHz / 64 / 1250)
    if (HAL_IWDG_Init(&hiwdg) != HAL_OK) {
        Error_Handler();
    }
}

// Função de Tratamento de Erro
void Error_Handler(void) {
    // Pode incluir códigos de diagnóstico, como acender LEDs ou enviar mensagens de depuração
    while(1) {
        // Loop infinito para indicar erro
    }
}

// Função para Controlar LEDs (Camada de Serviço)
void LED_Control(GPIO_PinState red, GPIO_PinState blue, GPIO_PinState orange, GPIO_PinState green) {
    LED_On(red, blue, orange, green);
}

// Função de Tratamento do Botão (Camada de Serviço)
void Button_Handler(Blackboard* board) {
    board->current_button_state = Digital_Read(&board->Parameters.digital_in);
    if (board->current_button_state == GPIO_PIN_SET && board->button_state == GPIO_PIN_RESET) {
        LED_Toggle(GPIO_PIN_0);
        LED_Toggle(GPIO_PIN_1);
        LED_Toggle(GPIO_PIN_2);
        LED_Toggle(GPIO_PIN_3);
    }
    board->button_state = board->current_button_state;
}

// Função para Controlar PWM (Camada de Serviço)
void PWM_Control(Blackboard* board, float duty_cycle) {
    PWM_SetDutyCycle(&board->Parameters.pwm, duty_cycle);
}

// Função para Rodar a Rotina Principal
void Run_Routine(Blackboard* board) {
    LED_Control(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET);

    Button_Handler(board);

    for (float duty = 0.1; duty <= 1.0; duty += 0.1) {
        PWM_Control(board, duty);
        HAL_Delay(500);  // Delay de 500 ms
    }

    PWM_Stop(&board->Parameters.pwm);
}
