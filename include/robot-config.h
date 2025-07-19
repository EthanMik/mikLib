#include "vex.h"

class motor;
class motor_group;
class Assembly;

extern vex::brain Brain;
extern vex::controller Controller;
extern vex::competition Competition;
extern bool calibrating;
extern bool disable_user_control;
extern bool force_calibrate_inertial;

extern Chassis chassis;
extern Assembly assembly;

enum port : int { PORT_A = 0, PORT_B = 1, PORT_C = 2, PORT_D = 3, PORT_E = 4, PORT_F = 5, PORT_G = 6, PORT_H = 7 };

void init(void);
void calibrate_inertial(void);