#pragma once

#include "vex.h"

enum class colors { RED, BLUE };
enum class LB_state { ACTIVE = 210, INACTIVE = 194, SCORING = 294 };

class manual_drive {   
public:
    manual_drive(
        hzn::motor_group LB_motors, 
        int LB_encoder_port, 
        hzn::motor intake_motor,
        int ring_color_sensor_port,
        int ring_distance_sensor_port,
        int mogo_clamp_piston_port, 
        int doinker_piston_port
    );

    void intake();
    void ring_sort();
    colors get_ring_color();

    void lady_brown();
    std::string set_LB_state(LB_state state);
    void set_LB_constants(float LB_max_voltage, float LB_kp, float LB_ki, float LB_kd, float LB_starti, float LB_settle_error, float LB_settle_time, float LB_timeout);
    void move_LB_to_angle(float angle, bool buffer_data = false);
    void move_LB_to_angle(float angle, float LB_max_voltage, float LB_settle_error, float LB_settle_time, float LB_timeout, float LB_kp, float LB_ki, float LB_kd, float LB_starti, bool buffer_data = false);

    void mogo_clamp();

    void doinker();

    void flip_direction();

    void user_control_tasks();

    hzn::motor_group LB_motors;
    vex::rotation LB_encoder;
    vex::motor intake_motor; 
    vex::optical ring_color_sensor;
    vex::distance ring_distance_sensor;
    vex::digital_out mogo_clamp_piston; 
    vex::digital_out doinker_piston;
    
    colors alliance_color;
    std::string state;
    
    float desired_angle;
    float LB_max_voltage;
    float LB_settle_error; 
    float LB_settle_time; 
    float LB_timeout; 
    float LB_kp; 
    float LB_ki; 
    float LB_kd;
    float LB_starti;

private:
    static int split_arcade_task(void);
    static int intake_task(void);
    static int lady_brown_task(void);
    static int mogo_clamp_task(void);
    static int doinker_task(void);
    static int flip_direction_task(void);

    vex::task _split_arcade_task;
    vex::task _intake_task;
    vex::task _lady_brown_task;
    vex::task _mogo_clamp_task;
    vex::task _doinker_task;
    vex::task _flip_direction_task;
};