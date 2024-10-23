#include "vex.h"

manual_drive::manual_drive(motor_chain left, motor_chain right)
  : leftDrive(left), rightDrive(right) {};

void manual_drive::control_split_arcade(float speedLimiter)
{
  float throttle = deadband(controller(primary).Axis3.value(), 5);
  float turn = deadband(controller(primary).Axis1.value(), 5);

  leftDrive.spin(fwd, percent_to_volt((throttle + turn) * speedLimiter), velocity_units::volt);
  rightDrive.spin(fwd, percent_to_volt((throttle - turn)) * speedLimiter, velocity_units::volt);    
}

void manual_drive::control_drive_tasks()
{
  thread(control_split_arcade());
}