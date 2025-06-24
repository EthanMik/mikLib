#pragma once

#include "vex.h"

enum auto_variation : int { ONE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6, SEVEN = 7, EIGHT = 8, NINE = 9 };
extern vex::task LB_move_task;

void mogo_constants(void);
void default_constants(void);
void odom_constants(void);

std::string template_auto(bool calibrate = false, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string template_auto_other_variation(bool calibrate, bool get_name, bool get_lineup);

std::string blue_left_winpoint(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string blue_left_sawp(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string blue_left_elim(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string blue_right_winpoint(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string blue_right_sawp(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string blue_right_elim(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string red_left_winpoint(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string red_left_sawp(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string red_left_elim(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string red_right_winpoint(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string red_right_sawp(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string red_right_elim(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string skills(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);

void drive_until_settled(float left_voltage, float right_voltage, float max_timeout = 2500, float min_timeout = 500);
void distance_reset();
void LB_task(int angle, bool override = false);
void start_intake(bool unjam_intake = true);
void stop_intake();
void intake_ring_halfway();
void color_sort_auton(color_sort color);