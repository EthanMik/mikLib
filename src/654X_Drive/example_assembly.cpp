#include "vex.h"

using namespace vex;

// Pass in the ports of the devices we want to use
Example_Assembly::Example_Assembly(
    mik::motor_group intake_motors_5w, 
    mik::motor intake_motor_11w,
    int long_piston_port, 
    int distance_sensor_port
) :
    // Assign the ports to the devices
    intake_motors_5w(intake_motors_5w),
    intake_motor_11w(intake_motor_11w),
    // Make sure when using a 3 wire device you convert the port
    long_piston(to_triport(long_piston_port)),
    distance_sensor(distance_sensor_port)
{};

// Spins intake if R1 is pressed or distance sensor detects something 5 inches away; stops otherwise
void Example_Assembly::intake_motor_11w_control() {
    if (Controller.ButtonR1.pressing() || distance_sensor.objectDistance(inches) < 5) {
        intake_motor_11w.spin(fwd, 12, volt);
    } else {
        intake_motor_11w.stop();
    }
}

// Spins intake forward if L1 is pressed, reverse if L2 is pressed; stops otherwise
void Example_Assembly::intake_motors_5w_control() {
    if (Controller.ButtonL1.pressing()) {
        intake_motors_5w.spin(fwd, 12, volt);
    } else if (Controller.ButtonL2.pressing()) {
        intake_motors_5w.spin(fwd, -12, volt);
    } else {
        intake_motors_5w.stop();
    }
}

// Extends piston when button A is pressed, can only extend again until button A is released and pressed again
void Example_Assembly::long_piston_control() {
    bool long_piston_activated = Controller.ButtonA.pressing(); 

    if (long_piston_activated && !was_long_piston_activated) {
        long_piston_extended = !long_piston_extended;
        long_piston.set(long_piston_extended);
    }
    was_long_piston_activated = long_piston_activated;
}