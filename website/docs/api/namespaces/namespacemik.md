---
title: mik

---

# mik



## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[mik::UI_auton_screen](/api/classes/classmik_1_1_u_i__auton__screen)**  |
| class | **[mik::UI_component](/api/classes/classmik_1_1_u_i__component)**  |
| class | **[mik::UI_config_screen](/api/classes/classmik_1_1_u_i__config__screen)**  |
| class | **[mik::UI_console_screen](/api/classes/classmik_1_1_u_i__console__screen)**  |
| class | **[mik::UI_graph_screen](/api/classes/classmik_1_1_u_i__graph__screen)**  |
| class | **[mik::UI_motors_screen](/api/classes/classmik_1_1_u_i__motors__screen)**  |
| class | **[mik::background](/api/classes/classmik_1_1background)**  |
| class | **[mik::button](/api/classes/classmik_1_1button)**  |
| class | **[mik::circle](/api/classes/classmik_1_1circle)**  |
| class | **[mik::controller_btn](/api/classes/classmik_1_1controller__btn)**  |
| class | **[mik::distance](/api/classes/classmik_1_1distance)**  |
| class | **[mik::distance_reset](/api/classes/classmik_1_1distance__reset)**  |
| class | **[mik::drawable](/api/classes/classmik_1_1drawable)**  |
| class | **[mik::graphic](/api/classes/classmik_1_1graphic)**  |
| class | **[mik::group](/api/classes/classmik_1_1group)**  |
| class | **[mik::image](/api/classes/classmik_1_1image)**  |
| class | **[mik::label](/api/classes/classmik_1_1label)**  |
| class | **[mik::line](/api/classes/classmik_1_1line)**  |
| class | **[mik::motor](/api/classes/classmik_1_1motor)**  |
| class | **[mik::motor_group](/api/classes/classmik_1_1motor__group)**  |
| class | **[mik::piston](/api/classes/classmik_1_1piston)**  |
| class | **[mik::pixel](/api/classes/classmik_1_1pixel)**  |
| class | **[mik::rectangle](/api/classes/classmik_1_1rectangle)**  |
| class | **[mik::screen](/api/classes/classmik_1_1screen)**  |
| class | **[mik::text](/api/classes/classmik_1_1text)**  |
| class | **[mik::textbox](/api/classes/classmik_1_1textbox)**  |
| class | **[mik::toggle](/api/classes/classmik_1_1toggle)**  |
| class | **[mik::tracker](/api/classes/classmik_1_1tracker)**  |

## Types

