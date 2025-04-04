#include "chassis_base.h"

/**
 * @brief 定时器获取函数初始化，在config文件中进行条用
 * 
 * @param getTick_fun 
 * @return uint8_t 
 */
uint8_t Chassis_Base::getMicroTick_regist(uint32_t (*getTick_fun)(void))
{
    if(getTick_fun != NULL)
    {
        Chassis_Base::get_systemTick = getTick_fun;
        return 1;
    }
    else
        return 0;
}


/**
 * @brief 计算任务循环时间
 * 
 * @return uint8_t 
 */
uint8_t Chassis_Base::update_timeStamp(void)
{
    uint32_t now_time=0;

    //Check get sysClock
    if(Chassis_Base::get_systemTick != NULL)
    {
        if(last_time == 0)
        {
            last_time = Chassis_Base::get_systemTick();
            return 1;
        }
        now_time = Chassis_Base::get_systemTick();

        //overflow
        if(now_time < last_time)
            dt = (float)((now_time + 0xFFFFFFFF) - last_time);  //now_time is 32bit, use 0XFFFFFFFF to avoid overflow
        else
            dt = (float)(now_time - last_time);
        
        last_time = now_time;
        
        dt *= 0.000001f;

        return 0;
    }
    else
    {
        dt = 0;
        return 1;
    }
}


