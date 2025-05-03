#include "vex.h"

class motor;
class motor_group;
class auton_drive;
class manual_drive;

extern vex::brain Brain;
extern vex::controller Controller;

extern auton_drive chassis;
extern manual_drive assembly;

void init(void);
void calibrate_inertial(void);
void mogo_constants(void);
void default_constants(void);