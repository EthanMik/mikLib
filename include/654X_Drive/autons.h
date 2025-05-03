#pragma once

#include "vex.h"

void blue_ringside_winpoint(bool calibrate);
void blue_ringside_sawp(bool calibrate);
void blue_ringside_elim(bool calibrate);
void blue_goalside_winpoint(bool calibrate);
void blue_goalside_sawp(bool calibrate);
void blue_goalside_elim(bool calibrate);
void red_ringside_winpoint(bool calibrate);
void red_ringside_sawp(bool calibrate);
void red_ringside_elim(bool calibrate);
void red_goalside_winpoint(bool calibrate);
void red_goalside_sawp(bool calibrate);
void red_goalside_elim(bool calibrate);


void goalside_red(bool set_pos = false);
void ring_side_red(bool set_pos = false);
void win_point_red(bool set_pos = false);
void solo_win_point_red(bool set_pos = false);

void goalside_blue(bool set_pos = false);
void ring_side_blue(bool set_pos = false);
void win_point_blue(bool set_pos = false);
void solo_win_point_blue(bool set_pos = false);

void skills(bool calibrate);

void drive_until_settled(float left_voltage, float right_voltage, float max_timeout = 2500, float min_timeout = 500);
void distance_reset();
void LB_task(int angle, bool override = false);
void start_intake(bool unjam_intake = true);
void stop_intake();
void intake_ring_halfway();
void color_sort_auton(color_sort color);