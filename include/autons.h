#pragma once

#include "vex.h"

void default_constants(void);
void odom_constants(void);

std::string template_auto(bool calibrate = false, mik::auto_variation var = mik::auto_variation::ONE, bool get_name = false);
std::string template_auto_other_variation(bool calibrate, bool get_name);

std::string blue_left_winpoint(bool calibrate, mik::auto_variation var = mik::auto_variation::ONE, bool get_name = false);
std::string blue_left_sawp(bool calibrate, mik::auto_variation var = mik::auto_variation::ONE, bool get_name = false);
std::string blue_left_elim(bool calibrate, mik::auto_variation var = mik::auto_variation::ONE, bool get_name = false);
std::string blue_right_winpoint(bool calibrate, mik::auto_variation var = mik::auto_variation::ONE, bool get_name = false);
std::string blue_right_sawp(bool calibrate, mik::auto_variation var = mik::auto_variation::ONE, bool get_name = false);
std::string blue_right_elim(bool calibrate, mik::auto_variation var = mik::auto_variation::ONE, bool get_name = false);
std::string red_left_winpoint(bool calibrate, mik::auto_variation var = mik::auto_variation::ONE, bool get_name = false);
std::string red_left_sawp(bool calibrate, mik::auto_variation var = mik::auto_variation::ONE, bool get_name = false);
std::string red_left_elim(bool calibrate, mik::auto_variation var = mik::auto_variation::ONE, bool get_name = false);
std::string red_right_winpoint(bool calibrate, mik::auto_variation var = mik::auto_variation::ONE, bool get_name = false);
std::string red_right_sawp(bool calibrate, mik::auto_variation var = mik::auto_variation::ONE, bool get_name = false);
std::string red_right_elim(bool calibrate, mik::auto_variation var = mik::auto_variation::ONE, bool get_name = false);
std::string skills(bool calibrate, mik::auto_variation var = mik::auto_variation::ONE, bool get_name = false);