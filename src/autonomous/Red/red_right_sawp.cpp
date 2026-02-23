#include "vex.h"

using namespace vex;
using namespace mik;

std::string red_right_sawp(bool calibrate, mik::auto_variation var, bool get_name) {
    if (get_name) { return "red right sawp"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);
        
        return "";
    }

    return "";
}