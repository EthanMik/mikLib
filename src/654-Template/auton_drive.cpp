#include "654-Template/motor_chain.h"
#include "654-Template/manual_drive.h"
#include "util.h"
#include "vex.h"

using namespace vex;

auton_drive::auton_drive(motor_chain leftDrive, motor_chain rightDrive):
    leftDrive(leftDrive),
    rightDrive(rightDrive)
{    
}



