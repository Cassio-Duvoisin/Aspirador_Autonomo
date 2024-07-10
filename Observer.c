/**
 * @file observer.c
 * @brief Implementação das funções de gerenciamento de observadores.
 */

#include "observer.h"

#define MAX_OBSERVERS 10

static ObserverCallback observers[MAX_OBSERVERS];
static int observer_count = 0;

void RegisterObserver(ObserverCallback callback) {
    if (observer_count < MAX_OBSERVERS) {
        observers[observer_count++] = callback;
    }
}

void NotifyObservers(void) {
    for (int i = 0; i < observer_count; i++) {
        observers[i]();
    }
}
