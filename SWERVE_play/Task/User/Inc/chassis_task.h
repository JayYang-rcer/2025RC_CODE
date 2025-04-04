#pragma once

#include "data_pool.h"
#include "chassis_base.h"

#ifdef __cplusplus
void Chassis_Pid_Init(void);
extern "C" {
#endif
void Chassis_Task(void *pvParameters);

#ifdef __cplusplus
}
#endif
