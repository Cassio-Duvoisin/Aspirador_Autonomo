#include "main.h"
#include <stdint.h>

#define MAX_OBSERVERS 5

typedef void (*ObserverCallback)(void);

// Estrutura para manter os observadores
typedef struct {
    ObserverCallback observers[MAX_OBSERVERS];
    uint8_t count;
} ObserverManager;

ObserverManager observer_manager = { .count = 0 };

// Funções para gerenciar observadores
void AddObserver(ObserverCallback callback);
void NotifyObservers(void);
void CheckButtonAndNotifyObservers(void);

// Função de callback do observador
void LED_ToggleCallback(void);

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    // Adiciona o callback do LED aos observadores
    AddObserver(LED_ToggleCallback);

    while (1)
    {
        CheckButtonAndNotifyObservers();
    }
}

void AddObserver(ObserverCallback callback)
{
    if (observer_manager.count < MAX_OBSERVERS)
    {
        observer_manager.observers[observer_manager.count++] = callback;
    }
}

void NotifyObservers(void)
{
    for (uint8_t i = 0; i < observer_manager.count; ++i)
    {
        observer_manager.observers[i]();
    }
}

void CheckButtonAndNotifyObservers(void)
{
    static uint8_t previous_state = 0;
    uint8_t current_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);

    if (current_state && !previous_state)
    {
        NotifyObservers();
    }

    previous_state = current_state;
}

void LED_ToggleCallback(void)
{
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
}

static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Configura os LEDs
    GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    // Configura o botão
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
