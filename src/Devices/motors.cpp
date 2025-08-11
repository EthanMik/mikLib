#include "vex.h"

using namespace mik;

mik::motor::motor(int port, bool reversed, std::string name) :
    vex::motor(port, ratio6_1, reversed), port_(port), gear_cartridge_(ratio6_1), reversed_(reversed), name_(std::move(name))
{};

mik::motor::motor(int port, bool reversed, vex::gearSetting gear_cartridge, std::string name) :
    vex::motor(port, gear_cartridge, reversed), port_(port), gear_cartridge_(gear_cartridge), reversed_(reversed), name_(std::move(name))
{};

const std::string mik::motor::port() const { return "PORT" + to_string(port_ + 1); }
bool mik::motor::reversed() const { return reversed_; }
vex::gearSetting mik::motor::gear_cartridge() const { return gear_cartridge_; }
std::string& mik::motor::name() { return name_; }
const std::string mik::motor::name() const { return name_; }

mik::motor_group::motor_group(const std::vector<mik::motor>& motors) :
    motors(motors)
{};

int32_t mik::motor_group::count(void) {
    return motors.size();
}

void mik::motor_group::setStopping(vex::brakeType mode) {
    for (mik::motor& motor : motors) {
        motor.setStopping(mode);
    }    
}

void mik::motor_group::setVoltage(float voltage, vex::voltageUnits units) {
    set_voltage = to_volt(voltage, units);
    for (mik::motor& motor : motors) {
        motor.setVelocity(volt_to_percent(set_voltage), vex::velocityUnits::pct);
    }
}

void mik::motor_group::resetPosition(void) {
    for (mik::motor& motor : motors) {
        motor.resetPosition();
    }
}

void mik::motor_group::setPosition(float value, vex::rotationUnits units) {
    for (mik::motor& motor : motors) {
        motor.setPosition(value, units);
    }
}

void mik::motor_group::setTimeout(int32_t time, vex::timeUnits units) {
    for (mik::motor& motor : motors) {
        motor.setTimeout(time, units);
    }
}

void mik::motor_group::spin(vex::directionType dir) {
    for (mik::motor& motor : motors) {   
        motor.spin(dir, set_voltage, vex::voltageUnits::volt); 
    }
}

void mik::motor_group::spin(vex::directionType dir, float voltage, vex::voltageUnits units) {
    for (mik::motor& motor : motors) {
        motor.spin(dir, voltage, units);
    }
}

bool mik::motor_group::spinFor(float rotation, vex::rotationUnits units, float voltage, vex::voltageUnits units_v, bool waitForCompletion) {
    if (motors.empty()) { return 0; }
    float velocity = volt_to_percent(to_volt(voltage, units_v));
    size_t last_index = motors.size() - 1;
    for (size_t i = 0; i < last_index; ++i) {
        motors[i].spinFor(rotation, units, velocity, vex::velocityUnits::pct, false);
    }
    return motors[last_index].spinFor(rotation, units, velocity, vex::velocityUnits::pct, waitForCompletion);
}

bool mik::motor_group::spinFor(vex::directionType dir, float rotation, vex::rotationUnits units, float voltage, vex::voltageUnits units_v, bool waitForCompletion) {
    if (motors.empty()) { return 0; }
    float velocity = volt_to_percent(to_volt(voltage, units_v));
    size_t last_index = motors.size() - 1;
    for (size_t i = 0; i < last_index; ++i) {
        motors[i].spinFor(dir, rotation, units, velocity, vex::velocityUnits::pct, false);
    }
    return motors[last_index].spinFor(dir, rotation, units, velocity, vex::velocityUnits::pct, waitForCompletion);
}

bool mik::motor_group::spinFor(float rotation, vex::rotationUnits units, bool waitForCompletion) {
    if (motors.empty()) { return 0; }
    size_t last_index = motors.size() - 1;
    for (size_t i = 0; i < last_index; ++i) {
        motors[i].spinFor(rotation, units, false);
    }
    return motors[last_index].spinFor(rotation, units, waitForCompletion);
}

bool mik::motor_group::spinFor(vex::directionType dir, float rotation, vex::rotationUnits units, bool waitForCompletion) {
    if (motors.empty()) { return 0; }
    size_t last_index = motors.size() - 1;
    for (size_t i = 0; i < last_index; ++i) {
        motors[i].spinFor(dir, rotation, units, false);
    }
    return motors[last_index].spinFor(dir, rotation, units, waitForCompletion);
}

struct SpinCtx {
    mik::motor_group*   self;
    vex::directionType  dir;     
    float               time;
    vex::timeUnits      units;
    float               voltage;
    vex::voltageUnits   units_v;
};

void mik::motor_group::spinFor(float time, vex::timeUnits units, float voltage, vex::voltageUnits units_v, bool waitForCompletion) {
    if (motors.empty()) { return; }

    SpinCtx* ctx = new SpinCtx{this, vex::directionType::undefined, time, units, voltage, units_v};
    int (*spin)(void*) = [](void* raw){ 
        auto* ctx = static_cast<SpinCtx*>(raw);
        for (auto& motor : ctx->self->getMotors()) {
            motor.spin(vex::directionType::undefined, ctx->voltage, ctx->units_v);
        }
        wait(ctx->time, ctx->units);
        ctx->self->stop(vex::brakeType::hold);
        delete ctx;
        return 0;
    };
    if (waitForCompletion) {
        spin(ctx);
    } else {
        vex::task t(spin, ctx);
    }
}

