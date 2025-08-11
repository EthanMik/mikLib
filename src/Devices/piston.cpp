#include "vex.h"

using namespace mik;

piston::piston(int triport) :
    solenoid(to_triport(triport)), triport_expander(0), state_(false)
{};

piston::piston(int triport, bool state) :
    solenoid(to_triport(triport)), triport_expander(0), state_(state)
{
    set(state);
};

piston::piston(int expander_port, int solenoid_port, bool state) :
    solenoid(triport_expander.Port[solenoid_port]), triport_expander(expander_port), state_(state)
{
    set(state);
};


bool piston::state() const {
    return state_;
}

void piston::open() {
    state_ = true;
    solenoid.set(state_);
}

void piston::close() {
    state_ = false;
    solenoid.set(state_);
}

void piston::toggle() {
    state_ = !state_;
    solenoid.set(state_);
}

void piston::set(bool state) {
    state_ = state;
    solenoid.set(state_);
}
