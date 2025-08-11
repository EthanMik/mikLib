#pragma once

#include "vex.h"

/** 
 * @file motors.h
 * @brief Wrapper for vex motor and motor group 
 */

namespace mik {

class motor : public vex::motor {

public:
    /**
     * @brief Creates a new motor object with a name on the port specified and sets the reversed flag.
     * @param port The port index for this motor. The index is zero-based.
     * @param reverse Sets the reverse flag for the new motor object.
     * @param name Sets the name for the motor
     */
    motor(int port, bool reversed, vex::gearSetting gear_cartridge, std::string name);

    motor(int port, bool reversed, std::string name);

    /** @return The port in PORT# format */
    const std::string port() const;
    /** @return True is motor is reversed */
    bool reversed() const;
    /** @return The gear cartidge used in mik::motor, default is 6 to 1 */
    vex::gearSetting gear_cartridge() const;
    /** @return The name given to mik::motor */
    std::string& name();
    /** @return The name given to mik::motor */
    const std::string name() const;

private:
    int port_;
    vex::gearSetting gear_cartridge_;
    bool reversed_;
    std::string name_;
};

class motor_group 
{
public:
    /** @brief Constructs an array of mik motors that can be controlled at the same time  */
    motor_group(const std::vector<mik::motor>& motors);

    /** 
     * @brief return the number of motors in the motor group
     * @return number of motors
     */
    int32_t count(void);

    /** 
     * @brief Sets the stopping mode of the motor group by passing a brake mode as a parameter.
     * @param mode The stopping mode can be set to coast, brake, or hold.  
     */
    void setStopping(vex::brakeType mode);

    /** 
     * @brief Sets the voltage of the motor group based on the parameters set in the command. This command will not run the motor. Any subsequent call that does not contain a specified motor voltage will use this value.
     * @param voltage Sets the amount of velocity.
     * @param units The measurement unit for the voltage value. 
     */
    void setVoltage(float voltage, vex::voltageUnits units);

    /** 
     * @brief Resets the motor's encoder to the value of zero. 
     */   
    void resetPosition(void);

    /** 
     * @brief Sets the value of all motor encoders to the value specified in the parameter.
     * @param value Sets the current position of the motor.
     * @param units The measurement unit for the position value.
     */
    void setPosition(float value, vex::rotationUnits units);

    /** 
     * @brief Sets the timeout for the motor group. If the motor group does not reach its' commanded position prior to the completion of the timeout, the motors will stop.
     * @param time Sets the amount of time.
     * @param units The measurement unit for the time value.
     */
    void setTimeout(int32_t time, vex::timeUnits units);

    /** 
     * @brief Turns the motors on, and spins them in the specified direction.
     * @param dir The direction to spin the motors.
     */
    void spin(vex::directionType dir);

    /**
     * @brief Turn on the motors and spins them in the specified direction and a specified voltage.
     * @param dir The direction to spin the motors. 
     * @param voltage Sets the amount of volts.
     * @param units The measurement unit for the voltage value. 
     */
    void spin(vex::directionType dir, float voltage, vex::voltageUnits units);

    /**
     * @brief Turn on the motors and spin them to a relative target rotation value at a specified velocity.
     * @return Returns a Boolean that signifies when the motor has reached the target rotation value.
     * @param rotation Sets the amount of rotation.
     * @param units The measurement unit for the rotation value.
     * @param voltage Sets the amount of velocity.
     * @param units_v The measurement unit for the velocity value.
     * @param waitForCompletion (Optional) If true, your program will wait until the motor reaches the target rotational value. If false, the program will continue after calling this function. By default, this parameter is true.
     */
    bool spinFor(float rotation, vex::rotationUnits units, float voltage, vex::voltageUnits units_v, bool waitForCompletion=true);

    bool spinFor(vex::directionType dir, float rotation, vex::rotationUnits units, float voltage, vex::voltageUnits units_v, bool waitForCompletion=true);

    /**
     * @brief Turn on the motors and spin them to a relative target rotation value.
     * @return Returns a Boolean that signifies when the motor has reached the target rotation value.
     * @param rotation Sets the amount of rotation.
     * @param units The measurement unit for the rotation value.        
     * @param waitForCompletion (Optional) If true, your program will wait until the motor reaches the target rotational value. If false, the program will continue after calling this function. By default, this parameter is true.
     */
    bool spinFor(float rotation, vex::rotationUnits units, bool waitForCompletion=true);

    bool spinFor(vex::directionType dir, float rotation, vex::rotationUnits units, bool waitForCompletion=true);

    /**
     * @brief Turn on the motors and spin them to a relative target time value at a specified velocity.
     * @param time Sets the amount of time.
     * @param units The measurement unit for the time value.
     * @param velocity Sets the amount of velocity.
     * @param units_v The measurement unit for the velocity value.       
     */
    void spinFor(float time, vex::timeUnits units, float voltage, vex::voltageUnits units_v, bool waitForCompletion=true);
    
    void spinFor(vex::directionType dir, float time, vex::timeUnits units, float voltage, vex::voltageUnits units_v, bool waitForCompletion=true);

    /** 
     * @brief Checks to see if any of the motors are rotating to a specific target.
     * @return Returns a true Boolean if the motor is on and is rotating to a target. Returns a false Boolean if the motor is done rotating to a target.
     */
    bool isSpinning(void);

    /** 
     * @brief Checks to see if all the motor are done rotating to a specific target.
     * @return Returns a false Boolean if the motor is on and is rotating to a target. Returns a true Boolean if the motor is done rotating to a target.
     */
    bool isDone(void);      

