#include "vex.h"

using namespace mik;

piston::piston(int triport) :
    solenoid(to_triport(triport)), state_(false)
{};

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
