#include "vex.h"
#include "motor_chain.h"
#include "manual_drive.h"
#include "auton_drive.h"

using namespace vex;

int main() {
  vexcodeInit();

  motor_chain leftDrive(PORT1, false, PORT2, false, PORT3, false, ratio18_1);
  motor_chain rightDrive(PORT7, false, PORT7, false, PORT9, false, ratio18_1);

  manual_drive manual_drive(leftDrive, rightDrive);

  manual_drive.control_drive_tasks();
  
  leftDrive.spin(fwd, 100, velocity_units::percent);
  //drive(leftDrive, rightDrive);

  //leftDrive.spin(fwd, 1, VelocityUnits::normalized);
  //rightDrive.spin(fwd, 1, VelocityUnits::normalized);
  
  //leftDrive.motorF.spin(fwd, 12, volt);



}