void mik::motor_group::spinFor(vex::directionType dir, float time, vex::timeUnits units, float voltage, vex::voltageUnits units_v, bool waitForCompletion) {
    if (motors.empty()) { return; }

    SpinCtx* ctx = new SpinCtx{this, dir, time, units, voltage, units_v};
    int (*spin)(void*) = [](void* raw){ 
        auto* ctx = static_cast<SpinCtx*>(raw);
        for (auto& motor : ctx->self->getMotors()) {
            motor.spin(ctx->dir, ctx->voltage, ctx->units_v);
        }
        wait(ctx->time, ctx->units);
        ctx->self->stop(vex::brakeType::hold);
        delete ctx;
        return 0;
    };
    if (waitForCompletion) {
        spin(ctx);
    } else {
        vex::task t(spin, ctx);
    }
}

bool mik::motor_group::isSpinning(void) {
    bool spinning = false;
    for (auto& motor : motors) {
        if (motor.isSpinning()) {
            spinning = true;
        }
    }
    return spinning;
}

bool mik::motor_group::isDone(void) {
    bool done = true;
    for (auto& motor : motors) {
        if (!motor.isDone()) {
            done = false;
        }
    }
    return done;
}

void mik::motor_group::stop(void) {
    for (auto& motor : motors) {
        motor.stop();
    }
}

void mik::motor_group::stop(vex::brakeType mode) {
    for (auto& motor : motors) {
        motor.stop(mode);
    }
}

void mik::motor_group::setMaxTorque(float value, vex::percentUnits units) {
    for (auto& motor : motors) {
        motor.setMaxTorque(value, units);
    }
}

void mik::motor_group::setMaxTorque(float value, vex::torqueUnits units) {
    for (auto& motor : motors) {
        motor.setMaxTorque(value, units);
    }
}

void mik::motor_group::setMaxTorque(float value, vex::currentUnits units) {
    for (auto& motor : motors) {
        motor.setMaxTorque(value, units);
    }
}

float mik::motor_group::position(vex::rotationUnits units) {
    if (motors.empty()) { return 0; }
    return motors[0].position(units);
}

float mik::motor_group::voltage(vex::voltageUnits units) {
    if (motors.empty()) { return 0; }
    return motors[0].voltage(units);
}

float mik::motor_group::averageVoltage(vex::voltageUnits units) {
    float voltage = 0;
    for (mik::motor& motor : motors) {
        voltage += motor.voltage(units);
    }
    return voltage / motors.size();
}

float mik::motor_group::current(vex::currentUnits units) {
    float current = 0;
    for (mik::motor& motor : motors) {
        current += motor.current(units);
    }
    return current;
}

float mik::motor_group::current(vex::percentUnits units) {
    float current = 0;
    for (mik::motor& motor : motors) {
        current += motor.current(units);
    }
    return current / motors.size();
}

float mik::motor_group::averageCurrent(vex::currentUnits units) {
    float current = 0;
    for (mik::motor& motor : motors) {
        current += motor.current(units);
    }
    return current / motors.size();
}

float mik::motor_group::power(vex::powerUnits units) {
    if (motors.empty()) { return 0; }
    return motors[0].power(units);
}

float mik::motor_group::averagePower(vex::powerUnits units) {
    float power = 0;
    for (mik::motor& motor : motors) {
        power += motor.power(units);
    }
    return power / motors.size();
}

float mik::motor_group::torque(vex::torqueUnits units) {
    if (motors.empty()) { return 0; }
    return motors[0].torque(units);
}

float mik::motor_group::averageTorque(vex::torqueUnits units) {
    float torque = 0;
    for (mik::motor& motor : motors) {
        torque += motor.torque(units);
    }
    return torque / motors.size();
}

float mik::motor_group::efficiency(vex::percentUnits units) {
    if (motors.empty()) { return 0; }
    return motors[0].efficiency(units);
}

float mik::motor_group::averageEfficiency(vex::percentUnits units) {
    float eff = 0;
    for (mik::motor& motor : motors) {
        eff += motor.efficiency(units);
    }
    return eff / motors.size();
}

float mik::motor_group::temperature(vex::percentUnits units) {
    if (motors.empty()) { return 0; }
    return motors[0].temperature(units);
}

float mik::motor_group::temperature(vex::temperatureUnits units) {
    if (motors.empty()) { return 0; }
    return motors[0].temperature(units);
}

float mik::motor_group::averageTemperature(vex::percentUnits units) {
    float temp = 0;
    for (mik::motor& motor : motors) {
        temp += motor.temperature(units);
    }
    return temp / motors.size();
}

float mik::motor_group::averageTemperature(vex::temperatureUnits units) {
    float temp = 0;
    for (mik::motor& motor : motors) {
        temp += motor.temperature(units);
    }
    return temp / motors.size();
}

float mik::motor_group::to_volt(float voltage, vex::voltageUnits velocityUnits) {
    switch (velocityUnits)
    {
    case vex::voltageUnits::mV:
        return voltage / 1000.0f;
    default:
        return voltage;
    }
}

std::vector<mik::motor>& mik::motor_group::getMotors() {
    return motors;
}