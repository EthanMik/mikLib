#pragma once

#include "vex.h"

enum class color_sort { RED, BLUE, NONE };
enum LB_state : int { ACTIVE = 206, INACTIVE = 229, HOLDING = 170, SCORING = 43, HANG = 345, DESCORE_TOP = 79, DECSCORE_BOTTOM = 65 };

class Assembly {
public:
    Assembly(
        mik::motor_group LB_motors, 
        int LB_encoder_port, 
        mik::motor intake_motor,
        int intake_encoder_port,
        int ring_color_sensor_port,
        int ring_distance_sensor_port,
        int mogo_clamp_piston_port, 
        int doinker_piston_port,
        int rush_piston_port,
        int list_piston_port
    );
    
    void init_LB();
    void initialize_user_control();
    void stop_motors(vex::brakeType brake);

    void intake();
    void unjam_intake_task();
    void select_ring_sort_mode();
    void select_ring_sort_mode(color_sort opposing_color);
    bool ring_sort();

    void lady_brown();
    void LB_state_manager(int state);
    void log_prev_state();
    void LB_reset_states();
    void lady_brown_manual();
    void set_LB_constants(float LB_max_voltage, float LB_kp, float LB_ki, float LB_kd, float LB_starti, float LB_settle_error, float LB_settle_time, float LB_timeout);
    void move_LB_to_angle(float angle, bool buffer_data = false);
    void move_LB_to_angle(float angle, float LB_max_voltage, float LB_settle_error, float LB_settle_time, float LB_timeout, float LB_kp, float LB_ki, float LB_kd, float LB_starti, bool buffer_data = false);
    
    void mogo_clamp();
    void doinker();
    void match_timer();
    void align_robot();

    mik::motor_group LB_motors;
    mik::motor intake_motor; 
    vex::rotation LB_encoder;
    vex::rotation intake_encoder;
    vex::optical ring_color_sensor;
    vex::distance ring_distance_sensor;
    vex::digital_out mogo_clamp_piston; 
    vex::digital_out doinker_piston;
    vex::digital_out rush_piston;
    vex::digital_out lift_piston;
    
    // Intake
    vex::task _unjam_intake_task;
    bool auto_unjam = false;
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
    bool ring_distance_close = false;
    int distance_start = 0;
    color_sort opposing_color = color_sort::NONE;
    float target_position;
    float current_position;
    float color_min = 0;
    float color_max = 0;
    const std::vector<int> blue_color_min_max = { 190, 240 };
    const std::vector<int> red_color_min_max = { 0, 35 };
    const float full_rotation = 473.6;
    const std::vector<int> hook_positions = { 85, 306 };

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
    int time_remaining = 0;


    // Align Robot
    bool is_aligning = false;
    bool prev_align_state = false;
    vex::task async_aligner;
    
    // Lady Brown
    vex::task async_LB;
    int LB_goto_state_task = 0;
    int LB_queued_state;
    int LB_goto_state;
    
    int prev_state;

    bool is_scoring = false;
    bool prev_scoring_state = false;

    bool is_active = false;
    bool prev_active_state = false;

    bool is_holding = false;
    bool prev_holding_state = false;

    bool is_hanging = false;
    bool prev_hanging_state = false;

    bool is_descoring_top = false;
    bool prev_descoring_top_state = false;

    bool is_descoring_bot = false;
    bool prev_descoring_bot_state = false;
    
    int LB_prev_state = 0;
    std::vector<std::reference_wrapper<bool>> LB_states = {is_scoring, is_active, is_holding, is_hanging, is_descoring_top, is_descoring_bot};

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