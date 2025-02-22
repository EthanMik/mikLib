#pragma once

#include "vex.h"

enum class color_sort { RED, BLUE, NONE };
enum port : int { PORT_A = 0, PORT_B = 1, PORT_C = 2, PORT_D = 3, PORT_E = 4, PORT_F = 5, PORT_G = 6, PORT_H = 7 };
enum LB_state : int { ACTIVE = 198, INACTIVE = 220, HOLDING = 170, SCORING = 60 };

class manual_drive {   
public:
    manual_drive(
        hzn::motor_group LB_motors, 
        int LB_encoder_port, 
        hzn::motor intake_motor,
        int intake_encoder_port,
        int ring_color_sensor_port,
        int ring_distance_sensor_port,
        int mogo_clamp_piston_port, 
        int doinker_piston_port,
        int rush_piston_port,
        int list_piston_port
    );
    void initialize_user_control();

    void intake();
    void select_ring_sort_mode();
    void select_ring_sort_mode(color_sort opposing_color);
    bool ring_sort();

    void lady_brown();
    void lady_brown_manual();
    void set_LB_constants(float LB_max_voltage, float LB_kp, float LB_ki, float LB_kd, float LB_starti, float LB_settle_error, float LB_settle_time, float LB_timeout);
    void move_LB_to_angle(float angle, bool buffer_data = false);
    void move_LB_to_angle(float angle, float LB_max_voltage, float LB_settle_error, float LB_settle_time, float LB_timeout, float LB_kp, float LB_ki, float LB_kd, float LB_starti, bool buffer_data = false);
    
    void mogo_clamp();
    void doinker();
    void match_timer();
    void align_robot();

    hzn::motor_group LB_motors;
    vex::rotation LB_encoder;
    vex::motor intake_motor; 
    vex::rotation intake_encoder;
    vex::optical ring_color_sensor;
    vex::distance ring_distance_sensor;
    vex::digital_out mogo_clamp_piston; 
    vex::digital_out doinker_piston;
    vex::digital_out rush_piston;
    vex::digital_out lift_piston;
    
    // Intake
    bool unjam_intake = true;
    bool measuring = false; 
    float intake_jam_start_time;
    float intake_start_pos;
    bool is_reversing = false;

    vex::task intake_ring_halfway_task;
    bool is_intaking_ring_halfway;

    bool is_sorting = false;
    int color_sort_mode = 0;
    int color_swap_cooldown = 0;
    bool ring_detected = false;
    color_sort opposing_color = color_sort::NONE;
    float target_position;
    float current_position;
    float color_min = 0;
    float color_max = 0;
    const std::vector<int> blue_color_min_max = { 190, 240 };
    const std::vector<int> red_color_min_max = { 0, 35 };
    const float full_rotation = 1319.77;
    const std::vector<int> hook_positions = { 169, 605, 1035 };

    // Doinker
    bool is_extended_doinker = false;
    bool is_extended_rush = false;
    bool is_extended_lift = false;
    bool prev_doinker_state = false;
    bool prev_rush_state = false;
    bool prev_lift_state = false;

    // Mogo Clamp
    bool is_clamping = false;
    bool prev_clamp_state = false;

    // Timer
    int start_time;

    // Align Robot
    bool prev_align_state = false;
    vex::task async_aligner;
    
    // Lady Brown
    int LB_goto_state;
    
    int prev_state;

    bool is_scoring = false;
    bool prev_scoring_state = false;

    bool is_active = false;
    bool prev_active_state = false;

    bool is_holding = false;
    bool prev_holding_state = false;
    
    int LB_override_cooldown;
    bool LB_override = false;
    bool intake_override = false;

    float desired_angle;
    float LB_max_voltage;
    float LB_settle_error; 
    float LB_settle_time; 
    float LB_timeout; 
    float LB_kp; 
    float LB_ki; 
    float LB_kd;
    float LB_starti;
};