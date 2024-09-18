#include "654-Template/motor_chain.h"
#include "654-Template/auton_drive.h"
#include "util.h"
#include "vex.h"

manual_drive::manual_drive(motor_chain left, motor_chain right)
  : leftDrive(left), rightDrive(right) {};

void manual_drive::control_drivetrain()
{
  while (1)
  {
    float throttle = deadband(controller(primary).Axis3.value(), 5);
    float turn = deadband(controller(primary).Axis1.value(), 5);

    leftDrive.spin(fwd, percent_to_volt(throttle + turn), velocity_units::volt);
    rightDrive.spin(fwd, percent_to_volt(throttle - turn), velocity_units::volt);    
  }
}

void manual_drive::control_drive_tasks()
{
  thread(control_drivetrain());
}