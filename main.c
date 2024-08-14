#include "Hardware_Proxy.h"


// Variáveis para ADC, GPIO e PWM
typedef struct{
    Analog_TypeDef analog;
    Digital_TypeDef digital_in;
    Digital_TypeDef digital_out;
    PWM_TypeDef pwm;
}Input_Output_Parameters;

typedef struct {
    Input_Output_Parameters Parameters;
    GPIO_PinState current_button_state;
    GPIO_PinState button_state;
    GPIO_PinState digital_state;
    GPIO_InitTypeDef GPIO_InitStruct;
    uint16_t adc_value;
}Blackboard;

static Blackboard blackboard;  

// Variável para o Watchdog Timer
static IWDG_HandleTypeDef hiwdg;

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

    // Inicialização do Blackboard
    Assemble_BlackBoard(&blackboard);

    // Inicialização dos LEDs
    LED_Init();
    while (1)
    {
        // Alimenta o Watchdog Timer
        HAL_IWDG_Refresh(&hiwdg);

        // Leitura do estado atual do botão
        blackboard.current_button_state = Digital_Read(&blackboard.Parameters.digital_in);

        
        // Exemplo de leitura de pino digital
        blackboard.digital_state = Digital_Read(&blackboard.Parameters.digital_in);
        
        blackboard.adc_value = Analog_Read(&blackboard.Parameters.analog, ADC_CHANNEL_0);
        
        //Roda a rotina padrão
        Run_Routine(&blackboard);
        
        // Atualiza o estado anterior do botão
        blackboard.button_state = blackboard.current_button_state;
        
    }
}

void Error_Handler(void) {
    // Função de tratamento de erro
    // Pode incluir códigos de diagnóstico, como acender LEDs ou enviar mensagens de depuração
    while(1) {
        // Loop infinito para indicar erro
    }
}

void Assemble_BlackBoard(Blackboard* board) {
    
    // Configuração do pino de emergência como entrada com interrupção
    __HAL_RCC_GPIOC_CLK_ENABLE();
    board->GPIO_InitStruct = {0};
    board->GPIO_InitStruct.Pin = EMERGENCY_BUTTON_PIN;
    board->GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    board->GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(EMERGENCY_BUTTON_PORT, &board->GPIO_InitStruct);

    // Configuração do NVIC para a interrupção do botão de emergência
    HAL_NVIC_SetPriority(EMERGENCY_BUTTON_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EMERGENCY_BUTTON_IRQn);

    // Inicialização do ADC
    Analog_Init(&board->Parameters.analog);

    // Inicialização do pino digital como entrada
    board->Parameters.digital_in.port = GPIOA;  		            // Exemplo: Porta A
    board->Parameters.digital_in.pin = GPIO_PIN_0;  	            // Exemplo: Pino 0
    Digital_InitInput(&board->Parameters.digital_in);

    // Inicialização do pino digital como saída
    board->Parameters.digital_out.port = GPIOB;  		        // Exemplo: Porta B
    board->Parameters.digital_out.pin = GPIO_PIN_5;  	        // Exemplo: Pino 5
    Digital_InitOutput(&board->Parameters.digital_out, GPIO_PIN_RESET);   // Estado inicial: Baixo

    // Inicialização do PWM
    board->Parameters.pwm.channel = TIM_CHANNEL_1;               // Canal 1 do TIM2
    PWM_Init(&board->Parameters.pwm, 1000);                      // Frequência do PWM: 1000 Hz

    // Variável para armazenar o estado anterior do botão
    board->button_state = GPIO_PIN_RESET;
}

void Run_Routine(Blackboard* board){
        // Exemplo de controle dos LEDs
        LED_On(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET);  // Ativa LED Vermelho e Azul, Desativa LED Laranja e Verde

        // Verifica se houve uma transição de estado (botão pressionado)
        if (board->current_button_state == GPIO_PIN_SET && button_state == GPIO_PIN_RESET) {
            // Inverte o estado dos LEDs
            LED_Toggle(GPIO_PIN_0);
            LED_Toggle(GPIO_PIN_1);
            LED_Toggle(GPIO_PIN_2);
            LED_Toggle(GPIO_PIN_3);
        }

        // Exemplo de escrita em pino digital
        Digital_Write(&board->Parameters.digital_out, GPIO_PIN_SET);      // Define o pino para Alto

        // Exemplo de controle do PWM (varia de 0% a 100% do ciclo de trabalho)
        for (float duty = 0.1; duty <= 1.0; duty += 0.1) {
            PWM_SetDutyCycle(&board->Parameters., duty);
            HAL_Delay(500);  // Delay de 500 ms
        }

        PWM_Stop(&board->Parameters.);  // Para o PWM
}
