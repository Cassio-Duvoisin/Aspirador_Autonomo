/**
 * @file observer.h
 * @brief Funções para gerenciamento de observadores (Observer Pattern).
 */

#ifndef OBSERVER_H
#define OBSERVER_H

/**
 * @brief Tipo de callback para observadores.
 */
typedef void (*ObserverCallback)(void);

/**
 * @brief Registra um observador.
 * @param callback Função de callback do observador.
 */
void RegisterObserver(ObserverCallback callback);

/**
 * @brief Notifica todos os observadores registrados.
 */
void NotifyObservers(void);

#endif
