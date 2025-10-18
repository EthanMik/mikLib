#pragma once

#include "vex.h"

std::string blue_left_winpoint(bool calibrate, mik::auto_variation var, bool get_name);
std::string blue_left_sawp(bool calibrate, mik::auto_variation var, bool get_name);
std::string blue_left_elim(bool calibrate, mik::auto_variation var, bool get_name);

std::string blue_right_winpoint(bool calibrate, mik::auto_variation var, bool get_name);
std::string blue_right_sawp(bool calibrate, mik::auto_variation var, bool get_name);
std::string blue_right_elim(bool calibrate, mik::auto_variation var, bool get_name);

std::string red_left_winpoint(bool calibrate, mik::auto_variation var, bool get_name);
std::string red_left_sawp(bool calibrate, mik::auto_variation var, bool get_name);
std::string red_left_elim(bool calibrate, mik::auto_variation var, bool get_name);

std::string red_right_winpoint(bool calibrate, mik::auto_variation var, bool get_name);
std::string red_right_sawp(bool calibrate, mik::auto_variation var, bool get_name);
std::string red_right_elim(bool calibrate, mik::auto_variation var, bool get_name);

std::string skills(bool calibrate, mik::auto_variation var, bool get_name);