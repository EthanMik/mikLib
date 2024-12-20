#include "vex.h"

using namespace vex;

vex::brain Brain;
vex::controller Controller;

auton_drive chassis(
    // Drivetrain motors
    hzn::motor_group({
      hzn::motor(vex::PORT4, false, "left_front_motor"), 
      hzn::motor(vex::PORT5, true, "left_middle_motor"), 
      hzn::motor(vex::PORT6, true, "left_back_motor")
    }),
    hzn::motor_group({
      hzn::motor(vex::PORT1, false, "right_front_motor"), 
      hzn::motor(vex::PORT2, false, "right_middle_motor"), 
      hzn::motor(vex::PORT3, true, "right_back_motor")
    }),

    PORT8,  // Inertia sensor port
    2.75,        // Drivetrain wheel diameter
    0.75,        // Drivetrain wheel ratio

    PORT16, // Forward Tracker Port
    2,           // Forward Tracker wheel diameter in inches (negative flips direction)
    1,           // Forward Tracker center distance in inches (a positive distance corresponds to a tracker on the right side of the robot, negative is left)

    PORT17,  // Sideways tracker port
    -2,           // Sideways tracker wheel diameter in inches (negative flips direction)
    1             // Sideways tracker center distance in inches (positive distance is behind the center of the robot, negative is in front)
);

manual_drive assembly(
  // Lady Brown motors
  hzn::motor_group({
    hzn::motor(vex::PORT11, false, "left_LB_motor"),
    hzn::motor(vex::PORT12, true, "right_LB_motor") 
  }), 

  vex::PORT13, // Lady Brown rotation sensor port

  hzn::motor(vex::PORT9, true, "intake_motor"),
  vex::PORT21, // Ring color sensor port
  vex::PORT14, // Ring distance sensor port

  PORT_A,  // Mogo clamp piston
  PORT_H   // Doinker piston
);

void init(void) {
  chassis.inertial.calibrate();
  while (chassis.inertial.isCalibrating()) {
    vex::task::sleep(25);
  }

  // Brain.Screen.render(true, true);

  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  vex::task::sleep(50);
  Brain.Screen.clearScreen();
  
  Brain.Screen.setFillColor(vex::color::black);
  
  Brain.Screen.setPenWidth(1);
  Brain.Screen.setPenColor(vex::color::white);
}

void default_constants(void) {
  chassis.set_turn_constants(12, .437, .0295, 3.486, 15, .1, 300, 3000);
  chassis.set_drive_constants(10, 1.5, 0, 10, 0, 1.5, 300, 5000);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_swing_constants(12, .3, .001, 2, 15, 1, 300, 3000);
  assembly.set_LB_constants(12, .2, .1, .02, 0, 4, 200, 3000);

  chassis.heading_max_voltage = 10;
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
  chassis.boomerang_lead = .5;
  chassis.drive_min_voltage = 0;
}