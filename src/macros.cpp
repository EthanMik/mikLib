#include "vex.h"

vex::task barrel_task;
float barrel_target = 0;
bool override_barrel = false;
float barrel_max_voltage = 12;

void start_barrel_task() {
    barrel_task = vex::task([](){
        PID barrel_pid(0.1, 0, 0);

        while (true) {
            if (!override_barrel) {
                const float error = barrel_target - assembly.barrel_motor.position(deg);
                const float output = barrel_pid.compute(error);
                assembly.barrel_motor.spin(fwd, clamp(output, -barrel_max_voltage, barrel_max_voltage), volt);
            }

            vex::this_thread::sleep_for(20);
        }


        return 0;
    });
}

void matchload(float volts) {
    assembly.back_intake_piston.open();

    assembly.transfer_motor.spin(fwd, volts, volt);
    assembly.front_intake_motor.spin(fwd, volts, volt);
    assembly.back_intake_motors.spin(fwd, volts, volt);        
}

void intake_rear(float volts) {
    assembly.transfer_motor.spin(fwd, volts, volt);
    assembly.front_intake_motor.spin(fwd, volts, volt);
    assembly.back_intake_motors.spin(fwd, volts, volt);
}

void stop_intake_rear() {
    assembly.back_intake_motors.stop();
    assembly.transfer_motor.stop();
    assembly.front_intake_motor.stop();  
}

void stop_matchload() {
    assembly.back_intake_piston.close();
    assembly.back_intake_motors.stop();
    assembly.transfer_motor.stop();
    assembly.front_intake_motor.stop();
}

void stop_intake() {
    assembly.back_intake_motors.stop();
    assembly.transfer_motor.stop();
    assembly.front_intake_motor.stop();
}

void intake(float volts) {
    assembly.front_intake_motor.spin(fwd, volts, volt);
    assembly.transfer_motor.spin(fwd, volts, volt);
}

void outtake_rear(float volts) {
    assembly.back_intake_piston.open();

    assembly.transfer_motor.spin(reverse, volts, volt);
    assembly.front_intake_motor.spin(reverse, volts, volt);
    assembly.back_intake_motors.spin(reverse, volts, volt);   
}

void lift_barrel() {
    vex::task lift_barrel([](){
        override_barrel = true;
        assembly.barrel_motor.spinFor(fwd, 300, deg, 600, velocityUnits::rpm, true);
        assembly.barrel_lift_piston.open();

        return 0;
    });
}

void drop_barrel() {
    assembly.barrel_lift_piston.close();
}

void score(float volts) {
    override_barrel = false;
    barrel_max_voltage = volts;
    barrel_target += BARREL_ROTATION / 2.0f;
}