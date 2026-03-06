#include "vex.h"

using namespace vex;
using namespace mik;

vex::brain Brain;
vex::controller Controller;
vex::competition Competition;

// mikLib v2.0 setup, if you are following along with video tutorials it is going to be slightly different

Chassis chassis(
    // Left drivetrain motors (left/right is looking from behind the robot)
    mik::motor_group({
        mik::motor(PORT11, true, blue_6_1, "left front motor"),
        mik::motor(PORT12, true, blue_6_1, "left middle motor"),
        mik::motor(PORT13, true, blue_6_1, "left back motor"),
    }),
    // Right drivetrain motors
    mik::motor_group({
        mik::motor(PORT2, false, blue_6_1, "right front motor"),
        mik::motor(PORT5, false, blue_6_1, "right middle motor"),
        mik::motor(PORT6, false, blue_6_1, "right back motor"),
    }),
	
    PORT3,  // Inertial sensor port
    360,    // Inertial scale (reading after a full 360° turn)
	false,  // Forces inertial sensor to recalibrate until it is within minimum threshold of 0.05 deg for 1 second
	
    forward_tracker, // Replace with "motor_encoder" if no forward tracker
    2.75,            // Drivetrain wheel diameter (in). Negative flips direction. Only needed with motor encoder
    0.75,            // Drivetrain gear ratio (ex: a 36 driving a 48 is 0.75). Only needed with motor encoder
	6,               // Drivetrain center distance (in), (half drivetrain track width). Only needed with motor encoder. Can be found automatically with "Get Offsets" on "Config" tab

    PORT4,  // Forward tracker port. PORT0 if unused. Accepts "PORT_A"
    2,      // Forward tracker wheel diameter (in). Negative flips direction. Pushing robot forward at 0° should increase Y. 2" omnis are 2", not 2.125"
    0,      // Forward tracker center distance (in). Positive = right of center, negative = left. Can be found automatically with "Get Offsets" on "Config" tab

    PORT14,  // Sideways tracker port. PORT0 if unused. Accepts "PORT_A"
    -2,      // Sideways tracker wheel diameter (in). Negative flips direction. Pushing robot right at 0° should increase X
    0.3,     // Sideways tracker center distance (in). Positive = behind center, negative = in front. Can be found automatically with "Get Offsets" on "Config" tab

    // Distance sensors mounted on a face of the robot
    mik::distance_reset({
        mik::distance(
			PORT8,		  // Distance sensor port
            front_sensor, // "front_sensor", "rear_sensor", "left_sensor", "right_sensor"
            5,            // X offset from tracking center (in). Positive = right of center, negative = left.
            3.5           // Y offset from tracking center (in). Positive = in front of center, negative = behind.
        ),
        mik::distance(PORT8, left_sensor, -2, -4)
    })
);

// Add your devices in assembly.h then create them here

/* Creating a motor group in assembly */
mik::motor_group Assembly::lower_intake_motors({
	mik::motor(PORT1, true, green_18_1, "bottom_intake"),
	mik::motor(PORT2, false, green_18_1, "middle_intake")
});

/* Creating upper intake motor in assembly */
mik::motor Assembly::upper_intake_motor(PORT16, false, blue_6_1, "upper_intake");

/* Creating pistons in assembly */
mik::piston Assembly::scraper_piston(PORT_B);
mik::piston Assembly::wing_piston(PORT_A);

/* Creating alternative vex devices in assembly */
vex::rotation Assembly::rotation_sensor(PORT6);
vex::optical Assembly::optical_sensor(PORT13);
vex::limit Assembly::limit_switch(to_triport(PORT_F));






// mikLib initialization below, you do not need to edit

Assembly assembly;

static void loading_screen(bool stop) {
	static vex::task loading_bar;

	if (stop) {
		loading_bar.stop();
		return;
	}

	Controller.Screen.setCursor(1, 1);
	Brain.Screen.drawImageFromBuffer((uint8_t*)mikLib_logo, 0, 0, mikLib_logo_size);

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
	motors_scr->init_motors();

	// Calibrate inertial
	chassis.calibrate_inertial();

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
	if (Competition.isDriverControl() && (Competition.isFieldControl() || Competition.isCompetitionSwitch()) && user_control_disabled) {
		auton_scr->disable_controller_overlay();
		return false;
	};
  	return user_control_disabled;
}
