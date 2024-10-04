using namespace vex;

class motor_chain;
class auton_drive;
class manual_drive;

extern motor_chain leftDrive;
extern motor_chain rightDrive;
extern auton_drive chassis;
extern manual_drive manual_tasks;
extern brain Brain;
extern controller Controller;
extern inertial Inertial;

void  vexcodeInit( void );