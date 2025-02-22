#include "vex.h"

using namespace vex;

vex::brain Brain;
vex::controller Controller;

auton_drive chassis(
    // Drivetrain motors
    hzn::motor_group({
      hzn::motor(vex::PORT4, true, "left_front_motor"), 
      hzn::motor(vex::PORT5, true, "left_middle_motor"), 
      hzn::motor(vex::PORT6, false, "left_back_motor")
    }),
    hzn::motor_group({
      hzn::motor(vex::PORT2, false, "right_front_motor"), 
      hzn::motor(vex::PORT1, true, "right_middle_motor"), 
      hzn::motor(vex::PORT3, false, "right_back_motor")
    }),

    PORT8,  // Inertia sensor port
    2.75,        // Drivetrain wheel diameter
    0.75,        // Drivetrain wheel ratio
    359.1,  // Inertial scale, value that reads after full 360

    PORT20, // Forward Tracker Port
    2.125,           // Forward Tracker wheel diameter in inches (negative flips direction)
    0,           // Forward Tracker center distance in inches (a positive distance corresponds to a tracker on the right side of the robot, negative is left)

    PORT16,  // Sideways tracker port
    2.125,           // Sideways tracker wheel diameter in inches (negative flips direction)
    0.519             // Sideways tracker center distance in inches (positive distance is behind the center of the robot, negative is in front)
);

manual_drive assembly(
  // Lady Brown motors
  hzn::motor_group({
    hzn::motor(vex::PORT11, false, "left_LB_motor"),
    hzn::motor(vex::PORT12, true, "right_LB_motor") 
  }), 

  vex::PORT17, // Lady Brown rotation sensor port

  hzn::motor(vex::PORT7, false, "intake_motor"),
  vex::PORT13, // Intake rotation sensor port
  vex::PORT18, // Ring color sensor port
  vex::PORT15, // Ring distance sensor port

  PORT_D,  // Mogo clamp piston
  PORT_C,  // Doinker piston
  PORT_B,  // Rush piston  
  PORT_G   // Lift piston
);

void init(void) {
  chassis.inertial.calibrate();
  while (chassis.inertial.isCalibrating()) {
    vex::task::sleep(25);
  }
  vex::task::sleep(100);

  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  vex::task::sleep(50);
  Brain.Screen.clearScreen();
  
  Brain.Screen.setFillColor(vex::color::black);
  
  Brain.Screen.setPenWidth(1);
  Brain.Screen.setPenColor(vex::color::white);

  assembly.doinker_piston.set(true);
  assembly.lift_piston.set(true);
  assembly.intake_encoder.resetPosition();
  assembly.ring_color_sensor.setLightPower(80, pct);
}

void mogo_constants(void) {
  chassis.set_turn_constants(12, .437, 0.02, 3.7, 15, .1, 300, 3000);
}

void default_constants(void) {
  chassis.set_turn_constants(12, .437, .0295, 3.486, 15, .1, 300, 3000);
  chassis.set_drive_constants(10, 1.5, 0, 10, 0, 1.5, 300, 5000);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_swing_constants(12, .437, .0295, 3.486, 15, .5, 300, 3000);
  assembly.set_LB_constants(12, .2, .1, .02, 0, 2, 200, 3000);

  chassis.heading_max_voltage = 10;
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
  chassis.boomerang_lead = .5;
  chassis.drive_min_voltage = 0;
}