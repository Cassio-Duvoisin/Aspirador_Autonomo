#ifndef OBSERVER_H
#define OBSERVER_H

#include <stdio.h>
#include <stdbool.h>
#include "Analog.h"
#include "Digital.h"

// Estrutura para Observer_Watcher_Type
typedef enum {
    IDLE = 0,
    REACH_TARGET = 1
}Observer_Watcher_Type;

Observer_Watcher_Type Observer_Reached_Target(Analog_TypeDef* analogPin, Digital_TypeDef* digitalPin);

#endif /* ANALOG_H */
