#pragma once

#include "data_pool.h"
#include "chassis_swerve.h"
#include "chassis_omni.h"

#ifdef __cplusplus
void Chassis_Pid_Init(void);
extern "C" {
#endif
void Chassis_Task(void *pvParameters);


#ifdef __cplusplus
}

extern Omni_Chassis chassis;
#endif
