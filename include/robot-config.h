#include "vex.h"

class motor;
class motor_group;
class Chassis;
class Assembly;

extern vex::brain Brain;
extern vex::controller Controller;
extern vex::competition Competition;
extern bool disable_user_control;

extern Chassis chassis;
extern Assembly assembly;

void init(void);
void calibrate_inertial(void);