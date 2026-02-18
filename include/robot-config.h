#pragma once

#include "v5.h"
#include "v5_vcs.h"

class motor;
class motor_group;
class Assembly;

extern vex::brain Brain;
extern vex::controller Controller;
extern vex::competition Competition;

extern bool calibrating;
extern bool force_calibrate_inertial;

extern Assembly assembly;

void init(void);

/** Disables user control in main, used by UI */
void disable_user_control(bool stop_all_motors_ = false);

/** @brief Re-enables user control, used by UI */
void enable_user_control(void);

/** @brief Returns true if user control is disabled by UI,
 * competition switch or field controller override this function
 */
bool control_disabled(void);
