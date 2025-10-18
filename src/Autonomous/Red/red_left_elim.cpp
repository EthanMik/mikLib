#include "vex.h"

using namespace vex;
using namespace mik;

std::string red_left_elim(bool calibrate, mik::auto_variation var, bool get_name) { 
    if (get_name) { return "red left elim"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);
        
        return "";
    }
    
    return "";
}