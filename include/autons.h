#pragma once

#include "vex.h"

enum auto_variation : int { ONE = 1, TWO = 2, THREE = 3, FOUR = 4 };

void default_constants(void);
void odom_constants(void);

/** @brief Only use when you need to get to places on the field fast with low accuracy.
 * To make the movements exit earlier, increase settle error.
 */
void motion_chaining_constants(void);

std::string template_auto(bool calibrate = false, auto_variation var = auto_variation::ONE, bool get_name = false);
std::string template_auto_other_variation(bool calibrate, bool get_name);

std::string blue_left_winpoint(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false);
std::string blue_left_sawp(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false);
std::string blue_left_elim(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false);
std::string blue_right_winpoint(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false);
std::string blue_right_sawp(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false);
std::string blue_right_elim(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false);
std::string red_left_winpoint(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false);
std::string red_left_sawp(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false);
std::string red_left_elim(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false);
std::string red_right_winpoint(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false);
std::string red_right_sawp(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false);
std::string red_right_elim(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false);
std::string skills(bool calibrate, auto_variation var = auto_variation::ONE, bool get_name = false);