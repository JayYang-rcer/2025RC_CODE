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
#include "speed_plan.h"
Omni_Chassis chassis(0.152/2.f, 0.442f/2.f, 3, 1.f); //底盘直径0.442m，轮子半径0.152m，底盘加速度0.5m/s^2
TrapePlanner planner(0.2,0.2,3000,100,3);
PID spd_pid;
void Chassis_Task(void *pvParameters)
{
    static Robot_Twist_t twist;
    for(;;)
    {   
        spd_pid.PID_Param_Init(12.0f, 0.015f, 0.0f, 16384.0f, 16384.0f, 10); 
        spd_pid.PID_Mode_Init(0.1f, 0.0f, false, true);
        if(xQueueReceive(Chassia_Port, &twist, pdTRUE) == pdPASS)
        {
            //底盘控制、电机控制    
            // chassis.Control(twist);
            // chassis.Motor_Control();
            if(twist.chassis_mode == NORMAL)
            {
                spd_pid.target = planner.Plan(0,5000,chassis.WheelMotor[2].get_angle());
                spd_pid.current = chassis.WheelMotor[2].get_speed();
                chassis.WheelMotor[2].Out = spd_pid.Adjust();
                Motor_SendMsgs(&hcan1, chassis.WheelMotor[2]);
            }
            else if(twist.chassis_mode == X_MOVE)
            {
                spd_pid.target = planner.Plan(5000,0,chassis.WheelMotor[2].get_angle());
                spd_pid.current = chassis.WheelMotor[2].get_speed();
                chassis.WheelMotor[2].Out = spd_pid.Adjust();
                Motor_SendMsgs(&hcan1, chassis.WheelMotor[2]);
            }
            else
            {}
        }	
        osDelay(1);
    }
}


void Chassis_Pid_Init(void)
{   
    chassis.Pid_Param_Init(0, 12.0f, 0.015f, 0.0f, 16384.0f, 16384.0f, 10); 
    chassis.Pid_Param_Init(1, 12.0f, 0.015f, 0.0f, 16384.0f, 16384.0f, 10); 
    chassis.Pid_Param_Init(2, 12.0f, 0.015f, 0.0f, 16384.0f, 16384.0f, 10); 

    chassis.Pid_Mode_Init(0, 0.1f, 0.0f, false, true);
    chassis.Pid_Mode_Init(1, 0.1f, 0.0f, false, true);
    chassis.Pid_Mode_Init(2, 0.1f, 0.0f, false, true);
}
