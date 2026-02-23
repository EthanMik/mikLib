#include "mikLib/Devices/tracker.h"
#include "mikLib/Drive/util.h"
#include <cstdlib>

using namespace mik;

tracker::tracker(int port) :
    port(port),
    expander(PORT0),
    rotation_tracker(port >= 0 ? port : PORT0),
    encoder_tracker(port < 0 ? to_triport(port) : to_triport(expander, PORT_A))
{
    is_three_wire = (port < 0);
};

tracker::tracker(int expander_port, int port) :
    port(port),
    expander(expander_port),
    rotation_tracker(PORT0),
    encoder_tracker(to_triport(expander, port))
{
    is_three_wire = true;
};

bool tracker::installed() {
    if (is_three_wire) {
        return true;
    } else {
        return rotation_tracker.installed();
    }
}

int tracker::index() {
    return port;
}
 
void tracker::resetPosition() {
    if (is_three_wire) {
        encoder_tracker.resetRotation();
    } else {
        rotation_tracker.resetPosition(); 
    }
}

float tracker::angle(vex::rotationUnits units) {
    if (is_three_wire) {
        return encoder_tracker.rotation(units);
    } else {
        return rotation_tracker.angle(units);
    }
}

void tracker::setPosition(float value, vex::rotationUnits units) {
    if (is_three_wire) {
        encoder_tracker.setPosition(value, units);
    } else {
        rotation_tracker.setPosition(value, units);
    }
}

float tracker::position(vex::rotationUnits units) {
    if (is_rev_encoder && units == vex::rotationUnits::deg) {
        return encoder_tracker.position(vex::rotationUnits::raw) * (360.0 / 8192.0);
    } else if (is_three_wire) {
        return encoder_tracker.position(units);
    } else {
        return rotation_tracker.position(units);
    }
}
