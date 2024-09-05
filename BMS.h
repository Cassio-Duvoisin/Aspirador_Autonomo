/**
 * @file BMS.h
 * @brief Funções para controle de BMS.
 */

#ifndef BMS_H
#define BMS_H

#define BATTERY_THERSHOLD_LOW         15
#define BATTERY_THERSHOLD_CRITICAL    5
#define BATTERY_THERSHOLD_CHARGE      1

void BMS_BatteryCheck(Blackboard_Type* board);

#endif