|                | Name           |
| -------------- | -------------- |
| enum class| **[UI_distance_units](/api/namespaces/namespacemik#enum-ui-distance-units)** { centimeters, inches, pixels} |
| enum class| **[alliance_colors](/api/namespaces/namespacemik#enum-alliance-colors)** { BLUE, RED} |
| enum int | **[auto_variation](/api/namespaces/namespacemik#enum-auto-variation)** { FOUR = 4, ONE = 1, THREE = 3, TWO = 2} |
| enum class| **[autons](/api/namespaces/namespacemik#enum-autons)** { OFF_SAWP, OFF_SKILLS, QUALS_ELIMS, RED_BLUE, RINGS_GOAL} |
| enum class| **[color](/api/namespaces/namespacemik#enum-color)** { BLACK, BLUE, BRIGHT_BLACK, BRIGHT_BLUE, BRIGHT_CYAN, BRIGHT_GREEN, BRIGHT_MAGENTA, BRIGHT_RED, BRIGHT_WHITE, BRIGHT_YELLOW, CYAN, GREEN, MAGENTA, RED, WHITE, YELLOW} |
| enum class| **[distance_position](/api/namespaces/namespacemik#enum-distance-position)** { FRONT_SENSOR, LEFT_SENSOR, REAR_SENSOR, RIGHT_SENSOR} |
| enum class| **[drive_direction](/api/namespaces/namespacemik#enum-drive-direction)** { FASTEST, FWD, REV} |
| enum class| **[drive_mode](/api/namespaces/namespacemik#enum-drive-mode)** { SPLIT_ARCADE, SPLIT_ARCADE_CURVED, TANK, TANK_CURVED}<br>Enumerates the available driver‑control schemes.  |
| enum class| **[input_type](/api/namespaces/namespacemik#enum-input-type)** { CONTROLLER, TOUCHSCREEN} |
| enum class| **[text_align](/api/namespaces/namespacemik#enum-text-align)** { CENTER, LEFT} |
| enum class| **[tracker_mode](/api/namespaces/namespacemik#enum-tracker-mode)** { FORWARD_TRACKER, MOTOR_ENCODER} |
| enum class| **[turn_direction](/api/namespaces/namespacemik#enum-turn-direction)** { CCW, CW, FASTEST}<br>Explicitly specifies rotation direction when turning or swinging.  |
| enum class| **[wall_position](/api/namespaces/namespacemik#enum-wall-position)** { AUTO, BOTTOM_WALL, LEFT_WALL, RIGHT_WALL, TOP_WALL} |

## Functions

|                | Name           |
| -------------- | -------------- |
| std::vector< [mik::motor](/api/classes/classmik_1_1motor) * > & | **[motor_registry](/api/namespaces/namespacemik#function-motor-registry)**() |

## Attributes

|                | Name           |
| -------------- | -------------- |
| int | **[PORT0](/api/namespaces/namespacemik#variable-port0)**  |
| int | **[PORT_A](/api/namespaces/namespacemik#variable-port-a)**  |
| int | **[PORT_B](/api/namespaces/namespacemik#variable-port-b)**  |
| int | **[PORT_C](/api/namespaces/namespacemik#variable-port-c)**  |
| int | **[PORT_D](/api/namespaces/namespacemik#variable-port-d)**  |
| int | **[PORT_E](/api/namespaces/namespacemik#variable-port-e)**  |
| int | **[PORT_F](/api/namespaces/namespacemik#variable-port-f)**  |
| int | **[PORT_G](/api/namespaces/namespacemik#variable-port-g)**  |
| int | **[PORT_H](/api/namespaces/namespacemik#variable-port-h)**  |
| const std::string | **[UI_black](/api/namespaces/namespacemik#variable-ui-black)**  |
| const std::string | **[UI_dark_gray](/api/namespaces/namespacemik#variable-ui-dark-gray)**  |
| const std::string | **[UI_light_gray](/api/namespaces/namespacemik#variable-ui-light-gray)**  |
| const std::string | **[UI_med_gray](/api/namespaces/namespacemik#variable-ui-med-gray)**  |
| const std::string | **[UI_red](/api/namespaces/namespacemik#variable-ui-red)**  |
| const std::string | **[UI_white](/api/namespaces/namespacemik#variable-ui-white)**  |
| [wall_position](/api/namespaces/namespacemik#enum-wall-position) | **[auto_detect_wall](/api/namespaces/namespacemik#variable-auto-detect-wall)**  |
| const std::string & | **[auton_bg_color](/api/namespaces/namespacemik#variable-auton-bg-color)**  |
| const std::string & | **[auton_calibrate_bg_color](/api/namespaces/namespacemik#variable-auton-calibrate-bg-color)**  |
| const std::string & | **[auton_calibrate_bg_pressing_color](/api/namespaces/namespacemik#variable-auton-calibrate-bg-pressing-color)**  |
| const std::string & | **[auton_calibrate_outline_color](/api/namespaces/namespacemik#variable-auton-calibrate-outline-color)**  |
| const std::string & | **[auton_calibrate_outline_pressed_color](/api/namespaces/namespacemik#variable-auton-calibrate-outline-pressed-color)**  |
| const std::string & | **[auton_calibrate_outline_pressing_color](/api/namespaces/namespacemik#variable-auton-calibrate-outline-pressing-color)**  |
| const std::string & | **[auton_data_bg_color](/api/namespaces/namespacemik#variable-auton-data-bg-color)**  |
| const std::string & | **[auton_data_outline_color](/api/namespaces/namespacemik#variable-auton-data-outline-color)**  |
| const std::string & | **[auton_data_pressed_color](/api/namespaces/namespacemik#variable-auton-data-pressed-color)**  |
| const std::string & | **[auton_data_pressing_color](/api/namespaces/namespacemik#variable-auton-data-pressing-color)**  |
| const std::string & | **[auton_description_bg_color](/api/namespaces/namespacemik#variable-auton-description-bg-color)**  |
| const std::string & | **[auton_description_outline_color](/api/namespaces/namespacemik#variable-auton-description-outline-color)**  |
| const std::string & | **[auton_num_bg_color](/api/namespaces/namespacemik#variable-auton-num-bg-color)**  |
| const std::string & | **[auton_num_outline_color](/api/namespaces/namespacemik#variable-auton-num-outline-color)**  |
| const std::string & | **[auton_num_pressed_color](/api/namespaces/namespacemik#variable-auton-num-pressed-color)**  |
| const std::string & | **[auton_num_pressing_color](/api/namespaces/namespacemik#variable-auton-num-pressing-color)**  |
| const std::string & | **[auton_pressing_toggle_bg_color](/api/namespaces/namespacemik#variable-auton-pressing-toggle-bg-color)**  |
| const std::string & | **[auton_text_color](/api/namespaces/namespacemik#variable-auton-text-color)**  |
| const std::string | **[auton_toggle_blue_bg_color](/api/namespaces/namespacemik#variable-auton-toggle-blue-bg-color)**  |
| const std::string | **[auton_toggle_elims_bg_color](/api/namespaces/namespacemik#variable-auton-toggle-elims-bg-color)**  |
| const std::string & | **[auton_toggle_knob_color](/api/namespaces/namespacemik#variable-auton-toggle-knob-color)**  |
| const std::string | **[auton_toggle_left_bg_color](/api/namespaces/namespacemik#variable-auton-toggle-left-bg-color)**  |
| const std::string | **[auton_toggle_off_bg_color](/api/namespaces/namespacemik#variable-auton-toggle-off-bg-color)**  |
| const std::string & | **[auton_toggle_panel_outline_color](/api/namespaces/namespacemik#variable-auton-toggle-panel-outline-color)**  |
| const std::string | **[auton_toggle_quals_bg_color](/api/namespaces/namespacemik#variable-auton-toggle-quals-bg-color)**  |
| const std::string | **[auton_toggle_red_bg_color](/api/namespaces/namespacemik#variable-auton-toggle-red-bg-color)**  |
| const std::string | **[auton_toggle_right_bg_color](/api/namespaces/namespacemik#variable-auton-toggle-right-bg-color)**  |
| const std::string | **[auton_toggle_sawp_bg_color](/api/namespaces/namespacemik#variable-auton-toggle-sawp-bg-color)**  |
| [color](/api/namespaces/namespacemik#enum-color) | **[black](/api/namespaces/namespacemik#variable-black)**  |
| [color](/api/namespaces/namespacemik#enum-color) | **[blue](/api/namespaces/namespacemik#variable-blue)**  |
| vex::gearSetting | **[blue_6_1](/api/namespaces/namespacemik#variable-blue-6-1)**  |
| [wall_position](/api/namespaces/namespacemik#enum-wall-position) | **[bottom_wall](/api/namespaces/namespacemik#variable-bottom-wall)**  |
| [color](/api/namespaces/namespacemik#enum-color) | **[bright_black](/api/namespaces/namespacemik#variable-bright-black)**  |
| [color](/api/namespaces/namespacemik#enum-color) | **[bright_blue](/api/namespaces/namespacemik#variable-bright-blue)**  |
| [color](/api/namespaces/namespacemik#enum-color) | **[bright_cyan](/api/namespaces/namespacemik#variable-bright-cyan)**  |
| [color](/api/namespaces/namespacemik#enum-color) | **[bright_green](/api/namespaces/namespacemik#variable-bright-green)**  |
| [color](/api/namespaces/namespacemik#enum-color) | **[bright_magenta](/api/namespaces/namespacemik#variable-bright-magenta)**  |
| [color](/api/namespaces/namespacemik#enum-color) | **[bright_red](/api/namespaces/namespacemik#variable-bright-red)**  |
| [color](/api/namespaces/namespacemik#enum-color) | **[bright_white](/api/namespaces/namespacemik#variable-bright-white)**  |
| [color](/api/namespaces/namespacemik#enum-color) | **[bright_yellow](/api/namespaces/namespacemik#variable-bright-yellow)**  |
| [turn_direction](/api/namespaces/namespacemik#enum-turn-direction) | **[ccw](/api/namespaces/namespacemik#variable-ccw)**  |
| [turn_direction](/api/namespaces/namespacemik#enum-turn-direction) | **[clockwise](/api/namespaces/namespacemik#variable-clockwise)**  |
| const std::string & | **[config_bg_color](/api/namespaces/namespacemik#variable-config-bg-color)**  |
| const std::string & | **[config_btn_outline_color](/api/namespaces/namespacemik#variable-config-btn-outline-color)**  |
| const std::string & | **[config_btn_outline_pressed_color](/api/namespaces/namespacemik#variable-config-btn-outline-pressed-color)**  |
| const std::string & | **[config_btn_outline_pressing_color](/api/namespaces/namespacemik#variable-config-btn-outline-pressing-color)**  |
| const std::string | **[config_data_btn_bg_color](/api/namespaces/namespacemik#variable-config-data-btn-bg-color)**  |
| const std::string | **[config_macro_btn_bg_color](/api/namespaces/namespacemik#variable-config-macro-btn-bg-color)**  |
| const std::string & | **[config_scroll_bar_color](/api/namespaces/namespacemik#variable-config-scroll-bar-color)**  |
| const std::string | **[config_test_btn_bg_color](/api/namespaces/namespacemik#variable-config-test-btn-bg-color)**  |
| const std::string & | **[config_text_color](/api/namespaces/namespacemik#variable-config-text-color)**  |
| const std::string & | **[console_bg_color](/api/namespaces/namespacemik#variable-console-bg-color)**  |
| const std::string & | **[console_outline_color](/api/namespaces/namespacemik#variable-console-outline-color)**  |
| const std::string & | **[console_scroll_bar_color](/api/namespaces/namespacemik#variable-console-scroll-bar-color)**  |
| const std::string & | **[console_text_bg_color](/api/namespaces/namespacemik#variable-console-text-bg-color)**  |
| const std::string & | **[console_text_color](/api/namespaces/namespacemik#variable-console-text-color)**  |
| [turn_direction](/api/namespaces/namespacemik#enum-turn-direction) | **[counter_clockwise](/api/namespaces/namespacemik#variable-counter-clockwise)**  |
| [turn_direction](/api/namespaces/namespacemik#enum-turn-direction) | **[cw](/api/namespaces/namespacemik#variable-cw)**  |
| [color](/api/namespaces/namespacemik#enum-color) | **[cyan](/api/namespaces/namespacemik#variable-cyan)**  |
| vex::fontType | **[default_font](/api/namespaces/namespacemik#variable-default-font)**  |
| [tracker_mode](/api/namespaces/namespacemik#enum-tracker-mode) | **[forward_tracker](/api/namespaces/namespacemik#variable-forward-tracker)**  |
| [drive_direction](/api/namespaces/namespacemik#enum-drive-direction) | **[forwards](/api/namespaces/namespacemik#variable-forwards)**  |
| [auto_variation](/api/namespaces/namespacemik#enum-auto-variation) | **[four](/api/namespaces/namespacemik#variable-four)**  |
| [distance_position](/api/namespaces/namespacemik#enum-distance-position) | **[front_sensor](/api/namespaces/namespacemik#variable-front-sensor)**  |
| const std::string & | **[graph_bg_color](/api/namespaces/namespacemik#variable-graph-bg-color)**  |
| const std::string & | **[graph_chart_bg_color](/api/namespaces/namespacemik#variable-graph-chart-bg-color)**  |
| const std::string & | **[graph_chart_outline_color](/api/namespaces/namespacemik#variable-graph-chart-outline-color)**  |
| const std::string & | **[graph_legend_bg_color](/api/namespaces/namespacemik#variable-graph-legend-bg-color)**  |
| const std::string & | **[graph_legend_outline_color](/api/namespaces/namespacemik#variable-graph-legend-outline-color)**  |
| const std::string & | **[graph_reset_btn_bg_color](/api/namespaces/namespacemik#variable-graph-reset-btn-bg-color)**  |
| const std::string & | **[graph_reset_btn_outline_color](/api/namespaces/namespacemik#variable-graph-reset-btn-outline-color)**  |
| const std::string & | **[graph_reset_btn_pressed_color](/api/namespaces/namespacemik#variable-graph-reset-btn-pressed-color)**  |
| const std::string & | **[graph_reset_btn_pressing_color](/api/namespaces/namespacemik#variable-graph-reset-btn-pressing-color)**  |
| const std::string & | **[graph_text_color](/api/namespaces/namespacemik#variable-graph-text-color)**  |
| [color](/api/namespaces/namespacemik#enum-color) | **[green](/api/namespaces/namespacemik#variable-green)**  |
| vex::gearSetting | **[green_18_1](/api/namespaces/namespacemik#variable-green-18-1)**  |
| [distance_position](/api/namespaces/namespacemik#enum-distance-position) | **[left_sensor](/api/namespaces/namespacemik#variable-left-sensor)**  |
| [wall_position](/api/namespaces/namespacemik#enum-wall-position) | **[left_wall](/api/namespaces/namespacemik#variable-left-wall)**  |
| const std::string & | **[loading_text_bg_color](/api/namespaces/namespacemik#variable-loading-text-bg-color)**  |
| const std::string & | **[loading_text_color](/api/namespaces/namespacemik#variable-loading-text-color)**  |
| [color](/api/namespaces/namespacemik#enum-color) | **[magenta](/api/namespaces/namespacemik#variable-magenta)**  |
| [tracker_mode](/api/namespaces/namespacemik#enum-tracker-mode) | **[motor_encoder](/api/namespaces/namespacemik#variable-motor-encoder)**  |
| const std::string & | **[motors_bg_color](/api/namespaces/namespacemik#variable-motors-bg-color)**  |
| const std::string & | **[motors_close_button_bg_color](/api/namespaces/namespacemik#variable-motors-close-button-bg-color)**  |
| const std::string & | **[motors_close_button_outline_color](/api/namespaces/namespacemik#variable-motors-close-button-outline-color)**  |
| const std::string & | **[motors_close_button_pressed_color](/api/namespaces/namespacemik#variable-motors-close-button-pressed-color)**  |
| const std::string & | **[motors_close_button_pressing_color](/api/namespaces/namespacemik#variable-motors-close-button-pressing-color)**  |
| const std::string & | **[motors_left_drive_btn_bg_color](/api/namespaces/namespacemik#variable-motors-left-drive-btn-bg-color)**  |
| const std::string & | **[motors_port_btn_outline_color](/api/namespaces/namespacemik#variable-motors-port-btn-outline-color)**  |
| const std::string & | **[motors_port_btn_pressed_color](/api/namespaces/namespacemik#variable-motors-port-btn-pressed-color)**  |
| const std::string & | **[motors_port_btn_pressing_color](/api/namespaces/namespacemik#variable-motors-port-btn-pressing-color)**  |
| const std::string & | **[motors_ports_btn_bg](/api/namespaces/namespacemik#variable-motors-ports-btn-bg)**  |
| const std::string & | **[motors_ports_btn_closed_color](/api/namespaces/namespacemik#variable-motors-ports-btn-closed-color)**  |
| const std::string & | **[motors_ports_btn_current_color](/api/namespaces/namespacemik#variable-motors-ports-btn-current-color)**  |
| const std::string & | **[motors_ports_btn_open_color](/api/namespaces/namespacemik#variable-motors-ports-btn-open-color)**  |
| const std::string & | **[motors_ports_btn_pressing_color](/api/namespaces/namespacemik#variable-motors-ports-btn-pressing-color)**  |
| const std::string & | **[motors_ports_text_color](/api/namespaces/namespacemik#variable-motors-ports-text-color)**  |
| const std::string & | **[motors_spin_left_bg_color](/api/namespaces/namespacemik#variable-motors-spin-left-bg-color)**  |
| const std::string & | **[motors_spin_left_outline_color](/api/namespaces/namespacemik#variable-motors-spin-left-outline-color)**  |
| const std::string & | **[motors_spin_left_pressed_color](/api/namespaces/namespacemik#variable-motors-spin-left-pressed-color)**  |
| const std::string & | **[motors_spin_left_pressing_color](/api/namespaces/namespacemik#variable-motors-spin-left-pressing-color)**  |
| const std::string & | **[motors_spin_right_bg_color](/api/namespaces/namespacemik#variable-motors-spin-right-bg-color)**  |
| const std::string & | **[motors_spin_right_outline_color](/api/namespaces/namespacemik#variable-motors-spin-right-outline-color)**  |
| const std::string & | **[motors_spin_right_pressed_color](/api/namespaces/namespacemik#variable-motors-spin-right-pressed-color)**  |
| const std::string & | **[motors_spin_right_pressing_color](/api/namespaces/namespacemik#variable-motors-spin-right-pressing-color)**  |
| const std::string & | **[motors_volt_btn_bg_color](/api/namespaces/namespacemik#variable-motors-volt-btn-bg-color)**  |
| const std::string & | **[motors_volt_btn_outline_color](/api/namespaces/namespacemik#variable-motors-volt-btn-outline-color)**  |
| const std::string & | **[motors_volt_btn_pressed_color](/api/namespaces/namespacemik#variable-motors-volt-btn-pressed-color)**  |
| const std::string & | **[motors_volt_btn_pressing_color](/api/namespaces/namespacemik#variable-motors-volt-btn-pressing-color)**  |
| [auto_variation](/api/namespaces/namespacemik#enum-auto-variation) | **[one](/api/namespaces/namespacemik#variable-one)**  |
| const std::string | **[pnematic_A_btn_bg_color](/api/namespaces/namespacemik#variable-pnematic-a-btn-bg-color)**  |
| const std::string | **[pnematic_B_btn_bg_color](/api/namespaces/namespacemik#variable-pnematic-b-btn-bg-color)**  |
| const std::string | **[pnematic_C_btn_bg_color](/api/namespaces/namespacemik#variable-pnematic-c-btn-bg-color)**  |
| const std::string | **[pnematic_D_btn_bg_color](/api/namespaces/namespacemik#variable-pnematic-d-btn-bg-color)**  |
| const std::string | **[pnematic_E_btn_bg_color](/api/namespaces/namespacemik#variable-pnematic-e-btn-bg-color)**  |
| const std::string | **[pnematic_F_btn_bg_color](/api/namespaces/namespacemik#variable-pnematic-f-btn-bg-color)**  |
| const std::string | **[pnematic_G_btn_bg_color](/api/namespaces/namespacemik#variable-pnematic-g-btn-bg-color)**  |
| const std::string | **[pnematic_H_btn_bg_color](/api/namespaces/namespacemik#variable-pnematic-h-btn-bg-color)**  |
| const std::string & | **[pnematic_bg_color](/api/namespaces/namespacemik#variable-pnematic-bg-color)**  |
| const std::string & | **[pnematic_close_btn_bg_color](/api/namespaces/namespacemik#variable-pnematic-close-btn-bg-color)**  |
| const std::string & | **[pnematic_close_btn_outline_color](/api/namespaces/namespacemik#variable-pnematic-close-btn-outline-color)**  |
| const std::string & | **[pnematic_close_btn_pressed_color](/api/namespaces/namespacemik#variable-pnematic-close-btn-pressed-color)**  |
| const std::string & | **[pnematic_close_btn_pressing_color](/api/namespaces/namespacemik#variable-pnematic-close-btn-pressing-color)**  |
| const std::string & | **[pnematic_port_btn_outline_color](/api/namespaces/namespacemik#variable-pnematic-port-btn-outline-color)**  |
| const std::string & | **[pnematic_port_btn_outline_pressed_color](/api/namespaces/namespacemik#variable-pnematic-port-btn-outline-pressed-color)**  |
| const std::string & | **[pnematic_port_btn_outline_pressing_color](/api/namespaces/namespacemik#variable-pnematic-port-btn-outline-pressing-color)**  |
| const std::string & | **[pnematic_text_color](/api/namespaces/namespacemik#variable-pnematic-text-color)**  |
| [distance_position](/api/namespaces/namespacemik#enum-distance-position) | **[rear_sensor](/api/namespaces/namespacemik#variable-rear-sensor)**  |
| [color](/api/namespaces/namespacemik#enum-color) | **[red](/api/namespaces/namespacemik#variable-red)**  |
| vex::gearSetting | **[red_36_1](/api/namespaces/namespacemik#variable-red-36-1)**  |
| [drive_direction](/api/namespaces/namespacemik#enum-drive-direction) | **[reversed](/api/namespaces/namespacemik#variable-reversed)**  |
| [distance_position](/api/namespaces/namespacemik#enum-distance-position) | **[right_sensor](/api/namespaces/namespacemik#variable-right-sensor)**  |
| [wall_position](/api/namespaces/namespacemik#enum-wall-position) | **[right_wall](/api/namespaces/namespacemik#variable-right-wall)**  |
| const std::string & | **[selector_bg_color](/api/namespaces/namespacemik#variable-selector-bg-color)**  |
| const std::string & | **[selector_bg_pressed_color](/api/namespaces/namespacemik#variable-selector-bg-pressed-color)**  |
| const std::string & | **[selector_bg_pressing_color](/api/namespaces/namespacemik#variable-selector-bg-pressing-color)**  |
| const std::string & | **[selector_outline_color](/api/namespaces/namespacemik#variable-selector-outline-color)**  |
| const std::string & | **[selector_outline_pressed_color](/api/namespaces/namespacemik#variable-selector-outline-pressed-color)**  |
| const std::string & | **[selector_outline_pressing_color](/api/namespaces/namespacemik#variable-selector-outline-pressing-color)**  |
| const std::string & | **[selector_scroll_bar_color](/api/namespaces/namespacemik#variable-selector-scroll-bar-color)**  |
| const std::string & | **[selector_text_color](/api/namespaces/namespacemik#variable-selector-text-color)**  |
| [auto_variation](/api/namespaces/namespacemik#enum-auto-variation) | **[three](/api/namespaces/namespacemik#variable-three)**  |
| [wall_position](/api/namespaces/namespacemik#enum-wall-position) | **[top_wall](/api/namespaces/namespacemik#variable-top-wall)**  |
| [auto_variation](/api/namespaces/namespacemik#enum-auto-variation) | **[two](/api/namespaces/namespacemik#variable-two)**  |
| [color](/api/namespaces/namespacemik#enum-color) | **[white](/api/namespaces/namespacemik#variable-white)**  |
| [color](/api/namespaces/namespacemik#enum-color) | **[yellow](/api/namespaces/namespacemik#variable-yellow)**  |

## Types Documentation

### enum UI_distance_units

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| centimeters | |   |
| inches | |   |
| pixels | |   |




### enum alliance_colors

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| BLUE | |   |
| RED | |   |




### enum auto_variation

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| FOUR | 4|   |
| ONE | 1|   |
| THREE | 3|   |
| TWO | 2|   |




### enum autons

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| OFF_SAWP | |   |
| OFF_SKILLS | |   |
| QUALS_ELIMS | |   |
| RED_BLUE | |   |
| RINGS_GOAL | |   |




### enum color

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| BLACK | |   |
| BLUE | |   |
| BRIGHT_BLACK | |   |
| BRIGHT_BLUE | |   |
| BRIGHT_CYAN | |   |
| BRIGHT_GREEN | |   |
| BRIGHT_MAGENTA | |   |
| BRIGHT_RED | |   |
| BRIGHT_WHITE | |   |
| BRIGHT_YELLOW | |   |
| CYAN | |   |
| GREEN | |   |
| MAGENTA | |   |
| RED | |   |
| WHITE | |   |
| YELLOW | |   |




### enum distance_position

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| FRONT_SENSOR | |   |
| LEFT_SENSOR | |   |
| REAR_SENSOR | |   |
| RIGHT_SENSOR | |   |




### enum drive_direction

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| FASTEST | |   |
| FWD | |   |
| REV | |   |




### enum drive_mode

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| SPLIT_ARCADE | |   |
| SPLIT_ARCADE_CURVED | |   |
| TANK | |   |
| TANK_CURVED | |   |



Enumerates the available driver‑control schemes. 

### enum input_type

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| CONTROLLER | |   |
| TOUCHSCREEN | |   |




### enum text_align

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| CENTER | |   |
| LEFT | |   |




### enum tracker_mode

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| FORWARD_TRACKER | |   |
| MOTOR_ENCODER | |   |




### enum turn_direction

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| CCW | |   |
| CW | |   |
| FASTEST | |   |



Explicitly specifies rotation direction when turning or swinging. 

### enum wall_position

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| AUTO | |   |
| BOTTOM_WALL | |   |
| LEFT_WALL | |   |
| RIGHT_WALL | |   |
| TOP_WALL | |   |





## Functions Documentation

### function motor_registry

```cpp
std::vector< mik::motor * > & motor_registry()
```


**Return**: Reference to the global registry of all logged motors 


## Attributes Documentation

### variable PORT0

```cpp
int PORT0 = INT16_MAX;
```


### variable PORT_A

```cpp
int PORT_A = -1;
```


### variable PORT_B

```cpp
int PORT_B = -2;
```


### variable PORT_C

```cpp
int PORT_C = -3;
```


### variable PORT_D

```cpp
int PORT_D = -4;
```


### variable PORT_E

```cpp
int PORT_E = -5;
```


### variable PORT_F

```cpp
int PORT_F = -6;
```


### variable PORT_G

```cpp
int PORT_G = -7;
```


### variable PORT_H

```cpp
int PORT_H = -8;
```


### variable UI_black

```cpp
const std::string UI_black =      "#000000";
```


### variable UI_dark_gray

```cpp
const std::string UI_dark_gray =  "#434343";
```


### variable UI_light_gray

```cpp
const std::string UI_light_gray = "#999999";
```


### variable UI_med_gray

```cpp
const std::string UI_med_gray =   "#666666";
```


### variable UI_red

```cpp
const std::string UI_red =        "#ff0000";
```


### variable UI_white

```cpp
const std::string UI_white =      "#ffffff";
```


### variable auto_detect_wall

```cpp
wall_position auto_detect_wall = wall_position::AUTO;
```


### variable auton_bg_color

```cpp
const std::string & auton_bg_color = UI_black;
```


### variable auton_calibrate_bg_color

```cpp
const std::string & auton_calibrate_bg_color = UI_med_gray;
```


### variable auton_calibrate_bg_pressing_color

```cpp
const std::string & auton_calibrate_bg_pressing_color = UI_light_gray;
```


### variable auton_calibrate_outline_color

```cpp
const std::string & auton_calibrate_outline_color = UI_white;
```


### variable auton_calibrate_outline_pressed_color

```cpp
const std::string & auton_calibrate_outline_pressed_color = UI_red;
```


### variable auton_calibrate_outline_pressing_color

```cpp
const std::string & auton_calibrate_outline_pressing_color = UI_white;
```


### variable auton_data_bg_color

```cpp
const std::string & auton_data_bg_color = UI_black;
```


### variable auton_data_outline_color

```cpp
const std::string & auton_data_outline_color = UI_white;
```


### variable auton_data_pressed_color

```cpp
const std::string & auton_data_pressed_color = UI_red;
```


### variable auton_data_pressing_color

```cpp
const std::string & auton_data_pressing_color = UI_red;
```


### variable auton_description_bg_color

```cpp
const std::string & auton_description_bg_color = UI_black;
```


### variable auton_description_outline_color

```cpp
const std::string & auton_description_outline_color = UI_med_gray;
```


### variable auton_num_bg_color

```cpp
const std::string & auton_num_bg_color = UI_black;
```


### variable auton_num_outline_color

```cpp
const std::string & auton_num_outline_color = UI_med_gray;
```


### variable auton_num_pressed_color

```cpp
const std::string & auton_num_pressed_color = UI_red;
```


### variable auton_num_pressing_color

```cpp
const std::string & auton_num_pressing_color = UI_light_gray;
```


### variable auton_pressing_toggle_bg_color

```cpp
const std::string & auton_pressing_toggle_bg_color = UI_light_gray;
```


### variable auton_text_color

```cpp
const std::string & auton_text_color = UI_white;
```


### variable auton_toggle_blue_bg_color

```cpp
const std::string auton_toggle_blue_bg_color =  "#25a3e3";
```


### variable auton_toggle_elims_bg_color

```cpp
const std::string auton_toggle_elims_bg_color = "#33e013";
```


### variable auton_toggle_knob_color

```cpp
const std::string & auton_toggle_knob_color = UI_white;
```


### variable auton_toggle_left_bg_color

```cpp
const std::string auton_toggle_left_bg_color =  "#d4e404";
```


### variable auton_toggle_off_bg_color

```cpp
const std::string auton_toggle_off_bg_color =   "#666666";
```


### variable auton_toggle_panel_outline_color

```cpp
const std::string & auton_toggle_panel_outline_color = UI_med_gray;
```


### variable auton_toggle_quals_bg_color

```cpp
const std::string auton_toggle_quals_bg_color = "#ff0000";
```


### variable auton_toggle_red_bg_color

```cpp
const std::string auton_toggle_red_bg_color =   "#f14a41";
```


### variable auton_toggle_right_bg_color

```cpp
const std::string auton_toggle_right_bg_color = "#6410a4";
```


### variable auton_toggle_sawp_bg_color

```cpp
const std::string auton_toggle_sawp_bg_color =  "#ff9900";
```


### variable black

```cpp
color black = color::BLACK;
```


### variable blue

```cpp
color blue = color::BLUE;
```


### variable blue_6_1

```cpp
vex::gearSetting blue_6_1 = vex::gearSetting::ratio6_1;
```


### variable bottom_wall

```cpp
wall_position bottom_wall = wall_position::BOTTOM_WALL;
```


### variable bright_black

```cpp
color bright_black = color::BRIGHT_BLACK;
```


### variable bright_blue

```cpp
color bright_blue = color::BRIGHT_BLUE;
```


### variable bright_cyan

```cpp
color bright_cyan = color::BRIGHT_CYAN;
```


### variable bright_green

```cpp
color bright_green = color::BRIGHT_GREEN;
```


### variable bright_magenta

```cpp
color bright_magenta = color::BRIGHT_MAGENTA;
```


### variable bright_red

```cpp
color bright_red = color::BRIGHT_RED;
```


### variable bright_white

```cpp
color bright_white = color::BRIGHT_WHITE;
```


### variable bright_yellow

```cpp
color bright_yellow = color::BRIGHT_YELLOW;
```


### variable ccw

```cpp
turn_direction ccw = turn_direction::CCW;
```


### variable clockwise

```cpp
turn_direction clockwise = turn_direction::CW;
```


### variable config_bg_color

```cpp
const std::string & config_bg_color = UI_black;
```


### variable config_btn_outline_color

```cpp
const std::string & config_btn_outline_color = UI_med_gray;
```


### variable config_btn_outline_pressed_color

```cpp
const std::string & config_btn_outline_pressed_color = UI_red;
```


### variable config_btn_outline_pressing_color

```cpp
const std::string & config_btn_outline_pressing_color = UI_white;
```


### variable config_data_btn_bg_color

```cpp
const std::string config_data_btn_bg_color =  "#232323";
```


### variable config_macro_btn_bg_color

```cpp
const std::string config_macro_btn_bg_color = "#000000";
```


### variable config_scroll_bar_color

```cpp
const std::string & config_scroll_bar_color = UI_med_gray;
```


### variable config_test_btn_bg_color

```cpp
const std::string config_test_btn_bg_color =  "#323232";
```


### variable config_text_color

```cpp
const std::string & config_text_color = UI_white;
```


### variable console_bg_color

```cpp
const std::string & console_bg_color = UI_black;
```


### variable console_outline_color

```cpp
const std::string & console_outline_color = UI_med_gray;
```


### variable console_scroll_bar_color

```cpp
const std::string & console_scroll_bar_color = UI_med_gray;
```


### variable console_text_bg_color

```cpp
const std::string & console_text_bg_color = UI_med_gray;
```


### variable console_text_color

```cpp
const std::string & console_text_color = UI_white;
```


### variable counter_clockwise

```cpp
turn_direction counter_clockwise = turn_direction::CCW;
```


### variable cw

```cpp
turn_direction cw = turn_direction::CW;
```


### variable cyan

```cpp
color cyan = color::CYAN;
```


### variable default_font

```cpp
vex::fontType default_font = vex::fontType::mono20;
```


### variable forward_tracker

```cpp
tracker_mode forward_tracker = tracker_mode::FORWARD_TRACKER;
```


### variable forwards

```cpp
drive_direction forwards = drive_direction::FWD;
```


### variable four

```cpp
auto_variation four = auto_variation::FOUR;
```


### variable front_sensor

```cpp
distance_position front_sensor = distance_position::FRONT_SENSOR;
```


### variable graph_bg_color

```cpp
const std::string & graph_bg_color = UI_black;
```


### variable graph_chart_bg_color

```cpp
const std::string & graph_chart_bg_color = UI_black;
```


### variable graph_chart_outline_color

```cpp
const std::string & graph_chart_outline_color = UI_med_gray;
```


### variable graph_legend_bg_color

```cpp
const std::string & graph_legend_bg_color = UI_black;
```


### variable graph_legend_outline_color

```cpp
const std::string & graph_legend_outline_color = UI_med_gray;
```


### variable graph_reset_btn_bg_color

```cpp
const std::string & graph_reset_btn_bg_color = UI_black;
```


### variable graph_reset_btn_outline_color

```cpp
const std::string & graph_reset_btn_outline_color = UI_med_gray;
```


### variable graph_reset_btn_pressed_color

```cpp
const std::string & graph_reset_btn_pressed_color = UI_red;
```


### variable graph_reset_btn_pressing_color

```cpp
const std::string & graph_reset_btn_pressing_color = UI_white;
```


### variable graph_text_color

```cpp
const std::string & graph_text_color = UI_white;
```


### variable green

```cpp
color green = color::GREEN;
```


### variable green_18_1

```cpp
vex::gearSetting green_18_1 = vex::gearSetting::ratio18_1;
```


### variable left_sensor

```cpp
distance_position left_sensor = distance_position::LEFT_SENSOR;
```


### variable left_wall

```cpp
wall_position left_wall = wall_position::LEFT_WALL;
```


### variable loading_text_bg_color

```cpp
const std::string & loading_text_bg_color = UI_dark_gray;
```


### variable loading_text_color

```cpp
const std::string & loading_text_color = UI_white;
```


### variable magenta

```cpp
color magenta = color::MAGENTA;
```


### variable motor_encoder

```cpp
tracker_mode motor_encoder = tracker_mode::MOTOR_ENCODER;
```


### variable motors_bg_color

```cpp
const std::string & motors_bg_color = UI_black;
```


### variable motors_close_button_bg_color

```cpp
const std::string & motors_close_button_bg_color = UI_black;
```


### variable motors_close_button_outline_color

```cpp
const std::string & motors_close_button_outline_color = UI_med_gray;
```


### variable motors_close_button_pressed_color

```cpp
const std::string & motors_close_button_pressed_color = UI_red;
```


### variable motors_close_button_pressing_color

```cpp
const std::string & motors_close_button_pressing_color = UI_white;
```


### variable motors_left_drive_btn_bg_color

```cpp
const std::string & motors_left_drive_btn_bg_color = "#303030";
```


### variable motors_port_btn_outline_color

```cpp
const std::string & motors_port_btn_outline_color = UI_dark_gray;
```


### variable motors_port_btn_pressed_color

```cpp
const std::string & motors_port_btn_pressed_color = UI_red;
```


### variable motors_port_btn_pressing_color

```cpp
const std::string & motors_port_btn_pressing_color = UI_white;
```


### variable motors_ports_btn_bg

```cpp
const std::string & motors_ports_btn_bg = UI_black;
```


### variable motors_ports_btn_closed_color

```cpp
const std::string & motors_ports_btn_closed_color = UI_red;
```


### variable motors_ports_btn_current_color

```cpp
const std::string & motors_ports_btn_current_color = UI_white;
```


### variable motors_ports_btn_open_color

```cpp
const std::string & motors_ports_btn_open_color = UI_med_gray;
```


### variable motors_ports_btn_pressing_color

```cpp
const std::string & motors_ports_btn_pressing_color = UI_light_gray;
```


### variable motors_ports_text_color

```cpp
const std::string & motors_ports_text_color = UI_white;
```


### variable motors_spin_left_bg_color

```cpp
const std::string & motors_spin_left_bg_color = UI_black;
```


### variable motors_spin_left_outline_color

```cpp
const std::string & motors_spin_left_outline_color = UI_med_gray;
```


### variable motors_spin_left_pressed_color

```cpp
const std::string & motors_spin_left_pressed_color = UI_red;
```


### variable motors_spin_left_pressing_color

```cpp
const std::string & motors_spin_left_pressing_color = UI_white;
```


### variable motors_spin_right_bg_color

```cpp
const std::string & motors_spin_right_bg_color = UI_black;
```


### variable motors_spin_right_outline_color

```cpp
const std::string & motors_spin_right_outline_color = UI_med_gray;
```


### variable motors_spin_right_pressed_color

```cpp
const std::string & motors_spin_right_pressed_color = UI_red;
```


### variable motors_spin_right_pressing_color

```cpp
const std::string & motors_spin_right_pressing_color = UI_white;
```


### variable motors_volt_btn_bg_color

```cpp
const std::string & motors_volt_btn_bg_color = UI_black;
```


### variable motors_volt_btn_outline_color

```cpp
const std::string & motors_volt_btn_outline_color = UI_med_gray;
```


### variable motors_volt_btn_pressed_color

```cpp
const std::string & motors_volt_btn_pressed_color = UI_white;
```


### variable motors_volt_btn_pressing_color

```cpp
const std::string & motors_volt_btn_pressing_color = UI_red;
```


### variable one

```cpp
auto_variation one = auto_variation::ONE;
```


### variable pnematic_A_btn_bg_color

```cpp
const std::string pnematic_A_btn_bg_color = "#303030";
```


### variable pnematic_B_btn_bg_color

```cpp
const std::string pnematic_B_btn_bg_color = "#595959";
```


### variable pnematic_C_btn_bg_color

```cpp
const std::string pnematic_C_btn_bg_color = "#858585";
```


### variable pnematic_D_btn_bg_color

```cpp
const std::string pnematic_D_btn_bg_color = "#cccccc";
```


### variable pnematic_E_btn_bg_color

```cpp
const std::string pnematic_E_btn_bg_color = "#303030";
```


### variable pnematic_F_btn_bg_color

```cpp
const std::string pnematic_F_btn_bg_color = "#595959";
```


### variable pnematic_G_btn_bg_color

```cpp
const std::string pnematic_G_btn_bg_color = "#858585";
```


### variable pnematic_H_btn_bg_color

```cpp
const std::string pnematic_H_btn_bg_color = "#cccccc";
```


### variable pnematic_bg_color

```cpp
const std::string & pnematic_bg_color = UI_black;
```


### variable pnematic_close_btn_bg_color

```cpp
const std::string & pnematic_close_btn_bg_color = UI_black;
```


### variable pnematic_close_btn_outline_color

```cpp
const std::string & pnematic_close_btn_outline_color = UI_med_gray;
```


### variable pnematic_close_btn_pressed_color

```cpp
const std::string & pnematic_close_btn_pressed_color = UI_red;
```


### variable pnematic_close_btn_pressing_color

```cpp
const std::string & pnematic_close_btn_pressing_color = UI_light_gray;
```


### variable pnematic_port_btn_outline_color

```cpp
const std::string & pnematic_port_btn_outline_color = UI_dark_gray;
```


### variable pnematic_port_btn_outline_pressed_color

```cpp
const std::string & pnematic_port_btn_outline_pressed_color = UI_red;
```


### variable pnematic_port_btn_outline_pressing_color

```cpp
const std::string & pnematic_port_btn_outline_pressing_color = UI_light_gray;
```


### variable pnematic_text_color

```cpp
const std::string & pnematic_text_color = UI_white;
```


### variable rear_sensor

```cpp
distance_position rear_sensor = distance_position::REAR_SENSOR;
```


### variable red

```cpp
color red = color::RED;
```


### variable red_36_1

```cpp
vex::gearSetting red_36_1 = vex::gearSetting::ratio36_1;
```


### variable reversed

```cpp
drive_direction reversed = drive_direction::REV;
```


### variable right_sensor

```cpp
distance_position right_sensor = distance_position::RIGHT_SENSOR;
```


### variable right_wall

```cpp
wall_position right_wall = wall_position::RIGHT_WALL;
```


### variable selector_bg_color

```cpp
const std::string & selector_bg_color = UI_black;
```


### variable selector_bg_pressed_color

```cpp
const std::string & selector_bg_pressed_color = UI_dark_gray;
```


### variable selector_bg_pressing_color

```cpp
const std::string & selector_bg_pressing_color = UI_med_gray;
```


### variable selector_outline_color

```cpp
const std::string & selector_outline_color = UI_dark_gray;
```


### variable selector_outline_pressed_color

```cpp
const std::string & selector_outline_pressed_color = UI_light_gray;
```


### variable selector_outline_pressing_color

```cpp
const std::string & selector_outline_pressing_color = UI_light_gray;
```


### variable selector_scroll_bar_color

```cpp
const std::string & selector_scroll_bar_color = UI_dark_gray;
```


### variable selector_text_color

```cpp
const std::string & selector_text_color = UI_white;
```


### variable three

```cpp
auto_variation three = auto_variation::THREE;
```


### variable top_wall

```cpp
wall_position top_wall = wall_position::TOP_WALL;
```


### variable two

```cpp
auto_variation two = auto_variation::TWO;
```


### variable white

```cpp
color white = color::WHITE;
```


### variable yellow

```cpp
color yellow = color::YELLOW;
```





-------------------------------

Updated on 2026-03-02 at 17:21:00 -0600