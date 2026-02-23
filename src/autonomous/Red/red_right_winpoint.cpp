#include "vex.h"

using namespace vex;
using namespace mik;

std::string red_right_winpoint(bool calibrate, mik::auto_variation var, bool get_name) { 
    if (get_name) { return "red right winpoint"; }
    if (calibrate) {
        chassis.set_coordinates(-40, 0, 90);
        
        return "";
    }
    
    return "";
}