    /** 
     * @brief Stops all motors using the default brake mode.
     */
    void stop(void);

    /** 
     * @brief Stops all motors using a specified brake mode.
     * @param mode The brake mode can be set to coast, brake, or hold. 
     */
    void stop(vex::brakeType mode);

    /** 
     * @brief Sets the max torque of the motors.
     * @param value Sets the amount of torque.
     * @param units The measurement unit for the torque value.
     */
    void setMaxTorque(float value, vex::percentUnits units);

    /** 
     * @brief Sets the max torque of the motors.
     * @param value Sets the amount of torque.
     * @param units The measurement unit for the torque value.
     */
    void setMaxTorque(float value, vex::torqueUnits units);
    
    /** 
     * @brief Sets the max torque of the motors.
     * @param value Sets the amount of torque.
     * @param units The measurement unit for the torque value.
     */
    void setMaxTorque(float value, vex::currentUnits units);

    /** 
     * @brief Gets the current position of the first motor in the group's encoder.
     * @returns Returns a float that represents the current position of the motor in the units defined in the parameter.
     * @param units The measurement unit for the position.
     */
    float position(vex::rotationUnits units);
    
    /** 
     * @brief Gets the current voltage of the first motor in the group.
     * @return Returns a float that represents the current voltage of the motor in the units defined in the parameter.
     * @param units The measurement unit for the voltage.
     */
    float voltage(vex::voltageUnits units = vex::voltageUnits::volt);

    /** 
     * @brief Gets the current average voltage of the motors in the group.
     * @return Returns a float that represents the current voltage of the motor in the units defined in the parameter.
     * @param units The measurement unit for the voltage.
     */
    float averageVoltage(vex::voltageUnits units);

    /** 
     * @brief Gets the sum electrical current for all motors in the group.
     * @return Returns a float that represents the electrical current of the motors in the units defined in the parameter.
     * @param units The measurement unit for the current.
     */
    float current(vex::currentUnits units = vex::currentUnits::amp);
    
    /** 
     * @brief Gets the electrical current of the motors in percentage of maximum.
     * @return Returns a float that represents the electrical current of the motors as percentage of max current.
     * @param units The measurement unit for the current.
     */
    float current(vex::percentUnits units);
        
    /** 
     * @brief Gets the average electrical current for all motors in the group.
     * @return Returns a float that represents the electrical current of the motors in the units defined in the parameter.
     * @param units The measurement unit for the current.
     */
    float averageCurrent(vex::currentUnits units = vex::currentUnits::amp);

    /** 
     * @brief Gets the power of the first motor in the group.
     * @return Returns a float that represents the power of the motor in the units defined in the parameter.
     * @param units The measurement unit for the power.
     */
    float power(vex::powerUnits units = vex::powerUnits::watt);

    /** 
     * @brief Gets the average power of all motors in the group.
     * @return Returns a float that represents the power of the motor in the units defined in the parameter.
     * @param units The measurement unit for the power.
     */
    float averagePower(vex::powerUnits units = vex::powerUnits::watt);

    /** 
     * @brief Gets the torque of the first motor in the group.
     * @return Returns a float that represents the torque of the motor in the units defined in the parameter.
     * @param units The measurement unit for the torque.
     */
    float torque(vex::torqueUnits units = vex::torqueUnits::Nm);

    /** 
     * @brief Gets the average torque of the motors in the group.
     * @return Returns a float that represents the torque of the motor in the units defined in the parameter.
     * @param units The measurement unit for the torque.
     */
    float averageTorque(vex::torqueUnits units = vex::torqueUnits::Nm);

    /** 
     * @brief Gets the efficiency of the first motor in the group.
     * @return Returns the efficiency of the motor in the units defined in the parameter.
     * @param units (Optional) The measurement unit for the efficiency. By default, this parameter is a percentage.
     */
    float efficiency(vex::percentUnits units = vex::percentUnits::pct);

    /** 
     * @brief Gets the average efficiency of the motors in the group.
     * @return Returns the efficiency of the motor in the units defined in the parameter.
     * @param units (Optional) The measurement unit for the efficiency. By default, this parameter is a percentage.
     */
    float averageEfficiency(vex::percentUnits units = vex::percentUnits::pct);

    /** 
     * @brief Gets the temperature of the first motor in the group.
     * @return Returns the temperature of the motor in the units defined in the parameter.
     * @param units The measurement unit for the temperature.
     */
    float temperature(vex::percentUnits units = vex::percentUnits::pct);

    /** 
     * @brief Gets the temperature of the first motor in the group.
     * @return Returns the temperature of the motor in the units defined in the parameter.
     * @param units The measurement unit for the temperature.
     */
    float temperature(vex::temperatureUnits units);

    /** 
     * @brief Gets the average temperature of the motors in the group.
     * @return Returns the temperature of the motor in the units defined in the parameter.
     * @param units The measurement unit for the temperature.
     */
    float averageTemperature(vex::percentUnits units = vex::percentUnits::pct);

    /** 
     * @brief Gets the average temperature of the motors in the group.
     * @return Returns the temperature of the motor in the units defined in the parameter.
     * @param units The measurement unit for the temperature.
     */
    float averageTemperature(vex::temperatureUnits units);

    /** 
     * @return The wrapped vex motors in a vector
     */   
    std::vector<mik::motor>& getMotors();
    
    
private:
    float to_volt(float voltage, vex::voltageUnits velocityUnits);
    
    float set_voltage = 6; 

    std::vector<mik::motor> motors;
};
}