#include "vex.h"

using namespace vex;

vex::brain Brain;
vex::controller Controller;
vex::competition Competition;
bool disable_user_control;

static const float MINIMUN_INERTIAL_CALIBRATION_ERROR = .05;

Chassis chassis(
    // Drivetrain motors
    mik::motor_group({
      mik::motor(vex::PORT4, false, "left_front_motor"), 
      mik::motor(vex::PORT8, true, "left_middle_motor"), 
      mik::motor(vex::PORT6, true, "left_back_motor")
    }),
    mik::motor_group({
      mik::motor(vex::PORT5, false, "right_front_motor"), 
      mik::motor(vex::PORT9, true, "right_middle_motor"), 
      mik::motor(vex::PORT10, false, "right_back_motor")
    }),

    PORT18,  // Inertia sensor port
    2.75,        // Drivetrain wheel diameter
    0.75,        // Drivetrain wheel ratio
    360,  // Inertial scale, value that reads after full 360

    PORT19, // Forward Tracker Port
    -2,           // Forward Tracker wheel diameter in inches (negative flips direction)
    0,           // Forward Tracker center distance in inches (a positive distance corresponds to a tracker on the right side of the robot, negative is left)

    PORT15,  // Sideways tracker port
    2,           // Sideways tracker wheel diameter in inches (negative flips direction)
    0.3             // Sideways tracker center distance in inches (positive distance is behind the center of the robot, negative is in front)
);

Assembly assembly(
  // Lady Brown motors
  mik::motor_group({
    mik::motor(vex::PORT13, true, "left_LB_motor"),
    mik::motor(vex::PORT20, false, "right_LB_motor") 
  }), 

  vex::PORT11, // Lady Brown rotation sensor port

  mik::motor(vex::PORT16, true, "intake_motor"),
  vex::PORT8, // Intake rotation sensor port
  vex::PORT14, // Ring color sensor port
  vex::PORT12, // Ring distance sensor port

  PORT_A,  // Mogo clamp piston
  PORT_D,  // Doinker piston
  PORT_C,  // Rush piston  
  PORT_B   // Lift piston
);

void calibrate_inertial(void) {
  chassis.inertial.calibrate();
  
  while (chassis.inertial.isCalibrating()) {
    vex::task::sleep(25);
  }

  float starting_rotation = chassis.inertial.rotation();
  task::sleep(1000);
  if (std::abs(chassis.inertial.rotation() - starting_rotation) > MINIMUN_INERTIAL_CALIBRATION_ERROR) { calibrate_inertial(); }
}

void init(void) {
  chassis.disable_control();
  Controller.Screen.setCursor(1, 1);
  Brain.Screen.drawImageFromFile("loading_screen.png", 0, 0);

  vex::task loading_bar([](){
    std::string calibrate = "Calibrating";
    int count = 0;
    while(1) {
      Brain.Screen.printAt(164, 220, calibrate.c_str());
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print((calibrate).c_str());
      task::sleep(200);
      calibrate.append(".");
      count++;
      if (count > 4) {
        count = 0;
        calibrate = "Calibrating";
        Brain.Screen.printAt(164, 220, (calibrate + "     ").c_str());
        Controller.Screen.setCursor(1, 1);
        Controller.Screen.print((calibrate + "     ").c_str());
      }

    }
    return 0;
  });
  
  calibrate_inertial();

  loading_bar.stop();
  int errors = run_diagnostic(); 
  if (errors > 0) {
    Controller.rumble(".");
    Controller.Screen.setCursor(1, 1);
    Controller.Screen.print((to_string(errors) + " ERRORS DETECTED").c_str());
    Controller.Screen.setCursor(2, 1);
    Controller.Screen.print("[Config]->[Error Data]");
    task::sleep(500);
  }

  Brain.Screen.clearScreen();
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print("                                  ");
  Brain.Screen.setCursor(1,1);
  vex::task::sleep(50);
  Brain.Screen.clearScreen();

  Brain.Screen.setFillColor(vex::color::black);
  
  Brain.Screen.setPenWidth(1);
  Brain.Screen.setPenColor(vex::color::white);
  chassis.enable_control();
  
  // assembly.doinker_piston.set(true);
  // assembly.lift_piston.set(true);
  assembly.intake_encoder.resetPosition();
  assembly.ring_color_sensor.setLightPower(80, pct);
  assembly.init_LB();
}