#ifndef MOTORS_H
#define MOTORS_H

#include "vex.h"

// Enum for different velocity units
enum class velocity_units {normalized, percent, volt};

namespace hzn {

class motor  {
    
public:
    motor(int port, bool reversed, std::string name);

    int port;
    bool reversed;
    std::string name;
    vex::motor mtr;
};

// Class to manage a group of three motors, similar to VEX motor group but with extended functionality
class motor_group 
{
public:
    // Constructor: initializes a variable amount of motor
    motor_group(const std::vector<hzn::motor>& motor_constructor);

    // Spins the motors in the specified direction and speed
    void spin(vex::directionType direction, float speed, velocity_units velocityUnits);

    // Spins the motors for a specified time
    void spin_for_time(vex::directionType direction, int speed, velocity_units velocityUnits, float time, vex::timeUnits timeUnits = vex::timeUnits::sec);
   
    // Changes the robots velocity in the opposite direction
    void flip_direction();

    // Sets the position of the motor encoders
    void set_position(float position, vex::rotationUnits rotationUnits);

    // Gets the combined position of all three motors
    float get_position(vex::rotationUnits rotationUnits);

    // Stops the motors with the specified brake type
    void stop(vex::brakeType brake = vex::brakeType::brake);

    // Returns the last set speed in the specified units
    float get_set_speed(velocity_units velocityUnits);

    float setSpeed;  // Stores the last set speed
    
    std::vector<hzn::motor> motor_constructor;
    
    std::vector<vex::motor> motors;
    
private:
    // Converts speed from various units to voltage
    float to_volt(float speed, velocity_units velocityUnits);

    // Converts voltage to the specified velocity units
    float from_volt(float volt, velocity_units velocityUnits);
};
}

#endif