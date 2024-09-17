#include "vex.h"
#include "motors.h"
using namespace vex;

int main() {
  vexcodeInit();

  Motors leftDrive(PORT1, false, PORT2, false, PORT3, false, ratio18_1);
  Motors rightDrive(PORT7, false, PORT7, false, PORT9, false, ratio18_1);

  leftDrive.spin(fwd, 1, VelocityUnits::normalized);
  rightDrive.spin(fwd, 1, VelocityUnits::normalized);
}
