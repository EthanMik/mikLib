#include "vex.h"

using namespace vex;
using namespace mik;

void intake_forward() {
    assembly.lower_intake_motors.spin(fwd, 12, volt);
}

void stop_intake() {
    assembly.lower_intake_motors.stop(brake);
}

void intake_reverse() {
    assembly.lower_intake_motors.spin(fwd, -12, volt);
}
