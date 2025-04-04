/**
 * @file fsm_joy.cpp
 * @author Yang JianYi
 * @brief 舵轮底盘应用文件，包括上位机控制接口的调用以及stm32手柄的调试，开关是通过宏定义来控制的(USE_ROS_CONTROL)。
 * @version 0.1
 * @date 2024-05-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "fsm_joy.h"
#include "drive_tim.h"
#include "chassis_task.h"

void Air_Joy_Task(void *pvParameters)
{
    for(;;)
    {
		Robot_Twist_t twist;
        if(air_joy.LEFT_X>1400&&air_joy.LEFT_X<1600)
            air_joy.LEFT_X = 1500;
        if(air_joy.LEFT_Y>1400&&air_joy.LEFT_Y<1600)
            air_joy.LEFT_Y = 1500;
        if(air_joy.RIGHT_X>1400&&air_joy.RIGHT_X<1600)
            air_joy.RIGHT_X = 1500;
        if(air_joy.RIGHT_Y>1400&&air_joy.RIGHT_Y<1600)  
            air_joy.RIGHT_Y = 1500;

        if(air_joy.LEFT_X!=0||air_joy.LEFT_Y!=0||air_joy.RIGHT_X!=0||air_joy.RIGHT_Y!=0)
        {
            if(air_joy.SWA>1950&&air_joy.SWA<2050)
            {
                if(air_joy.SWC>950&&air_joy.SWC<1050)
                {
                    twist.chassis_mode = NORMAL;
                }
                else if(air_joy.SWC>1450&&air_joy.SWC<1550)
                {
                    twist.chassis_mode = X_MOVE;
                }
                else if(air_joy.SWC>1950&&air_joy.SWC<2050)
                {
                    twist.chassis_mode = Y_MOVE;
                }
                else
                {
                    twist.chassis_mode = NORMAL;
                }
                
                twist.linear.x = (air_joy.LEFT_Y - 1500)/500.0 * 3;
                twist.linear.y = (air_joy.LEFT_X - 1500)/500.0 * 3;
                twist.angular.z = (air_joy.RIGHT_X - 1500)/500.0 * 4;
                xQueueSend(Chassia_Port, &twist, 0);
            }
        }
        else
        {
            twist = {0};
        }

        osDelay(1);
    }
}

