#include "vex.h"
#include "UI/graphics/logo.h"

using namespace vex;
using namespace mik;

vex::brain Brain;
vex::controller Controller;
vex::competition Competition;

bool calibrating = false;

// Allows recalibration of the inertial using MINIMUN_INERTIAL_CALIBRATION_ERROR
bool force_calibrate_inertial = true;

/* After inertial sensor calibration the program waits 1 second and checks 
  to see if the angle has changed more than this value. If so, it will recalibrate 
  the inertial sensor and vibrate the controller. The lower the value the less likelihood
  of a failed calibration. */ 
static const float MINIMUN_INERTIAL_CALIBRATION_ERROR = .05;

Chassis chassis(
    // Drivetrain motors
    mik::motor_group({
      mik::motor(PORT4, false, blue_6_1, "left_front_motor"), 
      mik::motor(PORT8, true, blue_6_1, "left_middle_motor"), 
      mik::motor(PORT6, true, blue_6_1, "left_back_motor")
    }),
    mik::motor_group({
      mik::motor(PORT5, false, blue_6_1, "right_front_motor"), 
      mik::motor(PORT9, true, blue_6_1, "right_middle_motor"), 
      mik::motor(PORT10, false, blue_6_1, "right_back_motor")
    }),

    PORT18, // Inertia sensor port
    360,    // Inertial scale, value that reads after turning robot a full 360

    PORT19, // Forward Tracker Port
    -2,     // Forward Tracker wheel diameter in inches (negative flips direction)
    0,      // Forward Tracker center distance in inches (a positive distance corresponds to a tracker on the right side of the robot, negative is left)

    PORT15,  // Sideways tracker port
    2,       // Sideways tracker wheel diameter in inches (negative flips direction)
    0.3,     // Sideways tracker center distance in inches (positive distance is behind the center of the robot, negative is in front)

    mik::distance_reset({
      // A distance sensor that is mounted on the front of the robot and is offset by 5 inches to the right and 3.5 inches forward from the tracking center 
      mik::distance(PORT17, rear_sensor, 5, 3.5)
    })
);

Assembly assembly(
  mik::motor_group({
    mik::motor(PORT13, true, green_18_1, "left_lift_motor"),
    mik::motor(PORT20, false, green_18_1, "right_lift_motor")
  }),

  mik::motor(PORT16, false, blue_6_1, "intake_motor"),
  vex::rotation(PORT11),
  mik::piston(PORT_A)
);

/** Allows UI to display all motor values */
void log_motors() {
  config_add_motors({chassis.left_drive, chassis.right_drive, assembly.lift_arm_motors}, {assembly.intake_motor});
}


void calibrate_inertial(void) {
  calibrating = true;
  chassis.inertial.calibrate();
  
  while (chassis.inertial.isCalibrating()) {
    vex::task::sleep(25);
  }
  
  // Recalibrate inertial until it is within calibration threshold
  float starting_rotation = chassis.inertial.rotation();
  task::sleep(1000);
  if (force_calibrate_inertial && std::abs(chassis.inertial.rotation() - starting_rotation) > MINIMUN_INERTIAL_CALIBRATION_ERROR) { 
    Controller.rumble("-");
    calibrate_inertial();
  }
  calibrating = false;
}

static void loading_screen(bool stop) {
  static vex::task loading_bar;
  
  if (stop) {
    loading_bar.stop();
    return;
  }

  Controller.Screen.setCursor(1, 1);
  Brain.Screen.drawImageFromBuffer(mikLib_logo, 0, 0, sizeof(mikLib_logo));
  loading_bar = vex::task([](){
    std::string calibrate = "Calibrating";
    Brain.Screen.setFillColor("#3d3d3d");
    int count = 0;
    while(1) {
      Brain.Screen.printAt(184, 220, calibrate.c_str());
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print((calibrate).c_str());
      task::sleep(200);
      calibrate.append(".");
      count++;
    if (count > 4) {
        count = 0;
        calibrate = "Calibrating";
        Brain.Screen.printAt(184, 220, (calibrate + "     ").c_str());
        Controller.Screen.setCursor(1, 1);
        Controller.Screen.print((calibrate + "     ").c_str());
      }

    }
    return 0;
  });
}

static void handle_disconnected_devices() {
  int errors = run_diagnostic(); 
  if (errors > 0) {
    Controller.rumble(".");
    Controller.Screen.setCursor(1, 1);
    Controller.Screen.print((to_string(errors) + " ERRORS DETECTED").c_str());
    Controller.Screen.setCursor(2, 1);
    Controller.Screen.print("[Config]->[Error Data]");
    task::sleep(500);
  }
}

void init(void) {
  // Start loading screen
  loading_screen(false);
  
  // Setup motors
  log_motors();
  
  // Calibrate inertial
  calibrate_inertial();

  // Stop loading screen
  loading_screen(true);

  // Check disconnected devices
  handle_disconnected_devices();

  // Init brain and controller screen
  Brain.Screen.clearScreen();
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print("                                  ");
  Brain.Screen.setCursor(1,1);
  vex::task::sleep(50);
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(vex::color::black);
  Brain.Screen.setPenWidth(1);
  Brain.Screen.setPenColor(vex::color::white);
  
  // Make sure user control is enabled
  enable_user_control();
}

static bool user_control_disabled = false;

void disable_user_control(bool stop_all_motors_) {
  user_control_disabled = true;
  if (stop_all_motors_) {
    stop_all_motors(vex::brakeType::hold);
    set_brake_all_motors(vex::brakeType::coast);
  }
}

void enable_user_control(void) {
  user_control_disabled = false;
}

bool control_disabled(void) {
  return user_control_disabled;
}