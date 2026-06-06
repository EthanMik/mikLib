#pragma once

#include "vex.h"

// Example constants that you can use
void default_constants(void);
void no_tracker_constants(void);
void motion_chaining_constants(void);

// Examples you can delete
std::string template_auto(bool calibrate , mik::auto_variation var, bool get_name );
std::string template_auto_other_variation(bool calibrate, bool get_name);

// Do not delete, needed for auton selector
std::string blue_left_winpoint(bool calibrate, mik::auto_variation var, bool get_name );
std::string blue_left_sawp(bool calibrate, mik::auto_variation var, bool get_name );
std::string blue_left_elim(bool calibrate, mik::auto_variation var, bool get_name );
std::string blue_right_winpoint(bool calibrate, mik::auto_variation var, bool get_name );
std::string blue_right_sawp(bool calibrate, mik::auto_variation var, bool get_name );
std::string blue_right_elim(bool calibrate, mik::auto_variation var, bool get_name );
std::string red_left_winpoint(bool calibrate, mik::auto_variation var, bool get_name );
std::string red_left_sawp(bool calibrate, mik::auto_variation var, bool get_name );
std::string red_left_elim(bool calibrate, mik::auto_variation var, bool get_name );
std::string red_right_winpoint(bool calibrate, mik::auto_variation var, bool get_name );
std::string red_right_sawp(bool calibrate, mik::auto_variation var, bool get_name );
std::string red_right_elim(bool calibrate, mik::auto_variation var, bool get_name );
std::string skills(bool calibrate, mik::auto_variation var, bool get_name );