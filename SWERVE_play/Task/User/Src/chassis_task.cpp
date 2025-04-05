/**
 * @file chassis_task.cpp
 * @author Yang JianYi
 * @brief 舵轮底盘应用文件，包括底盘配置的初始化以及控制接口的调用
 * @version 0.1
 * @date 2024-05-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "chassis_task.h"

Omni_Chassis chassis(0.152f/2,0,0.374f,3);

void Chassis_Task(void *pvParameters)
{
    static Robot_Twist_t twist;
    for(;;)
    {   
        if(xQueueReceive(Chassia_Port, &twist, 0) == pdPASS)
        {
            //底盘控制、电机控制    
            chassis.Control(twist);
            chassis.Motor_Control();
        }	
        osDelay(1);
    }
}


void Chassis_Pid_Init(void)
{   
    chassis.Pid_Param_Init(0, 12.0f, 0.015f, 0.0f, 0.0f, 12000.0f, 10); 
    chassis.Pid_Param_Init(1, 12.0f, 0.015f, 0.0f, 0.0f, 12000.0f, 10); 
    chassis.Pid_Param_Init(2, 12.0f, 0.015f, 0.0f, 0.0f, 12000.0f, 10); 

    chassis.Pid_Mode_Init(0, 0.1f, 0.0f, false, true);
    chassis.Pid_Mode_Init(1, 0.1f, 0.0f, false, true);
    chassis.Pid_Mode_Init(2, 0.1f, 0.0f, false, true);
}
