#ifndef LAUNCHER_H
#define LAUNCHER_H
#include "motor.h"
#include "pid.h"

#ifdef __cplusplus
extern "C" {
#endif 

#ifdef __cplusplus
}
#endif

class Launcher : public PidTimer
{
public:
    Launcher(float pitch_angle_max, float push_angle_max)   //最大俯仰角度和推杆最大行程
    {
        pitch_angle_max_ = pitch_angle_max;
        push_angle_max_ = push_angle_max;

        FrictionMotor[0].Mode = SET_eRPM;
        FrictionMotor[1].Mode = SET_eRPM;
        FrictionMotor[2].Mode = SET_eRPM;
        FrictionMotor[0].Out = 0;
    }
    Motor_C620 PitchMotor = Motor_C620(4);
    Motor_C620 PushMotor = Motor_C620(5);
    VESC FrictionMotor[3] = {VESC(101), VESC(102), VESC(103)};
    void PitchControl(float pitch_angle);
    void ShootControl(bool shoot_ready, bool shoot_on, float shoot_speed);
private:
    float pitch_angle_max_ = 0.0f, push_angle_max_ = 0.0f;
    PID PidPitchSpd, PidPitchPos, PidPushSpd, PidPushPos;
    bool machine_init_ = false;
    bool Reset();
    float pitch_angle_ = 0.0f;
    float push_angle_ = 0.0f;
};

#endif // LAUNCHER_H
