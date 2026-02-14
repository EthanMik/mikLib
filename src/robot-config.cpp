#include "vex.h"

using namespace vex;
using namespace mik;

vex::brain Brain;
vex::controller Controller;
vex::competition Competition;

// Forces inertial sensor to recalibrate until it is within minimum threshold for 1 second
bool force_calibrate_inertial = false;

Chassis chassis(
    // Left drivetrain motors (left/right is looking from behind the robot)
    mik::motor_group({
        mik::motor(PORT1, true, blue_6_1, "Left 5 PORT1"),
        mik::motor(PORT17, false, blue_6_1, "Left 4 PORT17"),
        mik::motor(PORT18, true, blue_6_1, "Left 3 PORT18"),
		mik::motor(PORT19, false, blue_6_1, "Left 2 PORT19"),
		mik::motor(PORT20, true, blue_6_1, "Left 1 PORT 20"),
    }),
    // Right drivetrain motors
    mik::motor_group({
        mik::motor(PORT11, false, blue_6_1, "Right 5 PORT11"),
        mik::motor(PORT12, true, blue_6_1, "Right 4 PORT12"),
        mik::motor(PORT13, false, blue_6_1, "Right 3 PORT13"),
		mik::motor(PORT14, true, blue_6_1, "Right 2 PORT14"),
		mik::motor(PORT15, false, blue_6_1, "Right 1 PORT15")
    }),
	
    PORT10, // Inertial sensor port
    360,    // Inertial scale (reading after a full 360° turn)
	
    forward_tracker, // Replace with "motor_encoder" if no forward tracker
    2.75,   // Drivetrain wheel diameter (in). Negative flips direction. Only needed with motor encoders
    0.75,   // Drivetrain gear ratio (e.g. 36T:48T = 0.75). Only needed with motor encoders
	6,      // Drivetrain center distance, Half the track width (center-to-center distance between left and right wheels). Only needed with motor encoders

    PORT19, // Forward tracker port. PORT0 if unused
    -2,     // Forward tracker wheel diameter (in). Negative flips direction. Pushing robot forward at 0° should increase Y
    0,      // Forward tracker center distance (in). Positive = right of center, negative = left

    PORT1, // Sideways tracker port. PORT0 if unused.
    2,      // Sideways tracker wheel diameter (in). Negative flips direction. Pushing robot right at 0° should increase X
    0.3,    // Sideways tracker center distance (in). Positive = behind center, negative = in front

    // Distance sensors mounted on a face of the robot
    mik::distance_reset({
        // mik::distance(port, position, x_offset, y_offset)
        mik::distance(PORT8,
            front_sensor, // "front_sensor", "rear_sensor", "left_sensor", "right_sensor"
            5,            // X offset from tracking center (in). Positive = right of center, negative = left.
            3.5           // Y offset from tracking center (in). Positive = in front of center, negative = behind.
        ),
        mik::distance(PORT8, left_sensor, -2, -4)
    })
);

// Make sure devices are passed in the same order as they are declared in assembly.h and and assembly.cpp
Assembly assembly(
	mik::motor_group({
		mik::motor(PORT13, true, green_18_1, "bottom_intake"),
		mik::motor(PORT20, false, green_18_1, "middle_intake")
	}),

	mik::motor(PORT16, false, blue_6_1, "upper_intake"),
	mik::piston(PORT_B),
	mik::piston(PORT_A)
);

/** Allows UI to display all motor values */
void log_motors() {
    config_add_motors({
		// Add all mik motor groups in here, you can log assembly motor groups
		chassis.left_drive,
		chassis.right_drive,
		// assembly.lower_intake_motors
    },
	{
		// Add all mik motors in here, you can log assembly motors
		// assembly.upper_intake_motor
    }
  );
}


// After inertial sensor calibration the program waits 1 second and checks to see if the angle has changed more than this value.
// If so, it will recalibrate the inertial sensor and vibrate the controller. The lower the value the less likelihood of a failed calibration.
static const float MINIMUM_INERTIAL_CALIBRATION_ERROR = .05;

bool calibrating = false;

void calibrate_inertial(void) {
	calibrating = true;
	chassis.inertial.calibrate();

	while (chassis.inertial.isCalibrating()) {
		vex::task::sleep(25);
	}

  	// Recalibrate inertial until it is within calibration threshold
  	float starting_rotation = chassis.inertial.rotation();
  	task::sleep(1000);
	if (force_calibrate_inertial && std::abs(chassis.inertial.rotation() - starting_rotation) > MINIMUM_INERTIAL_CALIBRATION_ERROR) {
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
		Brain.Screen.setFillColor(mik::loading_text_bg_color.c_str());
		Brain.Screen.setPenColor(mik::loading_text_color.c_str());
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

static void reset_screens() {
	Brain.Screen.clearScreen();
	Controller.Screen.setCursor(1, 1);
	Controller.Screen.print("                                  ");
	Brain.Screen.setCursor(1,1);
	vex::task::sleep(50);
	Brain.Screen.clearScreen();
	Brain.Screen.setFillColor(vex::color::black);
	Brain.Screen.setPenWidth(1);
	Brain.Screen.setPenColor(vex::color::white);
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
	reset_screens();

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
