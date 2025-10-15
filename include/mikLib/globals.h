#pragma once

#include "v5.h"
#include "v5_api.h"

namespace mik {

// Drive Globals
    /** @brief Enumerates the available driver‑control schemes. */
    enum class drive_mode {
        SPLIT_ARCADE,         // Left stick Y, right stick X
        SPLIT_ARCADE_CURVED,  // Split arcade with curved turns (from lemlib)
        TANK,                 // Tank drive
        TANK_CURVED,          // Tank drive with curved turn (from lemlib)
    };

    /** @brief Explicitly specifies rotation direction when turning or swinging. */
    enum class direction {
        FASTEST, // Direction chosen automatically (shortest path)
        CW,      // Clockwise rotation
        CCW      // Counter‑clockwise rotation
    };

    enum auto_variation : int { ONE = 1, TWO = 2, THREE = 3, FOUR = 4 };
    enum class distance_position { FRONT_SENSOR, REAR_SENSOR, LEFT_SENSOR, RIGHT_SENSOR };
    enum class wall_position { TOP_WALL, BOTTOM_WALL, LEFT_WALL, RIGHT_WALL };
    
    inline constexpr unsigned int PORT_A = 0;
    inline constexpr unsigned int PORT_B = 1;
    inline constexpr unsigned int PORT_C = 2;
    inline constexpr unsigned int PORT_D = 3;
    inline constexpr unsigned int PORT_E = 4;
    inline constexpr unsigned int PORT_F = 5;
    inline constexpr unsigned int PORT_G = 6;
    inline constexpr unsigned int PORT_H = 7;

    inline constexpr distance_position front_sensor = distance_position::FRONT_SENSOR;
    inline constexpr distance_position rear_sensor = distance_position::REAR_SENSOR;
    inline constexpr distance_position left_sensor = distance_position::LEFT_SENSOR;
    inline constexpr distance_position right_sensor = distance_position::RIGHT_SENSOR;

    inline constexpr wall_position top_wall = wall_position::TOP_WALL;
    inline constexpr wall_position bottom_wall = wall_position::BOTTOM_WALL;
    inline constexpr wall_position left_wall = wall_position::LEFT_WALL;
    inline constexpr wall_position right_wall = wall_position::RIGHT_WALL;

    inline constexpr vex::gearSetting blue_6_1  = vex::gearSetting::ratio6_1;
    inline constexpr vex::gearSetting green_18_1 = vex::gearSetting::ratio18_1;
    inline constexpr vex::gearSetting red_36_1   = vex::gearSetting::ratio36_1;

    inline constexpr direction clockwise         = direction::CW;
    inline constexpr direction counter_clockwise = direction::CCW;
    inline constexpr direction cw                = direction::CW;
    inline constexpr direction ccw               = direction::CCW;

    inline constexpr auto_variation one   = auto_variation::ONE;
    inline constexpr auto_variation two   = auto_variation::TWO;
    inline constexpr auto_variation three = auto_variation::THREE;
    inline constexpr auto_variation four  = auto_variation::FOUR;

// UI Globals

    // UI main color palette
    inline const std::string UI_white =      "#ffffff"; // Text and secondary primary outline color
    inline const std::string UI_light_gray = "#999999"; // Secondary outline color
    inline const std::string UI_med_gray =   "#666666"; // Primary outline color
    inline const std::string UI_dark_gray =  "#434343"; // Secondary background color
    inline const std::string UI_black =      "#000000"; // Primary background color
    inline const std::string UI_red =        "#ff0000"; // Tertiary outline color

    // Loading screen
    inline const std::string& loading_text_bg_color = UI_dark_gray; 
    inline const std::string& loading_text_color = UI_white; 

    // Selector panel colors
    inline const std::string& selector_text_color = UI_white;
    inline const std::string& selector_bg_color = UI_black;
    inline const std::string& selector_scroll_bar_color = UI_dark_gray;
    
    inline const std::string& selector_bg_pressing_color = UI_med_gray;
    inline const std::string& selector_bg_pressed_color = UI_dark_gray;
    inline const std::string& selector_outline_color = UI_dark_gray;
    inline const std::string& selector_outline_pressing_color = UI_light_gray;
    inline const std::string& selector_outline_pressed_color = UI_light_gray;

    // Config screen colors
    inline const std::string& config_text_color = UI_white;
    inline const std::string& config_bg_color = UI_black;
    inline const std::string& config_scroll_bar_color = UI_med_gray;

    inline const std::string& config_btn_outline_color = UI_med_gray;
    inline const std::string& config_btn_outline_pressing_color = UI_white;
    inline const std::string& config_btn_outline_pressed_color = UI_red;
    
    inline const std::string config_macro_btn_bg_color = "#000000";
    inline const std::string config_data_btn_bg_color =  "#232323";
    inline const std::string config_test_btn_bg_color =  "#323232";

    // Pnematic screen colors
    inline const std::string& pnematic_bg_color = UI_black;
    inline const std::string& pnematic_text_color = UI_white;
    
    inline const std::string& pnematic_port_btn_outline_color = UI_dark_gray;
    inline const std::string& pnematic_port_btn_outline_pressing_color = UI_light_gray;
    inline const std::string& pnematic_port_btn_outline_pressed_color = UI_red;

    inline const std::string& pnematic_close_btn_bg_color = UI_black;
    inline const std::string& pnematic_close_btn_outline_color = UI_med_gray;
    inline const std::string& pnematic_close_btn_pressing_color = UI_light_gray;
    inline const std::string& pnematic_close_btn_pressed_color = UI_red;
    
