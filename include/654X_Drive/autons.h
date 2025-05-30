#pragma once

#include "vex.h"

enum class auto_variation { ONE, TWO, THREE, FOUR, FIVE };
extern vex::task LB_move_task;

std::string blue_ringside_winpoint(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string blue_ringside_sawp(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string blue_ringside_elim(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string blue_goalside_winpoint(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string blue_goalside_sawp(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string blue_goalside_elim(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string red_ringside_winpoint(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string red_ringside_sawp(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string red_ringside_elim(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string red_goalside_winpoint(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string red_goalside_sawp(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string red_goalside_elim(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);
std::string skills(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false, bool get_lineup = false);

void drive_until_settled(float left_voltage, float right_voltage, float max_timeout = 2500, float min_timeout = 500);
void distance_reset();
void LB_task(int angle, bool override = false);
void start_intake(bool unjam_intake = true);
void stop_intake();
void intake_ring_halfway();
void color_sort_auton(color_sort color);