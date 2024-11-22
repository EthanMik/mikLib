#include "vex.h"

using namespace vex;

class motor;
class motor_group;
class auton_drive;
class manual_drive;

extern brain Brain;
extern controller Controller;

extern auton_drive chassis;
extern manual_drive assembly;

void init(void);
void default_constants(void);