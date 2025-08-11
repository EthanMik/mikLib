#include "vex.h"

using namespace vex;

// Pass in the devices we want to use
Assembly::Assembly(
    mik::motor_group lift_arm_motors,
    mik::motor intake_motor, 
    vex::rotation lift_arm_encoder,
    mik::piston long_piston
) :
    // Assign the ports to the devices
    lift_arm_motors(lift_arm_motors),
    intake_motor(intake_motor),
    lift_arm_encoder(lift_arm_encoder),
    long_piston(long_piston) // Make sure when using a 3 wire device that isnt mik::piston you convert the port. `to_triport(PORT_A)`.
{};

// You want to call this function once in the user control function in main.
void Assembly::init() {
    // Create the task to move the lift arm. We only want one task to be created
    lift_task = vex::task([](){
        assembly.move_lift_arm();
        return 0;
    });
    // To stop the task do `assembly.lift_task.stop();`
} 

// You want to put this function inside the user control loop in main.
void Assembly::control() {
    lift_arm_control();
    intake_motors_control();
    long_piston_control();
}

void Assembly::move_lift_arm() {
    // Create a proportional controller. Increase the P just enough so there isn't much oscillation.
    PID lift_PID(.1, 0, 0);
    while (true) {
        // How far we need to move until desired angle
        float error = lift_arm_position - lift_arm_encoder.angle();
        // Converting error into motor voltage
        float output = lift_PID.compute(error);
        lift_arm_motors.spin(fwd, output, volt);
        vex::this_thread::sleep_for(20);
    }
}

void Assembly::lift_arm_control() {
    // new_press macro only allows input to go through when button is pressed. Resets after button is released.
    if (btnX_new_press(Controller.ButtonX.pressing())) {
        // If Up arrow is pressed it will swap lift positions between scoring and loading
        if (lift_arm_position != SCORING) {
            lift_arm_position = SCORING; // Lift task will read this value
        } else {
            lift_arm_position = LOADING;
        }
    } else if (btnUp_new_press(Controller.ButtonUp.pressing())) {
        // If Up arrow is pressed it will swap lift positions between loading and idle
        if (lift_arm_position != LOADING) {
            lift_arm_position = LOADING;
        } else {
            lift_arm_position = IDLE;
        }
    }
}

// Spins intake forward if L1 is being held, reverse if L2 is being held; stops otherwise
void Assembly::intake_motors_control() {
    if (Controller.ButtonL1.pressing()) {
        intake_motor.spin(fwd, 12, volt);
    } else if (Controller.ButtonL2.pressing()) {
        intake_motor.spin(fwd, -12, volt);
    } else {
        intake_motor.stop();
    }
}


// Extends or retracts piston when button A is pressed, can only extend or retract again until button A is released and pressed again
void Assembly::long_piston_control() {
    if (btnA_new_press(Controller.ButtonA.pressing())) {
        long_piston.toggle();
    }
}