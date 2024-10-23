#include "vex.h"

using namespace vex;

class motor_chain;
class auton_drive;

extern brain Brain;
extern controller Controller;
extern inertial Inertial;

extern motor motorLF;
extern motor motorLM;
extern motor motorLB;
extern motor_chain leftDrive;

extern motor motorRF;
extern motor motorRM;
extern motor motorRB;
extern motor_chain rightDrive;

extern auton_drive chassis;

void  vexcodeInit( void );