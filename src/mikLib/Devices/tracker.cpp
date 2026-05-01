#include "mikLib/Devices/tracker.h"
#include "mikLib/Drive/util.h"
#include <cstdlib>

using namespace mik;

tracker::tracker(int port) :
    port(port),
    expander(PORT0),
    rotation_tracker(port >= 0 ? port : PORT0),
    encoder_tracker(port < 0 ? new vex::encoder(to_triport(port)) : nullptr)
{};

tracker::tracker(int expander_port, int port) :
    port(port),
    expander(expander_port),
    rotation_tracker(PORT0),
    encoder_tracker(new vex::encoder(to_triport(expander, port)))
{};

bool tracker::installed() {
    if (encoder_tracker) {
        return true;
    } else {
        return rotation_tracker.installed();
    }
}

int tracker::index() {
    return port;
}

void tracker::resetPosition() {
    if (encoder_tracker) {
        encoder_tracker->resetRotation();
    } else {
        rotation_tracker.resetPosition();
    }
}

float tracker::angle(vex::rotationUnits units) {
    if (encoder_tracker) {
        return encoder_tracker->rotation(units);
    } else {
        return rotation_tracker.angle(units);
    }
}

void tracker::setPosition(float value, vex::rotationUnits units) {
    if (encoder_tracker) {
        encoder_tracker->setPosition(value, units);
    } else {
        rotation_tracker.setPosition(value, units);
    }
}

float tracker::position(vex::rotationUnits units) {
    if (is_rev_encoder && units == vex::rotationUnits::deg && encoder_tracker) {
        return encoder_tracker->position(vex::rotationUnits::raw) * (360.0 / 8192.0);
    } else if (encoder_tracker) {
        return encoder_tracker->position(units);
    } else {
        return rotation_tracker.position(units);
    }
}
