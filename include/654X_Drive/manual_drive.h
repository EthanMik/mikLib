#pragma once

#include "vex.h"

enum class colors { RED, BLUE };
enum LB_state : int { ACTIVE = 68, INACTIVE = 40, SCORING = 190 };
enum port : int { PORT_A = 0, PORT_B = 1, PORT_C = 2, PORT_D = 3, PORT_E = 4, PORT_F = 5, PORT_G = 6, PORT_H = 7 };

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
    
    void LB_intake();

    void mogo_clamp();

    void doinker();

    void flip_direction();

    void match_timer();

    void user_control_tasks();

    hzn::motor_group LB_motors;
    vex::rotation LB_encoder;
    vex::motor intake_motor; 
    vex::optical ring_color_sensor;
    vex::distance ring_distance_sensor;
    vex::digital_out mogo_clamp_piston; 
    vex::digital_out doinker_piston;
    
    bool ring_detected = false;
    bool hook_detected = false;
    colors alliance_color;
    int intake_position;
    
    std::string state;
    int prev_state;
    bool is_scoring = false;
    bool is_active = false;
    bool intake_override = false;
    bool LB_override = false;

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
    static int LB_intake_task(void);
    static int split_arcade_task(void);
    static int mogo_clamp_task(void);
    static int doinker_task(void);
    static int flip_direction_task(void);
    static int match_timer_task(void);

    vex::task _LB_intake_task;
    vex::task _split_arcade_task;
    vex::task _mogo_clamp_task;
    vex::task _doinker_task;
    vex::task _flip_direction_task;
    vex::task _match_timer_task;
};