#include "mikLib/Devices/piston.h"
#include "mikLib/Drive/util.h"
#include "v5.h"

using namespace mik;

piston::piston(int triport) :
    expander_port_(PORT0), triport_port_(triport),
    triport_expander(PORT0), solenoid(to_triport(triport)), state_(false)
{};

piston::piston(int triport, bool state) :
    expander_port_(PORT0), triport_port_(triport),
    triport_expander(PORT0), solenoid(to_triport(triport)), state_(state)
{
    set(state);
};

piston::piston(int expander_port, int solenoid_port, bool state) :
    expander_port_(expander_port), triport_port_(solenoid_port),
    triport_expander(expander_port), solenoid(to_triport(triport_expander, solenoid_port)), state_(state)
{
    set(state);
};

int piston::triport_port() const { return triport_port_; }
int piston::expander_port() const { return expander_port_; }

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
