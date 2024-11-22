#include "vex.h"

using namespace vex;

brain Brain;
controller Controller;

auton_drive chassis(
    // Drivetrain motors
    hzn::motor_group({
      hzn::motor(PORT12, true, "left front motor"), 
      hzn::motor(PORT3, true, "left middle motor"), 
      hzn::motor(PORT19, true, "left back motor")
    }),
    hzn::motor_group({
      hzn::motor(PORT9, false, "right front motor"), 
      hzn::motor(PORT14, false, "right middle motor"), 
      hzn::motor(PORT20, false, "right back motor")
    }),

    PORT10, // Inertia sensor port
    2.75,   // Drivetrain wheel diameter
    0.75,   // Drivetrain wheel ratio

    PORT18, // Forward Tracker Port
    -2,      // Forward Tracker wheel diameter
    0.34375, // Forward Tracker center distance in inches (a positive distance corresponds to a tracker on the right side of the robot, negative is left)

    PORT4, // Sideways tracker port
    2,      // Sideways tracker wheel diameter (inches)
    3.125   // Sideways tracker center distance in inches (positive distance is behind the center of the robot, negative is in front)
);

manual_drive assembly(
  // Lady Brown motors
  hzn::motor_group({
    hzn::motor(PORT11, false, "left LB motor"),
    hzn::motor(PORT12, true, "right LB motor") 
  }), 

  PORT10, // Lady Brown rotation sensor port

  hzn::motor(PORT13, true, "Intake motor"),
  PORT14, // Ring color sensor port
  PORT15, // Ring distance sensor port

  PORT1,  // Mogo clamp piston Brain ThreeWire PortA -> PORT1
  PORT2   // Doinker piston Brain ThreeWire PortB -> PORT2
);

void init(void) {
  Brain.Screen.drawImageFromFile("loading.png", 0, 0);
  Brain.Screen.setCursor(2, 1);

  wait(200, msec);
  chassis.inertial.calibrate();

  while (chassis.inertial.isCalibrating()) {
    wait(25, msec);
  }

  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}

void default_constants(void) {
  chassis.set_turn_constants(12, .325, .03, 3.36, 15, .1, 300, 3000);
  chassis.set_drive_constants(10, 1.5, 0, 10, 0, 1.5, 300, 5000);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  assembly.set_LB_constants(12, .2, .1, .02, 0, 4, 200, 3000);

  // chassis.heading_max_voltage = 10;
  // chassis.drive_max_voltage = 8;
  // chassis.drive_settle_error = 3;
  // chassis.boomerang_lead = .5;
  // chassis.drive_min_voltage = 0;
}