    inline const std::string pnematic_A_btn_bg_color = "#303030";
    inline const std::string pnematic_B_btn_bg_color = "#595959";
    inline const std::string pnematic_C_btn_bg_color = "#858585";
    inline const std::string pnematic_D_btn_bg_color = "#cccccc";
    inline const std::string pnematic_E_btn_bg_color = "#303030";
    inline const std::string pnematic_F_btn_bg_color = "#595959";
    inline const std::string pnematic_G_btn_bg_color = "#858585";
    inline const std::string pnematic_H_btn_bg_color = "#858585";

    // Auton screen colors
    inline const std::string& auton_bg_color = UI_black;
    inline const std::string& auton_text_color = UI_white;

    inline const std::string& auton_toggle_panel_outline_color = UI_med_gray;
    inline const std::string& auton_toggle_knob_color = UI_white;
    inline const std::string& auton_pressing_toggle_bg_color = UI_light_gray;

    inline const std::string auton_toggle_blue_bg_color =  "#25a3e3";
    inline const std::string auton_toggle_red_bg_color =   "#f14a41";
    inline const std::string auton_toggle_left_bg_color =  "#d4e404";
    inline const std::string auton_toggle_right_bg_color = "#6410a4"; 
    inline const std::string auton_toggle_quals_bg_color = "#ff0000";
    inline const std::string auton_toggle_elims_bg_color = "#33e013";
    inline const std::string auton_toggle_off_bg_color =   "#666666";
    inline const std::string auton_toggle_sawp_bg_color =  "#ff9900";
    
    inline const std::string& auton_data_bg_color = UI_black;
    inline const std::string& auton_data_outline_color = UI_white;
    inline const std::string& auton_data_pressing_color = UI_red;
    inline const std::string& auton_data_pressed_color = UI_red;

    inline const std::string& auton_num_bg_color = UI_black;
    inline const std::string& auton_num_outline_color = UI_med_gray;
    inline const std::string& auton_num_pressing_color = UI_light_gray;
    inline const std::string& auton_num_pressed_color = UI_red;

    inline const std::string& auton_description_bg_color = UI_black;
    inline const std::string& auton_description_outline_color = UI_med_gray;

    inline const std::string& auton_calibrate_bg_color = UI_med_gray;
    inline const std::string& auton_calibrate_bg_pressing_color = UI_light_gray;
    inline const std::string& auton_calibrate_outline_color = UI_white;
    inline const std::string& auton_calibrate_outline_pressing_color = UI_white;
    inline const std::string& auton_calibrate_outline_pressed_color = UI_red;

    // Graph screen colors
    inline const std::string& graph_bg_color = UI_black;
    inline const std::string& graph_text_color = UI_white;

    inline const std::string& graph_chart_bg_color = UI_black;
    inline const std::string& graph_chart_outline_color = UI_med_gray;
    inline const std::string& graph_legend_bg_color = UI_black;
    inline const std::string& graph_legend_outline_color = UI_med_gray;
    
    inline const std::string& graph_reset_btn_bg_color = UI_black;
    inline const std::string& graph_reset_btn_outline_color = UI_med_gray;
    inline const std::string& graph_reset_btn_pressing_color = UI_white;
    inline const std::string& graph_reset_btn_pressed_color = UI_red;

    // Console screen colors
    inline const std::string& console_bg_color = UI_black;
    inline const std::string& console_text_color = UI_white;
    inline const std::string& console_text_bg_color = UI_med_gray;
    inline const std::string& console_outline_color = UI_med_gray;
    inline const std::string& console_scroll_bar_color = UI_med_gray;
    
    enum class color { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, BRIGHT_BLACK, BRIGHT_RED, BRIGHT_GREEN, BRIGHT_YELLOW, BRIGHT_BLUE, BRIGHT_MAGENTA, BRIGHT_CYAN, BRIGHT_WHITE }; 

    inline constexpr color black          = color::BLACK;
    inline constexpr color red            = color::RED;
    inline constexpr color green          = color::GREEN;
    inline constexpr color yellow         = color::YELLOW;
    inline constexpr color blue           = color::BLUE;
    inline constexpr color magenta        = color::MAGENTA;
    inline constexpr color cyan           = color::CYAN;
    inline constexpr color white          = color::WHITE;
    inline constexpr color bright_black   = color::BRIGHT_BLACK;
    inline constexpr color bright_red     = color::BRIGHT_RED;
    inline constexpr color bright_green   = color::BRIGHT_GREEN;
    inline constexpr color bright_yellow  = color::BRIGHT_YELLOW;
    inline constexpr color bright_blue    = color::BRIGHT_BLUE;
    inline constexpr color bright_magenta = color::BRIGHT_MAGENTA;
    inline constexpr color bright_cyan    = color::BRIGHT_CYAN;
    inline constexpr color bright_white   = color::BRIGHT_WHITE;

    enum class UI_distance_units {inches, centimeters, pixels};
    enum class input_type { CONTROLLER, TOUCHSCREEN };
    enum class text_align { LEFT, CENTER };
    enum class autons { RED_BLUE, RINGS_GOAL, QUALS_ELIMS, OFF_SAWP, OFF_SKILLS };

    #define UI_Graphic_ID    1
    #define UI_Background_ID 2
    #define UI_Label_ID      3
    #define UI_Button_ID     4
    #define UI_Toggle_ID     5
    #define UI_Textbox_ID    6

    #define SCREEN_WIDTH 480
    #define SCREEN_HEIGHT 240
}