#include "launcher.h"


bool Launcher::Reset()
{
    static int start_time=get_systemTick()/1000;
    if(get_systemTick()/1000 - start_time > 1000)
    {
        PitchMotor.encoder_offset = PitchMotor.get_encoder();
        PushMotor.encoder_offset = PushMotor.get_encoder();
        machine_init_ = true;
    }
    else
    {
        PitchMotor.Out = 3000;
        PushMotor.Out = 2000;
        machine_init_ = false;
    }
}


void Launcher::PitchControl(float pitch_angle)
{
    if(!machine_init_)
    {
        Reset();
    }
    else
    {
        //判断俯仰角度是否在范围内
        if(pitch_angle > pitch_angle_max_)
            pitch_angle = pitch_angle_max_;
        else{;}

        PidPitchPos.target = pitch_angle;
        PidPitchPos.current = PitchMotor.get_angle();
        PidPitchSpd.target = PidPitchPos.Adjust();
        PidPitchSpd.current = PitchMotor.get_speed();
        PitchMotor.Out = PidPitchSpd.Adjust();
    }
}

void Launcher::ShootControl(bool shoot_ready, bool shoot_on, float shoot_speed)
{
    if(machine_init_)
    {
        PidPushPos.target = push_angle_max_;
        PidPushPos.current = PushMotor.get_angle();
        PidPushSpd.target = PidPushPos.Adjust();
        PidPushSpd.current = PushMotor.get_speed();
        PushMotor.Out = PidPushSpd.Adjust();

        FrictionMotor[0].Out = shoot_speed;
        FrictionMotor[1].Out = shoot_speed;
        FrictionMotor[2].Out = shoot_speed*2.f/3.f;
    }
}
