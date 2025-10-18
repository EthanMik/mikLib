#include "vex.h"

using namespace vex;
using namespace mik;

void intake_ring_halfway() {
    assembly.intake_motor.spin(fwd, 10, volt);
    vex::task intake_ring_halfway_task([](){
        vex::distance d(PORT12);
        int timeout_start = Brain.Timer.time(vex::timeUnits::sec);
        while (1) {
            if (d.objectDistance(mm) < 50) {
                assembly.intake_motor.stop(brake);
                break;
            }
            if (Brain.Timer.time(vex::timeUnits::sec) - timeout_start > 5) {
                break;
            }
            vex::this_thread::sleep_for(50);

        }
        return 0;
  });
}

void intake_forward() {
    assembly.intake_motor.spin(fwd, 12, volt);
}

void stop_intake() {
    assembly.intake_motor.stop(brake);
}

void intake_reverse() {
    assembly.intake_motor.spin(fwd, -12, volt);
}

void clamp_goal() {
    assembly.long_piston.set(true);
    wait(.2, sec);
    mogo_constants();
}

void unclamp_goal() {
    assembly.long_piston.set(false);
    odom_constants();
}

void move_lift(int pos) {
    static bool lift_task_started = false;
    if (!lift_task_started) {
        assembly.init();
        lift_task_started = true;
    }
    assembly.lift_arm_position = pos;
}
